#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseDataAsset.h"
#include "CFlightDataAsset.generated.h"



USTRUCT(BlueprintType)
struct FFlightSetting
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float FlyWarkSpeed = 600.f;
	UPROPERTY(EditAnywhere)
		float MaxAcceleration = 2048.f;
	UPROPERTY(EditAnywhere)
		float BrakingDeceleration = 4096.0;
	UPROPERTY(EditAnywhere)
		FRotator RotationRate = FRotator(0.f, 540.f, 0.f);
};

USTRUCT(BlueprintType)
struct FFlightSetting_Sprint
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float FlyWarkSpeed = 1000.f;
	UPROPERTY(EditAnywhere)
		float FlySpeed = 4096.f;
	UPROPERTY(EditAnywhere)
		float MaxAcceleration = 20480.f;
	UPROPERTY(EditAnywhere)
		float BrakingDeceleration = 4096.0;
	UPROPERTY(EditAnywhere)
		FRotator RotationRate = FRotator(0.f, 720.f, 0.f);
};



UCLASS()
class PORTFOLIO_CPP_API UCFlightDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "FlightData")
		FFlightSetting FlightSetting;
	UPROPERTY(EditAnywhere, Category = "FlightData")
		FFlightSetting_Sprint FlightSetting_Sprint;



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Trail")
		class UNiagaraSystem* Flight_Trail;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Trail")
		FVector Flight_Trail_Location;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Trail")
		FRotator Flight_Trail_Rotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Trail")
		FVector Flight_Trail_Scale = FVector(1.f, 1.f, 1.f);



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Wave")
		class UNiagaraSystem* Flight_Wave;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Wave")
		FVector Flight_Wave_Location;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Wave")
		FRotator Flight_Wave_Rotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Wave")
		FVector Flight_Wave_Scale = FVector(1.f, 1.f, 1.f);



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "FlightUnderDust")
		TArray <class UNiagaraSystem*> FlightUnderDust;



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuperheroLnading")
		class UNiagaraSystem* Lnading_Concrete;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuperheroLnading")
		class UNiagaraSystem* Lnading_Ground;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuperheroLnading")
		class UNiagaraSystem* Lnading_Grass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuperheroLnading")
		class UNiagaraSystem* Lnading_Sand;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuperheroLnading")
		class UNiagaraSystem* Lnading_Water;



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		struct FAnimMontageBase Hover_Start;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		struct FAnimMontageBase FastMove_Start;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		struct FAnimMontageBase Landing;
};
