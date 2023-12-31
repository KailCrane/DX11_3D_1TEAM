#pragma once
#include "Monster.h"
class Grimace :
	public Monster
{
public:
	Grimace();
	virtual ~Grimace();
	Grimace* Clone()
	{
		Grimace* pGrimace = GameObject::Clone<Grimace>();
		return pGrimace;
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

private:
	void CreateProjectTile();
	void MonsterAttackCol();

	void BackstepRotTurn();
	void BackstepDirSet();
	void BackstepDirLive();

	void CreateMonsterWavefirst();
	void CreateMonsterWaveSecond();
private:
	Vec3 dir;
	Vec3 dir_backstep;
	Vec3 Ve_backstep;
	Vec3 dir_desh;

	GameObject* pMonsterAttackCol;
	int Health;

	bool isTrigger = false;

	float Shaketime;
	float ShakeNum;

private:
	bool isattack01 = true;
	bool isattack02 = true;
	bool isattack03 = true;
	bool isbackdash = true;


};