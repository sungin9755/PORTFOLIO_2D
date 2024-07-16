// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerZDCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

APlayerZDCharacter::APlayerZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->TargetArmLength = 600.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	//static ConstructorHelpers::FObjectFinder<UInputMappingContext> DEFAULT_CONTEXT(TEXT("/Game/InputAction/IMC_Default.IMC_Default"));
	//if (DEFAULT_CONTEXT.Succeeded()) DefaultContext = DEFAULT_CONTEXT.Object;

	//static ConstructorHelpers::FObjectFinder<UInputAction> IA_Move(TEXT("/Game/InputAction/IA_Move.IA_Move"));
	//if (IA_Move.Succeeded()) MoveAction = IA_Move.Object;

}

void APlayerZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	//if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	//{
	//	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	{
	//		SubSystem->AddMappingContext(DefaultContext, 0);
	//	}
	//}
}

void APlayerZDCharacter::Tick(float DeltaTime)
{
}

//void APlayerZDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	//Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
//	//{
//	//	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerZDCharacter::Move);
//	//}
//}

//void APlayerZDCharacter::Move(const FInputActionInstance& Instance)
//{
//	//FVector2D InputValue = Instance.GetValue().Get<FVector2D>();
//}

