#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Engine.h"
#include "Mesh.h"
#include "InstancingBuffer.h"
#include "MeshData.h"
#include "Animator.h"
#include "Resources.h"

namespace hm
{
	MeshRenderer::MeshRenderer()
		: Component(ComponentType::MeshRenderer)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	Component* MeshRenderer::Clone(GameObject* _pGameObject)
	{
		MeshRenderer* pMeshRenderer = _pGameObject->AddComponent(new MeshRenderer);
		pMeshRenderer->mpMesh = mpMesh;
		pMeshRenderer->mpMaterial = mpMaterial;
		return pMeshRenderer;
	}
	void MeshRenderer::Render(Camera* _pCamera)
	{
		AssertEx(nullptr != mpMaterial, L"MeshRenderer::Render() - Material is empty");
		AssertEx(nullptr != mpMaterial->GetShader(), L"MeshRenderer::Render() - Shader is empty");
		AssertEx(nullptr != mpMesh, L"MeshRenderer::Render() - Mesh is empty");

		PushScriptData();
		GetTransform()->PushData(_pCamera);
		CONST_BUFFER(ConstantBufferType::Transform)->Mapping();

		UINT32 meshCount = mpMesh->GetMeshContainerCount();
		for (UINT i = 0; i < meshCount; ++i)
		{
			if (false == mSubsetRenderFlags.empty() && false == mSubsetRenderFlags[i])
				continue;

			MaterialContainer* pContainer = mpMaterial->GetMaterialContainer(i);

			if (nullptr != GetAnimator())
				GetAnimator()->PushData();

			for (UINT32 j = 0; j < pContainer->materialSubsetVec.size(); ++j)
			{
				if (nullptr != GetAnimator())
					mpMaterial->SetInt(1, 1, i, j);

				mpMaterial->PushGraphicData(i, j);
				CONST_BUFFER(ConstantBufferType::Material)->Mapping();
				CONST_BUFFER(ConstantBufferType::Bloom)->Mapping();

				mpMesh->RenderInstancing(1, i);
				mpMaterial->ClearGraphicData();
			}
		}
	}

	void MeshRenderer::Render(Camera* _pCamera, InstancingBuffer* _pBuffer)
	{
		AssertEx(nullptr != mpMaterial, L"MeshRenderer::Render() - Material is empty");
		AssertEx(nullptr != mpMesh, L"MeshRenderer::Render() - Mesh is empty");

		PushScriptData();
		_pBuffer->PushData();
		GetTransform()->PushData(_pCamera);
		CONST_BUFFER(ConstantBufferType::Transform)->Mapping();

		UINT32 meshCount = mpMesh->GetMeshContainerCount();
		for (UINT32 i = 0; i < meshCount; ++i)
		{
			if (false == mSubsetRenderFlags.empty() && false == mSubsetRenderFlags[i])
				continue;

			MaterialContainer* pContainer = mpMaterial->GetMaterialContainer(i);

			if (nullptr != GetAnimator())
				GetAnimator()->PushData();
		
			for (UINT32 j = 0; j < pContainer->materialSubsetVec.size(); ++j)
			{
				if (nullptr != GetAnimator())
					mpMaterial->SetInt(1, 1, i, j);
				
				mpMaterial->PushGraphicData(i, j);
				CONST_BUFFER(ConstantBufferType::Material)->Mapping();
				CONST_BUFFER(ConstantBufferType::Bloom)->Mapping();

				mpMesh->RenderInstancing(_pBuffer, i);
				mpMaterial->ClearGraphicData();
			}
		}
	}
	void MeshRenderer::RenderExceptForShader(Camera* _pCamera, shared_ptr<Shader> _pShader, bool _bIsReflect)
	{
		AssertEx(nullptr != mpMaterial, L"MeshRenderer::Render() - Material is empty");
		AssertEx(nullptr != mpMaterial->GetShader(), L"MeshRenderer::Render() - Shader is empty");
		AssertEx(nullptr != mpMesh, L"MeshRenderer::Render() - Mesh is empty");

		PushScriptData();
		GetTransform()->PushData(_pCamera);
		CONST_BUFFER(ConstantBufferType::Transform)->Mapping();

		UINT32 meshCount = mpMesh->GetMeshContainerCount();
		for (UINT i = 0; i < meshCount; ++i)
		{
			if (false == mSubsetRenderFlags.empty() && false == mSubsetRenderFlags[i])
				continue;

			MaterialContainer* pContainer = mpMaterial->GetMaterialContainer(i);

			if (nullptr != GetAnimator())
				GetAnimator()->PushData();

			for (UINT32 j = 0; j < pContainer->materialSubsetVec.size(); ++j)
			{
				// No Instancing
				mpMaterial->SetInt(0, 0, i, j);

				// Animation Flag
				if (nullptr != GetAnimator())
					mpMaterial->SetInt(1, 1, i, j);
				else
					mpMaterial->SetInt(1, 0, i, j);

				// Reflection Flag
				if (true == _bIsReflect)
					mpMaterial->SetInt(2, 1, i, j);
				else
					mpMaterial->SetInt(2, 0, i, j);

				mpMaterial->PushGraphicDataExceptForShader(i, j);
				CONST_BUFFER(ConstantBufferType::Material)->Mapping();
				CONST_BUFFER(ConstantBufferType::Bloom)->Mapping();

				_pShader->Update();
				mpMesh->RenderInstancing(1, i);
				mpMaterial->ClearGraphicData();
			}
		}
	}
	void MeshRenderer::RenderEffect(Camera* _pCamera)
	{
		AssertEx(nullptr != mpMaterial, L"MeshRenderer::Render() - Material is empty");
		AssertEx(nullptr != mpMaterial->GetShader(), L"MeshRenderer::Render() - Shader is empty");
		AssertEx(nullptr != mpMesh, L"MeshRenderer::Render() - Mesh is empty");

		PushScriptData();
		GetTransform()->PushData(_pCamera);
		CONST_BUFFER(ConstantBufferType::Transform)->Mapping();

		UINT32 meshCount = mpMesh->GetMeshContainerCount();
		for (UINT i = 0; i < meshCount; ++i)
		{
			if (false == mSubsetRenderFlags.empty() && false == mSubsetRenderFlags[i])
				continue;

			MaterialContainer* pContainer = mpMaterial->GetMaterialContainer(i);
			for (UINT32 j = 0; j < pContainer->materialSubsetVec.size(); ++j)
			{
				mpMesh->RenderInstancing(1, i);
			}
		}
	}
	void MeshRenderer::RenderShadow(Camera* _pCamera)
	{
		PushScriptData();
		GetTransform()->PushData(_pCamera);
		CONST_BUFFER(ConstantBufferType::Transform)->Mapping();

		if (nullptr != GetAnimator())
			GetAnimator()->PushData();

		shared_ptr<Material> pShadowMaterial = GET_SINGLE(Resources)->Get<Material>(L"Shadow");

		if (nullptr != GetAnimator())
		{
			UINT32 materialCount = mpMaterial->GetMaterialContainerCount();
			while (materialCount > pShadowMaterial->GetMaterialContainerCount())
			{
				MaterialContainer* pMatContainer = new MaterialContainer;
				pMatContainer->AddSubset(new MaterialSubset);
				pShadowMaterial->AddMaterialContainer(pMatContainer);
			}
		}

		UINT32 containerCount = mpMesh->GetMeshContainerCount();
		for (UINT32 i = 0; i < containerCount; ++i)
		{
			if (nullptr != GetAnimator())
			{
				pShadowMaterial->SetInt(1, 1, i, 0);
				pShadowMaterial->PushGraphicData(i, 0);
			}
			else
			{
				pShadowMaterial->SetInt(1, 0);
				pShadowMaterial->PushGraphicData();
			}


			CONST_BUFFER(ConstantBufferType::Material)->Mapping();
			mpMesh->Render(i);
		}
	}
	void MeshRenderer::SetMaterial(shared_ptr<Material> _pMaterial)
	{
		mpMaterial = _pMaterial;
	}
	void MeshRenderer::SetMeshData(shared_ptr<MeshData> _pMeshData)
	{
		mpMesh = _pMeshData->GetMesh();
		mpMaterial = _pMeshData->GetMaterial();

		if (true == _pMeshData->HasAnimation())
		{
			if (nullptr == GetAnimator())
				mpGameObject->AddComponent(new Animator);

			GetAnimator()->SetBones(mpMesh->GetBones());
			GetAnimator()->SetAnimClip(mpMesh->GetAnimClip());
		}

		mSubsetRenderFlags.resize(mpMesh->GetMeshContainerCount(), true);
	}

	void MeshRenderer::PushScriptData()
	{
		const std::vector<MonoBehavior*>& scripts = GetGameObject()->GetScripts();

		for (auto pScript : scripts)
		{
			pScript->PushData();
		}
	}
	UINT64 MeshRenderer::GetInstanceID()
	{
		if (mpMesh == nullptr || mpMaterial == nullptr)
			return 0;

		UINT32 meshID = mpMesh->GetID();
		UINT32 materialID = mpMaterial->GetID();

		InstanceID instanceID = { meshID, materialID };
		return instanceID.id;
	}
	void MeshRenderer::SetSubsetRenderFlag(UINT32 _index, bool _flag)
	{
		AssertEx(_index < mpMesh->GetMeshContainerCount(), L"MeshRenderer::SetSubsetRenderFlag() - �޽� ������ �Էµ� Index���� ����");
		mSubsetRenderFlags[_index] = _flag;
		mpMaterial = mpMaterial->Clone();
	}
}