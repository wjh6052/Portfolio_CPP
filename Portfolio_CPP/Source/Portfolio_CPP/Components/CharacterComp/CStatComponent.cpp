#include "CStatComponent.h"
#include "../../Character/BaseCharacter.h"
#include "../../Global.h"

#include "GameFramework/CharacterMovementComponent.h"


UCStatComponent::UCStatComponent()
{
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	CheckNull(OwnerCharacter);
}


void UCStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	


	SetSpeed(ESpeedType::Joging);
	
}


void UCStatComponent::SetSpeed(ESpeedType input)
{	
	CheckNull(OwnerCharacter);

	switch (input)
	{
	case ESpeedType::Stop:
		SetSpeedType(ESpeedType::Stop);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed.Stop;
		break;

	case ESpeedType::Walk:
		SetSpeedType(ESpeedType::Walk);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed.Walk;
		break;

	case ESpeedType::Joging:
		SetSpeedType(ESpeedType::Joging);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed.Joging;
		break;

	case ESpeedType::Run:
		SetSpeedType(ESpeedType::Run);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed.Run;
		break;

	case ESpeedType::Sprint:
		SetSpeedType(ESpeedType::Sprint);
		break;

	default:
		break;
	}
}
