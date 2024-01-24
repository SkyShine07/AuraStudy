// copyright  D.H.B


#include "player/AbilitySystem/Abillities/ProjectileSpellAbility.h"

#include "Actor/AuraProjectile.h"
#include "Interface/CombatInterface.h"
#include "Kismet/KismetMathLibrary.h"

void UProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}

AAuraProjectile*  UProjectileSpellAbility::SpawnProjectile(FVector TargetLocation)
{
	if (!GetAvatarActorFromActorInfo()) return nullptr;

	if(!GetAvatarActorFromActorInfo()->HasAuthority()) return nullptr;

	FTransform  Transform;

	//Todo:1,设置发射物的生成位置和旋转（朝向）
	ICombatInterface* Combator=Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (Combator)
	{
		Transform.SetLocation(Combator->GetProjectileLocation());
	}

	FRotator  Rotator =UKismetMathLibrary::FindLookAtRotation(Transform.GetLocation(),TargetLocation);
	Rotator.Pitch=0;
	Transform.SetRotation(UE::Math::TQuat<double>(Rotator));
	
	AAuraProjectile* Projectile=GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,Transform,
					GetOwningActorFromActorInfo(),
					Cast<APawn>(GetOwningActorFromActorInfo()),
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//TODO:Add Ge for Cause Damage(添加伤害用的GE)
	

	
	Projectile->FinishSpawning(Transform);

	
	Projectile->SetOwner(GetAvatarActorFromActorInfo());
	
	return Projectile;
}
