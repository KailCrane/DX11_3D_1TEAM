#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
//#include "Monster.h"
namespace hm
{
	using PrefabMap = std::map<wstring, GameObject*>;
	class PrefabManager
	{
		DECLARE_SINGLE(PrefabManager);

	public:

		void Initialize();

		template<typename T>
		void AddPrefab(const wstring& _name, T* _pObject)
		{
			LayerType eLayerType = GetLayerType<T>();
			PrefabMap& prefabMap = mPrefabMap[static_cast<int>(eLayerType)];

			auto iter = prefabMap.find(_name);
			AssertEx(iter == prefabMap.end(), L"PrefabManager::AddPrefab() - �̹� ��ϵ� �̸����� �������� ����Ϸ��� �õ�");

			prefabMap[_name] = _pObject->Clone();
		}


		template<typename T>
		T* GetPrefab(const wstring& _name)
		{
			LayerType eLayerType = GetLayerType<T>();
			std::map<wstring, GameObject*>& prefabMap = mPrefabMap[static_cast<int>(eLayerType)];

			auto iter = prefabMap.find(_name);
			AssertEx(iter != prefabMap.end(), L"PrefabManager::GetPrefab() - ��ϵ��� ���� �������� ���������� �õ�");

			T* pObject = static_cast<T*>(iter->second)->Clone();
			return pObject;
		}

		void ClearPrefab();

		template<typename T>
		inline LayerType GetLayerType()
		{
			if (std::is_same_v<T, GameObject>)
				return LayerType::Unknown;
			else if (std::is_same_v<T, Player>)
				return LayerType::Player;
			//else if (std::is_same_v<T, Monster>)
			//	return LayerType::Monster;
			else if (std::is_same_v<T, Ground>)
				return LayerType::Ground;
			else if (std::is_same_v<T, DecoObject>)
				return LayerType::DecoObject;
			else if (std::is_same_v<T, WallObject>)
				return LayerType::WallObject;
			else
			{
				AssertEx(false, L"PrefabManager::GetLayerType() - ��ϵ��� ���� Ÿ��");
				return LayerType::End;
			}
		}

	private:
		void CreateDefaultPrefab();

	private:
		std::array<PrefabMap, LAYER_TYPE_COUNT> mPrefabMap;

	};
}


