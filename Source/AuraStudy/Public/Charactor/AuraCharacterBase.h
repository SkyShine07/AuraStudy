// copyright  D.H.B

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


//角色的抽象基类，玩家控制角色和AI派生于此

class UGameplayEffect;
class UAuraAttributeSet;
class UAuraAbilitySystemComponent;
UCLASS(Abstract)

class AURASTUDY_API AAuraCharacterBase : public ACharacter,public  IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	
	AAuraCharacterBase();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAuraAttributeSet* GetAuraAttributeSet() const{return AS;};

	virtual int32 GetLevel() override {return 1;};
	
protected:
	
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> ASC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAuraAttributeSet> AS;


	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS")
	TSubclassOf<UGameplayEffect> GE_DefaultPrimaryAttribute;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS")
	TSubclassOf<UGameplayEffect> GE_DefaultSencondaryAttribute;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS")
	TSubclassOf<UGameplayEffect> GE_DefaultVitalAttribute;
//---初始化属性
	void InitAttributesByGE();
	
};
