// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MyButton.generated.h"

class SMyButton;

UCLASS()
class PORTFOLIO_2D_API UMyButton : public UButton
{
    GENERATED_BODY()

public:
    UMyButton();

    int32 ButtonIndex;

    UPROPERTY()
    class UMyArmory_ButtonArrays* ParentWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FString ButtonImagePath;

    virtual void SynchronizeProperties() override;
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void ReleaseSlateResources(bool bReleaseChildren) override; // 추가된 부분

private:
    UFUNCTION()
    void HandleOnClicked();

    UFUNCTION()
    void HandleOnRightClicked();

    TSharedPtr<SMyButton> MySlateButton;
};
