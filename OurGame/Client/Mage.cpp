#include "pch.h"
#include "Mage.h"
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

Mage::Mage()
{
	mHP = 3.f; // ����
	mSpeed = 2.f; //�̵��ӵ�
	mAttackDamage = 1; // ���ݷ�
	mAttackRange = 10.f; // ���� ���� �Ÿ�
	mRecogRange = 5.f; //�����Ÿ�

	meBasicState = MonsterBasicState::Idle;
}

Mage::~Mage()
{
}

void Mage::SetBehaviorTree()
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
					if (pAnimator->GetFrameRatio() > 0.05)
						return BehaviorResult::Success;

					return BehaviorResult::Failure;
				});

			// ���� ����(Task) : ���� ����
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					SetHitCheck(false);
					meBasicState = MonsterBasicState::Teleport_Out;
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
				if (0 != animIndex)
					pAnimator->Play(0, true);

				return BehaviorResult::Success;
				});

			// �÷��̾� �Ÿ� Ȯ��(Condition) : �÷��̾ ��ó�� �ִ��� Ȯ��
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAnimator = GetAnimator();
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();


					float distance = (playerPos - myPos).Length();
					if (distance < mRecogRange && pAnimator->GetFrameRatio()>0.99)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pIdleSequence->AddChild(pStateChecker);
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pCheckNearbyPlayer);
			pIdleSequence->AddChild(new ChangeStateTask(MonsterBasicState::Teleport_Out)); //���� �������� �Ѿ�� State ��������ߵ�
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion

#pragma region Teleport_out Sequence
		Sequence* pTeleport_outSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Idle���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Teleport_Out == meBasicState)
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

			// ���� ���·� �Ѿ�� ���� 
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAnimator = GetAnimator();
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();

					float distance = (playerPos - myPos).Length();
					if (pAnimator->GetFrameRatio()>0.98)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pTeleport_outSequence->AddChild(pStateChecker);
			pTeleport_outSequence->AddChild(pRunAnimationTask);
			pTeleport_outSequence->AddChild(pCheckNearbyPlayer);
			pTeleport_outSequence->AddChild(new ChangeStateTask(MonsterBasicState::Teleport_In)); //���� �������� �Ѿ�� State ��������ߵ�
		}
		pStateSelector->AddChild(pTeleport_outSequence);

#pragma endregion

#pragma region Teleport_in Sequence
		Sequence* pTeleport_inSequence = new Sequence;
		{
			// ���� Ȯ��(Condition) : ���� ���°� Idle���� Ȯ��
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Teleport_In == meBasicState)
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

			// ���� ���·� �Ѿ�� ���� 
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAnimator = GetAnimator();
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();

					float distance = (playerPos - myPos).Length();
					if (pAnimator->GetFrameRatio() > 0.78)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pTeleport_inSequence->AddChild(pStateChecker);
			pTeleport_inSequence->AddChild(pRunAnimationTask);
			pTeleport_inSequence->AddChild(pCheckNearbyPlayer);
			pTeleport_inSequence->AddChild(new ChangeStateTask(MonsterBasicState::Attack)); //���� �������� �Ѿ�� State ��������ߵ�
		}
		pStateSelector->AddChild(pTeleport_inSequence);

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
				if (5 != animIndex)
					pAnimator->Play(5, true);

				return BehaviorResult::Success;
				});

			// �÷��̾� ��ǥ ��ǥ�� ���Ͱ� �̵�+ȸ�� �ϴ� ����(Task)
			BehaviorTask* pAttackMoveTask = new BehaviorTask([&]() {
				Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
				Vec3 myPos = GetTransform()->GetPosition();
				Vec3 myRot = GetTransform()->GetRotation();
				Vec3 scale = GetRigidBody()->GetGeometrySize();

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
				pTr->SetRotation(Vec3(-90.f, 0.f, angleDegree));

				return BehaviorResult::Success;
				});

			// ���� ������
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Animator* pAni = GetAnimator();


					if (pAni->GetFrameRatio() > 0.99)
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
			pAttackSequence->AddChild(pAttackMoveTask);
			pAttackSequence->AddChild(pAttackTask);
			pAttackSequence->AddChild(new ChangeStateTask(MonsterBasicState::Idle));
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

void Mage::Initialize()
{
	Monster::Initialize();

	GetAnimator()->RenameAnimation(0, L"Idle");
	GetAnimator()->SetLoop(0, true);
	GetAnimator()->SetHasExitFlag(0, true);

	GetAnimator()->RenameAnimation(1, L"attack");
	GetAnimator()->SetLoop(1, true);
	GetAnimator()->SetHasExitFlag(1, true);

	GetAnimator()->RenameAnimation(2, L"Teleport_out");
	GetAnimator()->SetLoop(2, true);
	GetAnimator()->SetHasExitFlag(2, true);

	GetAnimator()->RenameAnimation(3, L"Teleport_in");
	GetAnimator()->SetLoop(3, true);
	GetAnimator()->SetHasExitFlag(3, true);

	GetAnimator()->RenameAnimation(4, L"Death");
	GetAnimator()->SetLoop(4, true);
	GetAnimator()->SetHasExitFlag(4, true);

	GetAnimator()->RenameAnimation(5, L"attack_three");
	GetAnimator()->SetLoop(5, true);
	GetAnimator()->SetHasExitFlag(5, true);

	GetAnimator()->RenameAnimation(6, L"Turn_repeat");
	GetAnimator()->SetLoop(6, true);
	GetAnimator()->SetHasExitFlag(6, true);

	
}

void Mage::Update()
{
	Monster::Update();
}

void Mage::FixedUpdate()
{
	Monster::FixedUpdate();
}

void Mage::FinalUpdate()
{
	Monster::FinalUpdate();
}

void Mage::Render()
{
	Monster::Render();
}

void Mage::Destroy()
{
	Monster::Destroy();
}

void Mage::OnCollisionEnter(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		// �ӽ� �ڵ�
		if (mGroundCount == 0)
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}

		mGroundCount++;
	}
}

void Mage::OnCollisionStay(Collider* _pOtherCollider)
{

}

void Mage::OnCollisionExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		// �ӽ� �ڵ�
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}

void Mage::OnTriggerEnter(Collider* _pOtherCollider)
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
		// �ӽ� �ڵ�
		if (mGroundCount == 0)
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}

		mGroundCount++;
	}
}

void Mage::OnTriggerStay(Collider* _pOtherCollider)
{

}

void Mage::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		// �ӽ� �ڵ�
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}
