// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC//ERAICharacterBase.h"

#include "ERHUD.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/NPC//ERAIController.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/PackageComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/HPWidget.h"
#include "UI/Widgets/TalkWidget.h"

AERAICharacterBase::AERAICharacterBase()
{
	HPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPComp"));
	HPWidget->SetupAttachment(RootComponent);
	HPWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HPWidget->SetDrawSize(FVector2D(100,10));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	Box->SetupAttachment(RootComponent);
	
	AIControllerClass = AERAIController::StaticClass();
	HitIndex = 3;
}




void AERAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this,&AERAICharacterBase::OnBoxBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this,&AERAICharacterBase::OnBoxEndOverlap);
	
	if (!HPBar)
	{
		TSubclassOf<UHPWidget> HPClass = LoadClass<UHPWidget>(this,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_HP.WBP_HP_C'"));
		HPBar = CreateWidget<UHPWidget>(GetWorld(),HPClass);
	}
	HPWidget->SetWidget(HPBar);
	//HPBar->SetOwner(this);
}

float AERAICharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (CurrentAIState != EAIState::NPC)
	{
		if(CharacterPanel.NowHP / CharacterPanel.MaxHP <= 0.5)
		{
			ChangeToEnemy();
		}
		HitIndex --;
		if (HitIndex == 0)
		{
			ChangeToEnemy();
		}
	}
	if (HitSound)
	{
		FHitResult HitResult;
		FVector Impulse;
		DamageEvent.GetBestHitInfo(this,DamageCauser,HitResult,Impulse);
		UGameplayStatics::PlaySoundAtLocation(this,HitSound,HitResult.Location,GetActorRotation());
	}
	
	//HPBar->SetPercent();
	return 0;
}

void AERAICharacterBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CurrentAIState == EAIState::Enemy)
	{
		return;
	}
	if (AERPlayerCharacter* Player = Cast<AERPlayerCharacter>(OtherActor))
	{
		if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
		{
			HUD->ShowTips(NSLOCTEXT("HUD","PickUp","交谈"));
		}
		Player->SetNearNPC(this);
	}
}

void AERAICharacterBase::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (CurrentAIState == EAIState::Enemy)
	{
		return;
	}
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(OtherActor))
	{
		if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
		{
			if (HUD->GetCurrentMenuPage() == EMenuPage::Main)
			{
				HUD->HideTips();
				PlayerCharacter->SetNearNPC(nullptr);
			}
		}
	}
}

void AERAICharacterBase::EquipPackage()
{
	UDataTable* NPCInfo = LoadObject<UDataTable>(this,TEXT("/Script/Engine.DataTable'/Game/FakeER/Data/NPCInfo/DT_NPC.DT_NPC'"));
	if (NPCInfo->GetRowMap().Contains(NPCID))
	{
		TArray<int32>* LeftWeapon = reinterpret_cast<TArray<int32>*>(NPCInfo->GetRowMap()[NPCID]);
		if (PackageComponent)
		{
			PackageComponent->EquipLeftWeapon((*LeftWeapon)[0]);
		}
	}
}

void AERAICharacterBase::ChangeToEnemy()
{
	CurrentAIState = EAIState::Enemy;
	if (AERAIController* ERAIControll = Cast<AERAIController>(GetController()))
	{
		ERAIControll->GetBlackboardComponent()->SetValueAsBool(TEXT("IsNPC"),false);
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


void AERAICharacterBase::Talk(int32 Index)
{
	if (!TalkWidget)
	{
		TSubclassOf<UTalkWidget> TalkClass = LoadClass<UTalkWidget>(this,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_Talk.WBP_Talk_C'"));
		TalkWidget = CreateWidget<UTalkWidget>(GetWorld(),TalkClass);
	}
	if (TalkWidget && !TalkWidget->IsInViewport())
	{
		TalkWidget->AddToViewport();
	}
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if (HUD->GetCurrentMenuPage() == EMenuPage::Main)
		{
			if (CurrentAIState == EAIState::Businessman || CurrentAIState == EAIState::NPC)
			{
				NormalTalk(Index);
			}
			if (CurrentAIState == EAIState::Enemy)
			{
				BattleTalk(Index);
			}
		}
		if (HUD->GetCurrentMenuPage() == EMenuPage::Shop)
		{
			if (CurrentAIState == EAIState::Businessman)
			{
				ShopTalk(Index);
			}
		}
		if (HUD->GetCurrentMenuPage() == EMenuPage::Talk)
		{
			if (CurrentAIState == EAIState::Businessman || CurrentAIState == EAIState::NPC)
			{
				NormalTalk(Index + 1);
			}
			if (CurrentAIState == EAIState::Enemy)
			{
				BattleTalk(Index + 1);
			}
		}
	}
}

void AERAICharacterBase::BattleTalk(int32 Index)
{	
	UDataTable* NPCInfo = LoadObject<UDataTable>(this,TEXT("/Script/Engine.DataTable'/Game/FakeER/Data/NPCInfo/DT_NPC.DT_NPC'"));
	if (NPCInfo->GetRowMap().Contains(NPCID))
	{
		if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
		{
            TArray<FText>* BattleTalk = reinterpret_cast<TArray<FText>*>(NPCInfo->GetRowMap()[NPCID]);
            TArray<FText> BattleWords = *BattleTalk;
			if (Index >= BattleWords.Num())
			{
				TalkWidget->RemoveFromParent();
				HUD->SetCurrentMenuPage(EMenuPage::Main);
			}
			else
			{
				TalkWidget->Init(BattleWords[Index]);
				HUD->SetCurrentMenuPage(EMenuPage::Talk);
			}
		}
	}
}

void AERAICharacterBase::ShopTalk(int32 Index)
{
	
}

void AERAICharacterBase::NormalTalk(int32 Index)
{
	
}

