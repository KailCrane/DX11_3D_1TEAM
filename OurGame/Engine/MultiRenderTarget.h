#pragma once
#include "Texture.h"
namespace hm
{
	enum class MultiRenderTargetType
	{
		SwapChain,
		G_Buffer,
		Light,
		RimLighting,
		LightBlend,
		End,
	};

	enum
	{
		MULTI_RENDER_TARGET_TYPE_COUNT = MultiRenderTargetType::End,
		G_BUGGER_GROUP_COUNT = 5,
		SWAP_CHAIN_BUFFER_COUNT = 1,
		LIGHTING_GROUP_COUNT = 2,
		RIM_LIGHTING_GROUP_COUNT = 1,
		LIGHTBLEND_GROUP_COUNT = 1,
	};

	struct RenderTarget
	{
		shared_ptr<Texture> pTarget;
		float clearColors[4];
	};

	/*
	* RenderTarget�� �׷���� �����ϴ� Ŭ����
	* �� ������ Deferred Rendering�� ����ϱ� ����
	* OMSetRenderTarget ���� ����Ÿ�ٰ� ���õ� �۾����� �̷������.
	*/
	class MultiRenderTarget
	{
	public:
		/* Multi Render Target�� �ʿ��� �� ���ڸ� �޾� ���ο� �����ϴ� �Լ�
		* _eRenderTargetType   : ���� Ÿ���� Ÿ�� (ex. SwapChain , Light , G-Buffer)
		* _renderTargets       : �ܺο��� ������� ����Ÿ�� ����
		* _depthStencilTexture : ���� ���� �ؽ���
		*/
		void Create(MultiRenderTargetType _eRenderTargetType, const std::vector<RenderTarget>& _renderTargets, shared_ptr<Texture> _depthStencilTexture);

		/* �ټ��� ����Ÿ���� �����ϴ� �Լ�
		* DeviceContext�� OMSetRenderTarget�� ������ �Լ�
		* mRenderTargets�� ��� RenderTarget���� �����Ѵ�
		*/
		void OMSetRenderTarget();

		/* mRenderTargets�� Ư�� �ε����� ���� RenderTarget���� �����ϴ� �Լ�
		* _index : ����Ÿ������ ������ �ε���
		*/
		void OMSetRenderTarget(int _index);

		/* �ڽſ��� �׷��� ���� ��� �����ִ� �Լ�
		* RenderTargetView �Ӹ� �ƴ϶� DepthStencilView�� �ʱ�ȭ�Ѵ�.
		*/
		void ClearRenderTargetView();

		void SetClearColor(Vec4 _color);
		void SetClearColor(int _index, Vec4 _color);

	private:
		MultiRenderTargetType	     meRenderTargetType;
		std::vector<RenderTarget>	 mRenderTargets;
		int							 mRenderTargetCount;
		shared_ptr<Texture>		     mpDepthStencilTexture;

	};

}

