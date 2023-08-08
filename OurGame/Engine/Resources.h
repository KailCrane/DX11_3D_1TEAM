#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshData.h"
#include "GameObject.h"

namespace hm
{
	class Resources
	{
		DECLARE_SINGLE(Resources);

	public:
		// ���� ����� ���̴��� ��Ƽ������ �����ϴ� �Լ�
		void Initialize();

		// �������� ������ �ʿ䰡 �ִ� ���ҽ��� �����ϴ� �Լ�
		void Destroy();

		/* ����� �´� �ؽ��ĸ� �����ϴ� �Լ�
		* _name : Resources�� ���� �� ���ҽ��� ã�� �� �ִ� Ű ��
		* _eFormat : �ؽ��� ���� (DXGI_FORMAT_D24_UNORM_S8_UINT..)
		* _eTextureFormat : ����� �ؽ��� Ÿ�� (RTV, SRV, UAV ���), �� ������ �������� View�� �����
		* _width : �ؽ����� ���� ũ��
		* _height : �ؽ����� ���� ũ��
		*/
		shared_ptr<Texture> CreateTexture(const wstring& _name, DXGI_FORMAT _eFormat, UINT32 _eTextureType, int _width, int _height);

		/*�̹� ���ҽ��� �����ϴ� ��� �� ���ҽ��� �̿��� �ؽ��ĸ� ����� �Լ�
		* _name : Resources�� ���� �� ���ҽ��� ã�� �� �ִ� Ű ��
		* _eFormat : �ؽ��� ���� (DXGI_FORMAT_D24_UNORM_S8_UINT..)
		* _eTextureFormat : ����� �ؽ��� Ÿ�� (RTV, SRV, UAV ���), �� ������ �������� View�� �����
		*/ 
		shared_ptr<Texture> CreateTextureFromResource(const wstring& _name, DXGI_FORMAT _eFormat, UINT32 _eTextureType, ComPtr<ID3D11Texture2D> _tex2D);


		shared_ptr<MeshData> LoadFBX(const wstring& _path);

		/* ���ҽ��� �ε��ϴ� �Լ�
		* _key : �ҷ��� ���ҽ��� Ű
		* _path : ���� ���ҽ��� ���ٸ� �ҷ��� ���ҽ��� ���
		*/
		template<typename T>
		shared_ptr<T> Load(const wstring& _key, const wstring& _path);


		/* ���ҽ��� ����ϴ� �Լ�
		* _key : ������ ���ҽ��� Ű
		* _pObject : ������ ������Ʈ�� ����Ʈ ������
		*/
		template<typename T>
		bool Add(const wstring& _key, shared_ptr<T> _pObject);

		/* ���ҽ��� �ҷ����� �Լ�
		* _key : �ҷ��� ���ҽ��� Ű
		*/
		template<typename T>
		shared_ptr<T> Get(const wstring& _key);

		/* Add, Get, Load ���� �Լ����� ���ø����� ����� �� �ְ� ���ִ� �Լ� 
		* ���������� Ÿ�� T�� Ŭ������ �����Ͽ� ������ enum������ ��ȯ���ش�.
		*/
		template<typename T>
		ObjectType GetObjectType();

		// Rect Mesh�� ��ȯ�Ѵ�.
		shared_ptr<Mesh> LoadRectMesh();
		// Circle Mesh�� ��ȯ�Ѵ�.
		shared_ptr<Mesh> LoadCircleMesh();
		// Point Mesh�� ��ȯ�Ѵ�.
		shared_ptr<Mesh> LoadPointMesh();

		shared_ptr<Mesh> LoadCubeMesh();
		shared_ptr<Mesh> LoadSphereMesh();
		shared_ptr<Mesh> LoadBoundingCubeMesh();

		// ���� ����� Shader�� �����Ѵ�.
		void CreateDefaultShader();
		// ���� ����� Material�� �����Ѵ�.
		void CreateDefaultMaterial();

	private:
		using KeyObjMap = std::map<wstring, shared_ptr<Object>>;
		std::array<KeyObjMap, OBJECT_TYPE_COUNT> mResources;
	};
	template<typename T>
	inline shared_ptr<T> Resources::Load(const wstring& _key, const wstring& _path)
	{
		ObjectType eObjType = GetObjectType<T>();
		KeyObjMap& mObjMap = mResources[static_cast<int>(eObjType)];

		auto findIt = mObjMap.find(_key);
		if (mObjMap.end() != findIt)
			return static_pointer_cast<T>(findIt->second);

		shared_ptr<T> pObject = make_shared<T>();
		pObject->SetName(_key);
		pObject->Load(_path);

		mObjMap[_key] = pObject;

		return pObject;
	}
	template<typename T>
	inline bool Resources::Add(const wstring& _key, shared_ptr<T> _pObject)
	{
		ObjectType eObjType = GetObjectType<T>();
		KeyObjMap& mObjMap = mResources[static_cast<int>(eObjType)];

		auto findIt = mObjMap.find(_key);
		if (mObjMap.end() != findIt)
			return false;

		mObjMap[_key] = _pObject;
		return true;
	}
	template<typename T>
	inline shared_ptr<T> Resources::Get(const wstring& _key)
	{
		ObjectType eObjType = GetObjectType<T>();
		KeyObjMap& mObjMap = mResources[static_cast<int>(eObjType)];

		auto findIt = mObjMap.find(_key);
		if (mObjMap.end() != findIt)
			return static_pointer_cast<T>(findIt->second);

		return nullptr;
	}
	template<typename T>
	inline ObjectType Resources::GetObjectType()
	{
		if (std::is_same_v<T, GameObject>)
			return ObjectType::GameObject;
		else if (std::is_same_v<T, Texture>)
			return ObjectType::Texture;
		else if (std::is_same_v<T, Shader>)
			return ObjectType::Shader;
		else if (std::is_same_v<T, Material>)
			return ObjectType::Material;
		else if (std::is_same_v<T, Component>)
			return ObjectType::Component;
		else if (std::is_same_v<T, Mesh>)
			return ObjectType::Mesh;
		else if (std::is_same_v<T, MeshData>)
			return ObjectType::MeshData;
		else
		{
			AssertEx(false, L"�߸��� ���ҽ� Ÿ�� ����");
			return ObjectType::End;
		}
	}
}




