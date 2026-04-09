// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Engine/Engine.h"
#include "RPGEnemy.h"
#include "Net/UnrealNetwork.h"

void URPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Health, OldValue);
}

void URPGAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Mana, OldValue);
}

void URPGAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, AttackSpeed, OldValue);
}

void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Mana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        float Damage = -Data.EvaluatedData.Magnitude;

        if (Damage > 0)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Damage: %.1f"), Damage));

            AActor* TargetActor = Data.Target.GetAvatarActor();

            if (TargetActor)
            {
                ARPGEnemy* Enemy = Cast<ARPGEnemy>(TargetActor);

                if (Enemy)
                {
                    Enemy->ShowDamage(Damage); //Used for UI
                }
            }

        }
    }
}