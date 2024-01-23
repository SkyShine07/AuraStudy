// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DA/DA_CharcrorClassInfo.h"
#include "AuraGameModeBase.generated.h"


class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURASTUDY_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "CharcrorClassInfoClassInfo")
	TObjectPtr<UDA_CharcrorClassInfo> CharactorClassInfo;

public:

	void InitCharactorAttribute(UAbilitySystemComponent* ASC,ECharactorType& Type, int32 Level);
};
