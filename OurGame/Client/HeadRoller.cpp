#include "pch.h"
#include "HeadRoller.h"
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
/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "Npc.h"
#include "Monster.h"
#include "Grandma.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"



namespace hm
{
	HeadRoller::HeadRoller()
	{
		mMaxHP = 3.f;
		mHP = mMaxHP; // ����
		mSpeed = 2.f; //�̵��ӵ�
		mAttackDamage = 1; // ���ݷ�
		mAttackRange = 2.5f; // ���� ���� �Ÿ�
		mRecogRange = 7.f; //�����Ÿ�

		meBasicState = MonsterBasicState::Idle;

		SetName(L"HeadRoller");
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
						if (pAnimator->GetFrameRatio() > 0.1)
							return BehaviorResult::Success;

						return BehaviorResult::Failure;
					});

				// ���� ����(Task) : ���� ����
				BehaviorTask* pChangeState = new BehaviorTask([&]()
					{
						SetHitCheck(false);
						meBasicState = MonsterBasicState::Trace_to_Attack;
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
					if (0 != animIndex)
						pAnimator->Play(0, true);

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

				//// ���� ����(Task) : ���� ����
				//BehaviorTask* pChangeState = new BehaviorTask([&]()
				//	{
				//		meBasicState = MonsterBasicState::Trace;
				//		return BehaviorResult::Success;
				//	});

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
					if (3 != animIndex) {
						pAnimator->Play(3, false);
					}

					return BehaviorResult::Success;
					});

				//�ִϸ��̼� �ѹ� ����� ���� ���·� �Ѿ��
				BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
					{
						Animator* pAni = GetAnimator();

						if (pAni->GetFrameRatio() > 0.15)
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
				pIdle_To_TraceSequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace_to_Attack));
			}
			pStateSelector->AddChild(pIdle_To_TraceSequence);

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
						//�ʱ�ȭ �߿�
						GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
						GetTransform()->SetRelativePosition(Vec3(0.f, -1.f, 0.f));
						pAnimator->Play(1, false);
					}

					return BehaviorResult::Success;
					});

				// �÷��̾� ��ǥ ��ǥ�� ���Ͱ� �̵�+ȸ�� �ϴ� ����(Task)
				BehaviorTask* pTraceLookTask = new BehaviorTask([&]() {
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Vec3 myRot = GetTransform()->GetRotation();
					Vec3 scale = GetRigidBody()->GetGeometrySize();
					Animator* pAni = GetAnimator();

					Vec3 dir = playerPos - myPos;
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

					//GetRigidBody()->SetVelocity(Ve); //������� ����� �ڵ�

					Transform* pTr = GetTransform();
					Vec3 rot = Vec3(0, 0, -1);
					double angleRadian = atan2(dir.x, dir.z) - atan2(rot.x, rot.z);
					float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

					if (angleDegree < 0.f)
						angleDegree += 360.f;

					//������ ���� ������ �ڵ�
					pTr->SetRotation(Vec3(0.f, angleDegree, 0.f));



					{
						if (pAni->GetFrameRatio() > 0.05) {
							GetRigidBody()->SetVelocityExcludingColliders(-dir * 8.0f);
							GetRigidBody()->SetVelocity(dir * 8.f);
						}
					}

					{
						//dir ���� �����ؾߴ� Trace_to_attack�ʿ���
						attackDir = playerPos - myPos;
						attackDir.y = 0;
						attackDir.Normalize();
					}

					return BehaviorResult::Success;
					});

			
				// �ݶ��̴� �̵� ����
				BehaviorTask* pAttackMoveTask = new BehaviorTask([&]()
					{
						Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
						Vec3 myPos = GetTransform()->GetPosition();
						Animator* pAni = GetAnimator();

						if (pAni->GetFrameRatio() > 0.1) {
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
				Trace_to_AttackSequence->AddChild(pTraceLookTask);
				Trace_to_AttackSequence->AddChild(pAttackMoveTask);
				Trace_to_AttackSequence->AddChild(new ChangeStateTask(MonsterBasicState::Attack));
			}
			pStateSelector->AddChild(Trace_to_AttackSequence);

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
					if (2 != animIndex) {
						//�ʱ�ȭ �߿�
						GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
						GetTransform()->SetRelativePosition(Vec3(0.f, 0.f, 0.f));
						pAnimator->Play(2, true);
					}

					return BehaviorResult::Success;
					});

				// ���� ������
				BehaviorTask* pAttackTask = new BehaviorTask([&]()
					{
						Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
						Vec3 myPos = GetTransform()->GetPosition();
						Animator* pAni = GetAnimator();

						//�̺κ� �߿�
						GetRigidBody()->SetVelocityExcludingColliders(-attackDir * 14.0f);
						GetRigidBody()->SetVelocity(attackDir * 14.f);

						if (pAni->GetFrameRatio() > 0.15) {
							return BehaviorResult::Success;
						}
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
				pAttackSequence->AddChild(new ChangeStateTask(MonsterBasicState::Stun));
			}
			pStateSelector->AddChild(pAttackSequence);

#pragma endregion

#pragma region Stun Sequence
			Sequence* pStunSequence = new Sequence;
			{
				// ���� Ȯ��(Condition) : ���� ���°� Stun���� Ȯ��
				BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
					{
						if (MonsterBasicState::Stun == meBasicState)
							return BehaviorResult::Success;
						else
							return BehaviorResult::Failure;
					});

				// �ִϸ��̼� ����(Task) : ���¿� �´� �ִϸ��̼��� ������� �ʾҴٸ� ����
				BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
					Animator* pAnimator = GetAnimator();
					int animIndex = pAnimator->GetCurrentClipIndex();
					if (4 != animIndex)
					{
						//�ʱ�ȭ �߿�
						GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
						GetTransform()->SetRelativePosition(Vec3(0.f, -1.f, 0.f));
						pAnimator->Play(4, true);
					}

					return BehaviorResult::Success;
					});

				// �ִϸ��̼� ���� �ð�
				BehaviorTask* pAttackTask = new BehaviorTask([&]()
					{
						Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
						Vec3 myPos = GetTransform()->GetPosition();
						Animator* pAni = GetAnimator();


						if (pAni->GetFrameRatio() > 0.21)
							return BehaviorResult::Success;
						return BehaviorResult::Failure;

					});

				// ���� ����(Task) : ���� ����
				/*BehaviorTask* pChangeState = new BehaviorTask([&]()
					{
						meBasicState = MonsterBasicState::Trace;
						return BehaviorResult::Success;
					});*/

				pStunSequence->AddChild(pStateChecker);
				pStunSequence->AddChild(pRunAnimationTask);
				pStunSequence->AddChild(pAttackTask);
				pStunSequence->AddChild(new ChangeStateTask(MonsterBasicState::Idle_to_Trace));
			}
			pStateSelector->AddChild(pStunSequence);

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
						pAnimator->Play(8, false);
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
	void HeadRoller::OnCollisionEnter(Collider* _pOtherCollider)
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
	void HeadRoller::OnCollisionStay(Collider* _pOtherCollider)
	{
	}
	void HeadRoller::OnCollisionExit(Collider* _pOtherCollider)
	{
		if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			--mGroundCount;

			if (0 == mGroundCount)
				GetRigidBody()->ApplyGravity();
		}
	}
	void HeadRoller::OnTriggerEnter(Collider* _pOtherCollider)
	{
		Player* pPlayer = PLAYER;
		float attackDamage = pPlayer->GetAttackDamage();
		if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			if (mGroundCount == 0)
			{
				GetRigidBody()->RemoveGravity();
				GetRigidBody()->SetVelocity(Vec3::Zero);
			}

			mGroundCount++;
		}

		if (LayerType::Player == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			meBasicState = MonsterBasicState::Stun;
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
	void HeadRoller::OnTriggerStay(Collider* _pOtherCollider)
	{
	}
	void HeadRoller::OnTriggerExit(Collider* _pOtherCollider)
	{
		if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			--mGroundCount;

			if (0 == mGroundCount)
				GetRigidBody()->ApplyGravity();
		}
	}
}

