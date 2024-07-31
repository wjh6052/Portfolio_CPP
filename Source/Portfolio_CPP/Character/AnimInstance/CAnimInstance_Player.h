#pragma once

#include "CoreMinimal.h"
#include "CAnimInstance.h"
#include "CAnimInstance_Player.generated.h"


UCLASS()
class PORTFOLIO_CPP_API UCAnimInstance_Player : public UCAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PawnOwnerIsValid() override;


protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float IK_Alpha;
};
