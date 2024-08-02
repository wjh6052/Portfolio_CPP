#include "CAnimInstance_Player.h"


void UCAnimInstance_Player::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UCAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UCAnimInstance_Player::PawnOwnerIsValid()
{
	Super::PawnOwnerIsValid();

	
	
	IK_Alpha = FMath::Lerp(IK_Alpha, 1.f - FMath::Clamp((Speed / 50), 0.f, 1.f), 0.05f);
}
