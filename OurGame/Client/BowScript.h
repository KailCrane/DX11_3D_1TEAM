#pragma once
#include "MonoBehavior.h"
class BowScript :
    public MonoBehavior
{
public:
    BowScript();
    virtual ~BowScript() = default;

    virtual void Initialize() override;
    virtual void FixedUpdate() override;

    void SetPlayerState(PlayerState _eStateNum); // �÷��̾� ���¸� �������� �Լ�
    virtual Component* Clone(GameObject* _pGameObject);


private:
    PlayerState mPlayerStateNum;
};

