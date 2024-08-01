#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseDataAsset.h"
#include "CFlightDataAsset.generated.h"


UCLASS()
class PORTFOLIO_CPP_API UCFlightDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
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
		TArray <class UNiagaraSystem*> SuperheroLnading;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		struct FAnimMontageBase Hover_Start;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		struct FAnimMontageBase FastMove_Start;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		struct FAnimMontageBase Landing;
};
