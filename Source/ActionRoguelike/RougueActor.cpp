// Fill out your copyright notice in the Description page of Project Settings.


#include "RougueActor.h"

// Sets default values
ARougueActor::ARougueActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		//���� ��ײչʾ
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		//������ײ�뾶
		CollisionComponent->InitSphereRadius(15.0f);
		//�����������ײ���
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		//�������ƶ�
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectfileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/SphereMaterial.SphereMaterial'"));
	if (Material.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
	}
	ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.89f, 0.09f, 0.09f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	
	//��������������
	CollisionComponent->OnComponentHit.AddDynamic(this, &ARougueActor::OnHit);

	//��ʧ
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ARougueActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARougueActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//��ʼ���ٶ�
void ARougueActor::FireIndirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

//��ײ����
void ARougueActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
	
	Destroy();
}
