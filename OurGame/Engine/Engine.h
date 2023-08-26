#pragma once
#include "EnginePch.h"
#include "GraphicsCore.h"
#include "SwapChain.h"
#include "ConstantBuffer.h"
#include "MultiRenderTarget.h"
#include "Physics.h"
#include "Font.h"
#include "Tool.h"

namespace hm
{
	class GraphicsCore;
	
	/*
	 - ������ �������� �κ��� ����ϴ� ���� Ŭ����
	*/
	class Engine
	{
	public:
		Engine() = default;
		~Engine();

		// ������� ���� �̱��� Ŭ���� �ʱ�ȭ
		void Initialize(const WindowInfo& _windowInfo);

		// ���� �̱��� Ŭ������ ������Ʈ �Լ� ȣ��
		void Update();

		// �� �� ���� ��ó�� ����� ����
		void Render();

		// ���� �������ϱ� �� ����Ʈ �ʱ�ȭ
		void RenderBegin();

		// Present�� ������ �Ŀ� ó���ؾ� �� �۾����� ó���ϴ� �Լ�
		void RenderEnd();

		// ���α׷��� ����Ǳ� �� �������� �����ϴ� �Լ�
		void Destroy();

		const WindowInfo& GetWindowInfo() { return mWindowInfo; }
		HWND GetHwnd()		 { return mWindowInfo.hwnd; }
		Vec2 GetResolution() { return Vec2(static_cast<float>(mWindowInfo.width), 
										   static_cast<float>(mWindowInfo.height)); }

		// ������ ������ Ŭ������ �ܺο��� ������ �� �ֵ��� �Ѵ�.
		GraphicsCore* GetGraphicsCore() { return mpGraphicsCore; }
		SwapChain*    GetSwapChain()    { return mpSwapChain; }
		ConstantBuffer* GetConstantBuffer(ConstantBufferType _eContantBufferType) { return mConstantBufferGroup[static_cast<int>(_eContantBufferType)]; }
		MultiRenderTarget* GetMultiRenderTarget(MultiRenderTargetType _eMultiRenderTargetType) { return mMultiRenderTargets[static_cast<int>(_eMultiRenderTargetType)]; }
		Physics* GetPhysics() { return mpPhysics; }
		Font* GetFont() { return mpFont; }
		Tool* GetTool() { return mpTool; }

		// ������ ������ �����ϴ� �Լ�
		void ResizeWindow(int _width, int _height);
		void CreateMultiRenderTarget();
		void CreateConstantBuffer(RegisterCBV _eRegister, int _size);

		void SetSwapChainRTVClearColor(Vec4 _color);

	private:
		WindowInfo				mWindowInfo;
		D3D11_VIEWPORT			mViewport;
		D3D11_RECT				mScissorRect;

		GraphicsCore* mpGraphicsCore;
		SwapChain*    mpSwapChain;
		Physics* mpPhysics;
		Font* mpFont;
		Tool* mpTool;

		std::array<ConstantBuffer*, CONSTANT_BUFFER_TYPE_COUNT> mConstantBufferGroup;
		std::array<MultiRenderTarget*, MULTI_RENDER_TARGET_TYPE_COUNT> mMultiRenderTargets;
	};
}
