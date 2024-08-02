#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseDataAsset.h"
#include "CActionDataAsset.generated.h"

UCLASS()
class PORTFOLIO_CPP_API UCActionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Roll")
		FAnimMontageBase RollAnimMontage;


};
