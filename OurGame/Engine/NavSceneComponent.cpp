#include "pch.h"
#include "NavSceneComponent.h"
#include "Resources.h"
#include "NavMesh.h"

namespace hm
{
	NavSceneComponent::NavSceneComponent()
	{
	}
	NavSceneComponent::~NavSceneComponent()
	{
		auto iter = mUseCellList.begin();
		auto iterEnd = mUseCellList.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(*iter);
		}
	}
	void NavSceneComponent::Initialize()
	{
		// ���̾������� ��Ƽ���� ���
		mpMaterial = nullptr;

		if (nullptr != mpNavMesh)
		{
			size_t count = mpNavMesh->GetNavMeshPolygonCount();

			for (size_t i = 0; i < count; ++i)
			{
				NavigationCell* pCell = new NavigationCell;
				NavMeshPolygon polygon = mpNavMesh->GetNavMeshPolygon(i);
				Vec3 p1 = polygon.mVertexPosVec[0];
				Vec3 p2 = polygon.mVertexPosVec[1];
				Vec3 p3 = polygon.mVertexPosVec[2];

				pCell->center = (p1 + p2 + p3) / 3.f;
				pCell->polygon = polygon;

				mUseCellList.push_back(pCell);
				mCellMap.insert(std::make_pair(polygon.mIndex, pCell));
			}
		}
	}
	void NavSceneComponent::Update()
	{
	}
	void NavSceneComponent::Render()
	{
		// �׺�޽� ������ ������

	}
	void NavSceneComponent::SetNavMesh(const wstring& _name)
	{
		shared_ptr<NavMesh> pNavMesh = static_pointer_cast<NavMesh>(GET_SINGLE(Resources)->Load<Mesh>(_name, _name));
		if (nullptr != pNavMesh)
			mpNavMesh = pNavMesh;

		AssertEx(nullptr != mpNavMesh, L"NavSceneComponent::SetNavMesh() - �������� �ʴ� Ű�� �׺�޽��� �ҷ������� �õ�");
	}
}

