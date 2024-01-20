// copyright  D.H.B


#include "Charactor/AuraEnemy.h"
#include "Player/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AbilitySystem/AuraAttributeSet.h"

#define CUSTOM_DEPTH_RED 250

AAuraEnemy::AAuraEnemy()
{
    ASC=CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystem"));
    ASC->SetIsReplicated(true);
    ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);    

    AS=CreateDefaultSubobject<UAuraAttributeSet>("AS");
    
}

void AAuraEnemy::BeginPlay()
{
    Super::BeginPlay();

    ASC->InitAbilityActorInfo(this,this);
    InitAttributesByGE();
}

void AAuraEnemy::HighLightActor()
{
   bHightLight=true;

    GetMesh()->SetRenderCustomDepth(true);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    
    Weapon->SetRenderCustomDepth(true);
    Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    
}

void AAuraEnemy::UnHighLightActor()
{
    bHightLight=false;

    GetMesh()->SetRenderCustomDepth(false);
    Weapon->SetRenderCustomDepth(false);
    
}
