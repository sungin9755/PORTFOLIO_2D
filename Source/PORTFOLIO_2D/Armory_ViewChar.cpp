// Fill out your copyright notice in the Description page of Project Settings.


#include "Armory_ViewChar.h"
#include "ArmorySaveData.h"
#include "Kismet/GameplayStatics.h"

void UArmory_ViewChar::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Left && Button_Right)
	{
		Button_Left->OnClicked.AddDynamic(this, &UArmory_ViewChar::OnButtonClicked);
		Button_Right->OnClicked.AddDynamic(this, &UArmory_ViewChar::OnButtonClicked);
	}

	InitStats();
	
}

void UArmory_ViewChar::InitStats()
{
	LoadGame(UpgradeDataArray);

	WarriorStats.Health = 10.0f;
	WarriorStats.Attack = 10.0f;
	WarriorStats.AttackSpeed = 2.0f;
	WarriorStats.AttackRange = 5.0f;
	WarriorStats.MoveSpeed = 10.0f;
	WarriorStats.PickupRange = 5.0f;
	WarriorStats.CritChance = 5.0f;
	WarriorStats.CritDamage = 10.0f;

	MagicianStats.Health = 8.0f;
	MagicianStats.Attack = 12.0f;
	MagicianStats.AttackSpeed = 1.0f;
	MagicianStats.AttackRange = 15.0f;
	MagicianStats.MoveSpeed = 8.0f;
	MagicianStats.PickupRange = 5.0f;
	MagicianStats.CritChance = 0.0f;
	MagicianStats.CritDamage = 0.0f;
	
	currentChar = 0;
	for (int i = 0; i < 8; i++) {
		Text_Character->SetText(FText::FromString(TEXT("전사")));
		float* StatPtr = WarriorStats.GetStatByIndex(i);
		int LevelPtr = UpgradeDataArray[i].CurrentLevel;
		UTextBlock* currText = StatusTexts[i];

		UpdateStatText(currText, (StatPtr), LevelPtr);
	}
}


void UArmory_ViewChar::LoadGame(TArray<FUpgradeData>& OutUpgradeDataArray)
{
	UArmorySaveData* LoadGameInstance = Cast<UArmorySaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("MySaveSlot"), 0));

	if (LoadGameInstance)
	{
		OutUpgradeDataArray = LoadGameInstance->UpgradeDataArray;
	}
}

void UArmory_ViewChar::UpdateStatText(UTextBlock* TextBlock, float* BaseStat, int32 currentLevel)
{
	int statBonus = currentLevel * 6;
	FString StatText = FString::Printf(TEXT("%.0f + %d %%"), *BaseStat, statBonus);
	TextBlock->SetText(FText::FromString(StatText));
}


void UArmory_ViewChar::OnButtonClicked()
{
	if (currentChar == 0) {
		for (int i = 0; i < 8; i++) {
			Text_Character->SetText(FText::FromString(TEXT("전사")));
			float* StatPtr = WarriorStats.GetStatByIndex(i);
			int LevelPtr = UpgradeDataArray[i].CurrentLevel;
			UTextBlock* currText = StatusTexts[i];

			UpdateStatText(currText, StatPtr, LevelPtr);
		}
	}
	else if (currentChar == 1)
	{
		for (int i = 0; i < 8; i++) {
			Text_Character->SetText(FText::FromString(TEXT("마법사")));
			float* StatPtr = MagicianStats.GetStatByIndex(i);
			int LevelPtr = UpgradeDataArray[i].CurrentLevel;
			UTextBlock* currText = StatusTexts[i];

			UpdateStatText(currText, StatPtr, LevelPtr);
		}
	}
	
}

