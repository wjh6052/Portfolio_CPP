#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWings.generated.h"

UCLASS()
class PORTFOLIO_CPP_API ACWings : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWings();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SpawnWings(bool input);
	void AttachTo(FName InSocketName);

	void SetSprint(bool input);


	UFUNCTION(BlueprintImplementableEvent)
		void SpawnWingsImpact(bool input);

	UFUNCTION(BlueprintImplementableEvent)
		void HitReset();

	UFUNCTION(BlueprintImplementableEvent)
		void WingsMove();

	UFUNCTION(BlueprintImplementableEvent)
		void WingsStop();
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wings_Trail")
		class UNiagaraSystem* Wings_Trail;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wings_Trail")
		class UMaterialInstance* Dissolve_Inst;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;
	
	
private:
	UPROPERTY(EditAnywhere)
		class UMaterialInstanceDynamic* WingsDynamicMaterial;
	UPROPERTY(EditAnywhere)
		class UMaterialInstanceDynamic* DissolveMaterial;

	class UNiagaraComponent* Wings_TrailComp;
	class ACPlayer* OwnerPlayer;
	bool bSprint;
	bool bSpawnWings;
};
