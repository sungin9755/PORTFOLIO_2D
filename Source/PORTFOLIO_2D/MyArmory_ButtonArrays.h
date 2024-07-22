// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "MyButton.h"
#include "MyArmory_ButtonArrays.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeData
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Upgrade")
    int CurrentLevel;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Upgrade")
    int MaxLevel;

    FUpgradeData(int Current = 0, int Max = 10)
        : CurrentLevel(Current), MaxLevel(Max) {}
};

UCLASS()
class PORTFOLIO_2D_API UMyArmory_ButtonArrays : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void ReleaseSlateResources(bool bReleaseChildren) override; // 추가된 부분

    void UpdateUpgradeText(UTextBlock* TextBlock, const FUpgradeData& Data);
    void SaveGame(const TArray<FUpgradeData>& UpgradeDataArray);
    void LoadGame(TArray<FUpgradeData>& UpgradeDataArray);
    void OnButtonClick(int32 ButtonIndex);
    void OnRightButtonClick(int32 ButtonIndex);

    

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UGridPanel* ButtonContainer;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TArray<UMyButton*> Buttons;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TArray<UTextBlock*> UpgradeTexts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    TArray<FString> ButtonImagePaths;

    void InitializeButtons();
    void UpdateButtonStyles();

private:
    void InitializeUpgradeData(TArray<FUpgradeData>& UpgradeDataArray);

    TArray<FUpgradeData> UpgradeDataArray;
};
