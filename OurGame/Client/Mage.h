#pragma once
#include "Monster.h"
class MageColScript;
class Mage :
	public Monster
{
public:
	Mage();
	virtual ~Mage();
	Mage* Clone()
	{
		Mage* pMage = GameObject::Clone<Mage>();
		return pMage;
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
	void Teleport();
private:
	GameObject* pMageCol;
	MageColScript* pMageColSc;

	bool isTrigger01 = false;
	bool isTrigger02 = false;
	bool isTrigger03 = false;
};