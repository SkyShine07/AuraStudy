// copyright  D.H.B

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "DA/DA_CharcrorClassInfo.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


//角色的抽象基类，玩家控制角色和AI派生于此

class UGameplayAbility;
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

	virtual int32 GetLevel() override {return level;};

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	float level=1;
	
	virtual FVector GetProjectileLocation() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	FName WeaponProjectileSocket;
protected:
	
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> ASC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAuraAttributeSet> AS;


	//--初始GA

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;

	
	//---初始化属性
	void InitAttributesByGE();
	
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS")
	ECharactorType CharactorType;
	
};
