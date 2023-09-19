#include "pch.h"
#include "E_Bat.h"
#include "AI.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Input.h"
#include "ChangeStateCondition.h"

E_Bat::E_Bat()
{
}

E_Bat::~E_Bat()
{
}

void E_Bat::SetBehaviorTree()
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
				if (3 != animIndex)
					pAnimator->Play(3, true);

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

			pIdleSequence->AddChild(new ChangeStateCondition(MonsterBasicState::Idle));
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pCheckNearbyPlayer);
			pIdleSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion
	}
	pRootNode->AddChild(pStateSelector);
}

void E_Bat::Initialize()
{
}

void E_Bat::Update()
{
}

void E_Bat::FixedUpdate()
{
}

void E_Bat::FinalUpdate()
{
}

void E_Bat::Render()
{
}

void E_Bat::Destroy()
{
}

void E_Bat::OnCollisionEnter(Collider* _pOtherCollider)
{
}

void E_Bat::OnCollisionStay(Collider* _pOtherCollider)
{
}

void E_Bat::OnCollisionExit(Collider* _pOtherCollider)
{
}

void E_Bat::OnTriggerEnter(Collider* _pOtherCollider)
{
}

void E_Bat::OnTriggerStay(Collider* _pOtherCollider)
{
}

void E_Bat::OnTriggerExit(Collider* _pOtherCollider)
{
}
