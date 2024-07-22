// Fill out your copyright notice in the Description page of Project Settings.

#include "SMyButton.h"
#include "SlateOptMacros.h"
#include "Engine/Texture2D.h"
#include "Slate/SlateGameResources.h"
#include "Brushes/SlateImageBrush.h"
#include "Rendering/SlateRenderer.h"
#include "Framework/Application/SlateApplication.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMyButton::Construct(const FArguments& InArgs)
{
    ButtonImagePath = InArgs._ButtonImagePath;
    const FButtonStyle* InButtonStyle = InArgs._ButtonStyle;

    if (!ButtonImagePath.IsEmpty())
    {
        UTexture2D* ButtonTexture = LoadObject<UTexture2D>(nullptr, *ButtonImagePath);
        if (ButtonTexture)
        {
            FName BrushName(*ButtonImagePath);
            FIntPoint Size = ButtonTexture->GetImportedSize();
            ButtonBrush = MakeShareable(new FSlateImageBrush(ButtonTexture, FVector2D(Size.X, Size.Y)));

            FButtonStyle ButtonStyle = InButtonStyle ? *InButtonStyle : FButtonStyle();
            ButtonStyle.Normal.SetResourceObject(ButtonTexture);
            ButtonStyle.Hovered.SetResourceObject(ButtonTexture);
            ButtonStyle.Pressed.SetResourceObject(ButtonTexture);

            SButton::Construct(SButton::FArguments().ButtonStyle(&ButtonStyle));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load texture: %s"), *ButtonImagePath);
            SButton::Construct(SButton::FArguments().ButtonStyle(InButtonStyle));
        }
    }
    else
    {
        SButton::Construct(SButton::FArguments().ButtonStyle(InButtonStyle));
    }

    OnClicked = InArgs._OnClicked;
    OnRightClicked = InArgs._OnRightClicked;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SMyButton::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
    if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton && OnRightClicked.IsBound())
    {
        OnRightClicked.Execute();
        return FReply::Handled();
    }
    else if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && OnClicked.IsBound())
    {
        OnClicked.Execute();
        return FReply::Handled();
    }

    return SButton::OnMouseButtonDown(MyGeometry, MouseEvent);
}