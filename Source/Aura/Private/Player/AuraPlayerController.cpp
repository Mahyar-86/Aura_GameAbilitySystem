// Copyright Mahyar Kazazi.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
    CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (InputLocalPlayerSubsystem)
	{
		InputLocalPlayerSubsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisValue.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisValue.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);
	if (CursorHitResult.bBlockingHit == false) return;

	LastActor = CurrentActor;
	CurrentActor = CursorHitResult.GetActor();

	
	/**
	* Line trace from cursor. There are several scenarios:
	* A. LastActor is null && ThisActor is null
		-Do nothing
	* B. LastActor is null && ThisActor is valid
		-Highlight ThisActor
	*C. LastActor is valid && ThisActor is null
		-UnHighlight LastActor
	* D. Both actors are valid, but LastActor != ThisActor
		-UnHighlight LastActor, and Highlight ThisActor
	* E. Both actors are valid, and are the same actor
		- Do nothing
	*/

    if (LastActor == nullptr && CurrentActor != nullptr)
    {
        CurrentActor->HighlightActor();
    }
    else if (LastActor != nullptr && CurrentActor == nullptr)
    {
        LastActor->UnhighlightActor();
    }
    else if (LastActor != nullptr && CurrentActor != nullptr && LastActor != CurrentActor)
    {
        LastActor->UnhighlightActor();
        CurrentActor->HighlightActor();
    }
}
