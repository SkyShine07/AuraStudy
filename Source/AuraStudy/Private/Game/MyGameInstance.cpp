// copyright  D.H.B


#include "Game/MyGameInstance.h"
#include	"AbilitySystemGlobals.h"


void UMyGameInstance::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UAbilitySystemGlobals::Get().InitGlobalData();
}
