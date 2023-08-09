#pragma once
#include "Component.h"
#include "Material.h"
namespace hm
{
    class Mesh;
    class Camera;
    class InstancingBuffer;
    class MeshData;

    class MeshRenderer :
        public Component
    {
    public:
        MeshRenderer();
        virtual ~MeshRenderer();

        /* �޽��� �׷��ִ� �Լ�
        * ���ڷ� ���޵Ǵ� ī�޶� ���� �����, ��������� �޾ƿ´�.
        * _pCamera : �� �޽��� �׷��� ī�޶��� ������
        */
        void                 Render(Camera* _pCamera);
        void                 Render(Camera* _pCamera, InstancingBuffer* _pBuffer);

        void                 SetMaterial(shared_ptr<Material> _pMaterial);
        shared_ptr<Material> GetMaterial() const { return mpMaterial; }

        void                 SetMesh(shared_ptr<Mesh> _pMesh) { mpMesh = _pMesh; }
        shared_ptr<Mesh>     GetMesh()     const { return mpMesh; }
        void                 SetMeshData(shared_ptr<MeshData> _pMeshData);

        UINT64 GetInstanceID();

    private:
        shared_ptr<Material> mpMaterial; // ������ id 
        shared_ptr<Mesh>     mpMesh; // ������ id
	};
}


