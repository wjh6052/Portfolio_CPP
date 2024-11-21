#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CWings.generated.h"

UCLASS()
class PORTFOLIO_CPP_API ACWings : public APawn
{
	GENERATED_BODY()
	
public:	
	ACWings();

protected:
	virtual void BeginPlay() override;

public:	

	void SpawnWings(bool input);
	void AttachTo(FName InSocketName);

	void SetSprint(bool input);

	//Get
	FORCEINLINE FVector GetWing_L() const{ return Wing_L; }
	FORCEINLINE FVector GetWing_R() const{ return Wing_R; }



	UFUNCTION(BlueprintCallable)
		FORCEINLINE void WingsMoveReset() { Wing_L = FVector::ZeroVector; Wing_R = FVector::ZeroVector; }


	UFUNCTION(BlueprintCallable)
		void SetWingsMove(float input);

	

public:	// 블루프린트에서 호출될 이벤트

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnWingsImpact();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void WingsMove();

	UFUNCTION(BlueprintImplementableEvent)
		void WingsStop();



protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;


	UPROPERTY(BlueprintReadOnly)
		class UMaterialInstanceDynamic* WingsDynamicMaterial;
	UPROPERTY(BlueprintReadOnly)
		class UMaterialInstanceDynamic* DissolveMaterial;


	UPROPERTY(BlueprintReadOnly, Category = "Sawpn")
		class UNiagaraComponent* Wings_TrailComp;

	UPROPERTY(BlueprintReadOnly, Category = "Sawpn")
		bool bWings_Sprint;

	UPROPERTY(BlueprintReadOnly, Category = "Sawpn")
		bool bWings_Spawn;


public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wings_Trail")
		TObjectPtr<class UNiagaraSystem> Wings_Trail;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wings_Trail")
		class UMaterialInterface* Dissolve_Instance;

	
	
private:
	class ACPlayer* OwnerPlayer;

	

	

	FVector Wing_L;
	FVector Wing_R;

};
