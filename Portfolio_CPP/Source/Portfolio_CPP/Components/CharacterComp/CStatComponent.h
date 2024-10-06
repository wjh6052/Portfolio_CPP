#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Datas/DataAsset/CharacterDataAsset.h"
#include "CStatComponent.generated.h"





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
	FORCEINLINE bool GetSprint() const { return bSprint; }
	
	FORCEINLINE EStateType GetStateType() const { return StateType; }
	FORCEINLINE EStatusType GetStatusType() const { return StatusType; }
	FORCEINLINE ESpeedType GetSpeedType() const { return SpeedType; }

	FORCEINLINE UCharacterDataAsset* GetCharacterDataAsset() const { return CharacterDataAsset; }


	//set
	FORCEINLINE void SetSprint(bool input) { bSprint = input; }
	FORCEINLINE void SetCanMove(bool input) { bCanMove = input; }
	FORCEINLINE void SetCameraCanMove(bool input) { bCameraCanMove = input; }

	FORCEINLINE void SetStateType(EStateType input) { StateType = input; }
	FORCEINLINE void SetStatusType(EStatusType input) { StatusType = input; }
	FORCEINLINE void SetSpeedType(ESpeedType input) { SpeedType = input; }

	


	//Is
	FORCEINLINE bool IsCanMove() { return bCanMove; }
	FORCEINLINE bool IsCameraCanMove() { return bCameraCanMove; }

	FORCEINLINE bool IsSpeedType(ESpeedType input) { return SpeedType == input; }

	FORCEINLINE bool IsState(EStateType input) { return StateType == input; }
	FORCEINLINE bool IsStatus(EStatusType input) { return StatusType == input; }

	



public:
	//Set
	void SetSpeed(ESpeedType input);


private:
	UPROPERTY(EditAnywhere, Category = "Data")
		class UCharacterDataAsset* CharacterDataAsset;


public:
	class ABaseCharacter* OwnerCharacter;
	 


	//현재의 상태를 조절하는 열거형
	EStateType StateType;
	EStatusType StatusType;

	UPROPERTY(BlueprintReadOnly)
	ESpeedType SpeedType;


	bool bSprint = false;


	bool bCanMove = true;
	bool bCameraCanMove = true;


private:
	//무적모드
	bool God_Mode = false;
};
