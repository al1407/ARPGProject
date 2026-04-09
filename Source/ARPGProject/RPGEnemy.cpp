// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEnemy.h"


// Sets default values
ARPGEnemy::ARPGEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystem = CreateDefaultSubobject<URPGAbilityComponent>("ASC");
	AbilitySystem->SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>("Attributes");
}

// Called when the game starts or when spawned
void ARPGEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystem->InitAbilityActorInfo(this, this);

	// Apply default attributes
	if (DefaultAttributesEffect)
	{
		auto Context = AbilitySystem->MakeEffectContext();

		auto Spec = AbilitySystem->MakeOutgoingSpec(DefaultAttributesEffect, 1, Context);

		if (Spec.IsValid())
		{
			AbilitySystem->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
		}
	}
}

// Called every frame
void ARPGEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ARPGEnemy::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}
