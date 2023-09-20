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

	GameObject* pObj = pPlayer->GetGreatSword(); //Į ������Ʈ �����ͼ� �ؽ��� �׸��� or ����ȭ �����ϴ� �κ�
	pObj->Disable();
	PlayAnimation();

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
