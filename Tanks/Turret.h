// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class TANKS_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//Dodanie szkieletu klasy odpowiedzialnej za kierunek (wektor) wiezyczki, czyli w kt�r� stron� jest zwrocona
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Turret", Meta = (AllowPrivateAcces = "true"))
	class UArrowComponent* TurretDirection;
	
	
};
