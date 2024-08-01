#include "CHUD.h"
#include "Global.h"
#include "Character/BaseCharacter.h"

#include "Engine/Canvas.h"
#include "GameFramework/Character.h"



ACHUD::ACHUD()
{

}

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	BaseCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	CheckNull(BaseCharacter->StatComponent);
	
	FString typeStr = StaticEnum<ESpeedType>()->GetDisplayNameTextByValue(static_cast<int64>(BaseCharacter->StatComponent->GetSpeedType())).ToString();
	DrawText("SpeedType : " + typeStr, FLinearColor::Red, 10, Canvas->ClipY - 50, nullptr, 2.f);

}


