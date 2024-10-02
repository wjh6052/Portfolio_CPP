#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_SpawnLandingVFX.generated.h"


UCLASS()
class PORTFOLIO_CPP_API UCAN_SpawnLandingVFX : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


	float VectorLength = -500.f;
};
