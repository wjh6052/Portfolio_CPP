#include "CPlayer.h"
#include "../Global.h"

#include "../Datas/DataAsset/CharacterDataAsset.h"
#include "Components/SkeletalMeshComponent.h"


ACPlayer::ACPlayer()
{
	
	//Create Actor Component
	FlightComponent = CreateDefaultSubobject<UCFlightComponent>(L"FlightComponent");

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	CharacterType = ECharacterType::Player;
	GetStatComponent()->SetSpeed(ESpeedType::Joging);
	
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACPlayer::OnWalk);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);
	
}

void ACPlayer::OnMoveForward(float InAxis)
{	

	if(GetStatComponent()->IsStatus(EStatusType::Flight) && GetFlightComponent()->GetSprint())
		GetFlightComponent()->OnMoveForward_Flight(1);

	Super::OnMoveForward(InAxis);


	if (InAxis == 0.f)
	{
		if(GetStatComponent()->IsSpeedType(ESpeedType::Run))
		{
			GetStatComponent()->SetSpeed(ESpeedType::Joging);
		}
	}
	
		


	switch (GetStatComponent()->GetStatusType())
	{

	case EStatusType::Flight:
		GetFlightComponent()->OnMoveForward_Flight(InAxis);
		break;

	case EStatusType::Climbing:
		break;

	case EStatusType::Swimming:
		break;

	case EStatusType::Melee:
		break;


	default:
		OnMoveForward_Unarmed(InAxis);
		break;
	}
}

void ACPlayer::OnMoveRight(float InAxis)
{
	Super::OnMoveRight(InAxis);


	switch (GetStatComponent()->GetStatusType())
	{

	case EStatusType::Flight: 
		GetFlightComponent()->OnMoveRight_Flight(InAxis);
		break;

	case EStatusType::Climbing:
		break;

	case EStatusType::Swimming:
		break;

	case EStatusType::Melee:
		break;


	default:
		OnMoveRight_Unarmed(InAxis);
		break;
	}
}


void ACPlayer::OnJump()
{
	switch (GetStatComponent()->GetStateType())
	{

	case EStateType::Idling:
		break;

	default:
		return;
		break;
	}

	switch (GetStatComponent()->GetStatusType())
	{

	case EStatusType::Unarmed:
		if(IsMovementMode(EMovementMode::MOVE_Falling))
		{
			if (GetStatComponent()->IsStatus(EStatusType::Unarmed))
				GetFlightComponent()->StartFlight();
		}
		Super::OnJump();
		break;

	case EStatusType::Flight:
		GetFlightComponent()->EndFlight();
		break;

	case EStatusType::Climbing:
		break;

	case EStatusType::Swimming:
		break;

	case EStatusType::Melee:
		break;


	default:
		break;
	}
}

void ACPlayer::OffJump()
{
	Super::OffJump();

}

void ACPlayer::OnWalk()
{
	switch (GetStatComponent()->GetSpeedType())
	{
	case ESpeedType::Walk:
		GetStatComponent()->SetSpeed(ESpeedType::Joging);
		break;

	default:
		GetStatComponent()->SetSpeed(ESpeedType::Walk);
		break;
	}

}

void ACPlayer::OnRun()
{
	++Run;

	if (Run >= 2)
	{
		GetStatComponent()->SetSpeed(ESpeedType::Run);
		Run = 0;
	}
}

void ACPlayer::OffRun()
{
	GetWorld()->GetTimerManager().SetTimer(RunTimer, this, &ACPlayer::RunDelay, 0.25f, false);
}

void ACPlayer::RunDelay()
{
	Run = 0;
}

void ACPlayer::OnSprint()
{
	GetStatComponent()->SetSprint(true);

	if (GetStatComponent()->IsStatus(EStatusType::Flight))
	{
		GetFlightComponent()->SetSprint(GetStatComponent()->GetSprint());

		
		return;
	}

	CheckFalse(GetStatComponent()->IsState(EStateType::Idling));


	CheckNull(GetStatComponent()->GetCharacterDataAsset());
	PlayAnimMontage(GetStatComponent()->GetCharacterDataAsset()->RollAnimMontage.AnimMontage, GetStatComponent()->GetCharacterDataAsset()->RollAnimMontage.PlayRate);
}

void ACPlayer::OffSprint()
{
	GetStatComponent()->SetSprint(false);

	if (GetStatComponent()->IsStatus(EStatusType::Flight) && GetFlightComponent()->GetSprint())
	{
		GetFlightComponent()->SetSprint(GetStatComponent()->GetSprint());

		return;
	}
	CheckFalse(GetStatComponent()->IsStatus(EStatusType::Flight));

}



