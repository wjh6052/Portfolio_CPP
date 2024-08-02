#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMeleeCompoent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_CPP_API UCMeleeCompoent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMeleeCompoent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
