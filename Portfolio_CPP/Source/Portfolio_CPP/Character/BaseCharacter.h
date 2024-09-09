#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Components/CharacterComp/CStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.generated.h"


UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Player,
	Enemy,
	Boss
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
	//Get
	FORCEINLINE bool GetSprint() const { return bSprint; }
	FORCEINLINE FSpeed GetBaseSpeed() const { return BaseSpeed; }
	FORCEINLINE FStat GetBaseStat() const { return BaseStat; }
	FORCEINLINE class UCStatComponent* GetStatComponent() const { return StatComp; }

	//Set
	FORCEINLINE void SetSprint(bool input) { bSprint = input; }

	//IS
	FORCEINLINE bool IsMovementMode(EMovementMode input) { return input == GetCharacterMovement()->MovementMode; }
	
protected:
	virtual void OnMoveForward(float InAxis);
	void OnMoveForward_Unarmed(float InAxis);

	virtual void OnMoveRight(float InAxis);
	void OnMoveRight_Unarmed(float InAxis);

	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	void OnCameraZoom(float InAxis);

	
	virtual void OnJump();
	virtual void OffJump();

	


public:
	//Scene Component
	UPROPERTY(EditAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = Camera)
		class UCameraComponent* Camera;


private:
	//Actor Component
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCStatComponent> StatComp;


protected:
	//캐릭터의 타입을 결정하는 열거형
	ECharacterType CharacterType;
	
private:

	bool bSprint = false;

	//Speed
	UPROPERTY(EditAnywhere, Category = "Speed")
		FSpeed BaseSpeed;
	//Stat
	UPROPERTY(EditAnywhere, Category = "Stat")
		FStat BaseStat;

};
