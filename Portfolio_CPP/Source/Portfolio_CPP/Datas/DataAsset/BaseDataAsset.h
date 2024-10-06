#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAnimMontageBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		class UAnimMontage* AnimMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		float PlayRate = 1.0;
};

UCLASS()
class PORTFOLIO_CPP_API UBaseDataAsset : public UDataAsset
{
	GENERATED_BODY()
		
	
};
