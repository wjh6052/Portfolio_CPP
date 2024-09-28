#include "CWings.h"
#include "../Global.h"
#include "../Character/CPlayer.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"




ACWings::ACWings()
{
	
	CHelpers::CreateSceneComponent(this, &SkeletalMesh, "SkeletalMesh", GetRootComponent());
}

void ACWings::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<ACPlayer>(GetOwner());
	CheckNull(OwnerPlayer);

	
	if(Wings_Trail != nullptr)
	Wings_TrailComp = UNiagaraFunctionLibrary::SpawnSystemAttached
		(
			Wings_Trail,
			SkeletalMesh,
			"Center",
			FVector::ZeroVector,
			FRotator(0.f, -90.f, 0.f),
			FVector(10, 10, 10),
			EAttachLocation::Type::KeepRelativeOffset,
			false,
			ENCPoolMethod::None,
			false,
			true
		);
	Wings_TrailComp->SetActive(false);



	//Material
	if(SkeletalMesh != nullptr)
		WingsDynamicMaterial = UMaterialInstanceDynamic::Create(SkeletalMesh->GetMaterial(0), this);

	if(Dissolve_Instance != nullptr)
		DissolveMaterial = UMaterialInstanceDynamic::Create(Dissolve_Instance, this);
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
	bWings_Sprint = input;

	Wings_TrailComp->SetActive(input);

	if (input)
	{
		WingsStop();
	}
	else 
	{
		WingsMove();
	}
}

void ACWings::SetWingsMove(float input)
{
	Wing_L = FVector(0.f, input * 50, input * 30);
	Wing_R = FVector(0.f, input * 50, input * 30);
}

void ACWings::SpawnWings(bool input)
{
	bWings_Spawn = input;
	
	SpawnWingsImpact();
}

