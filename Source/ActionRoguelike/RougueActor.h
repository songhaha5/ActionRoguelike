// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RougueActor.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARougueActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARougueActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//������ײ����
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//������ײ���
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;
	//���������ƶ�
	UPROPERTY(VisibleDefaultsOnly, Category = MoveMent)
		UProjectileMovementComponent* ProjectileMovementComponent;
	//������������
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile);
	UStaticMeshComponent* ProjectileMeshComponent;
	//���������
	UPROPERTY(VisibleDefaultsOnly, Category = Movement);
	UMaterialInstanceDynamic* ProjectileMaterialInstance;
	//��ʼ���ٶ�
	void FireIndirection(const FVector& ShootDirection);

};
