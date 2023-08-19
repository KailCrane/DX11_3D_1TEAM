#pragma once
#include "Object.h"

namespace hm
{
    class StructuredBuffer;
    struct IndexBufferInfo
    {
        ComPtr<ID3D11Buffer>		pBuffer;
        int						    count;
    };

    struct MeshContainer
    {
        ComPtr<ID3D11Buffer>         pVertexBuffer;
        std::vector<IndexBufferInfo> indexBufferGroup;
        bool bHasAnimation = false;
    };

    struct FrameInfo
    {
        float	updateTime = 0.f;
        int		clipIndex = 0;
        int		frame = 0;
        int		nextFrame = 0;
        float	frameRatio = 0;
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
    };

    struct AnimationContainer
    {
        std::vector<AnimClipInfo> animClips;
        std::vector<BoneInfo> bones;

        shared_ptr<StructuredBuffer>              pOffsetBuffer;
        std::vector<shared_ptr<StructuredBuffer>> frameBuffer;
    };

    struct FrameContainer
    {
        FrameInfo frameInfo;
        shared_ptr<StructuredBuffer>	pBoneFinalMatrix;  // Ư�� �������� ���� ���
        bool							bBoneFinalUpdated = false;
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
        UINT32 GetMeshContainerCount() { return static_cast<UINT32>(mMeshContainerVec.size()); }

    public:
        // ���� ������ ���� ���� ���۸� �����ϴ� �Լ�
        ComPtr<ID3D11Buffer> CreateVertexBuffer(const std::vector<Vertex>& _buffer);
        // �ε��� ������ ���� �ε��� ���۸� �����ϴ� �Լ�
        IndexBufferInfo CreateIndexBuffer(const std::vector<int>& _buffer);

    public:
        const std::vector<BoneInfo>&     GetBones(int _containerIndex = 0) { return mAnimContainerVec[_containerIndex]->bones; }
        UINT32						     GetBoneCount(int _containerIndex = 0) { return static_cast<UINT32>(mAnimContainerVec[_containerIndex]->bones.size()); }
        const std::vector<AnimClipInfo>& GetAnimClip(int _containerIndex = 0) { return mAnimContainerVec[_containerIndex]->animClips; }

        bool							 IsAnimMesh(int _containerIndex = 0) { return !mAnimContainerVec[_containerIndex]->animClips.empty(); }
        shared_ptr<StructuredBuffer>	 GetBoneFrameDataBuffer(int index = 0, int _containerIndex = 0) { return mAnimContainerVec[_containerIndex]->frameBuffer[index]; } // ��ü �� ������ ����
        shared_ptr<StructuredBuffer>	 GetBoneOffsetBuffer(int _containerIndex = 0) { return  mAnimContainerVec[_containerIndex]->pOffsetBuffer; }

        const std::vector<AnimationContainer*>& GetAnimationContainers() { return mAnimContainerVec; }

    private:
        void AddAnimContainer(FBXLoader& _loader);
        Matrix GetMatrix(const FbxAMatrix& _matrix); // FbxAMatrix -> XMMATRIX

    private:
        std::vector<MeshContainer*>      mMeshContainerVec;
        std::vector<AnimationContainer*> mAnimContainerVec;
        UINT32 mHash;
	};
}


