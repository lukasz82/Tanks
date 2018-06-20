// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Ta struktura przechwytuje wszystkie mo¿liwe naciœniêcia przez u¿ytkownika
USTRUCT()
struct FTankInput
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywere, BlueprintReadOnly, Category = "Tank Input")
	FVector2D MovementInput;

	void Sanitize();
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

private:
	FVector2D RawMovementInput;
};

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

protected:
	//Dodanie szkieletu klasy odpowiedzialnej za kierunek (wektor) czo³gu, czyli w któr¹ stronê jest zwrócony
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Tank", Meta = (AllowPrivateAcces = "true"))
	class UArrowComponent* TankDirection; // to makro pozwala UE widzieæ tê w³aœciwoœæ w blueprintach, nie jest wymagane ale jest pomocne

	// Dodanie klasy odpowiadaj¹cej za "cia³o" czo³gu i pod³¹czenie sprita
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Tank", Meta = (AllowPrivateAcces = "true"))
	class UPaperSpriteComponent* TankSprite;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Tank", Meta = (AllowPrivateAcces = "true"))
	UChildActorComponent* ChildTurret;

	// Kamera w grze inicjacja
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Tank", Meta = (AllowPrivateAcces = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Tank input")
	FTankInput TankInput;
};
