#include "CWings.h"
#include "../Global.h"
#include "../Character/CPlayer.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"




ACWings::ACWings()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateSceneComponent(this, &SkeletalMesh, "SkeletalMesh", GetRootComponent());
}

void ACWings::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<ACPlayer>(GetOwner());
	CheckNull(OwnerPlayer);
	OwnerPlayer->GetFlightComponent();
	
	if(Wings_Trail != nullptr)
		Wings_TrailComp = UNiagaraFunctionLibrary::SpawnSystemAttached
		(
			Wings_Trail,
			OwnerPlayer->GetMesh(),
			TEXT("Center"),
			FVector::ZeroVector,
			FRotator(0.f, -90.f, 0.f),
			FVector(0, 0, 0),
			EAttachLocation::Type::KeepRelativeOffset,
			true,
			ENCPoolMethod::None,
			true,
			false
		);

	CheckNull(SkeletalMesh);
	UMaterialInstanceDynamic::Create(WingsDynamicMaterial, SkeletalMesh->GetMaterial(0));

	if(Dissolve_Inst != nullptr)
		UMaterialInstanceDynamic::Create(DissolveMaterial, Dissolve_Inst);

	
	

}

void ACWings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACWings::AttachTo(FName InSocketName)
{
	CheckNull(OwnerPlayer);

	AttachToComponent
	(
		OwnerPlayer->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);

}

void ACWings::SetSprint(bool input)
{
	bSprint = input;

	//Wings_TrailComp->SetActive(bSprint, bSprint);

	if (input)
	{
		WingsStop();
	}
	else 
	{
		WingsMove();
	}
}

void ACWings::SpawnWings(bool input)
{
	bSpawnWings = input;

	SetActorHiddenInGame(!bSpawnWings);

	SpawnWingsImpact(bSpawnWings);
}

