#pragma once
#include "Object.h"

namespace hm
{
    class StructuredBuffer;
    struct IndexBufferInfo
    {
        ComPtr<ID3D11Buffer>		pBuffer;
        UINT32						    count;
        void*                   pData;
    };

    struct VertexBufferInfo
    {
        ComPtr<ID3D11Buffer>        pBuffer;
        UINT32                         count;
        void*                     pData;
    };

    struct MeshContainer
    {
        VertexBufferInfo             vertexBufferInfo;
        std::vector<IndexBufferInfo> indexBufferGroup;
        bool bHasAnimation = false;
    };

    struct FrameInfo
    {

    };

    struct KeyFrameInfo
    {
        double	time;
        int	    frame;
        Vec3	scale;
        Vec4	rotation;
        Vec3	translate;
    };

    struct BoneInfo
    {
        wstring	boneName;
        int		parentIdx;
        Matrix	matOffset;
    };

    struct AnimClipInfo
    {
        wstring			animName;
        int			    frameCount;
        double			duration;
        std::vector<std::vector<KeyFrameInfo>>	keyFrames;
        bool            bLoop = false;
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
        void Render();
        void RenderInstancing(int _instanceCount = 1, int _index = 0);
        void RenderInstancing(InstancingBuffer* _pBuffer, int _index = 0);

        static UINT32 CreateHash(const Vertex& _vtx);
        void SetHash(UINT32 _hash) { mHash = _hash; }
        UINT32 GetHash() { return mHash; }

        void AddMeshContainer(const FbxMeshInfo* _pMeshInfo, FBXLoader& _loader);
        void AddMeshContainer(MeshContainer* _pMeshContainer);
        void ClearMeshContainers();
        void CreateBonesAndAnimations(FBXLoader& _loader);
        UINT32 GetMeshContainerCount() { return static_cast<UINT32>(mMeshContainerVec.size()); }
        MeshContainer* GetMeshContainer(int _containerIndex);

        void SaveBoneAndAnimations(FILE* _pFile);
        void LoadBoneAndAnimations(FILE* _pFile);

    public:
        // ���� ������ ���� ���� ���۸� �����ϴ� �Լ�
        VertexBufferInfo CreateVertexBuffer(const std::vector<Vertex>& _buffer);
        VertexBufferInfo CreateVertexBuffer(void* _pVtxData, UINT32 _size);
        // �ε��� ������ ���� �ε��� ���۸� �����ϴ� �Լ�
        IndexBufferInfo CreateIndexBuffer(const std::vector<int>& _buffer);
        IndexBufferInfo CreateIndexBuffer(void* _pIdxData, UINT32 _size);

    public:
        std::vector<BoneInfo>*     GetBones() { return &mBones; }
        UINT32						     GetBoneCount() { return static_cast<UINT32>(mBones.size()); }
        std::vector<AnimClipInfo>* GetAnimClip() { return &mAnimClips; }

        bool							 IsAnimMesh() { return !mAnimClips.empty(); }
        shared_ptr<StructuredBuffer>	 GetBoneFrameDataBuffer(int index = 0) { return frameBuffer[index]; } // ��ü �� ������ ����
        shared_ptr<StructuredBuffer>	 GetBoneOffsetBuffer() { return  pOffsetBuffer; }

    private:
        
        Matrix GetMatrix(const FbxAMatrix& _matrix); // FbxAMatrix -> XMMATRIX

    private:
        std::vector<MeshContainer*>      mMeshContainerVec;

        std::vector<AnimClipInfo> mAnimClips;
        std::vector<BoneInfo> mBones;

        shared_ptr<StructuredBuffer>              pOffsetBuffer;
        std::vector<shared_ptr<StructuredBuffer>> frameBuffer;

        UINT32 mHash;
	};
}


