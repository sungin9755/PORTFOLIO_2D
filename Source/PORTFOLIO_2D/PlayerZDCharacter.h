// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "PlayerZDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_2D_API APlayerZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
public:
	APlayerZDCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;

private:
//	UPROPERTY(VisibleAnywhere, Category = Input)
//		class UInputMappingContext* DefaultContext;
//
//	UPROPERTY(VisibleAnywhere, Category = Input)
//		class UInputAction* MoveAction;
//
//protected:
//	void Move(const const FInputActionInstance& Instance);
};
