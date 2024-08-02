#include "BaseCharacter.h"
#include "../Global.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


#define INPUT

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//Ä«¸Þ¶ó
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f; 
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm); 
	Camera->bUsePawnControlRotation = false;


	//Actor Component
	StatComponent = CreateDefaultSubobject<UCStatComponent>(TEXT("StatComponent"));


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// -> MovementComp
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);


}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#ifdef INPUT
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ABaseCharacter::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ABaseCharacter::OnVerticalLook);
	PlayerInputComponent->BindAxis("CameraZoom", this, &ABaseCharacter::OnCameraZoom);


	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ABaseCharacter::OnJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ABaseCharacter::OffJump);
}


void ABaseCharacter::OnMoveForward(float InAxis)
{
	CheckTrue(FMath::IsNearlyZero(InAxis));
	CheckFalse(GetStatComponent()->IsCanMove());
}

void ABaseCharacter::OnMoveForward_Unarmed(float InAxis)
{
	FVector direction = FQuat(FRotator(0, GetControlRotation().Yaw, 0)).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}


void ABaseCharacter::OnMoveRight(float InAxis)
{
	CheckTrue(FMath::IsNearlyZero(InAxis));
	CheckFalse(GetStatComponent()->IsCanMove());
}

void ABaseCharacter::OnMoveRight_Unarmed(float InAxis)
{
	FVector direction = FQuat(FRotator(0, GetControlRotation().Yaw, 0)).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}

void ABaseCharacter::OnHorizontalLook(float InAxis)
{
	AddControllerYawInput(InAxis);
}

void ABaseCharacter::OnVerticalLook(float InAxis)
{
	AddControllerPitchInput(InAxis);
}

void ABaseCharacter::OnCameraZoom(float InAxis)
{
	SpringArm->TargetArmLength = FMath::Clamp((InAxis * 10) + SpringArm->TargetArmLength, 150.f, 1000.f);	
}

void ABaseCharacter::OnJump()
{
	
	ACharacter::Jump();
}

void ABaseCharacter::OffJump()
{
	ACharacter::OnJumped();
}




#endif
