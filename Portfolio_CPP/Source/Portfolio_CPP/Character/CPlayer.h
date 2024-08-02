#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "../Components/CharacterComp/Player/CFlightComponent.h"
#include "CPlayer.generated.h"

UCLASS()
class PORTFOLIO_CPP_API ACPlayer : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	FORCEINLINE class UCFlightComponent* GetFlightComponent() const { return FlightComponent; }

public:
	virtual void OnMoveForward(float InAxis) override;
	void OnMoveForward_Flight(float InAxis);

	virtual void OnMoveRight(float InAxis) override;
	void OnMoveRight_Flight(float InAxis);

	virtual void OnJump() override;
	virtual void OffJump() override;

	void OnWalk();
	void OnRun();
	void OffRun();
	void RunDelay();
	void OnSprint();
	void OffSprint();


protected:
	//Actor Component
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UCFlightComponent> FlightComponent;


private:
	int Run = 0;
	FTimerHandle RunTimer;

	bool Sprint = false;

	UPROPERTY(EditAnywhere, Category = "ActionDataAsset")
		class UCActionDataAsset* ActionDataAsset;
};