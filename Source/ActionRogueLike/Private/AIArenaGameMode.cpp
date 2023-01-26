// Fill out your copyright notice in the Description page of Project Settings.


#include "AIArenaGameMode.h"

#include "MyCharacter.h"
#include "AI/MyAICharacter.h"
#include "Blueprint/UserWidget.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"

void AAIArenaGameMode::StartPlay()
{
	Super::StartPlay();
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(SpawnEnemyTimerHandle, this, &AAIArenaGameMode::TrySpawnEnemy, 5.0f, true);
	TimerManager.SetTimer(SpawnHealthPotionTimerHandle, this, &AAIArenaGameMode::TrySpawnHealthPotion, SpawnHealthPotionInterval, true);

	UUserWidget* MainHUD = CreateWidget<UUserWidget>(GetWorld(), MainHUDClass);
	MainHUD->AddToViewport();
}

void AAIArenaGameMode::SpawnEnemy(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}
	TArray<FVector> SpawnPoints = QueryInstance->GetResultsAsLocations();
	if(!SpawnPoints.IsEmpty())
	{
		FActorSpawnParameters SpawnParameters;

		AMyAICharacter* Enemy = GetWorld()->SpawnActor<AMyAICharacter>(EnemyAIClass, SpawnPoints[0], FRotator::ZeroRotator);
		EnemyCollection.Add(Enemy);
		Enemy->OnAICharacterDie.AddDynamic(this, &AAIArenaGameMode::EnemyKilled);
	}
}

void AAIArenaGameMode::TrySpawnEnemy()
{
	int EnemyNum = EnemyCollection.Num();
	int MaxEnemyNum = EnemyMaxNumCurve->GetFloatValue(UGameplayStatics::GetTimeSeconds(this));
	if(EnemyNum >= MaxEnemyNum)
	{
		return;
	}
	
	UEnvQueryInstanceBlueprintWrapper* EQSInstance= UEnvQueryManager::RunEQSQuery(this, SpawnAIEQS, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);
	EQSInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AAIArenaGameMode::SpawnEnemy);
}

void AAIArenaGameMode::EnemyKilled(AMyAICharacter* Enemy, AActor* Killer)
{
	EnemyCollection.RemoveSwap(Enemy);
}

void AAIArenaGameMode::TrySpawnHealthPotion()
{
	UEnvQueryInstanceBlueprintWrapper* EQSInstance = UEnvQueryManager::RunEQSQuery(this, SpawnHealthPotionEQS, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);
	EQSInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AAIArenaGameMode::SpawnHealthPotion);
}

void AAIArenaGameMode::SpawnHealthPotion(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus == EEnvQueryStatus::Success)
	{
		TArray<FVector> SpawnLocations;
		if(QueryInstance->GetQueryResultsAsLocations(SpawnLocations))
		{
			GetWorld()->SpawnActor<AHealthPotion>(HealthPotionClass, SpawnLocations[0] + FVector(0, 0, 20), FRotator::ZeroRotator);
		}
	}
}

void AAIArenaGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

	if(NewPlayer)
	{
		AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(NewPlayer->GetPawn());
		if(PlayerCharacter)
		{
			PlayerCharacter->OnCharacterDie.AddDynamic(this, &AAIArenaGameMode::PlayerDied);
		}
	}
}

void AAIArenaGameMode::PlayerDied(AMyCharacter* PlayerCharacter, AActor* Killer)
{
	APlayerController* Player = Cast<APlayerController>(PlayerCharacter->GetController());
	if(Player == nullptr)
	{
		return;
	}
	FTimerHandle RespawnTimerHandle;
	FTimerDelegate RespawnTimerDelegate;
	RespawnTimerDelegate.BindUFunction(this, "RespawnPlayer", Player);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnTimerDelegate, PlayerRespawnTime, false);
}

void AAIArenaGameMode::RespawnPlayer(APlayerController* Player)
{
	if(ensure(Player))
	{
		Player->UnPossess();
		EnableInput(Player);
		RestartPlayer(Player);
	}
}
