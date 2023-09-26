#include "pch.h"
#include "Lurker.h"
#include "AI.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Input.h"
#include "ChangeStateCondition.h"
#include "PaperBurnScript.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "ChangeStateTask.h"

Lurker::Lurker()
{
	mHP = 3.f; // ����
	mSpeed = 2.f; //�̵��ӵ�
	mAttackDamage = 1; // ���ݷ�
	mAttackRange = 2.5f; // ���� ���� �Ÿ�
	mRecogRange = 7.f; //�����Ÿ�
}

Lurker::~Lurker()
{
}

void Lurker::SetBehaviorTree()
{
	AI* pAI = AddComponent(new AI);

	// ��Ʈ ��� ���
	Selector* pRootNode = new Selector;
	pAI->SetRootNode(pRootNode);

	Selector* pStateSelector = new Selector;
	{

#pragma region Idle Sequence
		Sequence* pIdleSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Idle���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Idle == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				/*if (3 != animIndex)
					pAnimator->Play(3, true);*/

				return BehaviorResult::Success;
				});

			// �÷��̾� �Ÿ� Ȯ��(Condition) : �÷��̾ ��ó�� �ִ��� Ȯ��
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();

					float distance = (playerPos - myPos).Length();
					if (distance < mRecogRange)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pIdleSequence->AddChild(pStateChecker);
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pCheckNearbyPlayer);
			//pIdleSequence->AddChild(new ChangeStateTask(MonsterBasicState::Idle_to_Trace)); //���� �ٲ��ִ� �κ� ����ߵ�
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion



	}
	pRootNode->AddChild(pStateSelector);
}

void Lurker::Initialize()
{
	Monster::Initialize();
}

void Lurker::Update()
{
	Monster::Update();
}

void Lurker::FixedUpdate()
{
	Monster::FixedUpdate();
}

void Lurker::FinalUpdate()
{
	Monster::FinalUpdate();
}

void Lurker::Render()
{
	Monster::Render();
}

void Lurker::Destroy()
{
	Monster::Destroy();
}

void Lurker::OnCollisionEnter(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}
}

void Lurker::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Lurker::OnCollisionExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}




void Lurker::OnTriggerEnter(Collider* _pOtherCollider)
{
	Player* pPlayer = PLAYER;
	float attackDamage = pPlayer->GetAttackDamage();
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}
}

void Lurker::OnTriggerStay(Collider* _pOtherCollider)
{
}

void Lurker::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}
