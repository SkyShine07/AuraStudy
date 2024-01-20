// copyright  D.H.B


#include "player/AuraPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Player/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AbilitySystem/AuraAttributeSet.h"


AAuraPlayerState::AAuraPlayerState()
{
    //提高网络更新频率
    NetUpdateFrequency=100.f;

    ASC=CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystem"));
    ASC->SetIsReplicated(true);
    ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    
    AS=CreateDefaultSubobject<UAuraAttributeSet>("AS");

    
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass,Level);
    
}

void AAuraPlayerState::OnRep_Level()
{
    
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
    return ASC;
}
