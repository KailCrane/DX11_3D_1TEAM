#pragma once

namespace hm
{

	/*
	 - DirectX11���� �ֿ� ����� ����ϴ� Device�� Context�� �����ϴ� Ŭ����
	*/

	class GraphicsCore
	{
	public:
		GraphicsCore() = default;
		~GraphicsCore() = default;
	public:
		// ���ο��� ����̽�, ���ؽ�Ʈ�� Dxgi�� ����
		void Initialize();
		void Create2DRenderTarget();

		ComPtr<ID3D11DeviceContext> GetContext() { return mpContext; }
		ComPtr<ID3D11Device> GetDevice() { return mpDevice; }
		ComPtr<IDXGIFactory> GetDxgi() { return mpDxgi; }
		ComPtr<ID2D1RenderTarget> GetRenderTarget2D() { return mpRenderTarget2D; }
		ComPtr<ID2D1Factory> GetFactory2D() { return mpFactory2D; }

	private:
		// ����̽��� ���ؽ�Ʈ�� �����Ѵ�
		void CreateDeviceAndContext();

		// DxgiFactory�� �����Ѵ�. (DxgiFactory�� SwapChain�� ���� �� ����Ѵ�)
		void CreateDxgiFactory();

	private:
		ComPtr<ID3D11DeviceContext> mpContext;
		ComPtr<ID3D11Device> mpDevice;
		ComPtr<IDXGIFactory> mpDxgi;

		ComPtr<ID2D1RenderTarget> mpRenderTarget2D;
		ComPtr<ID2D1Factory> mpFactory2D;
	};
}


