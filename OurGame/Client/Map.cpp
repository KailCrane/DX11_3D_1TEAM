#include "pch.h"
#include "Map.h"
#include "PlacementScript.h"

namespace hm
{
	Map::Map(MapType _eMapType)
		: Scene(_eMapType)
	{
	}

	Map::~Map()
	{
	}
	void Map::Initialize()
	{
		Scene::Initialize();
	}
	void Map::Update()
	{
		Scene::Update();
	}
	void Map::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void Map::FinalUpdate()
	{
		Scene::FinalUpdate();
	}
	void Map::Render()
	{
		Scene::Render();
	}
	void Map::Enter()
	{
	//���� �Ͼ������ ������ִ� �ڵ�
	//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

#pragma region "����"
#pragma endregion

	//DecoObject == �ݶ��̴� ���� ������Ʈ
	//WallObject == �ݶ��̴� �ִ� ������Ʈ

	//Forward == �� ����� ���� ��ɾ�
	//Deferred == �� ����� �ִ� ��ɾ�

	//->GetTransform()->SetPositionExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [�̵�] ��Ű�� �Լ�
	//->GetTransform()->SetRotationExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [ȸ��] ��Ű�� �Լ�

	//Deferred_CullNone == ���׸��� ī�޶� ���� ©�� ���ִ� ���� _���� �״��

	//Object->AddComponent(new PlacementScript); == Ű����� �����̴� ������Ʈ �̵� ��ũ��Ʈ
	//SetGizmoTarget(Object); == ����Ƽ ������� ���콺�� �����̴� ������Ʈ �̵� �Լ�



	}
	void Map::Exit()
	{
	}
	void Map::SetGizmoTarget(GameObject* _pTarget)
	{
		TOOL->SetGameObject(_pTarget);
		_pTarget->AddComponent(new PlacementScript);
	}
}

