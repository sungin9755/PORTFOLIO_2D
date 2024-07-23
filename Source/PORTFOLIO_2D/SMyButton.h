// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Styling/SlateTypes.h"
#include "Brushes/SlateImageBrush.h"

class SMyButton : public SButton
{
public:
    SLATE_BEGIN_ARGS(SMyButton) {}
        SLATE_ARGUMENT(FString, ButtonImagePath)
        SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle)
        SLATE_EVENT(FSimpleDelegate, OnClicked)
        SLATE_EVENT(FSimpleDelegate, OnRightClicked)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

protected:
    virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

private:
    FSimpleDelegate OnClicked;
    FSimpleDelegate OnRightClicked;

    FString ButtonImagePath;
    TSharedPtr<FSlateImageBrush> ButtonBrush;
};
