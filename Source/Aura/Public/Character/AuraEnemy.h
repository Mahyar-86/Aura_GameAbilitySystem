// Copyright Mahyar Kazazi.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	
	/** Begin of IEnemyInterface implementation */
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	/** End of IEnemyInterface implementation */

protected:
	virtual void BeginPlay() override;

};
