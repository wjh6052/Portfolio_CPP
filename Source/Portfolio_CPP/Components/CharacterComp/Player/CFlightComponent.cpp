#include "CFlightComponent.h"
#include "../../../Global.h"
#include "../../../Character/CPlayer.h"
#include "../../../Datas/DataAsset/BaseDataAsset.h"
#include "../../../Datas/DataAsset/CFlightDataAsset.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"



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
	
	if (WingsClass != nullptr)
	{
		FActorSpawnParameters wingsOwner; 
		wingsOwner.Owner = Cast<AActor>(OwnerPlayer);
		Wings = GetWorld()->SpawnActor<ACWings>(WingsClass, FVector::ZeroVector, FRotator::ZeroRotator, wingsOwner);
		Wings->SetActorHiddenInGame(true);
		Wings->AttachTo(L"Wings");
	}

}


void UCFlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
		OwnerPlayer->GetCharacterMovement()->BrakingDecelerationFlying = FlightSetting.BrakingDeceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = FlightSetting.RotationRate;
	}
	else
	{
		OwnerPlayer->GetCharacterMovement()->BrakingDecelerationFlying = OwnerPlayer->StatComponent->Speed.BrakingDeceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = OwnerPlayer->StatComponent->Speed.RotationRate;
	}
}

void UCFlightComponent::StartFlight()
{
	bFlying = true;
	OwnerPlayer->StatComponent->SetStatusType(EStatusType::Flight);

	SetFlying(bFlying);
	SetFlightMovementParam(bFlying);
	Wings->SpawnWings(bFlying);


	StopToPlayAnim(&FlightDataAsset->Hover_Start);
	OwnerPlayer->GetCharacterMovement()->bOrientRotationToMovement = bFlying;
	Wings->HitReset();
}

void UCFlightComponent::EndFlight()
{
	bFlying = false;
	OwnerPlayer->OffSprint();
	OwnerPlayer->StatComponent->SetStatusType(EStatusType::Unarmed);

	SetFlying(bFlying);
	SetFlightMovementParam(bFlying);
	Wings->HitReset();
	Wings->SpawnWings(bFlying);

	SetSprint(bFlying);
}

void UCFlightComponent::SetSprint(bool input)
{
	bool bMainSprint = input;

	CheckFalse(CheckMovementMode(EMovementMode::MOVE_Falling) || CheckMovementMode(EMovementMode::MOVE_Flying));
	OwnerPlayer->GetCharacterMovement()->bUseControllerDesiredRotation = input;
	OwnerPlayer->GetCharacterMovement()->bOrientRotationToMovement = !input;

	bSprint = input;

	if (input)
	{
		OwnerPlayer->GetCharacterMovement()->MaxWalkSpeed = FlightSetting_Sprint.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxFlySpeed = FlightSetting_Sprint.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxAcceleration = FlightSetting_Sprint.MaxAcceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = FlightSetting_Sprint.RotationRate;
		
		SetActiveComponent(Flight_Wave_Ref, input, input);
		Wings->SetSprint(input);

		StopToPlayAnim(&FlightDataAsset->FastMove_Start);
	}
	else
	{
		OwnerPlayer->GetCharacterMovement()->MaxWalkSpeed = OwnerPlayer->StatComponent->Speed.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxFlySpeed = OwnerPlayer->StatComponent->Speed.FlyWarkSpeed;
		OwnerPlayer->GetCharacterMovement()->MaxAcceleration = OwnerPlayer->StatComponent->Speed.MaxAcceleration;
		OwnerPlayer->GetCharacterMovement()->RotationRate = OwnerPlayer->StatComponent->Speed.RotationRate;

		SetActiveComponent(Flight_Wave_Ref, input, input);

		Wings->SetSprint(input);

		CheckFalse(bMainSprint);
		if (bLanding)
		{
			StopToPlayAnim(&FlightDataAsset->Landing);
			bLanding = true;
		}
		else
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






