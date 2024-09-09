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

	CheckNull(BaseCharacter);
	CheckNull(BaseCharacter->GetStatComponent());
	
	FString speedType = StaticEnum<ESpeedType>()->GetDisplayNameTextByValue(static_cast<int64>(BaseCharacter->GetStatComponent()->GetSpeedType())).ToString();
	DrawText("Speed Type : " + speedType, FLinearColor::Red, 10, Canvas->ClipY - 50, nullptr, 2.f);

	FString statusType = StaticEnum<EStatusType>()->GetDisplayNameTextByValue(static_cast<int64>(BaseCharacter->GetStatComponent()->GetStatusType())).ToString();
	DrawText("Status Type : " + statusType, FLinearColor::Red, 10, Canvas->ClipY - 75, nullptr, 2.f);
}


