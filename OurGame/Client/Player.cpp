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
	, mHP(4)
	, mCost(4)
	, mSpeed(5.f)
	, mAttack(1.f)
	, mAttack_Speed(0.04f)
	, mDash_Speed(25.f)
	, meDirectionEvasion(DirectionEvasion::NONE)
	
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
	
	StateChange(PlayerState::IdleState);

	//mActiveState->Initialize();
	
#pragma region "�÷��̾� �ִϸ��̼� �̸� ����"
/*�ִϸ��̼� �̸� ����*/
	//���̵�
	GetAnimator()->RenameAnimation(42, L"_Player_Idle01"); //�̸�����
	GetAnimator()->SetLoop(42, true); //����
	GetAnimator()->SetHasExitFlag(42, true); // ���� �ִϸ��̼� �ٳ����� ���� f ? t
	GetAnimator()->RenameAnimation(43, L"_Player_Idle02");
	GetAnimator()->SetLoop(43, true); 
	GetAnimator()->SetHasExitFlag(43, true); 

	//�̵�
	GetAnimator()->RenameAnimation(67, L"_Player_Move");
	GetAnimator()->SetLoop(67, true);
	GetAnimator()->SetHasExitFlag(67, true);

	//ȸ��
	GetAnimator()->RenameAnimation(63, L"_Player_Evasion");
	GetAnimator()->SetLoop(63, true);
	GetAnimator()->SetHasExitFlag(63, true);
	
	//����
	GetAnimator()->RenameAnimation(69, L"_Player_Attack01");
	GetAnimator()->SetLoop(69, true);
	GetAnimator()->SetHasExitFlag(69, true);
	GetAnimator()->RenameAnimation(70, L"_Player_Attack02");
	GetAnimator()->SetLoop(70, true);
	GetAnimator()->SetHasExitFlag(70, true);

	//����
	GetAnimator()->RenameAnimation(7, L"_Player_Fallstart");
	GetAnimator()->SetLoop(7, true);
	GetAnimator()->SetHasExitFlag(7, true);
	GetAnimator()->RenameAnimation(8, L"_Player_Fallend");
	GetAnimator()->SetLoop(8, true);
	GetAnimator()->SetHasExitFlag(8, true);

	//��ٸ�
	GetAnimator()->RenameAnimation(20, L"_Player_ClimingUp");
	GetAnimator()->SetLoop(20, true);
	GetAnimator()->SetHasExitFlag(20, true);
	GetAnimator()->RenameAnimation(21, L"_Player_ClimingDown");
	GetAnimator()->SetLoop(21, true);
	GetAnimator()->SetHasExitFlag(21, true);
	GetAnimator()->RenameAnimation(22, L"_Player_ClimingEnd");
	GetAnimator()->SetLoop(22, true);
	GetAnimator()->SetHasExitFlag(22, true);





#pragma endregion















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
	mActiveState->Update();
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

	if (LayerType::Monster == pOtherCollider->GetGameObject()->GetLayerType())
	{
		
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

void Player::SetDirectionChange(DirectionEvasion _eState)
{
	meDirectionEvasion = _eState;
}

Player* Player::GetPlayer()
{
	AssertEx(spPlayer != nullptr, L"�÷��̾ Nullptr �̴� _ GetPlayer()~");
	return spPlayer; 
}
