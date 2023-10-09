// Fill out your copyright notice in the Description page of Project Settings.


#include "RouguelikeCharacter.h"

// Sets default values
ARouguelikeCharacter::ARouguelikeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPSCameraComponent);

	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void ARouguelikeCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using "));
}

// Called every frame
void ARouguelikeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARouguelikeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARouguelikeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARouguelikeCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ARouguelikeCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ARouguelikeCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARouguelikeCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARouguelikeCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARouguelikeCharacter::Fire);
}

void ARouguelikeCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ARouguelikeCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ARouguelikeCharacter::StartJump()
{
	bPressedJump = true;
}

void ARouguelikeCharacter::StopJump()
{
	bPressedJump = false;
}

void ARouguelikeCharacter::Fire()
{
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		//设置生成偏移
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);
		//偏移 从摄像机空间变换到世界空间
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		//目标方向向上偏斜
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			//枪口位置生成发射物
			ARougueActor* Projectile = World->SpawnActor<ARougueActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireIndirection(LaunchDirection);
			}
		}



	}
}
