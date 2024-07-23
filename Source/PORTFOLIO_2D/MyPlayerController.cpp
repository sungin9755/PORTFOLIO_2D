// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include <Kismet/KismetMathLibrary.h>

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
}
//
//void AMyPlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//
//	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
//	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
//}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//LookMouseCursor();
}

//void AMyPlayerController::MoveForward(float AxisValue)
//{
//	APawn* const MyPawn = GetPawn();
//
//	if (MyPawn)
//	{
//		FVector Direction = FVector::ForwardVector;
//		MyPawn->AddMovementInput(Direction, AxisValue);
//	}
//}
//
//void AMyPlayerController::MoveRight(float AxisValue)
//{
//	APawn* const MyPawn = GetPawn();
//	if (MyPawn)
//	{
//		FVector Direction = FVector::RightVector;
//		MyPawn->AddMovementInput(Direction, AxisValue);
//	}
//}

//void AMyPlayerController::LookMouseCursor()
//{
	//FHitResult Hit;
	//GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	//if (Hit.bBlockingHit)
	//{
	//	APawn* const MyPawn = GetPawn();
	//	if (MyPawn)
	//	{
	//		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), FVector(Hit.Location.X, Hit.Location.Y, MyPawn->GetActorLocation().Z));
	//		MyPawn->SetActorRotation(LookRotation);
	//	}
	//}
//}

