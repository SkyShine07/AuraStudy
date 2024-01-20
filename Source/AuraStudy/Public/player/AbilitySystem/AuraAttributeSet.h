// copyright  D.H.B

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * "ShowDebug AbilitySystem "控制台命令查看属性信息
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class AURASTUDY_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();



	/*
	 * 主属性四个：力量，智力，活力，韧性
	 */

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Strength,Category="Primary Attribute")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(ThisClass, Strength);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Intelligence,Category="Primary Attribute")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(ThisClass, Intelligence);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_vigor,Category="Primary Attribute")
	FGameplayAttributeData vigor;
	ATTRIBUTE_ACCESSORS(ThisClass, vigor);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_resilience,Category="Primary Attribute")
	FGameplayAttributeData resilience;
	ATTRIBUTE_ACCESSORS(ThisClass, resilience);
	
	/*
	 * 派生属性：护甲，护甲穿透，格挡几率，暴击几率，暴击伤害，暴击抗性，生命回复，蓝量回复，最大生命值，最大蓝量
	 */

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Armor,Category="Sencondary Attribute")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(ThisClass, Armor);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ArmorPenetration,Category="Sencondary Attribute")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(ThisClass, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_BlockChance,Category="Sencondary Attribute")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(ThisClass, BlockChance);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitChance,Category="Sencondary Attribute")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitChance);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitDamage,Category="Sencondary Attribute")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitResistance,Category="Sencondary Attribute")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HealthRegeneration,Category="Sencondary Attribute")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(ThisClass, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ManaRegeneration,Category="Sencondary Attribute")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(ThisClass, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Sencondary Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Sencondary Attribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);

	//重要属性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="vital Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ThisClass, Health);


	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="vital Attribute")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);


	//对属性进行Clamp

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	
	//注册属性的网络复制属性
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//属性复制的通知函数

	UFUNCTION()
	void OnRep_Strength(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_Intelligence(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_vigor(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_resilience(FGameplayAttributeData& oldValue);

	
	UFUNCTION()
	void OnRep_Armor(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_ArmorPenetration(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_BlockChance(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_CriticalHitChance(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_CriticalHitDamage(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_CriticalHitResistance(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_HealthRegeneration(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_ManaRegeneration(FGameplayAttributeData& oldValue);


	
	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData& oldValue);
	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData& oldValue);


	
};
