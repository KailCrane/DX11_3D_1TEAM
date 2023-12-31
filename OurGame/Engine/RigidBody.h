#pragma once
#include "Component.h"
namespace hm
{
	class RigidBody :
		public Component
	{
	public:
		RigidBody();
		virtual ~RigidBody();

		virtual void Initialize();
		virtual void FinalUpdate();
		virtual void Destroy();

		virtual Component* Clone(GameObject* _pGameObject);

		void SetPhysical(const PhysicsInfo& _physicsInfo = PhysicsInfo());
		bool IsAppliedPhysics();

		PxActor* GetActor() { return mpActor; }

		template<typename T>
		inline T* GetActor() const
		{
			T* pActor = mpActor->is<T>();
			assert(pActor);
			return pActor;
		}

		template<typename T>
		inline T* GetGeometry() const
		{
			GeometryType geomType = mPhysicsInfo.eGeometryType;
			switch (geomType)
			{
			case GeometryType::Sphere:
				return reinterpret_cast<T*>(&mPhysicsInfo.pGeometries->sphereGeom);
			case GeometryType::Box:
				return reinterpret_cast<T*>(&mPhysicsInfo.pGeometries->boxGeom);
			case GeometryType::Capsule:
				return reinterpret_cast<T*>(&mPhysicsInfo.pGeometries->capsuleGeom);
			case GeometryType::Plane:
				return reinterpret_cast<T*>(&mPhysicsInfo.pGeometries->planeGeom);
			case GeometryType::Mesh:
				return reinterpret_cast<T*>(&mPhysicsInfo.pGeometries->triangleGeom);
			case GeometryType::Convex:
				return reinterpret_cast<T*>(&mPhysicsInfo.pGeometries->convexGeom);
			}

			return nullptr;
		}

		void AddActorToScene();

		PxRigidDynamic* GetDynamicActor() { return GetActor<PxRigidDynamic>(); }
		PxRigidStatic* GetStaticActor() { return GetActor<PxRigidStatic>(); }
		PxTransform GetPhysicsTransform();
		void	    SetPhysicsTransform(PxTransform _transform);

		ActorType GetActorType() { return mPhysicsInfo.eActorType; }
		GeometryType GetGeometryType() { return mPhysicsInfo.eGeometryType; }
		Geometries* GetGeometries() { return mPhysicsInfo.pGeometries; }
		
		Vec3 GetGeometrySize() { return mPhysicsInfo.size * 2.f; }
		void SetGeometrySize(const Vec3& _geomSize);
		const PxFilterData& GetFilterData() { return mPhysicsInfo.filterData; }
		void SetOtherLayerInFilterData(LayerType _eOtherLayer) { mPhysicsInfo.filterData.word1 |= 1 << static_cast<int>(_eOtherLayer); }

		void SetVelocityExcludingColliders(const Vec3& _velocity);
		const Vec3& GetGraphicVelocity() { return mGraphicVelocity; }

		void SetVelocity(const Vec3& _velocity);
		void SetVelocity(Axis _eAxis, float _velocity);
		void AddVelocity(const Vec3& _velocity);
		void AddVelocity(Axis _eAxis, float _velocity);
		void AddGravity();

		const Vec3& GetVelocity() { return mVelocity; }

		void SetMaxVelocity(float _maxVelocity);
		void CheckMaxVelocity();
		bool GetmbAppliedGravity() { return mbAppliedGravity; }

		void ApplyGravity();
		void RemoveGravity();

		void SetLinearDamping(float _damping);
		void SetSimulationShapeFlag(bool _bFlag);
		void SetTriggerShapeFlag(bool _bFlag);

		void SetActorInSceneFlag(bool _bFlag);
		bool GetActorInSceneFlag() { return mbIsActorInScene; }
		bool IsActorInScene() { return mbIsActorInScene; }

		void AddForce(const Vec3& _force);
		void AddTorque(const Vec3& _force);
		void AddForceAndTorque(const Vec3& _force);
		void RemoveAxisSpeedAtUpdate(Axis _eAxis, bool _bFlag);

		PxMaterial* GetMaterial() { return mpMaterial; }

	private:
		void CreateBoxGeometry();
		void CreateCapsuleGeometry();
		void CreatePlaneGeometry();
		void CreateSphereGeometry();
		void CreateMeshGeometry();
		void CreateConvexGeometry();
		PxTriangleMesh* CreateTriangleMesh(const struct TriangleMeshInfo& _meshInfo);
		PxConvexMesh* CreateConvexMesh(const struct TriangleMeshInfo& _meshInfo);

	private:
		void CreateGeometry();
		void CreateShape();
		void CreateActor();
		void CreateMaterial();
		void InitializeActor();

	private:
		PxCapsuleController* CreateCharacterController();
	public:
		PxCapsuleController* GetCharacterController() { return mpCharacterController; }

	private:
		bool mbAppliedPhysics;
		bool mbAppliedGravity;
		bool mbIsActorInScene;
		PhysicsInfo mPhysicsInfo;

		PxActor* mpActor;
		PxShape* mpShape;
		PxMaterial* mpMaterial;

		Vec3 mGraphicVelocity; //
		Vec3 mVelocity; // x, z
		float mMaxVelocity;
		bool mZeroAxisV[AXIS_MAX];

		PxCapsuleController* mpCharacterController;
	};
}


