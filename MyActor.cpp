// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	//초기 액터 위치 세팅
	start = { 0, 0 };
	FVector Location = { start.X, start.Y, 100.f };
	SetActorLocation(Location);
	//위치 로그 출력
	UE_LOG(LogTemp, Display, TEXT("Initial location : { %d, %d }"), (int32)start.X, (int32)start.Y);

	for (int i = 0; i < 10; i++)
	{
		move();
	}

	UE_LOG(LogTemp, Display, TEXT("Event cnt : %d, Total distance : %.3f"), evCnt, totDist);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActor::move()
{
	//확률 이벤트로 실행
	if (createEvent())
	{
		evCnt++;
		UE_LOG(LogTemp, Warning, TEXT("Event occurred!!"));
		//step 메소드로 랜덤으로 다음 좌표 생성
		FVector2D NextLocation = { start.X + step(), start.Y + step() };

		//위치 로그 출력
		UE_LOG(LogTemp, Display, TEXT("Move { %d, %d }"), (int32)NextLocation.X, (int32)NextLocation.Y);

		//이동거리 계산
		float dist = distance(start, NextLocation);
		UE_LOG(LogTemp, Display, TEXT("Move distance: %.2f"), dist);

		//총 거리 업데이트
		totDist += dist;

		//액터 위치 업데이트
		FVector Location = { NextLocation.X, NextLocation.Y, 100.f };
		SetActorLocation(Location);
		start = NextLocation;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Event fail!!"));
}

int32_t AMyActor::step()
{
	return FMath::RandRange(0, 1);
}

//거리 계산 메소드
float AMyActor::distance(FVector2D first, FVector2D second)
{
	float dx = fabs(first.X - second.X);
	float dy = fabs(first.Y - second.Y);

	return sqrt(dx * dx + dy * dy);
}

//50%확률로 이벤트 발생
int32 AMyActor::createEvent()
{
	return FMath::RandRange(0, 1);
}
