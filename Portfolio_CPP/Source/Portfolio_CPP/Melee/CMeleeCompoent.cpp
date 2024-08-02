#include "CMeleeCompoent.h"

UCMeleeCompoent::UCMeleeCompoent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCMeleeCompoent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UCMeleeCompoent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

