// Copyright Mahyar Kazazi.


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"


AAuraCharacter::AAuraCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Character movement component default settings
	GetCharacterMovement()->bOrientRotationToMovement= true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
}
