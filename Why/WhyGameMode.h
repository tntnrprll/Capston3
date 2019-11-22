// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WhyPlayerController.h"
#include "WhyPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/GameMode.h"
#include "Blueprint/UserWidget.h"
#include "WhyPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "ColorBox.h"
#include "WhyHUD.h"
#include "WhyPlayerState.h"
#include "WhyGameState.h"
#include "WhyGameMode.generated.h"




/**
 * 
 */
UCLASS()
class WHY_API AWhyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AWhyGameMode();

	virtual void BeginPlay() override;

	void PostLogin(APlayerController* NewPlayer) override;
	virtual void Tick(float DeltaSeconds) override;



	UPROPERTY()
		TArray<FString> PlayerNameArray = {"Red","Yellow","Green","Black","Blue"};

	int32 SelectNameNumber;
	FString SelectName;

	//� �÷��̾ ������ ���� �� ������ �÷��̾�� ����� ���������� �޾ƿ��� �ٸ� �÷��̾��� ���� ��ư ��Ȱ��ȭ
	UFUNCTION(BlueprintCallable)
		void PlayerSayDie(APlayerController* SayPlayer,bool StageColor);

	UPROPERTY()
		TArray<APlayerController*> PlayerList;

	UFUNCTION(BlueprintCallable)
		TArray<APlayerController*> GetPlayerList();

	void Spawn(class AWhyPawn* Pawn);

	bool bGameStarted;
	static bool bInGameMenu;

	TArray<class AWhyPawn*> ToBeSpawned;



};
