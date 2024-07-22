// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "MyArmory_ButtonArrays.h"
#include "Armory_ViewChar.generated.h"

USTRUCT(BlueprintType) 
struct FCharStat{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float Health;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float Attack;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float AttackSpeed;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float AttackRange;
	
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float MoveSpeed;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float PickupRange;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float CritChance;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float CritDamage;

	float* GetStatByIndex(int32 Index) {
		switch (Index) {
		case 0: return &Health;
		case 1: return &Attack;
		case 2: return &AttackSpeed;
		case 3: return &AttackRange;
		case 4: return &MoveSpeed;
		case 5: return &PickupRange;
		case 6: return &CritChance;
		case 7: return &CritDamage;
		default: return nullptr;
		}
	}
};

/**
 * 
 */
UCLASS()
class PORTFOLIO_2D_API UArmory_ViewChar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void InitStats();
	void UpdateStatText(UTextBlock* TextBlock, float* BaseStat, int32 currentLevel);
	void LoadGame(TArray<FUpgradeData>& OutUpgradeDataArray);

private:
	UFUNCTION()
	void OnButtonClicked();

	TArray<FUpgradeData> UpgradeDataArray;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Left;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 currentChar;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Text_Character;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TArray<UTextBlock*> StatusTexts;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FCharStat WarriorStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FCharStat MagicianStats;
};
