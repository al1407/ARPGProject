ARPG GAS Framework Extension – Leap Slam Ability (Unreal Engine 5.5)

Overview
This project implements a modular Gameplay Ability System (GAS) extension using Unreal Engine 5.5, designed to be easily extended into an Action RPG (ARPG).

Built on top of the Unreal Top-Down template, the project demonstrates a scalable attribute system, a fully functional Leap Slam ability inspired by Path of Exile, and a clean separation between gameplay logic and UI. The system is designed to be data-driven, modular and designer-friendly with ability to extend, with most gameplay values exposed to Blueprint.

---

Key Features

Gameplay Ability System (GAS)

* Custom Ability System Component derived from UAbilitySystemComponent
* Custom Attribute Set containing Health, Mana, and AttackSpeed
* Attribute replication enabled
* Gameplay Effects used for damage, mana cost, cooldown, and default attributes

Leap Slam Ability

* Arc-based movement using LaunchCharacter (not teleport)
* Traverses gaps and obstacles
* Applies area-of-effect damage on landing
* Movement speed and duration scale with AttackSpeed
* Uses GAS for Manacost, cooldown duration, and damage via SetByCaller

Ability Architecture
Input → Ability System → Gameplay Ability → Gameplay Effects → Attribute Set

* Core logic implemented in C++
* Gameplay parameters exposed to Blueprint
* Effects configured through Blueprint for flexibility

---

Player Setup

The player character is based on the Unreal Top-Down template and extended with:

* Ability System Component
* Attribute Set

On BeginPlay:

* Ability System is initialized
* Default attributes are applied
* Leap Slam ability is granted

---

Controls (Enhanced Input)

Movement:
CLick to Move
WASD for movement added as well

Ability:
Q – Activate Leap Slam

The project uses Unreal’s Enhanced Input system with an Input Mapping Context applied at runtime.

---

Enemy System

* Custom enemy character implementing IAbilitySystemInterface
* Own Ability System Component and Attribute Set
* Receives damage via AoE overlap
* Handles UI events such as damage display

---

Damage System

* AoE detection using OverlapMultiByChannel
* Damage applied using GameplayEffect (GE_Damage)
* Uses SetByCaller with tag Data.Damage
* Fully scalable and extendable

---

UI and Feedback

Floating Damage Numbers

* Spawned from Enemy Blueprint (not from AttributeSet)
* Positioned using ProjectWorldToScreen
* Animated to move upward and fade out
* Automatically removed after animation

Health System

* Health updated through GAS
* UI updates handled at the actor level
* Designed for easy extension into a full HUD

---

Project Structure

Source

* AbilitySystem

	* RPGAbilityComponent
	* RPGAttributeSet

* Abilities

	* RPGGameplayAbility
	* RPGGA_LeapSlam
	* BP_RPGLeapSlam (exposes GE to be assigned)

* Characters

	* ARPGProjectCharacter (Extended Default)
	* RPGEnemy

Content

* Gameplay

	* Abilities
	* Effects

* UI

	* W_Damage

---

Gameplay Effects

BP_GE_Damage
Applies damage using SetByCaller

BP_GEManaCost
Reduces mana when ability is used

BP_GEAbilityCooldown
Controls ability cooldown duration

BP_GEDefaultAttributes
Initializes Health, Mana, and AttackSpeed

---

Design Decisions

Separation of Concerns
Gameplay logic is handled by GAS, while UI is handled by the actor and Blueprint layer. This keeps the system clean and maintainable.

Data-Driven Design
All key gameplay values are exposed to Blueprint, allowing designers to tweak values without modifying code.

Extensibility
The system is structured to support additional future integrations and extensions.

Cooldown Handling
Cooldown is applied using a GameplayEffect but enforced in C++ using a GameplayTag on the AbilitySystemComponent.
When the ability is activated, a cooldown tag is added. While this tag exists, the ability is blocked in CanActivateAbility. The tag is removed after the cooldown duration.

Reason:

* Ensures deterministic behavior regardless of editor configuration
* Avoids dependency on tags in UE 5.5
* Keeps cooldown logic explicit and easy to debug

Data-Driven Cooldown
Cooldown duration is read directly from the GameplayEffect at runtime instead of hardcoding values.

Reason:

* Designers can tweak cooldown without code changes
* Keeps gameplay tuning flexible
* Maintains single source of truth

Ability Structure
A base ability class (RPGGameplayAbility) is used, with Leap Slam implemented in a derived class. So that its easy to add more additional abilities in future.

Reason:

* Shared logic can be reused across abilities
* New abilities can be added without modifying existing code
* Keeps the system modular

Damage Handling Design
Damage is processed inside the AttributeSet, while UI is handled in the Enemy Blueprint.

Reason:

* Keeps gameplay data separate from presentation
* Avoids mixing UI logic with core systems
* Easier to extend UI later

---

How to Run

1. Open the project in Unreal Engine 5.5
2. Play the main level
3. Use click to move (Default) or WASD to move
4. Press Q to activate Leap Slam

You should observe arc-based movement, AoE damage on landing, floating damage numbers, and correct mana and cooldown behavior.

Expected Behavior

* Character performs an arc-based leap forward
* Enemy takes damage on landing (AoE)
* Damage numbers appear above enemy
* Ability cannot be spammed during cooldown
* Ability becomes usable again after cooldown duration

---

Extensibility

The system is designed to scale into a full ARPG:

* New abilities can be added by inheriting from RPGGameplayAbility
* New attributes can be added in RPGAttributeSet
* Additional enemies can reuse the same GAS setup
* Cooldown system can be reused using GameplayTags
* UI layer can be expanded into a full combat HUD

---

Future Improvements

* Animation montage integration for abilities
* Targeting system
* Cooldown UI indicators
* Multiplayer validation and replication improvements
* Damage types and resistance system

---

Summary

This project demonstrates a solid understanding of Unreal’s Gameplay Ability System, along with clean architecture, modular design, and a strong focus on scalability and usability for both engineers and designers.

---

Author

Developed By Alankar Pradhan as part of a technical assessment.
