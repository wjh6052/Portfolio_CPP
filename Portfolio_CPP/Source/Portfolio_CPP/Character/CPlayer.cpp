#include "CPlayer.h"
#include "../Global.h"
#include "../Datas/DataAsset/CActionDataAsset.h"
#include "../Components/CharacterComp/Player/CFlightComponent.h"


ACPlayer::ACPlayer()
{
	
	//Actor Component
	FlightComponent = CreateDefaultSubobject<UCFlightComponent>(TEXT("FlightComponent"));
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	CharacterType = ECharacterType::Player;

	
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
	if(InAxis == 0)
		if(GetStatComponent()->IsSpeedType(ESpeedType::Walk))
			GetStatComponent()->SetSpeed(ESpeedType::Joging);

	CheckFalse(GetStatComponent()->IsCanMove());

	switch (GetStatComponent()->GetStatus())
	{

	case EStatusType::Flight:
		OnMoveForward_Flight(InAxis);
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

void ACPlayer::OnMoveForward_Flight(float InAxis)
{
}

void ACPlayer::OnMoveRight(float InAxis)
{
	Super::OnMoveRight(InAxis);

	switch (GetStatComponent()->GetStatus())
	{

	case EStatusType::Flight:
		OnMoveRight_Flight(InAxis);
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

void ACPlayer::OnMoveRight_Flight(float InAxis)
{
}

void ACPlayer::OnJump()
{
	switch (GetStatComponent()->GetState())
	{

	case EStateType::Idling:
		break;

	default:
		return;
		break;
	}

	switch (GetStatComponent()->GetStatus())
	{

	case EStatusType::Unarmed:
		Super::OnJump();
		break;

	case EStatusType::Flight:
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

	case ESpeedType::Joging:
		GetStatComponent()->SetSpeed(ESpeedType::Walk);
		break;

	default:
		break;
	}

}

void ACPlayer::OnRun()
{
	++Run;

	if (Run >= 2)
		GetStatComponent()->SetSpeed(ESpeedType::Run);
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
	Sprint = true;
	if (GetStatComponent()->IsStatus(EStatusType::Flight))
	{


		return;
	}
	CheckFalse(GetStatComponent()->IsState(EStateType::Idling));


	CheckNull(ActionDataAsset);
	PlayAnimMontage(ActionDataAsset->RollAnimMontage.AnimMontage, ActionDataAsset->RollAnimMontage.PlayRate);
}

void ACPlayer::OffSprint()
{
	Sprint = false;
	CheckFalse(GetStatComponent()->IsStatus(EStatusType::Flight));

}



