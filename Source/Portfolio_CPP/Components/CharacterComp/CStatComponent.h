#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatComponent.generated.h"


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
	float Sprint = 600;
};


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


	//set
	FORCEINLINE void SetHP(float input) { Stat.HP += input; }
	FORCEINLINE void SetHP_Max(float input) { Stat.HP_Max += input; }
	FORCEINLINE void SetDamage(float input) { Stat.Damage += input; }
	FORCEINLINE void SetDefense(float input) { Stat.Defense += input; }
	FORCEINLINE void SetCritical_Damage(float input) { Stat.Critical_Damage += input; }
	FORCEINLINE void SetCritical_Chance(float input) { Stat.Critical_Chance += input; }

	FORCEINLINE void SetWalk(float input) { Speed.Walk = input; }
	FORCEINLINE void SetJoging(float input) { Speed.Joging = input; }
	FORCEINLINE void SetSprint(float input) { Speed.Sprint = input; }


private:
	class ABaseCharacter* OwnerCharacter;

	FStat Stat;
	FSpeed Speed;
};
