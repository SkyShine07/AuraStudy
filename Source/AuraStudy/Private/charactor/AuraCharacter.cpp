// copyright  D.H.B


#include "Charactor/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "player/AuraPlayerState.h"
#include "player/AbilitySystem/AuraAbilitySystemComponent.h"

AAuraCharacter::AAuraCharacter()
{

	GetMovementComponent()->bSnapToPlaneAtStart=true;
	GetMovementComponent()->bConstrainToPlane=true;
	//GetMovementComponent().borient
	
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;

	CharactorType=ECharactorType::Elementalist;
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



void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemActorInfo();

	UAuraAbilitySystemComponent* AuraAsc=Cast<UAuraAbilitySystemComponent>(ASC);
	AuraAsc->AddAbilities(StartUpAbilities);
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilitySystemActorInfo();


}
