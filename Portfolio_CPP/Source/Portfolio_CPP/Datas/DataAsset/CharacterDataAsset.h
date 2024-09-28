#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseDataAsset.h"
#include "CharacterDataAsset.generated.h"


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



UCLASS()
class PORTFOLIO_CPP_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		FSpeed Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Roll")
		FAnimMontageBase RollAnimMontage;


};
