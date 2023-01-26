// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthPotion.h"
#include "ActionRogueLike/ActionRogueLikeGameModeBase.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "AIArenaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AAIArenaGameMode : public AActionRogueLikeGameModeBase
{
public:
	GENERATED_BODY()
	virtual void StartPlay() override;
	UFUNCTION()
	void SpawnEnemy(class UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	UFUNCTION()
	void TrySpawnEnemy();
	UFUNCTION()
	void EnemyKilled(class AMyAICharacter* Enemy, AActor* Killer);
	UFUNCTION()
	void TrySpawnHealthPotion();
	UFUNCTION()
	void SpawnHealthPotion(class UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	virtual void RestartPlayer(AController* NewPlayer) override;
	UFUNCTION()
	void PlayerDied(class AMyCharacter* PlayerCharacter, AActor* Killer);
	UFUNCTION()
	void RespawnPlayer(APlayerController* Player);
protected:
	FTimerHandle SpawnHealthPotionTimerHandle;
	UPROPERTY(EditDefaultsOnly)
	float SpawnHealthPotionInterval;
	UPROPERTY(EditDefaultsOnly)
	class UEnvQuery* SpawnHealthPotionEQS;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHealthPotion> HealthPotionClass;
	FTimerHandle SpawnEnemyTimerHandle;
	UPROPERTY(EditDefaultsOnly)
	class UEnvQuery* SpawnAIEQS;
	UPROPERTY(EditDefaultsOnly)
	class UCurveFloat* EnemyMaxNumCurve;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMyAICharacter> EnemyAIClass;
	UPROPERTY()
	TArray<AMyAICharacter*> EnemyCollection;
	UPROPERTY(EditDefaultsOnly)
	float PlayerRespawnTime;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainHUDClass;
};
