// copyright  D.H.B


#include "player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interface/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	APlayerController::PlayerTick(DeltaTime);
	CursorTrace();
	
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
	inputSubsystem->AddMappingContext(AuraContext,0);


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
	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(Move,ETriggerEvent::Triggered,this,&AAuraPlayerController::InputMove);
	
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

