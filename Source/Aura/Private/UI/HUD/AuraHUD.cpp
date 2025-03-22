// Copyright Mahyar Kazazi.


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

TObjectPtr<UOverlayWidgetController> AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);

		return OverlayWidgetController;
	}
	
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(TObjectPtr<APlayerController> PC, TObjectPtr<APlayerState> PS, TObjectPtr<UAbilitySystemComponent> ASC, TObjectPtr<UAttributeSet> AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not initialized, please set it in BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not initialized, please set it in BP_AuraHUD"));
	
	OverlayWidget = Cast<UAuraUserWidget>(CreateWidget(GetWorld(), OverlayWidgetClass));

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	TObjectPtr<UOverlayWidgetController> WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	OverlayWidget->AddToViewport();
}
 