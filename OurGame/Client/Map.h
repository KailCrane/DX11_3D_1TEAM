#pragma once
#include "Scene.h"
namespace hm
{
	class Map :
		public Scene
	{
	public:
		Map(SceneType _eSceneType);
		virtual ~Map();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();
	
	};
}


