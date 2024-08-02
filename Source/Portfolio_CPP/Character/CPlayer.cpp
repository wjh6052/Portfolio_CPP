#include "CPlayer.h"
#include "../Global.h"

ACPlayer::ACPlayer()
{
	CharacterType = ECharacterType::Player;
	
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void ACPlayer::OnMoveForward(float InAxis)
{
	Super::OnMoveForward(InAxis);

	switch (StatComponent->GetStatus())
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

	switch (StatComponent->GetStatus())
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
	switch (StatComponent->GetState())
	{

	case EStateType::Idling:
		break;

	default:
		return;
		break;
	}

	switch (StatComponent->GetStatus())
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
