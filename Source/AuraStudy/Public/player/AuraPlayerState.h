// copyright  D.H.B

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interface/CombatInterface.h"
#include "AuraPlayerState.generated.h"

class UAuraAttributeSet;
/**
 * 
 */
UCLASS()
class AURASTUDY_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//---接口
	
	virtual int32 GetLevel() override {return Level;} ;


	
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAuraAttributeSet* GetAuraAttributeSet() const{return AS;};	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UAuraAttributeSet> AS;

protected:

	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_Level, Category = "GAS")
	int32 Level=1;

	UFUNCTION()
	void OnRep_Level();
	
};
