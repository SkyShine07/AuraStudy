// copyright  D.H.B


#include "player/AuraPlayerController.h"
#include "player/AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Algo/ForEach.h"
#include "Components/SplineComponent.h"
#include "Input/InputData.h"
#include "Interface/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;

	PathSpline=CreateDefaultSubobject<USplineComponent>(TEXT("PathSpline"));
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	APlayerController::PlayerTick(DeltaTime);
	CursorTrace();
	//AutoRun();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);
	if (!HitResult.bBlockingHit) return;

	
	if (CurrentActor)
	{
		LastActor=CurrentActor;
	}
	
	CurrentActor=Cast<IEnemyInterface>(HitResult.GetActor());
	
	//关闭上个高亮，开启当前的高亮
	if (LastActor==CurrentActor)
	{
		return;
	}
	if (CurrentActor)
	{
		CurrentActor->HighLightActor();
		if (LastActor)
		{
			LastActor->UnHighLightActor();
		}
		
	}
	
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//添加输入配置
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* inputSubsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	check(inputSubsystem);
	if (inputSubsystem)
	{
		inputSubsystem->AddMappingContext(AuraContext,0);
	}
	


	//输入模式设置
	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	
	SetInputMode(InputModeData);



}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	//绑定输入行为的函数
	 EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(Move,ETriggerEvent::Triggered,this,&AAuraPlayerController::InputMove);

	BindAction();
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRun) return ;

	FVector location=PathSpline->FindLocationClosestToWorldLocation(GetPawn()->GetActorLocation(),ESplineCoordinateSpace::World);
	FVector Direction=PathSpline->FindDirectionClosestToWorldLocation(location,ESplineCoordinateSpace::World);

	GetPawn()->AddMovementInput(Direction);
	float distance=FVector::Distance(location,CachedDestination);
	if (distance<=AcceptDistance)
	{
		bAutoRun=false;
	}
}

void AAuraPlayerController::InputMove(const FInputActionValue& value)
{
	//添加受控pawn的移动功能
	FVector2d InputValue=value.Get<FVector2d>();
	FRotator ControllerRotator=GetControlRotation();
	
	FVector ForwardDirection=FRotationMatrix(FRotator(0,ControllerRotator.Yaw,0)).GetUnitAxis(EAxis::X);	
	FVector RightDirection=FRotationMatrix(FRotator(0,ControllerRotator.Yaw,0)).GetUnitAxis(EAxis::Y);

	if (APawn* ControllPawn=GetPawn())
	{
		ControllPawn->AddMovementInput(ForwardDirection,InputValue.X);
		ControllPawn->AddMovementInput(RightDirection,InputValue.Y);		
	}
	

}

void AAuraPlayerController::BindAction()
{
	for (auto Element : InputData.Get()->InputDatas)
	{
		if (Element.InputAction)
		{
			EnhancedInputComponent->BindAction(Element.InputAction,ETriggerEvent::Triggered,this,&ThisClass::OnInputTagHeld,Element.Tag);		

			EnhancedInputComponent->BindAction(Element.InputAction,ETriggerEvent::Started,this,&ThisClass::OnInputTagPressed,Element.Tag);		
			EnhancedInputComponent->BindAction(Element.InputAction,ETriggerEvent::Completed,this,&ThisClass::OnInputTagRealse,Element.Tag);		

		}
	}
}

void AAuraPlayerController::OnInputTagPressed(FGameplayTag Tag)
{
	GetASC()->OnInputPressed(Tag);

	bTargeting=CurrentActor?true:false;
	
	//GEngine->AddOnScreenDebugMessage(-1,3,FColor::Cyan,Tag.ToString());
}

void AAuraPlayerController::OnInputTagRealse(FGameplayTag Tag)
{

	if (!Tag.MatchesTagExact(FGameplayTag::RequestGameplayTag("InputTag.LMB")))
	{
		GetASC()->OnInputRelease(Tag);
		return ;
	}
	if (bTargeting)
	{
		GetASC()->OnInputRelease(Tag);
		return ;
	}
	
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility,false,HitResult)&&GetPawn())
	{
		CachedDestination=HitResult.ImpactPoint;

		if (FollowTime<=ShortPressthreShould)
		{
			bAutoRun=true;

			UNavigationPath* path=UNavigationSystemV1::FindPathToLocationSynchronously(this,
				GetPawn()->GetActorLocation(),CachedDestination);
			if (path)
			{
				PathSpline->ClearSplinePoints();
				for (auto Point : path->PathPoints)
				{
					PathSpline->AddSplinePoint(Point,ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(),Point,10,10,FColor::Green);
				}

				
				
			}
			
		}
		
		
	
		
	}
	
	FollowTime=0;
	bTargeting=false;
	
	//GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,Tag.ToString());
}

void AAuraPlayerController::OnInputTagHeld(FGameplayTag Tag)
{
	

	if (!Tag.MatchesTagExact(FGameplayTag::RequestGameplayTag("InputTag.LMB")))
	{
		GetASC()->OnInputHeld(Tag);
		return ;
	}
	if (bTargeting)
	{
		GetASC()->OnInputHeld(Tag);
		return ;
	}

	FollowTime+=GetWorld()->GetDeltaSeconds();
	
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility,false,HitResult)&&GetPawn())
	{
		CachedDestination=HitResult.ImpactPoint;
		FVector3d MoveDirection=(CachedDestination-GetPawn()->GetActorLocation()).GetSafeNormal();

		
		GetPawn()->AddMovementInput(MoveDirection,1.0f);
	
		
	}
	
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (!ASC)
	{
		ASC=Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return ASC;
}

