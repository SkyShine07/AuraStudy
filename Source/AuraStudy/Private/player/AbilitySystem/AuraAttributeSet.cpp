// copyright  D.H.B


#include "player/AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AuraEffectContext/AuraEffectContext.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "Net/UnrealNetwork.h"
#include "player/AuraPlayerController.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
		//Clamp属性的查询值
	if (Attribute==GetHealthAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0,GetMaxHealth());
	}

	if (Attribute==GetManaAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0,GetMaxMana());
	}
	
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//  #include "GameplayEffectExtension.h"

	if (Data.EvaluatedData.Attribute==GetIncomingDamageAttribute())
	{
		//---TODO:处理伤害值传入的情况（Damage不复制，GESpec根据ASC的网络复制模式（Minal，Mix，Full）执行在服务器，Damage在服务器端变化）
		float LocalDamage=GetIncomingDamage();
		SetIncomingDamage(0);
		SetHealth(FMath::Clamp(GetHealth()-LocalDamage,0,GetMaxHealth()));

		//TODO:显示伤害值
		ACharacter* Character=Cast<ACharacter>(Data.EffectSpec.GetContext().GetSourceObject());
		if(Character&&Character->Controller)
		{
			AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(Character->Controller);
		
			if (AuraPlayerController)
			{
				FAuraEffectContext* AuraEffectContext= static_cast<FAuraEffectContext*>(Data.EffectSpec.GetContext().Get());
				if (AuraEffectContext)
				{
					AuraPlayerController->Client_ShowDamageText(LocalDamage,Data.Target.GetAvatarActor(),
															AuraEffectContext->GetIsCritial(),AuraEffectContext->GetIsBlock());
				}
				
			}
		}
		
		if (GetHealth()<=0.f)
		{
		//TODO:死亡
			
			ICombatInterface* CombatInterface=Cast<ICombatInterface>(Data.Target.GetAvatarActor());
			
			if (!CombatInterface) return ;
		
			CombatInterface->Die();
			
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,
						FString::Printf(TEXT( "%s Has Death"),*Data.Target.GetAvatarActor()->GetName()));
			return ;
		}
		//TODO:伤害效果

		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Effect.HitReact")));
		Data.Target.TryActivateAbilitiesByTag(TagContainer);
	
		
		
	}
	if (Data.EvaluatedData.Attribute==GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0,GetMaxHealth()));

		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,
						FString::Printf(TEXT( "%s of helath: %f"),
							*Data.Target.GetAvatarActor()->GetName(),GetHealth()));
		
	}

	if (Data.EvaluatedData.Attribute==GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(),0,GetMaxMana()));
	}
	
	
	
}



void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Strength,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Intelligence,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,vigor,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,resilience,COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ArmorPenetration,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitChance,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitDamage,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,BlockChance,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitResistance,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,HealthRegeneration,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ManaRegeneration,COND_None, REPNOTIFY_Always);

	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None, REPNOTIFY_Always);

	
	
}

void UAuraAttributeSet::OnRep_Strength(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Strength, oldValue);
}

void UAuraAttributeSet::OnRep_Intelligence(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Intelligence, oldValue);
}

void UAuraAttributeSet::OnRep_vigor(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,vigor, oldValue);
}

void UAuraAttributeSet::OnRep_resilience(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,resilience, oldValue);
}

//----------------------------------------
void UAuraAttributeSet::OnRep_Armor(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Armor, oldValue);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,ArmorPenetration, oldValue);
}

void UAuraAttributeSet::OnRep_BlockChance(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,BlockChance, oldValue);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,CriticalHitChance, oldValue);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,CriticalHitDamage, oldValue);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,CriticalHitResistance, oldValue);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,HealthRegeneration, oldValue);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,ManaRegeneration, oldValue);
}

//--------------------------------
void UAuraAttributeSet::OnRep_Health(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Health, oldValue);
	
}


void UAuraAttributeSet::OnRep_MaxHealth(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,MaxHealth, oldValue);
}

void UAuraAttributeSet::OnRep_Mana(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Mana, oldValue);
}

void UAuraAttributeSet::OnRep_MaxMana(FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,MaxMana, oldValue);
}
