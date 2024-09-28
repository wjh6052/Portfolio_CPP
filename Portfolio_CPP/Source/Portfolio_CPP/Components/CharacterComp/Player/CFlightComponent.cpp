#include "CFlightComponent.h"
#include "../../../Global.h"
#include "../../../Character/CPlayer.h"
#include "../../../Datas/DataAsset/BaseDataAsset.h"
#include "../../../Datas/DataAsset/CFlightDataAsset.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"



UCFlightComponent::UCFlightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCFlightComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<ACPlayer>(GetOwner());
	CheckNull(OwnerPlayer);


	if (FlightDataAsset != nullptr)
	{
		Flight_Trail_Ref = UNiagaraFunctionLibrary::SpawnSystemAttached
		(
			FlightDataAsset->Flight_Trail,
			OwnerPlayer->GetMesh(),
			TEXT("pelvis"),
			FlightDataAsset->Flight_Trail_Location,
			FlightDataAsset->Flight_Trail_Rotation,
			FVector(0, 0, 0),
			EAttachLocation::Type::KeepRelativeOffset,
			true,
			ENCPoolMethod::None,
			true,
			false
		);
		Flight_Wave_Ref = UNiagaraFunctionLibrary::SpawnSystemAttached
		(
			FlightDataAsset->Flight_Wave,
			OwnerPlayer->GetRootComponent(),
			TEXT(""),
			FlightDataAsset->Flight_Wave_Location,
			FlightDataAsset->Flight_Wave_Rotation,
			FVector(0, 0, 0),
			EAttachLocation::Type::KeepRelativeOffset,
			true,
			ENCPoolMethod::None,
			true,
			false
		);

		for (int i = 0; i < FlightDataAsset->FlightUnderDust.Num(); i++)
		{
			Under_Dust_Ref.Add(UNiagaraFunctionLibrary::SpawnSystemAttached
			(
				FlightDataAsset->FlightUnderDust[i],
				OwnerPlayer->GetRootComponent(),
				TEXT(""),
				FVector(0.f, 0.f, -150.f),
				FRotator().ZeroRotator,
				FVector(0,0,0),
				EAttachLocation::Type::KeepRelativeOffset,
				true,
				ENCPoolMethod::None,
				true,
				false
			));
		}
	}
	

	
	OwnerPlayer->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &UCFlightComponent::OnHit);


	CheckNull(WingsClass);	
	FActorSpawnParameters wingsOwner;
	wingsOwner.Owner = Cast<AActor>(OwnerPlayer);
	Wings = GetWorld()->SpawnActor<ACWings>(WingsClass, FVector::ZeroVector, FRotator::ZeroRotator, wingsOwner);
	Wings->SetActorHiddenInGame(true);
	Wings->AttachTo(L"Wings");
		

}


void UCFlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	LookAtLocation = UKismetMathLibrary::VInterpTo(
		LookAtLocation,
		OwnerPlayer->GetActorLocation() + (OwnerPlayer->GetActorForwardVector() * 5000.f) + FVector(0.f, 0.f, -2000.f),
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		10.f
		);

}

void UCFlightComponent::OnMoveForward_Flight(float InAxis)
{
	FVector controlRotation = OwnerPlayer->GetControlRotation().Vector();


	float direction_z = 0.f;
	direction_z += (-0.1f > controlRotation.Z && controlRotation.Z > -1.0) ? controlRotation.Z : 0;
	direction_z += (1.0f > controlRotation.Z && controlRotation.Z > 0.1f) ? controlRotation.Z : 0;

	FVector direction = FVector(controlRotation.X, controlRotation.Y, direction_z);

	OwnerPlayer->AddMovementInput(direction, InAxis);
}

void UCFlightComponent::OnMoveRight_Flight(float InAxis)
{
	CheckTrue(OwnerPlayer->GetStatComponent()->GetSprint());


	FVector direction = UKismetMathLibrary::GetRightVector(FRotator(0, OwnerPlayer->GetControlRotation().Yaw, 0));
	CheckTrue(OwnerPlayer->IsMovementMode(EMovementMode::MOVE_Falling));
	OwnerPlayer->AddMovementInput(direction, InAxis);
}

void UCFlightComponent::SetFlying(bool input)
{
	if (input)
	{		
		OwnerPlayer->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}
	else
	{	
		OwnerPlayer->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	}
}

void UCFlightComponent::SetFlightMovementParam(bool input)
{
	if (input)
	{
		OwnerPlayer->GetCharacterMovement()->BrakingDecelerationFlying = FlightDataAsset->FlightSetting.BrakingDeceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = FlightDataAsset->FlightSetting.RotationRate;
	}
	else
	{
		OwnerPlayer->GetCharacterMovement()->BrakingDecelerationFlying = OwnerPlayer->GetStatComponent()->Speed.BrakingDeceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = OwnerPlayer->GetStatComponent()->Speed.RotationRate;
	}
}

void UCFlightComponent::StartFlight()
{
	Flight_bFlying = true;
	OwnerPlayer->GetStatComponent()->SetStatusType(EStatusType::Flight);

	SetFlying(Flight_bFlying);
	SetFlightMovementParam(Flight_bFlying);

	if (Wings != nullptr)
	{
		Wings->SpawnWings(Flight_bFlying);	
	}


	OwnerPlayer->GetCharacterMovement()->bOrientRotationToMovement = true;
	StopToPlayAnim(&FlightDataAsset->Hover_Start);
	
	
	HitReset();

}

void UCFlightComponent::EndFlight()
{
	CheckTrue(Flight_bSprint); // Spawn중 날라감 방지

	Flight_bFlying = false;
	OwnerPlayer->OffSprint();
	OwnerPlayer->GetStatComponent()->SetStatusType(EStatusType::Unarmed);

	SetFlying(Flight_bFlying);
	SetFlightMovementParam(Flight_bFlying);

	HitReset(); 


	if (Wings != nullptr)
	{
		Wings->SpawnWings(Flight_bFlying);
	
	}
		

	SetSprint(Flight_bFlying); // Sprint 속도 되돌리기



	switch (OwnerPlayer->GetStatComponent()->GetSpeedType()) // 이동 속도 되돌리기
	{
	case ESpeedType::Joging:
		OwnerPlayer->GetStatComponent()->SetSpeed(ESpeedType::Joging);
		break;

	case ESpeedType::Walk:
		OwnerPlayer->GetStatComponent()->SetSpeed(ESpeedType::Walk);
		break;
	}
}

void UCFlightComponent::SetSprint(bool input)
{

	CheckFalse(CheckMovementMode(EMovementMode::MOVE_Falling) || CheckMovementMode(EMovementMode::MOVE_Flying));
	
	Flight_bSprint = input;


	OwnerPlayer->GetCharacterMovement()->bUseControllerDesiredRotation = input;
	OwnerPlayer->GetCharacterMovement()->bOrientRotationToMovement = !input;

	if(Wings != nullptr)
		Wings->SetSprint(input);

	if (input)
	{
		OwnerPlayer->GetCharacterMovement()->MaxWalkSpeed = FlightDataAsset->FlightSetting_Sprint.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxFlySpeed = FlightDataAsset->FlightSetting_Sprint.FlySpeed;
		OwnerPlayer->GetCharacterMovement()->MaxAcceleration = FlightDataAsset->FlightSetting_Sprint.MaxAcceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = FlightDataAsset->FlightSetting_Sprint.RotationRate;
		
		SetActiveComponent(Flight_Wave_Ref, input, input);	

		CheckFalse(Flight_bFlying);
		StopToPlayAnim(&FlightDataAsset->FastMove_Start);
	}
	else
	{
		OwnerPlayer->GetCharacterMovement()->MaxWalkSpeed = OwnerPlayer->GetStatComponent()->Speed.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxFlySpeed = OwnerPlayer->GetStatComponent()->Speed.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxAcceleration = OwnerPlayer->GetStatComponent()->Speed.MaxAcceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = OwnerPlayer->GetStatComponent()->Speed.RotationRate;

		SetActiveComponent(Flight_Wave_Ref, input, input);


		CheckFalse(Flight_bFlying);
		if (Flight_bLanding)
		{
			StopToPlayAnim(&FlightDataAsset->Landing);
			Flight_bLanding = false;
			return;
		}
		else if(Flight_bFlying)
		{
			StopToPlayAnim(&FlightDataAsset->Hover_Start);
		}

	}
		

	
}

bool UCFlightComponent::CheckMovementMode(EMovementMode input)
{	
	return OwnerPlayer->GetCharacterMovement()->MovementMode == input ? true : false;
}

void UCFlightComponent::StopToPlayAnim(struct FAnimMontageBase* inAnimMontage)
{
	CheckNull(inAnimMontage);
	OwnerPlayer->StopAnimMontage();

	OwnerPlayer->PlayAnimMontage(inAnimMontage->AnimMontage, inAnimMontage->PlayRate);
}

void UCFlightComponent::SetActiveComponent(UActorComponent* Component, bool bNewActive, bool bReset)
{
	CheckNull(Component);

	Component->SetActive(bNewActive, bReset);

}



void UCFlightComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	CheckFalse(Flight_bFlying);
	
	

	if (UKismetMathLibrary::InRange_FloatFloat(UKismetMathLibrary::NormalizeToRange(OwnerPlayer->GetControlRotation().Pitch, 270.f, 360.f), 0.f, 0.7f))
	{
		if (Hit.ImpactNormal.Z > 0.7f)
		{
			if (Flight_bSprint)
			{
				if (UKismetMathLibrary::NormalizeToRange(OwnerPlayer->GetControlRotation().Pitch, 270.f, 360.f) < 0.65f)
				{
					HitEvent(true);
				}
				else
				{
					HitEvent(false);
				}
			}
			else
			{
				HitEvent(false);
			}
		}
		else
		{
			SetSprint(false);
		}
	}
	else
	{
		CheckFalse(Flight_bSprint);

		CheckTrue(Hit.ImpactNormal.Z > 0.7f);

		SetSprint(false);
		
	}
	



}

void UCFlightComponent::HitEvent(bool input)
{
	if (input)
	{
		CheckTrue(HitReset_True);
		HitReset_True = true;

		Flight_bLanding = true;
		SetSprint(false);
		EndFlight();

		//StopToPlayAnim(&FlightDataAsset->Landing);

		
		OwnerPlayer->GetController()->SetControlRotation(FRotator(0.f, OwnerPlayer->GetControlRotation().Yaw, OwnerPlayer->GetControlRotation().Roll));
	}
	else
	{
		CheckTrue(HitReset_False);
		HitReset_False = true;



		Flight_bLanding = true;
		SetSprint(false);
		EndFlight();

		OwnerPlayer->GetController()->SetControlRotation(FRotator(0.f, OwnerPlayer->GetControlRotation().Yaw, OwnerPlayer->GetControlRotation().Roll));
	}
}




