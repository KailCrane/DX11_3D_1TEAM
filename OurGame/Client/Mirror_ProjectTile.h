#pragma once
#include "GameObject.h"
class Mirror_ProjectTile :
    public GameObject
{
public:
	Mirror_ProjectTile();
	virtual ~Mirror_ProjectTile();
	Mirror_ProjectTile* Clone()
	{
		Mirror_ProjectTile* pMirror_projecttile = GameObject::Clone<Mirror_ProjectTile>();
		return pMirror_projecttile;
	}

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

	void MirrorPos();

	float mHP; // ����
	float mSpeed; //�̵��ӵ�
	int mAttackDamage; // ���ݷ�

	
};

