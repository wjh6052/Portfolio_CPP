#include "CAN_SpawnLandingVFX.h"

#include "../../Global.h"
#include "../../Character/CPlayer.h"

FString UCAN_SpawnLandingVFX::GetNotifyName_Implementation() const
{
	return "SpawnLandingVFX";
}
void UCAN_SpawnLandingVFX::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);
	CheckNull(player->GetFlightComponent());

	bool onHit = false;
	FHitResult hitResult;
	onHit = player->GetFlightComponent()->NotifiLineTracetoUpVector(VectorLength, hitResult);
	CheckFalse(onHit);
	FVector HitPoint = hitResult.ImpactPoint;
	FRotator HitNormal = UKismetMathLibrary::MakeRotFromZX(hitResult.ImpactNormal, player->GetActorForwardVector());

	if (hitResult.PhysMaterial != nullptr)
	{
		player->GetFlightComponent()->SpawnNiagaraAtLocationOrAttach(false, player->GetFlightComponent()->GetLnadingVFX(hitResult.PhysMaterial->SurfaceType), nullptr, HitPoint, HitNormal);
	}
	else
	{
		player->GetFlightComponent()->SpawnNiagaraAtLocationOrAttach(false, player->GetFlightComponent()->GetLnadingVFX(EPhysicalSurface::SurfaceType_Default), nullptr, HitPoint, HitNormal);
	}

}