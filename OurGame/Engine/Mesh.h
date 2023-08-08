#pragma once
#include "Object.h"

namespace hm
{
    struct IndexBufferInfo
    {
        ComPtr<ID3D11Buffer>		pBuffer;
        int						    count;
    };

    struct MeshContainer
    {
        ComPtr<ID3D11Buffer>         pVertexBuffer;
        std::vector<IndexBufferInfo> indexBufferGroup;
    };

    struct FbxMeshInfo;
    class FBXLoader;
    class InstancingBuffer;
	class Mesh :
		public Object
	{
    public:
        Mesh();
        virtual ~Mesh();

        /* VertexBuffer�� IndexBuffer�� �޾Ƽ� �޽��� �����ϴ� �Լ�
        * _vertexBuffer : ���� �������� ���� ���͸� ����
        * _indexBuffer : �ε��� ������ ���� ���͸� ����
        */
        void Initialize(const std::vector<Vertex>& _vertexBuffer, const std::vector<int>& _indexBuffer);

        /*DrawIndexedInstanced�� �����ϴ� �Լ�
        * ���������� IASetVertexBuffer�� IASetIndexBuffer�� �����Ѵ�.
        * _instanceCount : �ν��Ͻ��� ����
        */
        void Render(int _instanceCount = 1, int _index = 0);
        void Render(InstancingBuffer* _pBuffer, int _index = 0);

        static shared_ptr<Mesh> CreateFromFBX(const FbxMeshInfo* meshInfo, FBXLoader& loader);
        static UINT32 CreateHash(const Vertex& _vtx);
        void SetHash(UINT32 _hash) { mHash = _hash; }
        UINT32 GetHash() { return mHash; }

        void AddMeshContainer(const struct FbxMeshInfo* meshInfo, FBXLoader& loader);
        UINT32 GetMeshContainerCount() { return static_cast<UINT32>(mMeshContainerVec.size()); }

    public:
        // ���� ������ ���� ���� ���۸� �����ϴ� �Լ�
        ComPtr<ID3D11Buffer> CreateVertexBuffer(const std::vector<Vertex>& _buffer);
        // �ε��� ������ ���� �ε��� ���۸� �����ϴ� �Լ�
        IndexBufferInfo CreateIndexBuffer(const std::vector<int>& _buffer);

    private:

    private:
        std::vector<MeshContainer*> mMeshContainerVec;
        UINT32 mHash;
	};
}


