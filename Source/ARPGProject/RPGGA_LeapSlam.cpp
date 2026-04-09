// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGA_LeapSlam.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.h"
#include "AbilitySystemGlobals.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "CollisionQueryParams.h"
#include "Engine/OverlapResult.h"
#include "GameplayTagContainer.h"
#include "CollisionShape.h"
#include "Engine/World.h"


static FGameplayTag LeapSlamCooldownTag = FGameplayTag::RequestGameplayTag(FName("Cooldown.LeapSlam"));

URPGGA_LeapSlam::URPGGA_LeapSlam()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void URPGGA_LeapSlam::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CachedHandle = Handle;
	CachedActorInfo = ActorInfo;
	CachedActivationInfo = ActivationInfo;

	if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get()))
	{
		PerformLeap(Character);

		UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();

		if (ASC && CooldownEffect)
		{
			FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(CooldownEffect, 1.0f, Context);

			if (SpecHandle.IsValid())
			{
				// Apply the cooldown effect
				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

				// Get duration directly from GE
				float CooldownDuration = SpecHandle.Data->GetDuration();

				// Apply tag
				ASC->AddLooseGameplayTag(LeapSlamCooldownTag);

				FTimerHandle TimerHandle;

				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ASC]()
					{
						ASC->RemoveLooseGameplayTag(LeapSlamCooldownTag);
					}, CooldownDuration, false);
			}
		}
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
}

void URPGGA_LeapSlam::PerformLeap(ACharacter* Character)
{
	FVector forward = Character->GetActorForwardVector();
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();

	float attackSpeed = 1.0f;

	if (ASC)
	{
		attackSpeed = ASC->GetNumericAttribute(URPGAttributeSet::GetAttackSpeedAttribute());
	}

	float scaledForward = ForwardStrength * attackSpeed;
	float scaledUpward = UpwardStrength * attackSpeed;

	FVector LaunchVelocity = (forward * scaledForward) + FVector(0,0,scaledUpward);
	
	Character->LaunchCharacter(LaunchVelocity, true, true);

	float duration = BaseDuration / attackSpeed;

	FTimerHandle TimerHandle;

	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, FName("OnLeapFinished"), Character);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, timerDelegate, duration, false);

}

void URPGGA_LeapSlam::ApplyAOEDamage(ACharacter* Character)
{

	if (!Character) return;

	FVector Location = Character->GetActorLocation();

	TArray<FOverlapResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	bool bHit = GetWorld()->OverlapMultiByChannel(HitResults, Location, FQuat::Identity, ECC_WorldDynamic, Sphere);

	if (!bHit) return;

	for (const FOverlapResult& Result : HitResults)
	{
		AActor* HitTargetActor = Result.GetActor();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Overlap triggered")); //Debug
		FString Msg = FString::Printf(TEXT("Hit Count: %d"), HitResults.Num());
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, Msg); //Debug

		if (HitTargetActor && HitTargetActor != Character)
		{
			UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(HitTargetActor);
			if (!TargetASC)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("No ASC on target"));
			}
			if (TargetASC && DamageEffect)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT(" ASC on Enemy is found "));
				FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
				FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffect, 1.0f, EffectContext);

				if (SpecHandle.IsValid())
				{
					SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Data.Damage"), -Damage);
					TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				}
			}
		}
	}

	// Apply AOE damage logic here, such as using a sphere trace to find nearby enemies and applying damage to them.
}

void URPGGA_LeapSlam::OnLeapFinished(ACharacter* Character)
{
	if (!Character) return;

	ApplyAOEDamage(Character);
	EndAbility(CachedHandle, CachedActorInfo, CachedActivationInfo, true, false);
	// Logic to execute when the leap finishes, such as resetting states or triggering additional effects.
}

bool URPGGA_LeapSlam::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		return false;
	}

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();

	//BLOCK IF COOLDOWN TAG EXISTS
	if (ASC->HasMatchingGameplayTag(LeapSlamCooldownTag))
	{
		return false;
	}

	return true;
}