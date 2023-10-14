#include "pch.h"
#include "HitStartState.h"
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

/* Event */
#include "SceneChangeEvent.h"
HitStartState::HitStartState()
	:State(PlayerState::HitStartState)
{
}

void HitStartState::Initialize()
{
}

void HitStartState::Update()
{
	//���� �ɾ �ٸ� ������Ʈ �Ѿ�� ���ִ� ���� �����
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	if (pAni->GetFrameRatio() > 0.6)
	{
		pPlayer->StateChange(PlayerState::HitEndState);
	}
	//pPlayer->StateChange(PlayerState::AttackState);
}

void HitStartState::Enter()
{
	PlayAnimation();
	Player* pPlayer = Player::GetPlayer();
	pPlayer->GetDamage();
	pPlayer->SetisDownState(true);
	pPlayer->SetAttackDamage(1.f);
	GameObject* pObj = pPlayer->GetGreatSword(); //Į ������Ʈ �����ͼ� �ؽ��� �׸��� or ����ȭ �����ϴ� �κ�
	pObj->Disable(); // Į ������Ʈ �ȱ׸���

	GameObject* pArrowObj = pPlayer->GetArrow(); //ȭ�� ������Ʈ
	pArrowObj->Disable(); //ȭ�� �ȱ׸���
	
}

void HitStartState::Exit()
{
}

void HitStartState::PlayAnimation()
{
	//�ִϸ��̼� ���
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	pAni->Play(37, false);
}
