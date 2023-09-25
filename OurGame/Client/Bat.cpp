#include "pch.h"
#include "Bat.h"
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
Bat::Bat()
{
	mHP=3.f; // ����
	mSpeed=2.f; //�̵��ӵ�
	mAttackDamage = 1; // ���ݷ�
	mAttackRange = 2.5f; // ���� ���� �Ÿ�
	mRecogRange = 7.f; //�����Ÿ�
}

Bat::~Bat()
{
}

void Bat::SetBehaviorTree()
{
	AI* pAI = AddComponent(new AI);


	// ��Ʈ ��� ���
	Selector* pRootNode = new Selector;
	pAI->SetRootNode(pRootNode);

	Selector* pStateSelector = new Selector;
	{
#pragma region Hit Sequence
		Sequence* pHitSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Attack���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Hit == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (4 != animIndex)
					pAnimator->Play(4, true);

				return BehaviorResult::Success;
				});

			// Hit �߻��� �۵��ϴ� �������ͽ�
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
				
					if (mHP <= 0) {
						isDead = true;
						meBasicState = MonsterBasicState::Dead;
						return BehaviorResult::Failure;
					}
					
					Animator* pAnimator = GetAnimator();
					if(pAnimator->GetFrameRatio()>0.3)
						return BehaviorResult::Success;

					return BehaviorResult::Failure;
				});

			// ���� ����(Task) : ���� ����
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					SetHitCheck(false);
					meBasicState = MonsterBasicState::Trace;
					return BehaviorResult::Success;
				});

			pHitSequence->AddChild(pStateChecker);
			pHitSequence->AddChild(pRunAnimationTask);
			pHitSequence->AddChild(pAttackTask);
			pHitSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pHitSequence);

#pragma endregion

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
					if (distance < mRecogRange)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});

			

			pIdleSequence->AddChild(pStateChecker);
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pCheckNearbyPlayer);
			pIdleSequence->AddChild(new ChangeStateTask(MonsterBasicState::Idle_to_Trace));
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion

#pragma region Idle_To_Trace Sequence
		Sequence* pIdle_To_TraceSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Idle_To_Trace���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Idle_to_Trace == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (4 != animIndex)
					pAnimator->Play(4, false);

				return BehaviorResult::Success;
				});

			//�ִϸ��̼� �ѹ� ����� ���� ���·� �Ѿ��
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAni = GetAnimator();
					
					if (pAni->GetFrameRatio()>0.3)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});

			//// ���� ����(Task) : ���� ����
			//BehaviorTask* pChangeState = new BehaviorTask([&]()
			//	{
			//		meBasicState = MonsterBasicState::Trace;
			//		return BehaviorResult::Success;
			//	});

			pIdle_To_TraceSequence->AddChild(pStateChecker);
			pIdle_To_TraceSequence->AddChild(pRunAnimationTask);
			pIdle_To_TraceSequence->AddChild(pCheckNearbyPlayer);
			pIdle_To_TraceSequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace));
		}
		pStateSelector->AddChild(pIdle_To_TraceSequence);

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
				if (2 != animIndex) //L"Move"
					pAnimator->Play(2, true);

				return BehaviorResult::Success;
				});

			// �÷��̾� ��ǥ ��ǥ�� ���Ͱ� �̵�+ȸ�� �ϴ� ����(Task)
			BehaviorTask* pTraceMoveTask = new BehaviorTask([&]() {
				Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
				Transform* pTr = GetTransform();
				Vec3 myPos = GetTransform()->GetPosition();
				Vec3 myRot = GetTransform()->GetRotation();

				Vec3 dir = playerPos - myPos;
				dir.Normalize();
				dir.y = 0;
				// ������ �̵��ӵ��� ���� ��
				// ������ �������ִ� Task�� �ʿ�
				GetRigidBody()->SetVelocity(dir * mSpeed);

				Vec3 rot = Vec3(0, 0, -1);
				double angleRadian = atan2(dir.x, dir.z) - atan2(rot.x, rot.z);
				float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

				if (angleDegree < 0.f)
					angleDegree += 360.f;

				//������ ���� ������ �ڵ�
				pTr->SetRotation(Vec3(-90.f, 0.f, angleDegree));
				
				return BehaviorResult::Success;
			});


			// �÷��̾� �Ÿ� Ȯ��(Condition) : �÷��̾ ��ó�� �ִ��� Ȯ��
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();	
					float distance = (playerPos - myPos).Length();
					Animator* pAni = GetAnimator();
	

					
					if (distance < mAttackRange && pAni->GetFrameRatio()>0.7f)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});


			// ���� ����(Task) : ���� ����
			/*BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					meBasicState = MonsterBasicState::Attack;
					return BehaviorResult::Success;
				});*/

			pTraceSequence->AddChild(pStateChecker);
			pTraceSequence->AddChild(pRunAnimationTask);
			pTraceSequence->AddChild(pTraceMoveTask);
			pTraceSequence->AddChild(pCheckNearbyPlayer);
			pTraceSequence->AddChild(new ChangeStateTask(MonsterBasicState::Attack));
		}
		pStateSelector->AddChild(pTraceSequence);

#pragma endregion

#pragma region Attack Sequence
		Sequence* pAttackSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Attack���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Attack == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (0 != animIndex)
					pAnimator->Play(0, true);

				return BehaviorResult::Success;
				});

			// ���� ������
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Animator* pAni = GetAnimator();


					if(pAni->GetFrameRatio()>0.7)
						return BehaviorResult::Success;
					return BehaviorResult::Failure;
				
				});

			// ���� ����(Task) : ���� ����
			/*BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					meBasicState = MonsterBasicState::Trace;
					return BehaviorResult::Success;
				});*/

			pAttackSequence->AddChild(pStateChecker);
			pAttackSequence->AddChild(pRunAnimationTask);
			pAttackSequence->AddChild(pAttackTask);
			pAttackSequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace));
		}
		pStateSelector->AddChild(pAttackSequence);

#pragma endregion

#pragma region Dead Sequence
		Sequence* pDeadSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Attack���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Dead == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (isDead == true)
				{
					isDead = false;
					GetScript<PaperBurnScript>()->SetPaperBurn();
					pAnimator->Play(4, false);
				}

				return BehaviorResult::Success;
				});

			// �����۹� ���� ����
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Animator* pAni= GetAnimator();
					int animIndex = pAni->GetCurrentClipIndex();

					

					if (GetScript<PaperBurnScript>()->IsFinished())
					{
						MapType type = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
						GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, static_cast<GameObject*>(this));
					}


					return BehaviorResult::Success;

				});

			pDeadSequence->AddChild(pStateChecker);
			pDeadSequence->AddChild(pRunAnimationTask);
			pDeadSequence->AddChild(pAttackTask);
			
		}
		pStateSelector->AddChild(pDeadSequence);

#pragma endregion

	}
	pRootNode->AddChild(pStateSelector);
}

void Bat::Initialize()
{
	Monster::Initialize();

	GetAnimator()->RenameAnimation(4, L"Hit"); 
	GetAnimator()->SetLoop(4, true); 
	GetAnimator()->SetHasExitFlag(4, true); 

	GetAnimator()->RenameAnimation(2, L"Idle"); 
	GetAnimator()->SetLoop(2, true); 
	GetAnimator()->SetHasExitFlag(2, true); 

	GetAnimator()->RenameAnimation(1, L"Move"); 
	GetAnimator()->SetLoop(1, true); 
	GetAnimator()->SetHasExitFlag(1, true); 

	GetAnimator()->RenameAnimation(0, L"Attack"); //�̸�����
	GetAnimator()->SetLoop(0, true); //����
	GetAnimator()->SetHasExitFlag(0, true); // ���� �ִϸ��̼� �ٳ����� ���� f ? t


	
}

void Bat::Update()
{
	Monster::Update();
}

void Bat::FixedUpdate()
{
	Monster::FixedUpdate();
}

void Bat::FinalUpdate()
{
	Monster::FinalUpdate();
}

void Bat::Render()
{
	Monster::Render();
}

void Bat::Destroy()
{
	Monster::Destroy();
}

void Bat::OnCollisionEnter(Collider* _pOtherCollider)
{
	int a = 0;
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}
}

void Bat::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Bat::OnCollisionExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}

void Bat::OnTriggerEnter(Collider* _pOtherCollider)
{
	Player* pPlayer = PLAYER;
	float attackDamage = pPlayer->GetAttackDamage();
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}

	if (LayerType::PlayerCol == _pOtherCollider->GetGameObject()->GetLayerType()
		|| LayerType::ArrowCol == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		TakeDamage(attackDamage);
		float hp = mHP;
		meBasicState = MonsterBasicState::Hit;
		SetHitCheck(true);
	}
}

void Bat::OnTriggerStay(Collider* _pOtherCollider)
{
}

void Bat::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}
