#include "pch.h"
#include "SwordScript.h"
#include "GameObject.h"
#include "Engine.h"

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

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"
#include "SwordHeavyEffect.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"

/* Event */
#include "SceneChangeEvent.h"

SwordScript::SwordScript()
{
}

void SwordScript::Initialize()
{
	GameObject* pObj = GetGameObject();

	gpEngine->GetTool()->UseGizmo();
	//gpEngine->GetTool()->SetGameObject(pObj);
}

void SwordScript::FixedUpdate()
{
	Player* pPlayer = Player::GetPlayer();
	Transform* pPlyer_Tr = pPlayer->GetTransform();
	Transform* pTr = GetTransform();
	GameObject* pObj = GetGameObject(); // �� ������Ʈ
	DirectionEvasion eDir = pPlayer->GetDirectioninfo(); // 8���� ���� �������°�
	
	Vec3 Pos = pPlyer_Tr->GetPosition();
	Vec3 Rot = pTr->GetRotation();

	if (eDir == DirectionEvasion::BACKWARD) {
		Pos.z += 0.25f;
		Pos.y += 0.15f;
		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 100.f, 60.f));

	}
	if (eDir == DirectionEvasion::FORWARD) {
		Pos.z -= 0.25f;
		Pos.y += 0.15f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 270.f, 60.f));
	}
	if (eDir == DirectionEvasion::LEFT) {
		Pos.x += 0.25f;
		Pos.z += 0.f;
		Pos.y += 0.15f;
		
		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 200.f, 60.f));
	}
	if (eDir == DirectionEvasion::RIGHT) {
		Pos.x -= 0.25f;
		Pos.z += 0.f;
		Pos.y += 0.15f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 350.f, 60.f));
	}

	if (eDir == DirectionEvasion::TOPLEFT) {
		//Pos.z += 0.125f;
		//Pos.x += 0.125f;
		Pos.y += 0.15f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(330.f, 235.f, 60.f));
	}

	
	//Fsm ��������
	//�� �ݶ��̴� �ѱ� ���� fsm �����
	//8���⿡ �˸´� Tr����
	//���������� �˸´� 8���� Tr ����
	//





	pObj->GetRigidBody()->SetGeometrySize(Vec3(1.f, 0.2f, 0.2f)); //�̹� ������� �ݶ��̴� ������ ����

	pObj->GetRigidBody()->SetSimulationShapeFlag(false); // �ݶ��̴� ����
	//pObj->GetRigidBody()->SetSimulationShapeFlag(true); // �ݶ��̴� �ѱ�
	


	

}

Component* SwordScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new SwordScript);

}
