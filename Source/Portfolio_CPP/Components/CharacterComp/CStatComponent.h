#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatComponent.generated.h"


//--struct---------------------------------------------------------------------

USTRUCT(Atomic, BlueprintType)
struct FStat
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float HP = 100;
	UPROPERTY(EditAnywhere)
		float HP_Max = 100;
	UPROPERTY(EditAnywhere)
		float Damage = 10;
	UPROPERTY(EditAnywhere)
		float Defense = 5;
	UPROPERTY(EditAnywhere)
		float Critical_Damage = 1.5;
	UPROPERTY(EditAnywhere)
		float Critical_Chance = 20;

	//무적모드
	UPROPERTY(EditAnywhere)
		bool God_Mode = false;
};

USTRUCT(Atomic, BlueprintType)
struct FSpeed
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Stop = 0;
	UPROPERTY(EditAnywhere)
		float Walk = 200;
	UPROPERTY(EditAnywhere)
		float Joging = 400;
	UPROPERTY(EditAnywhere)
		float Run = 600;

	UPROPERTY(EditAnywhere)
		float FlyWarkSpeed = 600.f;
	UPROPERTY(EditAnywhere)
		float MaxAcceleration = 2048.f;
	UPROPERTY(EditAnywhere)
		float BrakingDeceleration = 0;
	UPROPERTY(EditAnywhere)
		FRotator RotationRate = FRotator(0.f, 720.f, 0.f);

};


//--enum---------------------------------------------------------------------

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
enum class EStatusType : uint8
{
	Unarmed,
	Flight,
	Climbing,
	Swimming,
	Melee
};

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Stop,
	Walk,
	Joging,
	Run,
	Sprint
};



//--class---------------------------------------------------------------------

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_CPP_API UCStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatComponent();


protected:
	virtual void BeginPlay() override;


public:
	//get
	FORCEINLINE float GetHP() { return Stat.HP; }
	FORCEINLINE float GetHP_Max() { return Stat.HP_Max; }
	FORCEINLINE float GetDamage() { return Stat.Damage; }
	FORCEINLINE float GetDefense() { return Stat.Defense; }
	FORCEINLINE float GetCritical_Damage() { return Stat.Critical_Damage; }
	FORCEINLINE float GetCritical_Chance() { return Stat.Critical_Chance; }

	
	FORCEINLINE EStateType GetState() { return StateType; }
	FORCEINLINE EStatusType GetStatus() { return StatusType; }
	FORCEINLINE ESpeedType GetSpeedType() { return SpeedType; }


	//set
	FORCEINLINE void SetHP(float input) { Stat.HP += input; }
	FORCEINLINE void SetHP_Max(float input) { Stat.HP_Max += input; }
	FORCEINLINE void SetDamage(float input) { Stat.Damage += input; }
	FORCEINLINE void SetDefense(float input) { Stat.Defense += input; }
	FORCEINLINE void SetCritical_Damage(float input) { Stat.Critical_Damage += input; }
	FORCEINLINE void SetCritical_Chance(float input) { Stat.Critical_Chance += input; }

	FORCEINLINE void SetWalkSpeed(float input) { Speed.Walk = input; }
	FORCEINLINE void SetJogingSpeed(float input) { Speed.Joging = input; }
	FORCEINLINE void SetSprintSpeed(float input) { Speed.Run = input; }

	FORCEINLINE void SetStateType(EStateType input) { StateType = input; }
	FORCEINLINE void SetStatusType(EStatusType input) { StatusType = input; }
	FORCEINLINE void SetSpeedType(ESpeedType input) { SpeedType = input; }

	FORCEINLINE void SetCanMove(bool input) { bCanMove = input; }
	FORCEINLINE void SetCameraCanMove(bool input) { bCameraCanMove = input; }


	//Is
	FORCEINLINE bool IsCanMove() { return bCanMove; }
	FORCEINLINE bool IsCameraCanMove() { return bCameraCanMove; }

	FORCEINLINE bool IsState(EStateType input) { if (StateType == input) return true; return false; }
	FORCEINLINE bool IsStatus(EStatusType input) { if (StatusType == input) return true; return false; }

	



public:
	//Set
	void SetSpeed(ESpeedType input);




public:
	class ABaseCharacter* OwnerCharacter;
	 
	//현재의 상태를 조절하는 열거형
	EStateType StateType;
	EStatusType StatusType;
	UPROPERTY(BlueprintReadOnly)
	ESpeedType SpeedType;

	FStat Stat;
	UPROPERTY(EditAnywhere, Category = "SpeedData")
	FSpeed Speed;

	bool bCanMove = true;
	bool bCameraCanMove = true;
};
