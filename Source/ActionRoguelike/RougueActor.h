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

	//球体碰撞函数
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//球体碰撞组件
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;
	//发射物体移动
	UPROPERTY(VisibleDefaultsOnly, Category = MoveMent)
		UProjectileMovementComponent* ProjectileMovementComponent;
	//发射物网格体
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile);
	UStaticMeshComponent* ProjectileMeshComponent;
	//发射物材质
	UPROPERTY(VisibleDefaultsOnly, Category = Movement);
	UMaterialInstanceDynamic* ProjectileMaterialInstance;
	//初始化速度
	void FireIndirection(const FVector& ShootDirection);

};
