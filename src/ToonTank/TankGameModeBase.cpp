// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    // Get references and game win/lost conditions
    // Get HandleGameStart() to initialise the start countdown, turret activation, pawn check etc.
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    // Check what type of Actor died. If turret activation, pawn check etc.
    // Call Blueprint version GameStart();


    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

        if (PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    else if (APawnTurret *DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        if (--TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("A %s died"), *DeadActor->GetName());
}

void ATankGameModeBase::HandleGameStart() 
{
    // Initialize the start countdown, turret condition, pawn check etc.
    // Call Blueprint version GameStart();
    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
    
    GameStart();

    if (PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, 
                                                                            &APlayerControllerBase::SetPlayerEnabledState, 
                                                                            true);
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    // See if the player ahas destoryed all the turrets, show win result.
    // else if turret destroyed player. show lose result.
    // Call blueprint version GameOver(bool)
    GameOver(PlayerWon);
}



int32 ATankGameModeBase::GetTargetTurretCount() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    
    return TurretActors.Num();
}
