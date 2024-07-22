// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyArmory_ButtonArrays.h"
#include "ArmorySaveData.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_2D_API UArmorySaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FUpgradeData> UpgradeDataArray;
};
