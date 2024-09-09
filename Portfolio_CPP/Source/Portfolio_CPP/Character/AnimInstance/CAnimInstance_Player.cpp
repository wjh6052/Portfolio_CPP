#include "CAnimInstance_Player.h"
#include "../../Global.h"
#include "../CPlayer.h"

#include "Kismet/KismetMathLibrary.h"


void UCAnimInstance_Player::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerPlayer = Cast<ACPlayer>(TryGetPawnOwner());
	CheckNull(OwnerPlayer);
}

void UCAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UCAnimInstance_Player::PawnOwnerIsValid()
{
	Super::PawnOwnerIsValid();

	
	
	IKvariable();
	Flightvariable();
}

void UCAnimInstance_Player::IKvariable()
{
	IK_Alpha = FMath::Lerp(IK_Alpha, 1.f - FMath::Clamp((Speed / 50), 0.f, 1.f), 0.05f);
}

void UCAnimInstance_Player::Flightvariable()
{
	Flight_MaxFlySpeed = OwnerPlayer->GetCharacterMovement()->MaxFlySpeed;

	
	UKismetMathLibrary::FInterpTo(Flight_Speed_MoveRate, UKismetMathLibrary::MapRangeUnclamped(Speed, 0, Flight_MaxFlySpeed, 0, 0), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0);

	LookAtLocation = FVector::ZeroVector;


	FVector flight_Speed = UKismetMathLibrary::LessLess_VectorRotator(OwnerPlayer->GetVelocity(), OwnerPlayer->GetActorRotation());

	 

	Flight_Speed_X = UKismetMathLibrary::MapRangeClamped(flight_Speed.X, Flight_MaxFlySpeed * -1.f, Flight_MaxFlySpeed, -1.f, 1.f);
	Flight_Speed_Y = UKismetMathLibrary::MapRangeClamped(flight_Speed.Y, Flight_MaxFlySpeed * -1.f, Flight_MaxFlySpeed, -1.f, 1.f);
	Flight_Speed_Z = UKismetMathLibrary::MapRangeClamped(flight_Speed.Z, Flight_MaxFlySpeed * -1.f, Flight_MaxFlySpeed, -1.f, 1.f);


	Flight_Lean_X = OwnerPlayer->GetFlightComponent()->Lean_X;
	Flight_Lean_Y = OwnerPlayer->GetFlightComponent()->Lean_Y;


	bSprint = OwnerPlayer->GetFlightComponent()->GetSprint();

	FVector demo = OwnerPlayer->GetVelocity();
	UKismetMathLibrary::Vector_Normalize(demo, 0.0001f);
	
	
	HighSpeedVerticalSpeed = UKismetMathLibrary::FInterpTo(Flight_Speed_MoveRate, demo.Z, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),0);
	
	
	LookAtLocation = OwnerPlayer->GetFlightComponent()->LookAtLocation;
}
