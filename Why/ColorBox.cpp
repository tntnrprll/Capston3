// Fill out your copyright notice in the Description page of Project Settings.

#include "ColorBox.h"


// Sets default values
AColorBox::AColorBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	
	//StaticMesh 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> STATICMESH(TEXT("StaticMesh'/Game/StarterContent/Shapes/BaseBox.BaseBox'"));
	if (STATICMESH.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(STATICMESH.Object);
	}

	OverStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OverStaticMeshComponent"));
	
	//OverMesh 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OVERMESH(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	if (OVERMESH.Succeeded())
	{
		OverStaticMeshComponent->SetStaticMesh(OVERMESH.Object);
	}

	//Base material 설정
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BASE(TEXT("Material'/Game/Material/BaseMaterial.BaseMaterial'"));
	if (BASE.Succeeded())
	{
		OverStaticMeshComponent->SetMaterial(0, BASE.Object);
	}

	//One Click material 설정
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ONE(TEXT("MaterialInstanceConstant'/Game/Platformer/Materials/M_Plastic_Green_Pattern_Inst.M_Plastic_Green_Pattern_Inst'"));
	if (ONE.Succeeded())
	{
		One = ONE.Object;
	}
	//Two Click Material 설정
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TWO(TEXT("Material'/Game/Platformer/Materials/M_Plastic_Blue_Pattern_Parent.M_Plastic_Blue_Pattern_Parent'"));
	if (TWO.Succeeded())
	{
		Two = TWO.Object;
	}
	//Three Click Material 설정
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> THREE(TEXT("MaterialInstanceConstant'/Game/Platformer/Materials/M_Plastic_Orange_Pattern_Inst.M_Plastic_Orange_Pattern_Inst'"));
	if (THREE.Succeeded())
	{
		Three = THREE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SECONDSTAGE(TEXT("MaterialInstanceConstant'/Game/Platformer/Materials/M_Metal_Red_Instance.M_Metal_Red_Instance'"));
	if (SECONDSTAGE.Succeeded())
	{
		SecondStageColor = SECONDSTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FIRSTSTAGE(TEXT("MaterialInstanceConstant'/Game/Platformer/Materials/M_Metal_Grey_Instance.M_Metal_Grey_Instance'"));
	if (FIRSTSTAGE.Succeeded())
	{
		FirstStageColor =FIRSTSTAGE.Object;
	}



	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetWorldScale3D(FVector(1.f,1.f,1.f));
	RootComponent = Collision;
	
	StaticMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -200.0f));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetWorldScale3D(FVector(2.5f, 2.5f, 2.5f));
	StaticMeshComponent->SetMaterial(0, FirstStageColor);

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetupAttachment(RootComponent);
	OverlapComponent->SetWorldScale3D(FVector(5.0f, 5.0f, 20.0f));
	OverlapComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));

	OverStaticMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	OverStaticMeshComponent->SetupAttachment(RootComponent);
	OverStaticMeshComponent->SetWorldScale3D(FVector(3.3f,3.3f, 1.0f));
	OverStaticMeshComponent->SetVisibility(false);

	SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);
	SpawnPoint->SetRelativeLocation(FVector(0.0f,0.0f, 110.f));

	NumberText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NumberText"));
	NumberText->SetupAttachment(RootComponent);
	NumberText->SetRelativeLocation(FVector(-20.0f, 90.0f, 70.0f));
	NumberText->SetText(FString::FromInt(ClickedNumber));
	NumberText->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	NumberText->SetWorldSize(80.0f);
	//NumberText->SetIsReplicated(true);

	if (Role == ROLE_Authority)
	{
		ClickedNumber = 0;
		bIsActive = true;
	}
	

	bReplicates = true;
	
	
}

// Called when the game starts or when spawned
void AColorBox::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AColorBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
}

bool AColorBox::IsActive()
{
	return bIsActive;
}
void AColorBox::SetActive(bool NewState)
{

	bIsActive = NewState;
	if (Role < ROLE_Authority)
	{
		ServerSetActive(NewState);
	}
}
bool AColorBox::ServerSetActive_Validate(bool NewState)
{
	return true;
}
void AColorBox::ServerSetActive_Implementation(bool NewState)
{
	if (Role == ROLE_Authority)
	{
		SetActive(NewState);
	}
	
}
void AColorBox::WasActive_Implementation()
{
	if (bIsActive)
	{
		//Destroy();
	}

	
}

void AColorBox::SetClickedNumber()
{
	if (Role == ROLE_Authority)
	{
		
		if (ClickedNumber == 2)
		{
			
			ClickedNumberReset();
			
		}
		else
		{
			ClickedNumber += 1;
		}
	}
	
}

void AColorBox::ClickedNumberReset()
{
	if (Role == ROLE_Authority)
	{
		ClickedNumber = -1;
	}
}

int32 AColorBox::GetClickedNumber()
{
	return ClickedNumber;
}

//마우스가 박스 위로 올라왔을때 어떤 박스 위에 있는 지 알려줌
void AColorBox::NotifyActorBeginCursorOver()
{
	OverStaticMeshComponent->SetVisibility(true);
}

void AColorBox::NotifyActorEndCursorOver()
{
	OverStaticMeshComponent->SetVisibility(false);
}

void AColorBox::NotifyActorOnClicked(FKey PressedButton)
{
	
}

void AColorBox::ClickedBy(APawn* Pawn)
{
	if (Role == ROLE_Authority)
	{
		//현재 작업을 할 pawn을 세팅
		ClickedInstigator = Pawn;
		
		
	}
}

//박스의 높낮이에 따른 변수를 변경하고 변경점에 이르렀을때 변경하기 위한 변수를 세팅
void AColorBox::SampleFunction(APawn* Pawn,bool Stage)
{
	//클라이언트 상에서 클릭 이벤트 실행
	ClientOnClickedBy(Pawn,Stage);
	
	//박스의 스테이지가 false일때
	if (!bIsActive)
	{
		//이미 3번 클릭 된 상태라면
		if (Step == 3)
		{
			if (!IsChangePoint)//한번 더 클릭되었을 경우 스테이지가 바뀌도록 하기위해서(4번 클릭되었을 경우 스테이지가 바뀌어야 하지만 4번째 눌리는 것에는 높낮이 변화가 없음)
			{
				Step--;
				IsChangePoint = true;
			}
			else
			{
				IsChangePoint = false;
			}
		}
		else
		{
			Step--;
		}


	}
	else
	{
		if (IsFirst)
		{
			Step++;
			IsFirst = false;
		}
		else
		{
			if (Step == 0)//현재의 높낮이에 대한 값이 0이라면 변경점에 대한 값을 변경
			{
				if (!IsChangePoint1)
				{
					Step++;
					IsChangePoint1 = true;
				}
				else
				{
					IsChangePoint1 = false;
				}
			}
			else
			{
				
				Step++;
			}
		}


		
	}
}

//박스가 클릭되었을 때 박스에 적힌 숫자가 이 박스의 상태에 따라 다르게 보이도록 하기위해
void AColorBox::ClientOnClickedBy_Implementation(APawn* Pawn,bool Stage)
{
	//이것을 일어나도록 하게한 플레이어를 받아옴
	ClickedInstigator = Pawn;
	
	//박스에 표시될 숫자
	int32 a;
	if (!Stage)
	{
		a = -1 * (ClickedNumber + 1);
	}
	else
	{
		a = ClickedNumber + 1;
	}
	//박스의 글자 변경
	NumberText->SetText(FText::FromString(FString::FromInt(a)));
	//스테이지에 따른 색 변경과 높낮이 변경 반영
	if (!Stage)
	{
		//박스의 색을 변경
		StaticMeshComponent->SetMaterial(0, SecondStageColor);
		
		//박스의 높낮이 변경
		FVector CollisionLocation;
		if (ClickedNumber == -1)
		{
			CollisionLocation = Collision->GetComponentLocation();
		}
		else if (ClickedNumber == 0)
		{
			CollisionLocation = Collision->GetComponentLocation() + FVector(0.0f, 0.0f, (ClickedNumber+1)*40.0f);
		}
		else
		{
			CollisionLocation = Collision->GetComponentLocation() + FVector(0.0f, 0.0f, ClickedNumber*40.0f);
		}
		
		Collision->SetRelativeLocation(CollisionLocation);
		
	}
	else
	{

		StaticMeshComponent->SetMaterial(0, FirstStageColor);
		
		FVector CollisionLocation;
		if (ClickedNumber == -1)
		{
			CollisionLocation = Collision->GetComponentLocation();
		}
		else if (ClickedNumber == 0)
		{
			CollisionLocation = Collision->GetComponentLocation() + FVector(0.0f, 0.0f, (ClickedNumber + 1)*-40.0f);
		}
		else
		{
			CollisionLocation = Collision->GetComponentLocation() + FVector(0.0f, 0.0f, ClickedNumber*-40.0f);
		}
		Collision->SetRelativeLocation(CollisionLocation);
		
	}
}

void AColorBox::SetNumberText()
{
	int32 a;
	if (!bIsActive)
	{
		a = -1 * (ClickedNumber + 1);
	}
	else
	{
		a = ClickedNumber + 1;
	}
	NumberText->SetText(FText::FromString(FString::FromInt(a)));
	
}

FVector AColorBox::GetSpawnPoint()
{
	return SpawnPoint->GetComponentLocation();
}



void AColorBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AColorBox, ClickedNumber);
	DOREPLIFETIME(AColorBox, bIsActive);
	DOREPLIFETIME(AColorBox, Step);


}

int32 AColorBox::GetStep()
{
	return Step;
}

