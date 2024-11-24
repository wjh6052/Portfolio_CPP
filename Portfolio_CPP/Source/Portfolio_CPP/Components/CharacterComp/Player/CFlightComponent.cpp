#include "CFlightComponent.h"
#include "../../../Global.h"
#include "../../../Character/CPlayer.h"
#include "../../../Datas/DataAsset/BaseDataAsset.h"
#include "../../../Datas/DataAsset/CFlightDataAsset.h"


#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h" 
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


	if (GetFlightDataAsset() != nullptr)
	{
		Flight_Trail_Ref = UNiagaraFunctionLibrary::SpawnSystemAttached
		(
			GetFlightDataAsset()->Flight_Trail,
			OwnerPlayer->GetMesh(),
			TEXT("pelvis"),
			GetFlightDataAsset()->Flight_Trail_Location,
			GetFlightDataAsset()->Flight_Trail_Rotation,
			FVector(0, 0, 0),
			EAttachLocation::Type::KeepRelativeOffset,
			true,
			ENCPoolMethod::None,
			true,
			false
		);
		Flight_Wave_Ref = UNiagaraFunctionLibrary::SpawnSystemAttached
		(
			GetFlightDataAsset()->Flight_Wave,
			OwnerPlayer->GetRootComponent(),
			TEXT(""),
			GetFlightDataAsset()->Flight_Wave_Location,
			GetFlightDataAsset()->Flight_Wave_Rotation,
			FVector(1, 1, 1),
			EAttachLocation::Type::KeepRelativeOffset,
			true,
			ENCPoolMethod::None,
			true,
			false
		);

		for (int i = 0; i < GetFlightDataAsset()->FlightUnderDust_Impact.Num(); i++)
		{
			Under_Dust_Ref.Add(UNiagaraFunctionLibrary::SpawnSystemAttached
			(
				GetFlightDataAsset()->FlightUnderDust_Impact[i],
				OwnerPlayer->GetRootComponent(),
				TEXT(""),
				FVector(0.f, 0.f, -150.f),
				FRotator().ZeroRotator,
				FVector(1,1,1),
				EAttachLocation::Type::KeepRelativeOffset,
				false,
				ENCPoolMethod::None,
				false,
				true
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


	// Sprint때 바닥과 상호작용하여 먼지를 일으킴
	if (Flight_bSprint && GetFlightDataAsset()->bOnFlightUnderDust)
	{
		Sprint_FlightUnderDust();
	}
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
		OwnerPlayer->GetCharacterMovement()->BrakingDecelerationFlying = GetFlightDataAsset()->FlightSetting.BrakingDeceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = GetFlightDataAsset()->FlightSetting.RotationRate;
	}
	else
	{
		OwnerPlayer->GetCharacterMovement()->BrakingDecelerationFlying = OwnerPlayer->GetStatComponent()->GetCharacterDataAsset()->Speed.BrakingDeceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = OwnerPlayer->GetStatComponent()->GetCharacterDataAsset()->Speed.RotationRate;
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
	StopToPlayAnim(&GetFlightDataAsset()->Hover_Start);
	
	
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
		OwnerPlayer->GetCharacterMovement()->MaxWalkSpeed = GetFlightDataAsset()->FlightSetting_Sprint.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxFlySpeed = GetFlightDataAsset()->FlightSetting_Sprint.FlySpeed;
		OwnerPlayer->GetCharacterMovement()->MaxAcceleration = GetFlightDataAsset()->FlightSetting_Sprint.MaxAcceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = GetFlightDataAsset()->FlightSetting_Sprint.RotationRate;
		
		SetActiveComponent(Flight_Wave_Ref, input, input);	

		CheckFalse(Flight_bFlying);
		StopToPlayAnim(&GetFlightDataAsset()->FastMove_Start);
	}
	else
	{
		OwnerPlayer->GetCharacterMovement()->MaxWalkSpeed = OwnerPlayer->GetStatComponent()->GetCharacterDataAsset()->Speed.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxFlySpeed = OwnerPlayer->GetStatComponent()->GetCharacterDataAsset()->Speed.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxAcceleration = OwnerPlayer->GetStatComponent()->GetCharacterDataAsset()->Speed.MaxAcceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = OwnerPlayer->GetStatComponent()->GetCharacterDataAsset()->Speed.RotationRate;

		SetActiveComponent(Flight_Wave_Ref, input, input);



		
		

		if (Flight_bLanding)
		{
			StopToPlayAnim(&GetFlightDataAsset()->Landing);
			Flight_bLanding = false;
			return;
		}
		else if(Flight_bFlying)
		{
			StopToPlayAnim(&GetFlightDataAsset()->Hover_Start);
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

int UCFlightComponent::GetSurfaceType(EPhysicalSurface SurfaceType)
{
	switch (SurfaceType)
	{
	case SurfaceType_Default:
		return 0;
		break;
	case SurfaceType1:
		return 1;
		break;
	case SurfaceType2:
		return 2;
		break;
	case SurfaceType3:
		return 3;
		break;
	case SurfaceType4:
		return 4;
		break;
	default:
		return 0;
		break;
	}

	return 0;
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

		
		//카메라 이동
		OwnerPlayer->GetController()->SetControlRotation(FRotator(0.f, OwnerPlayer->GetControlRotation().Yaw, OwnerPlayer->GetControlRotation().Roll));
	}
	else
	{
		CheckTrue(HitReset_False);
		HitReset_False = true;



		EndFlight();
		Flight_bLanding = true;
		//SetSprint(false);

		
	}
}



//-------------------------------Sprint_FlightUnderDust------------------------------------
void UCFlightComponent::Sprint_FlightUnderDust()
{
	FHitResult hitResult;

	if (NotifiLineTracetoUpVector(GetFlightDataAsset()->FlightUnderDustLength, hitResult))
	{
		FVector velocity_Normalize = OwnerPlayer->GetVelocity();
		UKismetMathLibrary::Vector_Normalize(velocity_Normalize, 0.0001f);

		
		FRotator hitImpactNormal = FRotator(
			UKismetMathLibrary::MakeRotFromZX(hitResult.ImpactPoint, OwnerPlayer->GetActorForwardVector()).Pitch,
			UKismetMathLibrary::Conv_VectorToRotator(velocity_Normalize).Yaw,
			UKismetMathLibrary::MakeRotFromZX(hitResult.ImpactPoint, OwnerPlayer->GetActorForwardVector()).Roll
		);



		CheckNull(GetDustVFX(hitResult.PhysMaterial->SurfaceType));
		
		FHitResult SweepHitResult;
		GetDustVFX(hitResult.PhysMaterial->SurfaceType)->K2_SetWorldLocationAndRotation(hitResult.ImpactPoint, hitImpactNormal, false, SweepHitResult, true);

		GetDustVFX(hitResult.PhysMaterial->SurfaceType)->SetActive(true, true);

	}

	
}

UNiagaraComponent* UCFlightComponent::GetDustVFX(EPhysicalSurface SurfaceType)
{
	
	if (Under_Dust_Ref[GetSurfaceType(SurfaceType)] != nullptr)
		return Under_Dust_Ref[GetSurfaceType(SurfaceType)];

	return nullptr;
}






//-----------------------------------------Notifi-----------------------------------------

bool UCFlightComponent::NotifiLineTracetoUpVector(float vectorLength, FHitResult& hitResult)
{
	if (OwnerPlayer == nullptr)
		return false;
	FVector start = OwnerPlayer->GetActorLocation();
	FVector end = (OwnerPlayer->GetActorUpVector() * vectorLength) + start;
	TArray<AActor*> ignores;
	ignores.Add(OwnerPlayer);
	bool bRetrunValue = UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
		false,
		ignores,
		EDrawDebugTrace::None,
		hitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.f
	);
	return bRetrunValue;
}

UNiagaraSystem* UCFlightComponent::GetLandingVFX(EPhysicalSurface SurfaceType)
{
	
	if(GetFlightDataAsset()->Landing_Impact[GetSurfaceType(SurfaceType)] != nullptr)
		return GetFlightDataAsset()->Landing_Impact[GetSurfaceType(SurfaceType)];


	return nullptr;
}

UNiagaraComponent* UCFlightComponent::SpawnNiagaraAtLocationOrAttach(bool isAttach, UNiagaraSystem* SystemTemplate, USceneComponent* AttachToComponent, FVector Location, FRotator Rotation)
{
	if (isAttach)
	{
		return UNiagaraFunctionLibrary::SpawnSystemAttached(SystemTemplate, AttachToComponent, L"", Location, Rotation, EAttachLocation::KeepRelativeOffset, true, true);
	}
	else
	{
		return UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SystemTemplate, Location, Rotation, FVector(1.f, 1.f, 1.f));
	}
}
