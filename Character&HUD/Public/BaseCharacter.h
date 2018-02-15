#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class EXAMPLEPROJECT2_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UFUNCTION(BlueprintCallable, Category="Character|Health")
		void SetCurrentHealth(float NewHealth) { CurrentHealth = NewHealth; }
	UFUNCTION(BlueprintPure, Category = "Character|Health")
		float GetCurrentHealth() const { return CurrentHealth; }
	UFUNCTION(BlueprintPure, Category = "Character|Health")
		float GetMaxHealth() const { return MaxHealth; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Death")
		void OnDeath();
	virtual void OnDeath_Implementation() PURE_VIRTUAL(ABaseCharacter::OnDeath_Implementation, );

	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Health")
		float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
		bool bIsSprinting;
};
