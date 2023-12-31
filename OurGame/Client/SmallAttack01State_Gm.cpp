#include "pch.h"
#include "SmallAttack01State_Gm.h"
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
SmallAttack01State_Gm::SmallAttack01State_Gm()
	: State_Grandma(GrandmaState::SmallAttack01State)
	, mCount_Ani(0)
{
}

void SmallAttack01State_Gm::Initialize()
{
}

void SmallAttack01State_Gm::Update()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();
	Transform* Tr_Gm = pGrandma->GetTransform();

	//pGrandma->StateChange_Grandma(GrandmaState::IdleState);

	if (mCount_Ani > 2) {
		mCount_Ani = 0;
		pGrandma->StateChange_Grandma(GrandmaState::Small_IdleState);
	}

	if (pAni_Gm->GetFrameRatio() > 0.25) {
		PlayAnimation(); // 애니메이션 실행

		//포지션 이동
		{
			Vec3 pos = Tr_Gm->GetPosition();
			pos.z = pos.z - 6.f;
			Tr_Gm->SetPosition(pos);
		}

		mCount_Ani++; // 횟수 조절
	}
}

void SmallAttack01State_Gm::Enter()
{
	PlayAnimation();
}

void SmallAttack01State_Gm::Exit()
{
}

void SmallAttack01State_Gm::PlayAnimation()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();
	pAni_Gm->Play(18, false);
}
