#include "pch.h"
#include "HeadRoller.h"
#include "AI.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Collider.h"

#define IDLE_ANIM_INDEX 0
#define TRACE_ANIM_INDEX 3

namespace hm
{
	HeadRoller::HeadRoller()
		: meBasicState(MonsterBasicState::Idle)
	{
	}

	HeadRoller::~HeadRoller()
	{
	}

	void HeadRoller::SetBehaviorTree()
	{
		/*
		* �����̺�� Ʈ���� ����ϴ� ���ʹ� ��� SetBehaviorTree �Լ��� �������̵��ؼ� �����ؾ� ��
		* �� �Լ��� Monster Ŭ������ Initialize���� �ڵ����� ȣ���
		* �� �Լ����� �ϴ� �� : AI ������Ʈ ����, �����̺�� ��� ����
		* ���� § ���� �ڵ忡���� ���� �Լ��� ���� �� �ְԲ� �ؼ� ����ȭ������ 
		* �����δ� ��带 ���� ���Ͱ� �������� ���� Ŭ����ȭ�ؼ� �߰��ϴ°� �� ����
		* ex) RunAnimationTask�� ��� BehaviorTask�� ��ӹ��� RunBehaviorTask Ŭ������ ������ �� �������� ���ڷ� �ִϸ��̼��� �ε����� �̸��� �ްԲ� �Ͽ� ����
		*/
		AI* pAI = AddComponent(new AI);
		Player* pPlayer = PLAYER;
		
		// ��Ʈ ��� ���
		Selector* pRootNode = new Selector;
		pAI->SetRootNode(pRootNode);

		Selector* pStateSelector = new Selector;
		{
#pragma region Idle Sequence
			Sequence* pIdleSequence = new Sequence;
			{
				// ���� Ȯ��(Condition) : ���� ���°� Idle���� Ȯ��
				BehaviorCondition* pStateChecker= new BehaviorCondition([&]()
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
					if (IDLE_ANIM_INDEX != animIndex)
						pAnimator->Play(IDLE_ANIM_INDEX, true);

					return BehaviorResult::Success;
					});

				// �÷��̾� �Ÿ� Ȯ��(Condition) : �÷��̾ ��ó�� �ִ��� Ȯ��
				BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]() 
					{
						Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
						Vec3 myPos = GetTransform()->GetPosition();

						float distance = (playerPos - myPos).Length();
						if (distance < 10.f)
						{
							return BehaviorResult::Success;
						}
						return BehaviorResult::Failure;
					});

				// ���� ����(Task) : ���� ����
				BehaviorTask* pChangeState = new BehaviorTask([&]()
					{
						meBasicState = MonsterBasicState::Trace;
						return BehaviorResult::Success;
					});

				pIdleSequence->AddChild(pStateChecker);
				pIdleSequence->AddChild(pRunAnimationTask);
				pIdleSequence->AddChild(pCheckNearbyPlayer);
				pIdleSequence->AddChild(pChangeState);
			}
			pStateSelector->AddChild(pIdleSequence);

#pragma endregion
#pragma region Trace Sequence
			Sequence* pTraceSequence = new Sequence;
			{
				// ���� Ȯ��(Condition) : ���� ���°� Trace���� Ȯ��
				BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
					{
						if (MonsterBasicState::Trace == meBasicState)
							return BehaviorResult::Success;
						else
							return BehaviorResult::Failure;
					});

				// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
				BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
					Animator* pAnimator = GetAnimator();
					int animIndex = pAnimator->GetCurrentClipIndex();
					if (TRACE_ANIM_INDEX != animIndex)
						pAnimator->Play(TRACE_ANIM_INDEX, true);

					return BehaviorResult::Success;
					});

				// ���� ����(Task) : �÷��̾��� ������ Ȯ���Ͽ� ����
				BehaviorTask* pTraceTask = new BehaviorTask([&]() {
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					
					Vec3 dir = playerPos - myPos;
					dir.Normalize();

					// ������ �̵��ӵ��� ���� ��
					// ������ �������ִ� Task�� �ʿ�
					GetRigidBody()->SetVelocity(dir * 1.f);

					return BehaviorResult::Success;
					});

				pTraceSequence->AddChild(pStateChecker);
				pTraceSequence->AddChild(pRunAnimationTask);
				pTraceSequence->AddChild(pTraceTask);
			}
			pStateSelector->AddChild(pTraceSequence);

#pragma endregion
		}
		pRootNode->AddChild(pStateSelector);

	}

	void HeadRoller::Initialize()
	{
		Monster::Initialize();
	}

	void HeadRoller::Update()
	{
		Monster::Update();
	}

	void HeadRoller::FixedUpdate()
	{
		Monster::FixedUpdate();
	}

	void HeadRoller::FinalUpdate()
	{
		Monster::FinalUpdate();
	}

	void HeadRoller::Render()
	{
		Monster::Render();
	}

	void HeadRoller::Destroy()
	{
		Monster::Destroy();
	}
	void HeadRoller::OnTriggerEnter(Collider* _pOtherCollider)
	{
		if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}
	}
	void HeadRoller::OnTriggerStay(Collider* _pOtherCollider)
	{
	}
	void HeadRoller::OnTriggerExit(Collider* _pOtherCollider)
	{
		if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			GetRigidBody()->ApplyGravity();
		}
	}
}

