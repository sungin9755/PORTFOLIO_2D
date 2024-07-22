// Fill out your copyright notice in the Description page of Project Settings.


#include "MyArmory_ButtonArrays.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Styling/SlateTypes.h"
#include "Styling/WidgetStyle.h"
#include "Kismet/GameplayStatics.h"
#include "ArmorySaveData.h"
#include "Engine/Engine.h"

void UMyArmory_ButtonArrays::NativeConstruct()
{
    Super::NativeConstruct();
    UE_LOG(LogTemp, Warning, TEXT("NativeConstruct called"));
    InitializeButtons();
}

void UMyArmory_ButtonArrays::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    for (UMyButton* Button : Buttons)
    {
        if (Button)
        {
            Button->ReleaseSlateResources(bReleaseChildren);
        }
    }
}

void UMyArmory_ButtonArrays::InitializeButtons()
{
    UE_LOG(LogTemp, Warning, TEXT("InitializeButtons called"));

    LoadGame(UpgradeDataArray);

    if (Buttons.Num() == 8 && UpgradeTexts.Num() == 16 && ButtonContainer)
    {
        const int32 NumCols = 3;
        const int32 NumRows = 9;

        int32 TextIndex = 0;

        for (int32 Index = 0; Index < 8; ++Index)
        {
            int32 ButtonRow = (Index / NumCols) * 3;
            int32 Col = Index % NumCols;

            if (Buttons[Index])
            {
                UGridSlot* ButtonSlot = ButtonContainer->AddChildToGrid(Buttons[Index]);
                ButtonSlot->SetRow(ButtonRow);
                ButtonSlot->SetColumn(Col);

                Buttons[Index]->ButtonIndex = Index;
                Buttons[Index]->ParentWidget = this;

                // 이미지 경로 설정
                if (ButtonImagePaths.IsValidIndex(Index))
                {
                    Buttons[Index]->ButtonImagePath = ButtonImagePaths[Index];
                    UE_LOG(LogTemp, Warning, TEXT("Button %d Image Path: %s"), Index, *ButtonImagePaths[Index]);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("ButtonImagePaths does not have enough elements"));
                }

                UE_LOG(LogTemp, Warning, TEXT("Button %d bound"), Index);
            }

            if (UpgradeTexts[TextIndex] && UpgradeTexts[TextIndex + 1])
            {
                UGridSlot* TextSlot1 = ButtonContainer->AddChildToGrid(UpgradeTexts[TextIndex]);
                TextSlot1->SetRow(ButtonRow + 1);
                TextSlot1->SetColumn(Col);

                UGridSlot* TextSlot2 = ButtonContainer->AddChildToGrid(UpgradeTexts[TextIndex + 1]);
                TextSlot2->SetRow(ButtonRow + 2);
                TextSlot2->SetColumn(Col);

                UpdateUpgradeText(UpgradeTexts[TextIndex + 1], UpgradeDataArray[Index]);

                TextIndex += 2;
            }
        }
        UpdateButtonStyles();
    }
}

void UMyArmory_ButtonArrays::OnButtonClick(int32 ButtonIndex)
{
    UE_LOG(LogTemp, Warning, TEXT("OnButtonClick called with index %d"), ButtonIndex);
    if (ButtonIndex >= 0 && ButtonIndex < UpgradeDataArray.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("Inside if condition"));
        if (UpgradeDataArray[ButtonIndex].CurrentLevel < UpgradeDataArray[ButtonIndex].MaxLevel)
        {
            UpgradeDataArray[ButtonIndex].CurrentLevel++;
            int32 TextIndex = ButtonIndex * 2 + 1;

            if (UpgradeTexts.IsValidIndex(TextIndex))
            {
                UpdateUpgradeText(UpgradeTexts[TextIndex], UpgradeDataArray[ButtonIndex]);
            }
            SaveGame(UpgradeDataArray);
        }
    }
}

void UMyArmory_ButtonArrays::OnRightButtonClick(int32 ButtonIndex)
{
    UE_LOG(LogTemp, Warning, TEXT("OnRightButtonClick called with index %d"), ButtonIndex);
    // 오른쪽 클릭 이벤트 처리 로직 추가
    // 예: UpgradeDataArray[ButtonIndex].CurrentLevel을 1 감소
    if (ButtonIndex >= 0 && ButtonIndex < UpgradeDataArray.Num())
    {
        if (UpgradeDataArray[ButtonIndex].CurrentLevel > 0)
        {
            UpgradeDataArray[ButtonIndex].CurrentLevel--;
            int32 TextIndex = ButtonIndex * 2 + 1;

            if (UpgradeTexts.IsValidIndex(TextIndex))
            {
                UpdateUpgradeText(UpgradeTexts[TextIndex], UpgradeDataArray[ButtonIndex]);
            }
            SaveGame(UpgradeDataArray);
        }
    }
}

void UMyArmory_ButtonArrays::UpdateButtonStyles()
{
    for (UMyButton* Button : Buttons)
    {
        if (Button)
        {
            // 현재 버튼의 스타일을 가져옵니다.
            FButtonStyle NewStyle = Button->WidgetStyle; // 스타일 직접 수정

            FSlateBrush TransparentBrush = NewStyle.Normal;
            TransparentBrush.DrawAs = ESlateBrushDrawType::NoDrawType;

            UObject* ButtonImage = NewStyle.Normal.GetResourceObject();
            NewStyle.Normal.SetResourceObject(ButtonImage);
            NewStyle.Hovered.SetResourceObject(ButtonImage);
            NewStyle.Pressed.SetResourceObject(ButtonImage);

            Button->SetStyle(NewStyle);
        }
    }
}

void UMyArmory_ButtonArrays::UpdateUpgradeText(UTextBlock* TextBlock, const FUpgradeData& Data)
{
    FString UpgradeText = FString::Printf(TEXT("%d / %d"), Data.CurrentLevel, Data.MaxLevel);
    TextBlock->SetText(FText::FromString(UpgradeText));
}

void UMyArmory_ButtonArrays::SaveGame(const TArray<FUpgradeData>& InUpgradeDataArray)
{
    UArmorySaveData* SaveGameInstance = Cast<UArmorySaveData>(UGameplayStatics::CreateSaveGameObject(UArmorySaveData::StaticClass()));
    SaveGameInstance->UpgradeDataArray = InUpgradeDataArray;
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySaveSlot"), 0);
}

void UMyArmory_ButtonArrays::LoadGame(TArray<FUpgradeData>& OutUpgradeDataArray)
{
    UArmorySaveData* LoadGameInstance = Cast<UArmorySaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("MySaveSlot"), 0));

    if (LoadGameInstance)
    {
        OutUpgradeDataArray = LoadGameInstance->UpgradeDataArray;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No save game found, initializing data"));
        InitializeUpgradeData(OutUpgradeDataArray);
        SaveGame(OutUpgradeDataArray); // Save the initialized data
    }
}

void UMyArmory_ButtonArrays::InitializeUpgradeData(TArray<FUpgradeData>& InUpgradeDataArray)
{
    InUpgradeDataArray.Empty();
    for (int32 i = 0; i < 8; ++i) // Assuming there are 8 upgrade data slots
    {
        InUpgradeDataArray.Add(FUpgradeData(0, 10));
    }
}
