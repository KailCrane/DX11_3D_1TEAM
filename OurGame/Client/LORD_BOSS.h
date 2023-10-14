#pragma once
#include "Monster.h"
#include "TimerObject.h"
class LORD_BOSS_ROLL;
class MonsterSlowObject;
class LORD_BOSS :
    public Monster
{
public:
	LORD_BOSS();
	virtual ~LORD_BOSS();
	LORD_BOSS* Clone()
	{
		LORD_BOSS* pLORD_BOSS = GameObject::Clone<LORD_BOSS>();
		return pLORD_BOSS;
	}

	virtual void SetBehaviorTree();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnCollisionEnter(Collider* _pOtherCollider); //���̳���,����ƽ�� �浹 �Ͼ���� ���Լ���
	virtual void OnCollisionStay(Collider* _pOtherCollider);
	virtual void OnCollisionExit(Collider* _pOtherCollider);

	virtual void OnTriggerEnter(Collider* _pOtherCollider); //Ű��ƽ�� �浹���Ͼ���� ���Լ���
	virtual void OnTriggerStay(Collider* _pOtherCollider);
	virtual void OnTriggerExit(Collider* _pOtherCollider);

public:
	void SetObject(LORD_BOSS_ROLL* _obj) { pObject = _obj; }

	void CutSceneEnd() { isCutSceneEnd = true; }

private:
	
	void SlowTurnLive();
	void SlowTurn(); // �Ⱦ�
	void Follow(); // �Ⱦ� 
	void PrevFollowSet();
	void PrevFollowLive();
	void PrevRollLive();
	bool LookRay(); // �Ⱦ�

	//������ ���϶� ���� �̵�+ȸ��
	void LaserFollow_Turn();
	void LaserPrevFollowSet();
	void LaserPrevFollowLive();
	void CreateCow(Vec3 _pos);

	//���� �ݶ��̴� ������Ʈ
	void MonsterAttackCol();
	void MonsterSilent_ClapCol();
	void MonsterBackswingCol();

	//����ü ����(�׾Ƹ�������)
	void CreatePOTProJectTile();
	void CreatePOTProJectTile(int _a);
private:
	Vec3 RotDir;
	Vec3 PosDir;
	Vec3 PrevDir;

	Vec3 PotProjectPos;

	Vec3 LaserPos = Vec3(14.5f, 10.f, -10.f);
	Vec3 LaserRot = Vec3(-90.f, 360.f, 130.f);

	int Health;
	float TurnSpeed;
	float mMagnScale;
	bool isGround = false;
	bool isWall = false;
	bool isCrash = true;
	bool isSilent_Clap = false;
	bool isCutSceneEnd = false;

	MonsterBasicState PrevState;

	LORD_BOSS_ROLL* pObject;
	GameObject* pMonsterAttackCol;
	MonsterSlowObject* pMonsterSilent_ClapCol;
	GameObject* pBackswingCol;

	TimerObject mTimer;
private:
	//���� ���� bool
	bool isMelee_Jump01 = true;
	bool isMelee_Jump02 = true;
	bool isMelee_Jump03 = true;
	bool isMelee_Slam01 = true;
	bool isMelee_Slam02 = true;
	bool isMelee_Slam03 = true;

	bool isBackSwing = true;

	bool isLaser = true;

	bool isLandSlam = true;

	bool isBall = true;

	bool isRollWall = true;

};

