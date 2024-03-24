// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/ERPlayerCharacter.h"

#include <string>

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ERHUD.h"
#include "InputMappingContext.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Actors/SceneItemsActor.h"
#include "Camera/CameraComponent.h"
#include "Characters/NPC//ERAICharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/PackageComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/EquipUserWidget.h"
#include "UI/MenuUserWidget.h"
#include "UI/PackageUserWidget.h"


#define BINDACTION(NAME,ACTION,FUNCNAME)		if (KeyInfoData->GetRowMap().Contains(NAME))\
			{\
				FKeyInfo* KeyInfo = reinterpret_cast<FKeyInfo*>(KeyInfoData->GetRowMap()[NAME]);\
				EnhancedInputComponent->BindAction(KeyInfo->InputAction,ETriggerEvent::ACTION,this,&AERPlayerCharacter::FUNCNAME);\
			}

AERPlayerCharacter::AERPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	
	bIsKeyboard = true;
	Sensitivity = 30.f;
	LockEnemies.Empty();
}

void AERPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	BindKeys();
	GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->UpdateAdditionAttack();

	if (ExecuteSequence)
	{
		ExecuteSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), ExecuteSequence, FMovieSceneSequencePlaybackSettings(), ExecuteSequenceActor);
	}
}

void AERPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bCanAddEndurance)
	{
		if (CharacterPanel.NowEndurance < CharacterPanel.MaxEndurance)
		{
			CharacterPanel.NowEndurance += AddEnduranceSpeed;
		}
	}
	if (bIsLock)
	{
		GetController()->SetControlRotation(UKismetMathLibrary::FindLookAtRotation(CameraComponent->GetComponentLocation(), LockedEnemy->GetActorLocation()));
	}
}

void AERPlayerCharacter::BindKeys()
{
	if(InputMappingContext)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
			InputMappingContext->UnmapAll();

			AddKeyToImc(TEXT("MoveBack"));
			AddKeyToImc(TEXT("MoveRight"));
			AddKeyToImc(TEXT("MoveLeft"));
			AddKeyToImc(TEXT("UseItem"));
			AddKeyToImc(TEXT("Roll"));
			AddKeyToImc(TEXT("RightLightAttack"));
			AddKeyToImc(TEXT("RightHeavyAttack"));
			AddKeyToImc(TEXT("LeftLightAttack"));
			AddKeyToImc(TEXT("BattleArt"));
			AddKeyToImc(TEXT("Interact"));
			AddKeyToImc(TEXT("Jump"));
			AddKeyToImc(TEXT("MoveForward"));
			AddKeyToImc(TEXT("Look"));
			AddKeyToImc(TEXT("Lock"));
			AddKeyToImc(TEXT("Menu"));
			AddKeyToImc(TEXT("KeyUp"));
			AddKeyToImc(TEXT("KeyLeft"));
			AddKeyToImc(TEXT("KeyRight"));
			AddKeyToImc(TEXT("KeyDown"));
			AddKeyToImc(TEXT("Test"));
			AddKeyToImc(TEXT("BothHand"));
			AddKeyToImc(TEXT("Shift"));
			
			InputLocalPlayerSubsystem->AddMappingContext(InputMappingContext,0);
		}
	}
}

void AERPlayerCharacter::AddKeyToImc(FName InName)
{
	if (KeyInfoData->GetRowMap().Contains(InName))
	{
		FKeyInfo* KeyInfo = reinterpret_cast<FKeyInfo*>(KeyInfoData->GetRowMap()[InName]);
		if (bIsKeyboard)
		{
			InputMappingContext->MapKey(KeyInfo->InputAction,KeyInfo->InputKeyboard);
		}
		else
		{
			InputMappingContext->MapKey(KeyInfo->InputAction,KeyInfo->InputGamepad);
		}
	}
}

void AERPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (KeyInfoData)
		{
			BINDACTION(TEXT("UseItem"),Completed,UseItem)
			BINDACTION(TEXT("Roll"),Canceled,Roll)
			BINDACTION(TEXT("Roll"),Triggered,Run)
			BINDACTION(TEXT("Roll"),Completed,OverRun)
			BINDACTION(TEXT("RightLightAttack"),Started,RightLightAttack)
			BINDACTION(TEXT("RightHeavyAttack"),Canceled,RightHeavyAttack)
			BINDACTION(TEXT("RightHeavyAttack"),Started,ChargeAttack)
			
			BINDACTION(TEXT("LeftLightAttack"),Started,LeftLightAttack)
			BINDACTION(TEXT("BattleArt"),Started,BattleArt)
			BINDACTION(TEXT("Interact"),Started,Interact)
			BINDACTION(TEXT("Jump"),Started,DoJump)
			BINDACTION(TEXT("Look"),Triggered,Look)
			BINDACTION(TEXT("MoveForward"),Triggered,Move)
			BINDACTION(TEXT("MoveBack"),Triggered,Move)
			BINDACTION(TEXT("MoveLeft"),Triggered,Move)
			BINDACTION(TEXT("MoveRight"),Triggered,Move)
			BINDACTION(TEXT("Lock"),Started,LockOn)
			BINDACTION(TEXT("Menu"),Started,OpenMenu)
			BINDACTION(TEXT("KeyUp"),Started,ChangeSpell)
			BINDACTION(TEXT("KeyDown"),Started,ChangeItem)
			BINDACTION(TEXT("KeyLeft"),Started,ChangeLeftWeapon)
			BINDACTION(TEXT("KeyRight"),Started,ChangeRightWeapon)
			BINDACTION(TEXT("Test"),Started,Test)
			BINDACTION(TEXT("BothHand"),Started,RightBothHand)
		}	
	}
}

bool AERPlayerCharacter::IsExecute()
{
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult ExecuteHitResult;
	if (		UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(),
														  GetActorLocation(),
														  GetActorLocation() + GetActorForwardVector() * 80 ,
														  20,
														  ObjectTypes,
														  false,
														  ActorsToIgnore,
														  EDrawDebugTrace::ForDuration,
														  ExecuteHitResult,
														  true))
	{
		if (Cast<AERCharacterBase>( ExecuteHitResult.GetActor()))
		{
			//Start Execute
			ExecuteCharacter =Cast<AERCharacterBase>(ExecuteHitResult.GetActor());
			CancelLock();
			if (ExecuteCharacter->GetCanExecute())
			{
				FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ExecuteCharacter->GetActorLocation());
				if (UKismetMathLibrary::InRange_FloatFloat(Rotator.Yaw, -30.f, 30.f))
				{
					if(BindCharacter(this,ExecuteCharacter, ExecuteSequenceActor ))
					{
						
						ExecuteCharacter->SetActorRotation(GetActorRotation());
						ExecuteCharacter->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 80);
						GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
						ExecuteCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
						if (ExecuteSequencePlayer)
						{
							ExecuteSequencePlayer->Play();
							ExecuteSequencePlayer->OnFinished.AddDynamic(this,&AERPlayerCharacter::OnExecuteFinished);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void AERPlayerCharacter::OnExecuteFinished()
{
	ExecuteSequenceActor->ResetBindings();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ExecuteCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ExecuteSequencePlayer->OnFinished.RemoveDynamic(this,&AERPlayerCharacter::OnExecuteFinished);
	
	ExecuteCharacter = nullptr;
}

void AERPlayerCharacter::Interact()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		EMenuPage MenuPage = HUD->GetCurrentMenuPage();
		switch (MenuPage)
		{
		case EMenuPage::Main:
			if (NearItem)
			{
				PickUpNearItem();
			}
			if (NearNPC)
			{
				TalkWithNPC();
			}
			if (NearActor)
			{
				InterWithActor();
			}
			break;
		case EMenuPage::Tips:
			HUD->HideTips();
			HUD->HidePickUpUI();
			if (NearItem)
			{
				HUD->ShowTips(NSLOCTEXT("HUD","PickUp","拾取"));
			}
			break;
		case EMenuPage::Talk:
			if (NearNPC)
			{
				NearNPC->Talk(NearNPC->GetTalkIndex() + 1);
			}
			break;
		default:
			break;
		}
	}
}

void AERPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Vector = Value.Get<FVector2D>();
	if (GetController())
	{
		InputX = Vector.X;
		InputY = Vector.Y;
		if (bIsRoll)
		{
			return;
		}
		AddMovementInput(FRotator(0,GetControlRotation().Yaw,0).Quaternion().GetForwardVector(),Vector.X);
		AddMovementInput(FRotator(0,GetControlRotation().Yaw,0).Quaternion().GetRightVector(),Vector.Y);
	}
}

void AERPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Vector = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerPitchInput(Vector.Y * -1 * GetWorld()->GetDeltaSeconds() * Sensitivity);
		AddControllerYawInput(Vector.X * GetWorld()->GetDeltaSeconds() * Sensitivity);
	}
}

void AERPlayerCharacter::LockOn()
{
	if (bIsLock)
	{
		CancelLock();
	}
	else
	{
		if (FindLockEnemy())
		{
			LockedEnemy->BeLocked();
			bIsLock = true;
			bUseControllerRotationYaw = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;
		}
		else
		{
			GetController()->SetControlRotation(GetActorRotation());
			if (SelectLockEnemy())
			{
				LockedEnemy->BeLocked();
				bIsLock = true;
				bUseControllerRotationYaw = true;
				GetCharacterMovement()->bOrientRotationToMovement = false;
			}
		}
	}
}

void AERPlayerCharacter::CancelLock()
{
	if (LockedEnemy)
	{
		LockedEnemy->CancelLocked();
		LockedEnemy = nullptr;
	}
	bIsLock = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
}

bool AERPlayerCharacter::FindLockEnemy()
{
	LockedEnemy = nullptr;
	LockEnemies.Empty();
	EnemyRotationMap.Empty();
	LockRotation.Empty();
	TArray<TEnumAsByte<EObjectTypeQuery>> Objects;
	Objects.Add(ObjectTypeQuery3);
	TArray<AActor*>ActorsToIgnore;
	ActorsToIgnore.Add(this);
	TArray<FHitResult>OutHits;
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation(),
		750.f,
		Objects,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHits,
		true))
	{
		for (auto Key:OutHits)
		{
			if (Cast<AERCharacterBase>(Key.GetActor()))
			{
				LockEnemies.AddUnique(Cast<AERCharacterBase>(Key.GetActor()));
			}
		}
		if (LockEnemies.IsEmpty())
		{
			return false;
		}
		return SelectLockEnemy();		
	}
	return false;
}

bool AERPlayerCharacter::SelectLockEnemy()
{
	for (auto key:LockEnemies)
	{
		TArray<AActor* >ActorsToIgnore;
		ActorsToIgnore.Add(this);
		FHitResult LineHitResult;
		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), CameraComponent->GetComponentLocation(), key->GetActorLocation(), TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, LineHitResult, true))
		{
			if (LineHitResult.GetActor() != key)
			{
				UKismetSystemLibrary::PrintString(GetWorld(), LineHitResult.GetActor()->GetName());
				LockEnemies.Remove(key);
				break;
			}
		}
		int32 Rotation = UKismetMathLibrary::Abs(UKismetMathLibrary::FindLookAtRotation(CameraComponent->GetComponentLocation(),GetMesh()->GetComponentLocation()).Yaw - UKismetMathLibrary::FindLookAtRotation(CameraComponent->GetComponentLocation(), key->GetActorLocation()).Yaw);
		EnemyRotationMap.Add(Rotation, key);
		LockRotation.Add(Rotation);
	}
	if (EnemyRotationMap.IsEmpty())
	{
		return false;
	}
	int32 Min;
	float MinNum;
	UKismetMathLibrary::MinOfFloatArray(LockRotation, Min, MinNum);
	if (UKismetMathLibrary::InRange_FloatFloat(MinNum, 0.f, 60.f))
	{
		LockedEnemy = EnemyRotationMap[MinNum];
	}
	return true;
}

void AERPlayerCharacter::OpenMenu()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		EMenuPage MenuPage = HUD->GetCurrentMenuPage();
		switch (MenuPage)
		{
		case EMenuPage::Menu:
			HUD->ToggleMenu();
			break;
		case EMenuPage::Main:
			HUD->ToggleMenu();
			break;
		case EMenuPage::Equip:
			HUD->GetMenuUserWidget()->GetEquipWidget()->RemoveFromParent();
			HUD->ShowMenu();
			break;
		case EMenuPage::ChooseItem:
			HUD->GetMenuUserWidget()->GetEquipWidget()->CloseItemWidget();
			break;
		case EMenuPage::Package:
			HUD->GetMenuUserWidget()->GetPackageWidget()->RemoveFromParent();
			HUD->ShowMenu();
			break;
		case EMenuPage::Tips:
			break;
		default:
			
			break;
		}
	}
}

void AERPlayerCharacter::PickUpNearItem()
{
	if (PackageComponent)
	{
		if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
		{
			PackageComponent->AddItemToPackage(NearItem->GetID(),NearItem->GetNum());
            HUD->ShowPickUpUI(NearItem->GetID(), NearItem->GetNum());
            NearItem->Destroy();
			NearItem = nullptr;
		}
	}
}

void AERPlayerCharacter::TalkWithNPC()
{
	
	NearNPC->Talk(0);
}

void AERPlayerCharacter::InterWithActor()
{
	
}

void AERPlayerCharacter::Test()
{
	if (PackageComponent)
	{
		PackageComponent->EquipRightWeapon(100);
	}
}

void AERPlayerCharacter::RightLightAttack()
{
	if (GetCharacterState() == ECharacterState::Normal)
	{
		if (IsExecute())
		{
			return;
		}
		Super::RightLightAttack();
	}
}

#undef BINDACTION






