#include "CAnimInstance.h"
#include "../../Global.h"
#include "../BaseCharacter.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	ABaseCharacter* ownerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	CheckNull(ownerCharacter);

	
}


void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	ABaseCharacter* ownerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	CheckNull(ownerCharacter);

	Speed = FMath::Lerp(Speed, ownerCharacter->GetVelocity().Size2D(), 0.05f);

	FRotator controlRotation = FRotator(0, ownerCharacter->GetControlRotation().Yaw, 0);
	float direction = CalculateDirection(ownerCharacter->GetVelocity(), controlRotation);
	Direction = FMath::Lerp(Direction, direction, 0.05f);

	bFalling = ownerCharacter->GetCharacterMovement()->IsFalling();


	StateType = ownerCharacter->StatComponent->GetState();

	StatusType = ownerCharacter->StatComponent->GetStatus();

	


}
