#include "pch.h"
#include "ArrowScript.h"
#include "GameObject.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"

/* Manager */
#include "PrefabManager.h"
#include "EventManager.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Resources.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "Npc.h"
#include "Monster.h"
#include "Grandma.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"
#include "SwordHeavyEffect.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "AttackState.h"

/* Event */
#include "SceneChangeEvent.h"
ArrowScript::ArrowScript()
{
	timerObj.SetEndTime(0.9f); //ȭ�� �ܿ� �ð� ����
	mSpeed = 20;
}

void ArrowScript::Initialize()
{
}

void ArrowScript::FixedUpdate()
{
	Player* pPlayer = Player::GetPlayer(); // �÷��̾�*
	Animator* pAni = pPlayer->GetAnimator(); // �÷��̾� �ִϸ��̼�
	Transform* pPlyer_Tr = pPlayer->GetTransform(); //�÷��̾� Ʈ������
	DirectionEvasion eDir = pPlayer->GetDirectioninfo(); // �÷��̾� 8���� ���� �������°�
	mPlayerStateNum; //�÷��̾� ����FSM

	Transform* pTr = GetTransform(); // ȭ�� Ʈ������
	GameObject* pObj = GetGameObject(); // ȭ�� ������Ʈ
	RigidBody* pRb = GetRigidBody();
	pRb->SetMaxVelocity(100.f);

	Vec3 Pos = pPlyer_Tr->GetPosition(); //�÷��̾� Pos
	Vec3 Rot = pTr->GetRotation(); // ȭ�� ȸ�� Rot

	timerObj.Update(); //�߻��� ��Ÿ���� �ð� Ȯ�ο�

#pragma region �÷��̾� ���⿡���� ȭ�� ��ġ
	if (ArrowAtkCheck == false) //ȭ���� ���ݻ��°� �ƴҶ�
	{ 
		timerObj.Stop();

		if (eDir == DirectionEvasion::BACKWARD) {
			Pos.x -= 0.15f;
			Pos.z -= 0.25;
			Pos.y += 0.25f;
			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(0.f, 180.f, 0.f));

		}
		if (eDir == DirectionEvasion::FORWARD) {
			Pos.x += 0.15f;
			Pos.z += 0.25;
			Pos.y += 0.25f;
			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(0.f, 0.f, 0.f));
		}
		if (eDir == DirectionEvasion::LEFT) {
			Pos.x -= 0.25f;
			Pos.z += 0.15f;
			Pos.y += 0.25f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(0.f, 270.f, 0.f));
		}
		if (eDir == DirectionEvasion::RIGHT) {
			Pos.x += 0.25f;
			Pos.z -= 0.15f;
			Pos.y += 0.25f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(0.f, 90.f, 0.f));
		}

		if (eDir == DirectionEvasion::TOPLEFT) {
			Pos.x += 0.00f;
			Pos.z += 0.30f;
			Pos.y += 0.25f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(0.f, 315.f, 0.f));
		}

		if (eDir == DirectionEvasion::TOPRIGHT) {
			Pos.x += 0.30f;
			Pos.z -= 0.00f;
			Pos.y += 0.25f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(0.f, 45.f, 0.f));
		}

		if (eDir == DirectionEvasion::BOTTOMLEFT) {
			Pos.x -= 0.30f;
			Pos.z -= 0.00f;
			Pos.y += 0.25f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(0.f, 225.f, 0.f));
		}

		if (eDir == DirectionEvasion::BOTTOMRIGHT) {
			Pos.x -= 0.00f;
			Pos.z -= 0.30f;
			Pos.y += 0.25f;

			pTr->SetPosition(Pos);
			pTr->SetRotation(Vec3(0.f, 135.f, 0.f));
		}
	}
#pragma endregion

	if (ArrowAtkCheck == true) //ȭ���� ���� �����϶�
	{
		pRb->SetVelocity(DirPos * mSpeed);
		timerObj.Start();
		if (timerObj.IsFinished() == true)
		{
			timerObj.Stop();
			pObj->Disable();
			//isBurn = false;
		}
	}

	if (isBurn == true) {
		mSpeed = 20;

		mpLight->Enable();
		mpParticle->Enable();
	}

	else
	{
		//mpLight->Disable();
		//mpParticle->Disable();
	}
	
}

void ArrowScript::SetPlayerState(PlayerState _eStateNum)
{
	mPlayerStateNum = _eStateNum;
}

Component* ArrowScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new ArrowScript);
}
