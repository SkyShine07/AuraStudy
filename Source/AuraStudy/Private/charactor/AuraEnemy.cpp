// copyright  D.H.B


#include "Charactor/AuraEnemy.h"


#define CUSTOM_DEPTH_RED 250

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
