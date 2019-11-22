// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"
#include "ColorBox.generated.h"

UCLASS()
class WHY_API AColorBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AColorBox();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(EditAnywhere,Category="Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "OverMesh")
	UStaticMeshComponent* OverStaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Number")
	UTextRenderComponent* NumberText;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* Collision;

	UPROPERTY()
		UBoxComponent* OverlapComponent;

	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInterface* Material;
	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInterface* One;
	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInterface* Two;
	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInterface* Three;


	UPROPERTY(VisibleAnywhere, Category = SecondStage)
	UMaterialInterface* SecondStageColor;
	UPROPERTY(VisibleAnywhere, Category = FirstStage)
	UMaterialInterface* FirstStageColor;


	UPROPERTY(EditAnywhere, Replicated, Category = ClickedNumber)
		int32 ClickedNumber=0;


	UFUNCTION()
	virtual void NotifyActorBeginCursorOver() override;
	UFUNCTION()
	virtual void NotifyActorEndCursorOver() override;
	UFUNCTION()
	virtual void NotifyActorOnClicked(FKey PressedButton = EKeys::LeftMouseButton) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SpawnPoint;
	UFUNCTION()
	FVector GetSpawnPoint();

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		APawn* ClickedInstigator;
	UFUNCTION(BlueprintAuthorityOnly)
		void ClickedBy(APawn* Pawn);
	UFUNCTION(NetMulticast, Reliable)
		void ClientOnClickedBy(APawn* Pawn,bool Stage);
	void ClientOnClickedBy_Implementation(APawn* Pawn,bool Stage);

	UFUNCTION()
		void SetClickedNumber();
	UFUNCTION()
		int32 GetClickedNumber();
	UFUNCTION()
		void SetNumberText();

	UFUNCTION()
		void ClickedNumberReset();

	//Active
	UFUNCTION(BlueprintPure)
		bool IsActive();
	UPROPERTY(Replicated)
		bool bIsActive;
	UFUNCTION(BlueprintCallable)
		void SetActive(bool NewState);
	UFUNCTION(BlueprintNativeEvent)
		void WasActive();
	virtual void WasActive_Implementation();
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerSetActive(bool NewState);
	bool ServerSetActive_Validate(bool NewState);
	void ServerSetActive_Implementation(bool NewState);

	UPROPERTY(Replicated)
		int32 Step = 0;

	UFUNCTION()
		int32 GetStep();
	UPROPERTY()
		bool IsChangePoint =true;
	UPROPERTY()
		bool IsChangePoint1 = true;
	UPROPERTY()
		bool IsFirst = true;

	UFUNCTION()
		void SampleFunction(APawn* Pawn,bool Stage);

	UPROPERTY()
		bool ClickedNumberChangePoint = true;
};
