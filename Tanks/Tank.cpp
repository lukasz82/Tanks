// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "PaperSpriteComponent.h"
// Trzeba pamiêtaæ ¿e w nowej wersji silnika uncludowaæ komponenty bo nie s¹ standordowo do³¹cozne do silnika
#include "Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "TankStatics.h"

void FTankInput::Sanitize()
{
	// Jeœli player naciœnie dwa przyciski jednoczeœnie, takie zabezpieczenie
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput = MovementInput.GetSafeNormal();
	RawMovementInput.Set(0.0f, 0.0f);
}

void FTankInput::MoveX(float AxisValue)
{
	RawMovementInput.X += AxisValue;
}

void FTankInput::MoveY(float AxisValue)
{
	RawMovementInput.Y += AxisValue;
}
// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TankBase"));
	}

	TankDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TankDirection"));
	TankDirection->AttachTo(RootComponent);

	TankSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TankSprite"));
	TankSprite->AttachTo(TankDirection);

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->CameraLagSpeed = 2.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->AttachTo(RootComponent);
	SpringArm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	// Rzut ortograficzny, zabezpiecza p³aski rzut na mapê bez krawêdzi
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 1024.f;
	CameraComponent->AspectRatio = 3.0f / 4.0f;
	CameraComponent->AttachTo(SpringArm, USpringArmComponent::SocketName);
	CameraComponent->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	ChildTurret = CreateDefaultSubobject<UChildActorComponent>(TEXT("Turret"));
	ChildTurret->AttachTo(TankDirection);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
int x = 0;
int sekunda = 0;
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	x++;
	if (x == 59)
	{
		x = 0;
		sekunda++;
	}
	TankInput.Sanitize();
	//UE_LOG(LogTemp,Warning,TEXT("Movement: (%f %f %i %i)"),TankInput.MovementInput.X, TankInput.MovementInput.Y, x, sekunda);
	// Poruszanie siê czo³gu
	{
		// Ustawiam wektor wzglêdem wspó³rzednych x i y
		FVector DesiredMovementDirection = FVector(TankInput.MovementInput.X, TankInput.MovementInput.Y, 0.0f);
		if (!DesiredMovementDirection.IsNearlyZero())
		{
			// Obroc czolg, obracam komponentTankDirection
			// nie rootcomponent
			FRotator MovementAngle = DesiredMovementDirection.Rotation();
			float DeltaYaw = UTankStatics::FindDeltaAngleDegress(TankDirection->GetComponentRotation().Yaw, MovementAngle.Yaw);
			bool bReverse = false;
			if (DeltaYaw != 0.0f)
			{
				float AdjusedDeltatYaw = DeltaYaw;
				if (AdjusedDeltatYaw < -90.0f)
				{
					AdjusedDeltatYaw += 180.0f;
					bReverse = true;
				}
				else if (AdjusedDeltatYaw > 90.0f)
				{
					AdjusedDeltatYaw -= 180.0f;
					bReverse = true;
				}

				float MaxYawThisFrame = YawSpeed * DeltaTime;

				if (MaxYawThisFrame > FMath::Abs(AdjusedDeltatYaw))
				{
					if (bReverse)
					{
						//Ruszaj odwrotnie
						FRotator FacingAngle = MovementAngle;
						FacingAngle.Yaw = MovementAngle.Yaw + 180.0f;
						TankDirection->SetWorldRotation(FacingAngle);
					}
					else
					{
						TankDirection->SetWorldRotation(MovementAngle);
					}
				}
				else
				{
					TankDirection->AddLocalRotation(FRotator(0.0f, FMath::Sign(AdjusedDeltatYaw) * MaxYawThisFrame, 0.0f));
				}
			}

			//Poruszanie czo³giem
			{
				FVector MovementDirection = TankDirection->GetForwardVector() * (bReverse ? -1.0f : 1.0f);
				FVector Pos = GetActorLocation();
				Pos.X += MovementDirection.X * MoveSpeed * DeltaTime;
				Pos.Y += MovementDirection.Y * MoveSpeed * DeltaTime;
				SetActorLocation(Pos);
			}
		}
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ATank::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATank::MoveY);
}

void ATank::MoveX(float AxisValue)
{
	TankInput.MoveX(AxisValue);
}

void ATank::MoveY(float AxisValue)
{
	TankInput.MoveY(AxisValue);
}
