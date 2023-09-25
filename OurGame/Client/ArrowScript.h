#pragma once
#include "MonoBehavior.h"

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


private:
    PlayerState mPlayerStateNum;
};

