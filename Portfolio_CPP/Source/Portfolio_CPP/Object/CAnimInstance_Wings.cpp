#include "CAnimInstance_Wings.h"
#include "../Global.h"
#include "CWings.h"






void UCAnimInstance_Wings::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerWings = Cast<ACWings>(TryGetPawnOwner());
	CheckNull(OwnerWings);

	
}


void UCAnimInstance_Wings::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	CheckNull(OwnerWings);
	Anim_Wing_L = OwnerWings->GetWing_L();
	Anim_Wing_R = OwnerWings->GetWing_R();	
}
