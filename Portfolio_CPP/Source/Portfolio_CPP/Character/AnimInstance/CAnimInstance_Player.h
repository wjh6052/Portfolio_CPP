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

	void IKvariable();
	void Flightvariable();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float IK_Alpha;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	float Flight_MaxFlySpeed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	float Flight_Speed_MoveRate;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	float Flight_Speed_X;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	float Flight_Speed_Y;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	float Flight_Speed_Z;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	float Flight_Lean_X;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	float Flight_Lean_Y;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	float HighSpeedVerticalSpeed;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	FVector LookAtLocation;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight")
	bool bSprint;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OwnerPlayer")
	class ACPlayer* OwnerPlayer;
};
