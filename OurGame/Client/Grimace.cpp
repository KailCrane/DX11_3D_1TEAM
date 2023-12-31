#include "pch.h"
#include "Grimace.h"
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
#include "AudioSound.h"
#include "Factory.h"
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
#include "RenderManager.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "Npc.h"
#include "Monster.h"
#include "SwordHeavyEffect.h"
#include "Ladder.h"
#include "LadderCollider.h"
#include "HeadRoller.h"
#include "Grimace_ProjectTile.h"

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
#include "PaperBurnScript.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "SwordScript.h"
#include "PlayerColScript.h"
#include "BowScript.h"
#include "ArrowScript.h"
#include "MonsterColScript.h"
/* Event */
#include "SceneChangeEvent.h"
 /*State 모음*/
#include "State.h"
#include "PauseState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "MagicAttackState.h"
#include "EvasionState.h"
#include "FallState.h"
#include "HitStartState.h"
#include "HittingState.h"
#include "HitEndState.h"
#include "FallDownState.h"
#include "DeadState.h"
#include "ClimingDownState.h"
#include "ClimingEndState.h"
#include "ClimingUpState.h"
#include "BowState.h"

Grimace::Grimace()
{
	mMaxHP = 30.f;
	mHP = mMaxHP; // 피통
	Health = (mHP / mMaxHP) * 100;
	mSpeed = 6.f; //이동속도
	mAttackDamage = 1; // 공격력
	mAttackRange = 9.f; // 공격 감지 거리
	mRecogRange = 15.f; //감지거리

	meBasicState = MonsterBasicState::Idle;
	MonsterAttackCol();

	Shaketime = 0.2f;
	ShakeNum = 0.04f;
}

Grimace::~Grimace()
{
}

void Grimace::SetBehaviorTree()
{
	AI* pAI = AddComponent(new AI);

	// 루트 노드 등록
	Selector* pRootNode = new Selector;
	pAI->SetRootNode(pRootNode);

	Selector* pStateSelector = new Selector;
	{

#pragma region Idle Sequence
		Sequence* pIdleSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Idle == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (0 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					pAnimator->Play(0, true);
				}

				return BehaviorResult::Success;
				});

			// 플레이어 거리 확인(Condition) : 플레이어가 근처에 있는지 확인
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
			pIdleSequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace));
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion

#pragma region Delay Sequence
		Sequence* pDelaySequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Delay == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (0 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					pAnimator->Play(0, true);
				}

				return BehaviorResult::Success;
				});

			// 플레이어 거리 확인(Condition) : 플레이어가 근처에 있는지 확인
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAnimator = GetAnimator();

					
					if (pAnimator->GetFrameRatio() > 0.95)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pDelaySequence->AddChild(pStateChecker);
			pDelaySequence->AddChild(pRunAnimationTask);
			pDelaySequence->AddChild(pCheckNearbyPlayer);
			pDelaySequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace));
		}
		pStateSelector->AddChild(pDelaySequence);

#pragma endregion

#pragma region Trace Sequence
		Sequence* pTraceSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Trace인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Trace == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (1 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					isTrigger = false;
					pAnimator->Play(1, true);
				}

				if (pAnimator->GetFrameRatio() > 0.73) {
					//GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					pAnimator->Play(1, true);
				}

				return BehaviorResult::Success;
				});

			// 플레이어 목표 좌표로 몬스터가 이동+회전 하는 실행(Task)
			BehaviorTask* pTraceMoveTask = new BehaviorTask([&]() {
				Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
				Animator* pAni = GetAnimator();
				Vec3 myPos = GetTransform()->GetPosition();
				Vec3 myRot = GetTransform()->GetRotation();
				Vec3 scale = GetRigidBody()->GetGeometrySize();

				dir = playerPos - myPos;
				dir.Normalize();
				dir.y = 0;
				

				Vec3 lookNormal = GetTransform()->GetLook();
				lookNormal.Normalize();

				Vec3 Ve = dir * mSpeed;
			
				if (pAni->GetFrameRatio() < 0.6f)
					GetRigidBody()->SetVelocityExcludingColliders(-dir * 7.0f);
				else
					GetRigidBody()->SetVelocityExcludingColliders(-dir * 0.0f);

				GetRigidBody()->SetVelocity(Ve);


				if (IsRaysCollide(myPos + scale * lookNormal, lookNormal, LayerType::Ground, 1.f))
				{
					GetRigidBody()->SetVelocity(Ve * 0);
				}

				if (IsRaysCollide(myPos + scale * lookNormal, lookNormal, LayerType::WallObject, 1.f))
				{
					GetRigidBody()->SetVelocity(Ve * 0);
				}

				if (IsRaysCollide(myPos + scale * lookNormal, lookNormal, LayerType::DecoObject, 1.f))
				{
					GetRigidBody()->SetVelocity(Ve * 0);
				}


				//회전 파트
				Transform* pTr = GetTransform();
				Vec3 rot = Vec3(0, 0, -1);
				double angleRadian = atan2(dir.x, dir.z) - atan2(rot.x, rot.z);
				float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

				if (angleDegree < 0.f)
					angleDegree += 360.f;

				//몬스터의 고개를 돌리는 코드
				pTr->SetRotation(Vec3(180.f, angleDegree, 0.f));

				return BehaviorResult::Success;
				});


			// 언젠간 쓰겟지
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					float distance = (playerPos - myPos).Length();
					Animator* pAni = GetAnimator();

					if (pAni->GetFrameRatio() > 0.9f)
					{
						GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
						GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
						pAni->Play(3, true);
					}
					

					return BehaviorResult::Success;
					
				});


			// 상태 변경(Task) : 상태 변경
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Vec3 myRot = GetTransform()->GetRotation();
					Vec3 scale = GetRigidBody()->GetGeometrySize();
					Animator* pAni = GetAnimator();

					float distance = (playerPos - myPos).Length();

					MonsterBasicState eState = MonsterBasicState::Trace;

					

					if (distance > 6.f && distance < 10.f && pAni->GetFrameRatio()>0.7)
					{
						dir_desh = playerPos - myPos;
						dir_desh.Normalize();
						dir_desh.y = 0;

						eState = MonsterBasicState::Attack03; //돌진 공격
					}

					else if (distance > 3.5f && distance < 5.5f )
					{
						eState = MonsterBasicState::Attack01; // 땅찍기
					}

					else if (distance < 3.5f )
					{
						dir_backstep = playerPos - myPos;
						dir_backstep.Normalize();
						dir_backstep.y = 0;

						eState = MonsterBasicState::Trace_BackStep;
					}

					if (Health >= 41 && Health <= 61 ) //50% 미만일떄 디펜딩 자세 시작
					{
						eState = MonsterBasicState::Defend_Start;
					}
					
					//임시 테스트
					//eState = MonsterBasicState::Attack03;

					bool check = GetAttackCheck();

					if (check == false) {
						SetBasicState(eState);
					}
					return BehaviorResult::Success;
				});

			pTraceSequence->AddChild(pStateChecker);
			pTraceSequence->AddChild(pRunAnimationTask);
			pTraceSequence->AddChild(pTraceMoveTask);
			pTraceSequence->AddChild(pCheckNearbyPlayer);
			pTraceSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pTraceSequence);

#pragma endregion

#pragma region Trace_Backstep Sequence
		Sequence* pTrace_BackstepSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Trace인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Trace_BackStep == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				AudioSound* pSound = GetAudioSound();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (3 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					pAnimator->Play(3, true);

					BackstepDirSet();
					BackstepRotTurn();
					
					pSound->SetSound(L"Grimace_backdash", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\Grimace\\BackDash01.wav");
					pSound->Play(50);
				}


				return BehaviorResult::Success;
				});

			// 플레이어 목표 좌표로 몬스터가 이동+회전 하는 실행(Task)
			BehaviorTask* pTraceMoveTask = new BehaviorTask([&]() {
				Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
				Vec3 myPos = GetTransform()->GetPosition();
				Vec3 myRot = GetTransform()->GetRotation();
				Vec3 scale = GetRigidBody()->GetGeometrySize();
				Animator* pAni = GetAnimator();

				GetRigidBody()->SetMaxVelocity(100.f);

				BackstepDirLive();

				//그리마스 수정

				if (pAni->GetFrameRatio() > 0.2f && pAni->GetFrameRatio() < 0.45f) 
				{
					GetRigidBody()->SetVelocityExcludingColliders(dir_backstep * 15);
					GetRigidBody()->SetVelocity(-Ve_backstep * 3);
				}
				else
				{
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetRigidBody()->SetVelocity(Vec3::Zero);
				}

				

				

				return BehaviorResult::Success;
				});


			// 다음 시퀀스로 넘어가는 조건 
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					float distance = (playerPos - myPos).Length();
					Animator* pAni = GetAnimator();

					//여기 건들여야함

					if (pAni->GetFrameRatio()>0.9)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});


			// 상태 변경(Task) : 상태 변경
			/*BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					meBasicState = MonsterBasicState::Attack;
					return BehaviorResult::Success;
				});*/

			pTrace_BackstepSequence->AddChild(pStateChecker);
			pTrace_BackstepSequence->AddChild(pRunAnimationTask);
			pTrace_BackstepSequence->AddChild(pTraceMoveTask);
			pTrace_BackstepSequence->AddChild(pCheckNearbyPlayer);
			pTrace_BackstepSequence->AddChild(new ChangeStateTask(MonsterBasicState::Attack02));
		}
		pStateSelector->AddChild(pTrace_BackstepSequence);

#pragma endregion

#pragma region Attack01 Sequence
		Sequence* pAttack01Sequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Attack인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Attack01 == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (2 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					pAnimator->Play(2, true);
				}

				return BehaviorResult::Success;
				});

			// 공격 딜레이
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					AudioSound* pSound = GetAudioSound();

					Animator* pAni = GetAnimator();

					if (pAni->GetFrameRatio() > 0.7 && pAni->GetFrameRatio() < 0.8) {
						pMonsterAttackCol->Enable();
						pMonsterAttackCol->GetScript<MonsterColScript>()->SetAniRatio(pAni->GetFrameRatio());
						GET_SINGLE(RenderManager)->AddCameraShakeEffect(0.05f, 0.04f);
						if (isattack01 == true)
						{
							isattack01 = false;
							pSound->SetSound(L"Grimace_atk01", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\LORDBOSS\\MeleeSlam.wav");
							pSound->Play(20);
						}
					}
					if (pAni->GetFrameRatio() > 0.8) {
						pMonsterAttackCol->GetScript<MonsterColScript>()->SetAniRatio(pAni->GetFrameRatio());
						pMonsterAttackCol->Disable();
					}

					if (pAni->GetFrameRatio() > 0.95) {
						isattack01 = true;
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;

				});

			// 상태 변경(Task) : 상태 변경
			/*BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					meBasicState = MonsterBasicState::Trace;
					return BehaviorResult::Success;
				});*/

			pAttack01Sequence->AddChild(pStateChecker);
			pAttack01Sequence->AddChild(pRunAnimationTask);
			pAttack01Sequence->AddChild(pAttackTask);
			pAttack01Sequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace_BackStep));
		}
		pStateSelector->AddChild(pAttack01Sequence);

#pragma endregion

#pragma region Attack02 Sequence
		Sequence* pAttack02Sequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Attack인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Attack02 == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				AudioSound* pSound = GetAudioSound();
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (4 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					pAnimator->Play(4, true);

					pSound->SetSound(L"Grimace_atk02", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\Grimace\\projecttile.wav");
					pSound->Play(50);
				}

				return BehaviorResult::Success;
				});

			// 공격 딜레이
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Animator* pAni = GetAnimator();
					AudioSound* pSound = GetAudioSound();


					if (pAni->GetFrameRatio() > 0.5) {
						if (true != isTrigger) {
							isTrigger = true;
							CreateProjectTile();

							if (isattack02 == true)
							{
								isattack02 = false;
							}
						}
					}

					if (pAni->GetFrameRatio() > 0.95)
					{
						isattack02 = true;
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;

				});

			// 상태 변경(Task) : 상태 변경
			/*BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					meBasicState = MonsterBasicState::Trace;
					return BehaviorResult::Success;
				});*/

			pAttack02Sequence->AddChild(pStateChecker);
			pAttack02Sequence->AddChild(pRunAnimationTask);
			pAttack02Sequence->AddChild(pAttackTask);
			pAttack02Sequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace));
		}
		pStateSelector->AddChild(pAttack02Sequence);

#pragma endregion

#pragma region Attack03 Sequence
		Sequence* pAttack03Sequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Attack인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Attack03 == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
				Vec3 myPos = GetTransform()->GetPosition();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (13 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					dir_desh = playerPos - myPos;
					dir_desh.Normalize();
					dir_desh.y = 0;
					pAnimator->Play(13, true);

					/*AudioSound* pSound = GetAudioSound();
					pSound->SetSound(L"Grimace_atk03", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\Grimace\\dash.wav");
					pSound->Play(50);*/
				}

				return BehaviorResult::Success;
				});

			// 공격 딜레이
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Animator* pAni = GetAnimator();
					Vec3 geomSize = GetRigidBody()->GetGeometrySize();
					Vec3 lookNormal = GetTransform()->GetLook();
					lookNormal.Normalize();
					AudioSound* pSound = GetAudioSound();

					GetRigidBody()->SetMaxVelocity(100.f);

					if (pAni->GetFrameRatio() > 0.2)
					{
						if (isattack03 == true)
						{
							isattack03 = false;
							pSound->SetSound(L"Grimace_atk03", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\Grimace\\dash.wav");
							pSound->Play(50);
						}
					}

					dir_desh.Normalize();
					if (pAni->GetFrameRatio() > 0.45 && pAni->GetFrameRatio() < 0.6)
					{
						SetAttackCheck(true);
						GetRigidBody()->SetVelocityExcludingColliders(-dir_desh * 10.0f);
						GetRigidBody()->SetVelocity(dir_desh * 40.f);
						GET_SINGLE(RenderManager)->AddCameraShakeEffect(Shaketime, ShakeNum);

						
						//그리마스 수정
						
						if (IsRaysCollide(myPos + (lookNormal * geomSize), lookNormal, LayerType::Ground, 0.5f))
						{
							GetRigidBody()->SetVelocity(dir_desh * 0.f);
						}

						if (IsRaysCollide(myPos + (lookNormal * geomSize), lookNormal, LayerType::WallObject, 0.5f))
						{
							GetRigidBody()->SetVelocity(dir_desh * 0.f);
						}
						
					}
					else 
					{
						SetAttackCheck(false);
						GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
						GetRigidBody()->SetVelocity(Vec3::Zero);
					}
				


					if (pAni->GetFrameRatio() > 0.90)
					{
						isattack03 = true;
						return BehaviorResult::Success;

					}
					return BehaviorResult::Failure;

				});

			// 상태 변경(Task) : 상태 변경
			/*BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					meBasicState = MonsterBasicState::Trace;
					return BehaviorResult::Success;
				});*/

			pAttack03Sequence->AddChild(pStateChecker);
			pAttack03Sequence->AddChild(pRunAnimationTask);
			pAttack03Sequence->AddChild(pAttackTask);
			pAttack03Sequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace));
		}
		pStateSelector->AddChild(pAttack03Sequence);

#pragma endregion

#pragma region Defend_Start Sequence
		Sequence* pDefend_StartSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Defend_Start == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (7 != animIndex) {
					CreateMonsterWavefirst();
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					pAnimator->Play(7, true);
				}
				return BehaviorResult::Success;
				});

			//다음 시퀀스로 넘어가는 조건
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAni = GetAnimator();
					Transform* pTr = GetTransform();
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Vec3 myRot = GetTransform()->GetRotation();
					Vec3 scale = GetRigidBody()->GetGeometrySize();

					dir = playerPos - myPos;
					dir.Normalize();
					dir.y = 0;

					Vec3 rot = Vec3(0, 0, -1);
					double angleRadian = atan2(dir.x, dir.z) - atan2(rot.x, rot.z);
					float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

					if (angleDegree < 0.f)
						angleDegree += 360.f;

					//몬스터의 고개를 돌리는 코드
					pTr->SetRotation(Vec3(180.f, angleDegree, 0.f));



					if (pAni->GetFrameRatio() > 0.95)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pDefend_StartSequence->AddChild(pStateChecker);
			pDefend_StartSequence->AddChild(pRunAnimationTask);
			pDefend_StartSequence->AddChild(pCheckNearbyPlayer);
			pDefend_StartSequence->AddChild(new ChangeStateTask(MonsterBasicState::Defend));
		}
		pStateSelector->AddChild(pDefend_StartSequence);

#pragma endregion

#pragma region Defend Sequence
		Sequence* pDefendSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Trace인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Defend == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (8 != animIndex) {
					pAnimator->Play(8, true);
				}

				return BehaviorResult::Success;
				});

			// 플레이어 목표 좌표로 몬스터가 이동+회전 하는 실행(Task)
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
				// 몬스터의 이동속도가 들어가야 함
				// 방향을 변경해주는 Task도 필요
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



				//GetRigidBody()->SetVelocity(Ve); //따라오게 만드는 코드

				Transform* pTr = GetTransform();
				Vec3 rot = Vec3(0, 0, -1);
				double angleRadian = atan2(dir.x, dir.z) - atan2(rot.x, rot.z);
				float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

				if (angleDegree < 0.f)
					angleDegree += 360.f;

				//몬스터의 고개를 돌리는 코드
				pTr->SetRotation(Vec3(180.f, angleDegree, 0.f));

				return BehaviorResult::Success;
				});


			// 다음 시퀀스로 넘어가는 조건 
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					float distance = (playerPos - myPos).Length();
					Animator* pAni = GetAnimator();

					//여기 건들여야함

					if (Health < 30 )
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});


			// 상태 변경(Task) : 상태 변경
			/*BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					meBasicState = MonsterBasicState::Attack;
					return BehaviorResult::Success;
				});*/

			pDefendSequence->AddChild(pStateChecker);
			pDefendSequence->AddChild(pRunAnimationTask);
			pDefendSequence->AddChild(pTraceMoveTask);
			pDefendSequence->AddChild(pCheckNearbyPlayer);
			pDefendSequence->AddChild(new ChangeStateTask(MonsterBasicState::Defend_Break));
		}
		pStateSelector->AddChild(pDefendSequence);

#pragma endregion

#pragma region Defend_Break Sequence
		Sequence* pDefend_BreakSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Defend_Break == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (10 != animIndex) {
					CreateMonsterWaveSecond();
					pAnimator->Play(10, true);
				}

				return BehaviorResult::Success;
				});

			// 이동 Move Task
			BehaviorTask* pMoveTask = new BehaviorTask([&]() {
				Vec3 myPos = GetTransform()->GetPosition();
				
				//이부분 중요
				GetRigidBody()->SetVelocityExcludingColliders(+dir * 3.0f);
				GetRigidBody()->SetVelocity(-dir * 3.f);
				const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(LayerType::Ground);
				for (int i = 0; i < gameObjects.size(); ++i)
				{
					if (gameObjects[i]->GetCollider())
					{
						if (GetCollider()->Raycast(myPos, dir, gameObjects[i]->GetCollider(), 0.5f))
						{
							GetRigidBody()->SetVelocity(-dir * 0.f);
						}
					}
				}

				return BehaviorResult::Success;
				});

			//다음 시퀀스로 넘어가는 조건
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAni = GetAnimator();

					if (pAni->GetFrameRatio() > 0.9)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pDefend_BreakSequence->AddChild(pStateChecker);
			pDefend_BreakSequence->AddChild(pRunAnimationTask);
			pDefend_BreakSequence->AddChild(pMoveTask);
			pDefend_BreakSequence->AddChild(pCheckNearbyPlayer);
			pDefend_BreakSequence->AddChild(new ChangeStateTask(MonsterBasicState::Dazed));
		}
		pStateSelector->AddChild(pDefend_BreakSequence);

#pragma endregion

#pragma region Dazed Sequence
		Sequence* pDazedSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Dazed == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (0 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					pAnimator->Play(0, true);
				}
				return BehaviorResult::Success;
				});

			//다음 시퀀스로 넘어가는 조건
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAni = GetAnimator();

					if (pAni->GetFrameRatio() > 0.95)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pDazedSequence->AddChild(pStateChecker);
			pDazedSequence->AddChild(pRunAnimationTask);
			pDazedSequence->AddChild(pCheckNearbyPlayer);
			pDazedSequence->AddChild(new ChangeStateTask(MonsterBasicState::Idle));
		}
		pStateSelector->AddChild(pDazedSequence);

#pragma endregion

#pragma region Dead Sequence
		Sequence* pDeadSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Attack인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Dead == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pAniIsrunningTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				
				if (pAnimator->GetFrameRatio() > 0.9)
					return BehaviorResult::Success;
			
				return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				GameObject* pObj = GetGameObject(); //이거 확인도 필요함
				int animIndex = pAnimator->GetCurrentClipIndex();
				
				if (isDead == true)
				{
					//pObj->GetRigidBody()->SetSimulationShapeFlag(false);
					//pObj->Disable();
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -4.f, 0.f));
					isDead = false;
					GetScript<PaperBurnScript>()->SetPaperBurn();
					GameObject* pObj = GetGameObject();
					pObj->DisableCollider();
					pAnimator->Play(6, false);
					
				}

				//pObj->GetRigidBody()->SetSimulationShapeFlag(false); // 콜라이더 끄기
				//pObj->GetRigidBody()->SetSimulationShapeFlag(true); // 콜라이더 켜기


				return BehaviorResult::Success;
				});

			// 페이퍼번 실행 조건
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Animator* pAni = GetAnimator();
					int animIndex = pAni->GetCurrentClipIndex();



					if (GetScript<PaperBurnScript>()->IsFinished())
					{

						GetScript<yj::MonsterKeyScript>()->SendDeathTrigger();
						MapType type = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
						GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, static_cast<GameObject*>(pMonsterAttackCol));
						GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, static_cast<GameObject*>(this));
					}


					return BehaviorResult::Success;

				});

			pDeadSequence->AddChild(pStateChecker);
			pDeadSequence->AddChild(pAniIsrunningTask);
			pDeadSequence->AddChild(pRunAnimationTask);
			pDeadSequence->AddChild(pAttackTask);

		}
		pStateSelector->AddChild(pDeadSequence);

#pragma endregion
	}
	pRootNode->AddChild(pStateSelector);
}

void Grimace::Initialize()
{
	Monster::Initialize();

	Animator* pAnimator = GetAnimator();
	pAnimator->SetLoop(0, true);
}

void Grimace::Update()
{
	Health = (mHP / mMaxHP) * 100;
	Monster::Update();
}

void Grimace::FixedUpdate()
{
	Monster::FixedUpdate();
}

void Grimace::FinalUpdate()
{
	Monster::FinalUpdate();
}

void Grimace::Render()
{
	//FONT->DrawString(std::to_wstring(Health), 30.f, Vec3(50.f, 890.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff0000ff, FONT_ALIGN::LEFT);


	Monster::Render();
}

void Grimace::Destroy()
{
	Monster::Destroy();
}

void Grimace::OnCollisionEnter(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		// 임시 코드
		if (mGroundCount == 0)
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}

		mGroundCount++;
	}
}

void Grimace::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Grimace::OnCollisionExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{

		// 임시 코드
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}

void Grimace::OnTriggerEnter(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		// 임시 코드
		if (mGroundCount == 0)
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}

		mGroundCount++;
	}

	

	Player* pPlayer = PLAYER;
	float attackDamage = pPlayer->GetAttackDamage();

	if (LayerType::PlayerCol == _pOtherCollider->GetGameObject()->GetLayerType()
		|| LayerType::ArrowCol == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		if (isGODState == false) {
			HitSound();
			TakeDamage(attackDamage);
			if (mHP <= 0) {
				isDead = true;
				isGODState = true;
				SetAttackCheck(false);
				meBasicState = MonsterBasicState::Dead;
			}
		}
	}
}

void Grimace::OnTriggerStay(Collider* _pOtherCollider)
{
}

void Grimace::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{

		// 임시 코드
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}

void Grimace::CreateProjectTile()
{
	PhysicsInfo physicsInfo;
	physicsInfo.eActorType = ActorType::Kinematic;
	physicsInfo.eGeometryType = GeometryType::Box;
	physicsInfo.size = Vec3(0.3f, 4.3f, 0.3f);

	Vec3 Pos = GetTransform()->GetPosition();
	Pos.y -= 2.f;

	Grimace_ProjectTile* pProjectTile = Factory::CreateObjectHasPhysical<Grimace_ProjectTile>(Vec3(Pos), physicsInfo, L"Deferred_CullNone", L"..\\Resources\\FBX\\Monster\\_DROP_SOUL50.fbx");
	pProjectTile->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
	pProjectTile->GetTransform()->SetPosition(GetTransform()->GetPosition());
	pProjectTile->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

	pProjectTile->GetMeshRenderer()->GetMaterial()->SetBloom(true, 0);
	pProjectTile->GetMeshRenderer()->GetMaterial()->SetBloomPower(3.f, 0);
	pProjectTile->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(0.f, 1.f, 0.f, 1.f));

	pProjectTile->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
	pProjectTile->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);

	pProjectTile->Initialize();

	GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pProjectTile);
}

void Grimace::MonsterAttackCol()
{
	//몬스터 공격 콜라이더
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Kinematic;
		physicsInfo.eGeometryType = GeometryType::Sphere;
		physicsInfo.size = Vec3(10.f, 0.1f, 10.f);
		//ChandelierSlam_Variant
		pMonsterAttackCol = Factory::CreateObjectHasPhysical<GameObject>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Monster\\ChandelierSlam_Variant.fbx", false, LayerType::MonsterCol);
		pMonsterAttackCol->GetMeshRenderer()->SetMaterial(pMonsterAttackCol->GetMeshRenderer()->GetMaterial()->Clone());

		pMonsterAttackCol->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
		pMonsterAttackCol->GetTransform()->SetRotation(Vec3(00.f, 00.f, 0.f));
		pMonsterAttackCol->GetMeshRenderer()->GetMaterial()->SetBloom(true);
		MonsterColScript* MonSc = pMonsterAttackCol->AddComponent(new MonsterColScript);
		MonSc->SetInit(Vec3(10.f, 1.f, 10.f), 0.7f);
		MonSc->SetOffSetPos(Vec3(0.f, -4.f, 0.f));
		pMonsterAttackCol->Disable();

		auto pFollowSc2 = pMonsterAttackCol->AddComponent(new OwnerFollowScript(this));
		pMonsterAttackCol->Initialize();
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pMonsterAttackCol);
	}
}

void Grimace::BackstepRotTurn()
{
	Transform* pTr = GetTransform();
	Vec3 rot = Vec3(0, 0, -1);
	double angleRadian = atan2(dir_backstep.x, dir_backstep.z) - atan2(rot.x, rot.z);
	float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

	if (angleDegree < 0.f)
		angleDegree += 360.f;

	//몬스터의 고개를 돌리는 코드
	pTr->SetRotation(Vec3(180.f, angleDegree, 0.f));
}

void Grimace::BackstepDirSet()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	dir_backstep = playerPos - myPos;
	dir_backstep.y = 0;
	dir_backstep.Normalize();
}

void Grimace::BackstepDirLive()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myRot = GetTransform()->GetRotation();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 scale = GetRigidBody()->GetGeometrySize();

	Vec3 dirBack = -GetTransform()->GetLook();

	Ve_backstep = dir_backstep * mSpeed;

	//그리마스 수정
	if (IsRaysCollide(myPos + scale * dirBack, dirBack, LayerType::WallObject, 1.f))
	{
		Ve_backstep = Vec3::Zero;
	}

	if (IsRaysCollide(myPos + scale * dirBack, dirBack, LayerType::Ground, 1.f))
	{
		Ve_backstep = Vec3::Zero;
	}

	if (IsRaysCollide(myPos + scale * dirBack, dirBack, LayerType::DecoObject, 1.f))
	{
		Ve_backstep = Vec3::Zero;
	}

}

void Grimace::CreateMonsterWavefirst()
{
	// 초록거미
	{
		SpawnDoor<Lurker>* pLurker = Factory::SpawnMonster<Lurker>(Vec3(4.5f, -5.5f, 1.5f), Vec3(-90.f, -90.f, 180.f));
		pLurker->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pLurker->Initialize();
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pLurker);

	}

	// 마법사
	{
		SpawnDoor<Mage>* pMage = Factory::SpawnMonster<Mage>(Vec3(-15.5f, -5.5f, 17.f), Vec3(-90.f, 90.f, 180.f));
		pMage->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pMage->Initialize();
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pMage);
	}
}

void Grimace::CreateMonsterWaveSecond()
{
	//콩벌레
	{
		SpawnDoor<HeadRoller>* pRoller = Factory::SpawnMonster<HeadRoller>(Vec3(4.5f, -5.5f, 17.f), Vec3(180.f, -90.f, 180.f));
		pRoller->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pRoller->Initialize();
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pRoller);

	}


	// 박쥐
	{
		SpawnDoor<Bat>* pBat = Factory::SpawnMonster<Bat>(Vec3(-15.5f, -5.5f, 1.5f), Vec3(-90.f, 90.f, 180.f));
		pBat->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pBat->Initialize();
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pBat);

	}
}
