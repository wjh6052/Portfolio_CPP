#include "CNS_CanMove.h"
#include "../Global.h"

#include "../Character/BaseCharacter.h"



FString UCNS_CanMove::GetNotifyName_Implementation() const
{
	return "CanMove";
}

void UCNS_CanMove::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);	
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ABaseCharacter>(MeshComp->GetOwner()));
	ABaseCharacter* ownerCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());


	ownerCharacter->GetStatComponent()->SetCanMove(false);
}

void UCNS_CanMove::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ABaseCharacter>(MeshComp->GetOwner()));
	ABaseCharacter* ownerCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());

	ownerCharacter->GetStatComponent()->SetCanMove(true);

}
