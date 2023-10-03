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
	mMaxHP = 3.f;
	mHP = mMaxHP; // ����
	mSpeed = 1.5f; //�̵��ӵ�
	mAttackDamage = 1; // ���ݷ�
	mAttackRange = 4.f; // ���� ���� �Ÿ�
	mRecogRange = 9.f; //�����Ÿ�

	meBasicState = MonsterBasicState::Birth;
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
				if (8 != animIndex)
					pAnimator->Play(8, true);

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
					if (pAnimator->GetFrameRatio() > 0.99)
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

#pragma region Birth Sequence
		Sequence* pBirthSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Birth���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Birth == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (10 != animIndex)
					pAnimator->Play(10, true);

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



			pBirthSequence->AddChild(pStateChecker);
			pBirthSequence->AddChild(pRunAnimationTask);
			pBirthSequence->AddChild(pCheckNearbyPlayer);
			pBirthSequence->AddChild(new ChangeStateTask(MonsterBasicState::Hop_dojge));
		}
		pStateSelector->AddChild(pBirthSequence);

#pragma endregion

#pragma region Hop_dojge Sequence
		Sequence* Hop_dojgeSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Hop_dojge���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Hop_dojge == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (8 != animIndex)
					pAnimator->Play(8, false);

				return BehaviorResult::Success;
				});

			//�ִϸ��̼� �ѹ� ����� ���� ���·� �Ѿ��
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAni = GetAnimator();

					if (pAni->GetFrameRatio() > 0.99)
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

			Hop_dojgeSequence->AddChild(pStateChecker);
			Hop_dojgeSequence->AddChild(pRunAnimationTask);
			Hop_dojgeSequence->AddChild(pCheckNearbyPlayer);
			Hop_dojgeSequence->AddChild(new ChangeStateTask(MonsterBasicState::Idle));
		}
		pStateSelector->AddChild(Hop_dojgeSequence);

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
				if (7 != animIndex)
					pAnimator->Play(7, true);

				return BehaviorResult::Success;
				});

			//�ִϸ��̼� �ѹ� ����� ���� ���·� �Ѿ��
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAni = GetAnimator();

					if (pAni->GetFrameRatio() > 0.99)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});

			pIdleSequence->AddChild(pStateChecker);
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pCheckNearbyPlayer);
			pIdleSequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace)); 
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
				if (3 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -0.4f, 0.f));
					pAnimator->Play(3, true);
				}

				return BehaviorResult::Success;
				});

			// �÷��̾� ��ǥ ��ǥ�� ���Ͱ� �̵�+ȸ�� �ϴ� ����(Task)
			BehaviorTask* pTraceMoveTask = new BehaviorTask([&]() {
				Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
				Vec3 myPos = GetTransform()->GetPosition();
				Vec3 myRot = GetTransform()->GetRotation();
				Vec3 scale = GetRigidBody()->GetGeometrySize();

				dir = playerPos - myPos;
				Vec3 Num = scale * dir;
				float offset = max(max(fabs(scale.x), fabs(scale.y)), fabs(scale.z));

				dir.Normalize();
				dir.y = 0;
				// ������ �̵��ӵ��� ���� ��
				// ������ �������ִ� Task�� �ʿ�
				Vec3 Ve = dir * mSpeed;

				const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(LayerType::Ground);

				for (int i = 0; i < gameObjects.size(); ++i)
				{
					if (gameObjects[i]->GetCollider())
					{
						for (size_t j = 1; j <= 8; j++)
						{
							if (GetCollider()->Raycast(myPos, ConvertDir(static_cast<DirectionEvasion>(j)), gameObjects[i]->GetCollider(), offset + 0.5f))
							{
								if (static_cast<DirectionEvasion>(j) == DirectionEvasion::FORWARD)
								{
									Ve.z = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::BACKWARD)
								{
									Ve.z = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::LEFT)
								{
									Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::RIGHT)
								{
									Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::TOPLEFT)
								{
									if (Ve.x > Ve.z)
										Ve.z = 0;
									else
										Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::TOPRIGHT)
								{
									if (Ve.x > Ve.z)
										Ve.z = 0;
									else
										Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::BOTTOMLEFT)
								{
									if (Ve.x > Ve.z)
										Ve.z = 0;
									else
										Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::BOTTOMRIGHT)
								{
									if (Ve.x > Ve.z)
										Ve.z = 0;
									else
										Ve.x = 0;
								}

							}
						}
					}
				}



				GetRigidBody()->SetVelocity(Ve); //������� ����� �ڵ�
				//GetTransform()->SetPositionExcludingColliders(-Ve * 0.5f);

				Transform* pTr = GetTransform();
				Vec3 rot = Vec3(0, 0, -1);
				double angleRadian = atan2(dir.x, dir.z) - atan2(rot.x, rot.z);
				float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

				if (angleDegree < 0.f)
					angleDegree += 360.f;

				//������ ���� ������ �ڵ�
				pTr->SetRotation(Vec3(-90.f, 0.f, angleDegree));

				//�̺κ� �߿�
				GetRigidBody()->SetVelocityExcludingColliders(-dir * 2.0f);
				GetRigidBody()->SetVelocity(dir * 2.f);

				return BehaviorResult::Success;
				});


			// �÷��̾� �Ÿ� Ȯ��(Condition) : �÷��̾ ��ó�� �ִ��� Ȯ��
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					float distance = (playerPos - myPos).Length();
					Animator* pAni = GetAnimator();

					if (pAni->GetFrameRatio() > 0.99f)
					{
						GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
						GetTransform()->SetRelativePosition(Vec3(0.f, -0.4f, 0.f));
					}


					if (distance < mAttackRange && pAni->GetFrameRatio()>0.99f)
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
			pTraceSequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace_to_Attack));
		}
		pStateSelector->AddChild(pTraceSequence);

#pragma endregion

#pragma region Trace_to_Attack Sequence
		Sequence* Trace_to_AttackSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Hop_dojge���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Trace_to_Attack == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (1 != animIndex) {
					
					pAnimator->Play(1, false);
				}

				return BehaviorResult::Success;
				});

			//�ִϸ��̼� �ѹ� ����� ���� ���·� �Ѿ��
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAni = GetAnimator();

					if (pAni->GetFrameRatio() > 0.99)
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

			Trace_to_AttackSequence->AddChild(pStateChecker);
			Trace_to_AttackSequence->AddChild(pRunAnimationTask);
			Trace_to_AttackSequence->AddChild(pCheckNearbyPlayer);
			Trace_to_AttackSequence->AddChild(new ChangeStateTask(MonsterBasicState::Attack01));
		}
		pStateSelector->AddChild(Trace_to_AttackSequence);

#pragma endregion

#pragma region Attack01 Sequence
		Sequence* pAttackSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Attack���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Attack01 == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (2 != animIndex)
					pAnimator->Play(2, true);

				return BehaviorResult::Success;
				});

			// ���� ������
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Animator* pAni = GetAnimator();

					//�̺κ� �߿�
					GetRigidBody()->SetVelocityExcludingColliders(-dir * 6.8f);
					GetRigidBody()->SetVelocity(dir * 6.8f);

					if (pAni->GetFrameRatio() > 0.7)
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
				GameObject* pObj = GetGameObject(); //�̰� Ȯ�ε� �ʿ���
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (isDead == true)
				{
					//pObj->GetRigidBody()->SetSimulationShapeFlag(false);
					//pObj->Disable();
					isDead = false;
					GetScript<PaperBurnScript>()->SetPaperBurn();
					pAnimator->Play(9, false);
				}

				//pObj->GetRigidBody()->SetSimulationShapeFlag(false); // �ݶ��̴� ����
				//pObj->GetRigidBody()->SetSimulationShapeFlag(true); // �ݶ��̴� �ѱ�


				return BehaviorResult::Success;
				});

			// �����۹� ���� ����
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Animator* pAni = GetAnimator();
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
		if (mGroundCount == 0)
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}

		mGroundCount++;
	}
}

void Lurker::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Lurker::OnCollisionExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}




void Lurker::OnTriggerEnter(Collider* _pOtherCollider)
{
	Player* pPlayer = PLAYER;
	float attackDamage = pPlayer->GetAttackDamage();

	if (LayerType::PlayerCol == _pOtherCollider->GetGameObject()->GetLayerType()
		|| LayerType::ArrowCol == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		TakeDamage(attackDamage);
		float hp = mHP;
		meBasicState = MonsterBasicState::Hit;
		SetHitCheck(true);
	}

	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		if (mGroundCount == 0)
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}

		mGroundCount++;
	}
}

void Lurker::OnTriggerStay(Collider* _pOtherCollider)
{
}

void Lurker::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}
