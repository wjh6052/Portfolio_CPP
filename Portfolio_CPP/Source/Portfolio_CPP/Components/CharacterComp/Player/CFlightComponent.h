#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../../Object/CWings.h"
#include "../../../Datas/DataAsset/BaseDataAsset.h"
#include "CFlightComponent.generated.h"


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
		float MaxAcceleration = 20480.f;
	UPROPERTY(EditAnywhere)
		float BrakingDeceleration = 4096.0;
	UPROPERTY(EditAnywhere)
		FRotator RotationRate = FRotator(0.f, 720.f, 0.f);
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_CPP_API UCFlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCFlightComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetFlying(bool input);
	void SetFlightMovementParam(bool input);

	void StartFlight();
	void EndFlight();

	void SetSprint(bool input);
	bool CheckMovementMode(EMovementMode input);

	void StopToPlayAnim(struct FAnimMontageBase* inAnimMontage);
	void SetActiveComponent(class UActorComponent* Component, bool bNewActive, bool bReset);
	


private:
	UPROPERTY(EditAnywhere, Category = "FlightData")
		class UCFlightDataAsset* FlightDataAsset;

	UPROPERTY(EditAnywhere, Category = "FlightData")
		TSubclassOf<ACWings> WingsClass;



	UPROPERTY(EditAnywhere, Category = "FlightData")
		FFlightSetting FlightSetting;
	UPROPERTY(EditAnywhere, Category = "FlightData")
		FFlightSetting_Sprint FlightSetting_Sprint;

	class ACWings* Wings;

	class ACPlayer* OwnerPlayer;

	bool bFlying = false;
	bool bSprint = false;
	bool bLanding = false;



	class UNiagaraComponent* Flight_Trail_Ref;
	class UNiagaraComponent* Flight_Wave_Ref;
	TArray<class UNiagaraComponent*> Under_Dust_Ref;
	FTimerHandle SetActiveComponentTime;
};
