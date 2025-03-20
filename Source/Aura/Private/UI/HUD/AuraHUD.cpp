// Copyright Mahyar Kazazi.


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	AddOverlayWidget();
}

void AAuraHUD::AddOverlayWidget() const
{
	const TObjectPtr<UUserWidget> CreatedWidget = CreateWidget(GetWorld(), OverlayWidgetClass);
	CreatedWidget->AddToViewport();
}
 