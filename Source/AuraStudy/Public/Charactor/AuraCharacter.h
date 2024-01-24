// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "Charactor/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURASTUDY_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	void InitAbilitySystemActorInfo();
/*
 * begin CombatInterface 
 */

	
	/*
	 * End  CombatInterface 
	 */
	
	//初始化ASC
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
};
