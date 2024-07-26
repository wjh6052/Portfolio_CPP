#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Components/CharacterComp/CStatComponent.h"
#include "BaseCharacter.generated.h"


UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Player,
	Enemy,
	Boss
};

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idling,
	Rolling,
	Attacking,
	Hitted,
	Groggy,
	Dying
};

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Stop,
	Walk,
	Joging,
	Sprint
};



UCLASS()
class PORTFOLIO_CPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();


protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:	
	FORCEINLINE FSpeed GetSpeed() { return BaseSpeed; }
	FORCEINLINE FStat GetStat() { return BaseStat; }


private:
	//Scene Component
	UPROPERTY(EditAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = Camera)
		class UCameraComponent* Camera;


private:
	//Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatComponent* StatComponent;



private:
	//현재의 상태를 조절하는 열거형
	EStateType StateType;


	//캐릭터의 타입을 결정하는 열거형
	ECharacterType CharacterType;
	

	//Speed
	UPROPERTY(EditAnywhere, Category = "Speed")
		FSpeed BaseSpeed;
	//Stat
	UPROPERTY(EditAnywhere, Category = "Stat")
		FStat BaseStat;

};
