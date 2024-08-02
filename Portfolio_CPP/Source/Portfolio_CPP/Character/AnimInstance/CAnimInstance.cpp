#include "CAnimInstance.h"
#include "../../Global.h"
#include "../BaseCharacter.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);

	
}


void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	CheckNull(OwnerCharacter);

	Speed = FMath::Lerp(Speed, OwnerCharacter->GetVelocity().Size2D(), 0.05f);

	float direction = CalculateDirection(OwnerCharacter->GetVelocity(), FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0));
	Direction = FMath::Lerp(Direction, direction, 0.05f);

	bFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();


	StateType = OwnerCharacter->GetStatComponent()->GetState();

	StatusType = OwnerCharacter->GetStatComponent()->GetStatus();

	
	PawnOwnerIsValid();

}

void UCAnimInstance::PawnOwnerIsValid()
{
}
