#include "CStatComponent.h"
#include "../../Character/BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"


UCStatComponent::UCStatComponent()
{

}


void UCStatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(this->GetOwner());
	
	if (OwnerCharacter == nullptr) return;

	OwnerCharacter->GetStat() = Stat;
	OwnerCharacter->GetSpeed() = Speed;
}


void UCStatComponent::SetSpeed(ESpeedType input)
{
	if (OwnerCharacter == nullptr) return;

	switch (input)
	{
	case ESpeedType::Stop:
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed.Stop;
		break;

	case ESpeedType::Walk:
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed.Walk;
		break;

	case ESpeedType::Joging:
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed.Joging;
		break;

	case ESpeedType::Sprint:
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed.Sprint;
		break;

	default:
		break;
	}
}
