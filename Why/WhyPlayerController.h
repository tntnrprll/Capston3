// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WhyPawn.h"
#include "ColorBox.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "WhyPlayerState.h"
#include "Engine/World.h"
#include "WhyGameState.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Net/UnrealNetwork.h"
#include "WhyGameInstance.h"
#include "WhyGameState.h"
#include "WhyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WHY_API AWhyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AWhyPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void SetVisiblePlayer();

	UFUNCTION()
	void InputClickPressed();
	UFUNCTION()
	void LeftClickPressed(); 

	virtual void SetupInputComponent() override;
	
	bool IsDieTime = false;


	UPROPERTY()
		FVector Location;
	UFUNCTION()
		FVector GetLocation();
	UPROPERTY()
		bool IsSetLocation = false;
	UFUNCTION()
		void SetIsSetLocation(bool State);
	UFUNCTION()
		bool GetIsSetLocation();
	UFUNCTION()
	void SetDestination(const FVector DestLocation);
	UFUNCTION()
	void MoveToMouseCursor();

	UFUNCTION()
		void Clicked(AColorBox* Box);
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetClickedNumber(AColorBox* Box);
	bool ServerSetClickedNumber_Validate(AColorBox* Box);
	void ServerSetClickedNumber_Implementation(AColorBox* Box);


	UPROPERTY(EditAnywhere, Category = PlayerNumber)
		int32 PlayerNumber = 0;
	UPROPERTY(EditAnywhere, Category = TargetNumber)
		int32 TargetNumber=0;

	UFUNCTION(BlueprintCallable)
		int32 GetPlayerNumber();
	UFUNCTION(BlueprintCallable)
		void SetPlayerNumber(int32 Num);

	UPROPERTY()
		bool StartPoint = false;

	UPROPERTY()
		AWhyPlayerState* State;

	UFUNCTION()
		void GetPlayerAndSetTargetColor();

	UPROPERTY(Replicated)
		int32 HP=100;
	UPROPERTY(Replicated)
		int32 MP=100;

	UFUNCTION()
		void SetHP(int32 Num);
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerSetHP(int32 Num);
	bool ServerSetHP_Validate(int32 Num);
	void ServerSetHP_Implementation(int32 Num);
	//체력을 쓸지 기력을 쓸지 판단
	UFUNCTION()
		void AttempHPMP(int32 Num);

	UFUNCTION()
		void SetMP(int32 Num);
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerSetMP(int32 Num);
	bool ServerSetMP_Validate(int32 Num);
	void ServerSetMP_Implementation(int32 Num);

	UFUNCTION(BlueprintCallable)
		float GetHP();
	UFUNCTION(BlueprintCallable)
		float GetMP();

	UPROPERTY()
		int32 NowBoxNumber;
	UPROPERTY()
		int32 BecomeBoxNumber;

	UFUNCTION()
		AColorBox* GetBecomeBoxReference();
	UFUNCTION()
		AColorBox* GetNowBoxReference();
	UPROPERTY()
		AColorBox* NowBox;
	UPROPERTY()
		AColorBox* BecomeBox;

	UFUNCTION()
		void SetNowBox();

	UPROPERTY()
		bool IsCheckPoint = true;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//현재 무슨 시간인지
	UPROPERTY(Replicated)
		bool WhatTime;

	//deathtime으로 만들 수 있는 기회가 있는지-->PlayerState로
	UPROPERTY()
		bool CanSetDeathTime = true;
	UFUNCTION()
		void SetCanSetDeathTime(bool Value);
	UFUNCTION()
		bool GetCanSetDeathTime();


	UPROPERTY(Replicated)
		FText OutChatMessage;

	UFUNCTION(BlueprintCallable)
		void SetOutChatMessage(FString Message);

	UFUNCTION(BlueprintCallable)
		FText GetOutChatMessage();

	UPROPERTY(Replicated)
		FString PlayerRandomName;

	UFUNCTION(BlueprintCallable)
		FString GetPlayerRandomName();

	UPROPERTY(Replicated)
		bool IsActiveDieSay = true;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerSetIsActiveDieSay(bool Value);
	bool ServerSetIsActiveDieSay_Validate(bool Value);
	void ServerSetIsActiveDieSay_Implementation(bool Value);

	UFUNCTION(BlueprintCallable)
		bool GetIsActiveDieSay();

	UPROPERTY(Replicated)
		bool SayColor = true;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerSayColor(bool Value);
	bool ServerSayColor_Validate(bool Value);
	void ServerSayColor_Implementation(bool Value);

	UFUNCTION(BlueprintCallable)
		bool GetSayColor();

	UPROPERTY(Replicated)
		bool TextVisible = false;
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerTextVisible(bool Value);
	bool ServerTextVisible_Validate(bool Value);
	void ServerTextVisible_Implementation(bool Value);
	UFUNCTION(BlueprintCallable)
		bool GetTextVisible();

	UFUNCTION(BlueprintCallable)
		void SetPlayerScore(int32 Num);
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerSetPlayerScore(int32 Num);
	bool ServerSetPlayerScore_Validate(int32 Num);
	void ServerSetPlayerScore_Implementation(int32 Num);


	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerAddChangeCost();
	bool ServerAddChangeCost_Validate();
	void ServerAddChangeCost_Implementation();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerResetChangeCost();
	bool ServerResetChangeCost_Validate();
	void ServerResetChangeCost_Implementation();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void ServerSetIsDie(bool Value);
	bool ServerSetIsDie_Validate(bool Value);
	void ServerSetIsDie_Implementation(bool Value);

	UFUNCTION()
		void SetIsDie(bool Value);


	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetStage(bool Stage);
	bool ServerSetStage_Validate(bool Stage);
	void ServerSetStage_Implementation(bool Stage);


	bool endvalue = false;

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetGetPoint(int32 Value);
	bool ServerSetGetPoint_Validate(int32 Value);
	void ServerSetGetPoint_Implementation(int32 Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerAddCatchedPlayerNumber(int32 Num);
	bool ServerAddCatchedPlayerNumber_Validate(int32 Num);
	void ServerAddCatchedPlayerNumber_Implementation(int32 Num);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerResetCatchedPlayerNumber();
	bool ServerResetCatchedPlayerNumber_Validate();
	void ServerResetCatchedPlayerNumber_Implementation();

	void TargetPlayerDie();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetSortScore();
	bool ServerSetSortScore_Validate();
	void ServerSetSortScore_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetPlayerRandomName();
	bool ServerSetPlayerRandomName_Validate();
	void ServerSetPlayerRandomName_Implementation();

};