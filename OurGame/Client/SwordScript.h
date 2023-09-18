#pragma once
#include "MonoBehavior.h"

class SwordScript :
    public MonoBehavior
{
public:
    SwordScript();
    virtual ~SwordScript() = default;

    virtual void Initialize() override ;
    virtual void FixedUpdate() override;

    void SetPlayerState(PlayerState _eStateNum); // �÷��̾� ���¸� �������� �Լ�
    virtual Component* Clone(GameObject* _pGameObject);


private:
    const int mAttackState = 3; //3
    const int mEvasionState = 5; //5
    PlayerState mPlayerStateNum;


};

//PauseState,
//IdleState,
//MoveState,
//AttackState, ////
//MagicAttackState,
//EvasionState, /////
//FallState,
//HitStartState,
//HittingState,
//HitEndState,
//FallDownState,
//DeadState,
//ClimingUpState,
//ClimingDownState,
//ClimingEndState,
