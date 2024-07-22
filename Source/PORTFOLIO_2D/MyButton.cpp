// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"
#include "MyArmory_ButtonArrays.h"
#include "SMyButton.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"

UMyButton::UMyButton()
{
    OnClicked.AddDynamic(this, &UMyButton::HandleOnClicked);
}

void UMyButton::SynchronizeProperties()
{
    Super::SynchronizeProperties();
}

void UMyButton::HandleOnClicked()
{
    if (ParentWidget)
    {
        ParentWidget->OnButtonClick(ButtonIndex);
    }
}

void UMyButton::HandleOnRightClicked()
{
    if (ParentWidget)
    {
        ParentWidget->OnRightButtonClick(ButtonIndex);
    }
}

TSharedRef<SWidget> UMyButton::RebuildWidget()
{
    MySlateButton = SNew(SMyButton)
        .ButtonImagePath(ButtonImagePath)
        .ButtonStyle(&WidgetStyle)  // 블루프린트에서 정의된 스타일 사용
        .OnClicked(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnClicked))
        .OnRightClicked(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnRightClicked));

    return MySlateButton.ToSharedRef();
}

void UMyButton::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);
    MySlateButton.Reset();
}
