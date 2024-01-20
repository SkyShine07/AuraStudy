// copyright  D.H.B


#include "UI/Widget/AuraUserWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Player/AbilitySystem/AuraAbilitySystemComponent.h"

bool UAuraUserWidget::Initialize()
{
	bool bSuccess=Super::Initialize();

	ASC=Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn()));

	return bSuccess;
	
}
