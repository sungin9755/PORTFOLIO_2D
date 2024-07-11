// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DNinputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_2D_API UDNinputConfigData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefualtsOnly, BlueprintReadOnly)
		UInputAction* InputMove;
};
