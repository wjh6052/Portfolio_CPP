#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Wings.generated.h"




UCLASS()
class PORTFOLIO_CPP_API UCAnimInstance_Wings : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


protected:
	class ACWings* OwnerWings;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector Anim_Wing_L;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector Anim_Wing_R;

};
