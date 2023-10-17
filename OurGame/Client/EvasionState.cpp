#include "pch.h"
#include "EvasionState.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"
#include "ClientEnum.h"

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
#include "State.h"

/* Event */
#include "SceneChangeEvent.h"

EvasionState::EvasionState()
	:State(PlayerState::EvasionState)
{
}

void EvasionState::Initialize()
{
}

void EvasionState::Update()
{
	//���� �ɾ �ٸ� ������Ʈ �Ѿ�� ���ִ� ���� �����
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	Transform* pTr = pPlayer->GetTransform();
	RigidBody* pRb = pPlayer->GetRigidBody();

	if (pAni->GetFrameRatio() > 0.2f)
		pPlayer->StateChange(PlayerState::IdleState);


	//�����ͼ� ƨ��� �� �ֱ�
	DirectionEvasion eDE = pPlayer->GetDirectioninfo();
	float DashSpeed = pPlayer->GetDashSpeed();

	Vec3 totalDir = ConvertDir(eDE); // 8���� ���� üũ�� �ִ� �� ���� ����
	pRb->SetVelocity(totalDir * DashSpeed);
	
	
}

void EvasionState::Enter()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	Transform* pTr = pPlayer->GetTransform();
	RigidBody* pRb = pPlayer->GetRigidBody();

	if (IS_PRESS(P_UP))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::FORWARD);
	}

	if (IS_PRESS(P_DOWN))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::BACKWARD);
	}

	if (IS_PRESS(P_RIGHT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::RIGHT);
	}

	if (IS_PRESS(P_LEFT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::LEFT);
	}

	if (IS_PRESS(P_UP) && IS_PRESS(P_LEFT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::TOPLEFT);
	}

	if (IS_PRESS(P_UP) && IS_PRESS(P_RIGHT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::TOPRIGHT);
	}

	if (IS_PRESS(P_DOWN) && IS_PRESS(P_LEFT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::BOTTOMLEFT);
	}

	if (IS_PRESS(P_DOWN) && IS_PRESS(P_RIGHT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::BOTTOMRIGHT);
	}

	float mMoveSpeed = pPlayer->GetMoveSpeed();
	Transform* tr = pPlayer->GetTransform();
	RigidBody* rb = pPlayer->GetRigidBody();
	DirectionEvasion Dir = pPlayer->GetDirectioninfo();
	if (IS_PRESS(P_UP))
	{
		tr->SetRotation(Vec3(0.f, 180.f, 90.f));
		//tr->SetRotation(Vec3(-90.f, 0.f, 180.f));
	}

	if (IS_PRESS(P_DOWN))
	{
		tr->SetRotation(Vec3(0.f, 0.f, 90.f));

	}

	if (IS_PRESS(P_LEFT))
	{
		tr->SetRotation(Vec3(0.f, 90.f, 90.f));

	}

	if (IS_PRESS(P_RIGHT))
	{
		tr->SetRotation(Vec3(0.f, -90.f, 90.f));

	}

	if (IS_PRESS(P_UP) && IS_PRESS(P_LEFT))
	{
		//mMoveSpeed = mMoveSpeed / 1.5f;
		tr->SetRotation(Vec3(0.f, 135.f, 90.f));
	}
	if (IS_PRESS(P_UP) && IS_PRESS(P_RIGHT))
	{
		//mMoveSpeed = mMoveSpeed / 1.5f;
		tr->SetRotation(Vec3(0.f, 225.f, 90.f));
	}
	if (IS_PRESS(P_DOWN) && IS_PRESS(P_LEFT))
	{
		//mMoveSpeed = mMoveSpeed / 1.5f;
		tr->SetRotation(Vec3(0.f, 45.f, 90.f));
	}
	if (IS_PRESS(P_DOWN) && IS_PRESS(P_RIGHT))
	{
		//mMoveSpeed = mMoveSpeed / 1.5f;
		tr->SetRotation(Vec3(0.f, 315.f, 90.f));
	}


	GameObject* pObj = pPlayer->GetGreatSword(); //Į ������Ʈ �����ͼ� �ؽ��� �׸��� or ����ȭ �����ϴ� �κ�
	pObj->Disable();
	GameObject* pObjCol = pPlayer->GetAttackCol(); 
	pObjCol->Disable();

	PlayAnimation();

	AudioSound* pSound = pPlayer->GetAudioSound();
	pSound->SetSound(L"Evasion", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\Player\\PlayerRoll.ogg");
	pSound->Play(150);

}

void EvasionState::Exit()
{
	Player* pPlayer = Player::GetPlayer();

	GameObject* pObj = pPlayer->GetGreatSword(); //Į ������Ʈ �����ͼ� �ؽ��� �׸��� or ����ȭ �����ϴ� �κ�
	pObj->Enable(); 
}

void EvasionState::PlayAnimation()
{
	//�ִϸ��̼� ���
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	pAni->Play(63, false);
}
