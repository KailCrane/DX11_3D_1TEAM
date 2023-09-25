#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

class ArrowScript :
    public MonoBehavior
{
public:
    ArrowScript();
    virtual ~ArrowScript() = default;

    virtual void Initialize() override;
    virtual void FixedUpdate() override;

    void SetPlayerState(PlayerState _eStateNum); // �÷��̾� ���¸� �������� �Լ�
    virtual Component* Clone(GameObject* _pGameObject);

public:
    bool GetArrowAtkCheck() { return ArrowAtkCheck; }
    void SetArrowAtkCheck(bool _ArrowAtkCheck) { ArrowAtkCheck = _ArrowAtkCheck; }

    bool GetIsBurn() { return ArrowAtkCheck; }
    void SetBurn() { isBurn = true; }   
    void BurnReset() { isBurn = false; }

    void SetDirPos(Vec3 _dir) { DirPos = _dir; }
private:
    PlayerState mPlayerStateNum;

    bool ArrowAtkCheck = false;
    Vec3 DirPos = Vec3::Zero;

    TimerObject timerObj;

    bool isBurn = false;
};

