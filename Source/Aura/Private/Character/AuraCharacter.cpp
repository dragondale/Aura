


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	/* Typical parameters for topdown game */
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::OnRep_PlayerState()
{
	/* Init Ability Actor Info for the client */
	
	Super::OnRep_PlayerState();
	InitAuraAbilityComponent();

	InitOverlay();
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	/* Init Ability Actor Info for the server */
	
	Super::PossessedBy(NewController);
	InitAuraAbilityComponent();
	
	InitOverlay();
}

void AAuraCharacter::InitAuraAbilityComponent()
{
	if (AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(GetPlayerState()))
	{
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
		AttributeSet = AuraPlayerState->GetAttributeSet();
	}
}

void AAuraCharacter::InitOverlay() const
{
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, GetPlayerState(), AbilitySystemComponent, AttributeSet);
		}
	}
}
