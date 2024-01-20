// copyright  D.H.B


#include "Charactor/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{

	GetMovementComponent()->bSnapToPlaneAtStart=true;
	GetMovementComponent()->bConstrainToPlane=true;
	//GetMovementComponent().borient
	
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;

	//ASC=GetPlayerState()
	
}

void AAuraCharacter::InitAbilitySystemActorInfo()
{
	AAuraPlayerState* Ps=GetPlayerState<AAuraPlayerState>();
	check(Ps);
	ASC=Ps->GetAbilitySystemComponent();
	ASC->InitAbilityActorInfo(Ps,this);
	
	AS=Ps->GetAuraAttributeSet();

	InitAttributesByGE();
	
}

int32 AAuraCharacter::GetLevel()
{
	AAuraPlayerState* Ps=GetPlayerState<AAuraPlayerState>();
	check(Ps);
	return Ps->GetLevel();	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemActorInfo();
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilitySystemActorInfo();
	
}
