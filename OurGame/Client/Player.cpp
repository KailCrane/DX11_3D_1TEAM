#include "pch.h"
#include "Player.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"

 /*State ����*/
#include "State.h"
#include "PauseState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "MagicAttackState.h"
#include "EvasionState.h"
#include "FallState.h"
#include "HitState.h"
#include "FallDownState.h"
#include "DeadState.h"

Player* Player::spPlayer;

Player::Player()
	: GameObject(LayerType::Player)
{
	AssertEx(spPlayer == nullptr, L"�̹� ���� �÷��̾� ������");
	spPlayer = this; //�������� ����

	mState[int(PlayerState::PauseState)] = new PauseState;
	mState[int(PlayerState::IdleState)] = new IdleState;
	mState[int(PlayerState::MoveState)] = new MoveState;
	mState[int(PlayerState::AttackState)] = new AttackState;
	mState[int(PlayerState::MagicAttackState)] = new MagicAttackState;
	mState[int(PlayerState::EvasionState)] = new EvasionState;
	mState[int(PlayerState::FallState)] = new FallState;
	mState[int(PlayerState::HitState)] = new HitState;
	mState[int(PlayerState::FallDownState)] = new FallDownState;
	mState[int(PlayerState::DeadState)] = new DeadState;

	
}

Player::~Player()
{
	for (size_t i = 0; i < PLAYER_STATE_COUNT; i++)
	{
		SAFE_DELETE(mState[i]);
	}
}

void Player::Initialize()
{
	GameObject::Initialize();
	
	//StateChange(PlayerState::IdleState);

	//mActiveState->Initialize();
	



	//GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

	/* �ִϸ��̼��� �̸��� FBX�� ����Ǿ� �ִ� ���� �״�� �������Ƿ� �ش� FBX�� ����ϴ� Ŭ������ �����ڿ� ���� Ư�� �κп���
			 ����ϱ� ���� �̸����� �ϰ������� �ٲ��� �ʿ䰡 ����
	pPotHead->GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

	 �ݺ� ���θ� �����ϴ� �Լ� (Finished �÷��׸� ����� �� ����)
	pPotHead->GetAnimator()->SetLoop(L"PotHead_Idle", true);

	 �ε��� ��ȣ�ε� ��� ����
	pPotHead->GetAnimator()->SetLoop(9, true);

	 HasExit�� ���� �ִϸ��̼� �����߿� �ٸ� �ִϸ��̼��� ����Ǿ��� �� �ٷ� �ѱ���� ���θ� ���� (�⺻������ true)
	 �� ���� false�� �ִϸ��̼� �÷��� ���� �ٸ� �ִϸ��̼� Play�� ����Ǿ��� �� ���� �ִϸ��̼��� �� ������ �����
	pPotHead->GetAnimator()->SetHasExitFlag(9, false);*/

	
}

void Player::Update()
{
	GameObject::Update();
	//mActiveState->Update();
}

void Player::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void Player::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Player::Render()
{
	GameObject::Render();
}

void Player::Destroy()
{
	GameObject::Destroy();
}

void Player::OnTriggerEnter(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}
}

void Player::OnTriggerStay(Collider* pOtherCollider)
{
}

void Player::OnTriggerExit(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}

void Player::StateChange(PlayerState _eState)
{
	if (mActiveState != nullptr) {
		mActiveState->Exit();
	}

	mActiveState = mState[int(_eState)];
	mActiveState->Enter();
}

Player* Player::GetPlayer()
{
	AssertEx(spPlayer != nullptr, L"�÷��̾ Nullptr �̴� _ GetPlayer()~");
	return spPlayer; 
}
