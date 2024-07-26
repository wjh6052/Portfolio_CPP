#include "CStatComponent.h"
#include "../../Character/BaseCharacter.h"



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
