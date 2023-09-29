#include "pch.h"
#include "GraphicsCore.h"
#include "Engine.h"

namespace hm
{
	void GraphicsCore::Initialize()
	{
		CreateDeviceAndContext();
		CreateDxgiFactory();
		CreateVideoLibrary();

	}
	void GraphicsCore::Create2DRenderTarget()
	{
		D2D1_FACTORY_OPTIONS option = {};
		option.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

		
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, option,
			mpFactory2D.GetAddressOf());

		AssertEx(SUCCEEDED(hr), L"GraphicsCore::Create2DRenderTarget() - 2D ���丮 ���� ����");

		IDXGISurface* pBackSurface = nullptr;
		gpEngine->GetSwapChain()->GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&pBackSurface));

		D2D1_RENDER_TARGET_PROPERTIES propertyOption = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_HARDWARE,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));


		hr = mpFactory2D->CreateDxgiSurfaceRenderTarget(pBackSurface, propertyOption,
			mpRenderTarget2D.GetAddressOf());

		AssertEx(SUCCEEDED(hr), L"GraphicsCore::Create2DRenderTarget() - 2D ����Ÿ�� ���� ����");

		if (nullptr != pBackSurface)
		{
			pBackSurface->Release();
			pBackSurface = nullptr;
		}
	}
	void GraphicsCore::CreateDeviceAndContext()
	{
		// Create Device/Context
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

//#if defined(DEBUG_BUILD)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif
		HRESULT hResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
			0, creationFlags,
			featureLevels, ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION, &mpDevice,
			0, &mpContext);
		AssertEx(SUCCEEDED(hResult), L"GraphicsCore::CreateDeviceAndContext() - Device ���� ����");
	}


	void GraphicsCore::CreateDxgiFactory()
	{
		// Create DXGI
		HRESULT hResult = CreateDXGIFactory(IID_PPV_ARGS(&mpDxgi));
		AssertEx(SUCCEEDED(hResult), L"GraphicsCore::CreateDxgiFactory() - DxgiFactory ���� ����");
	}
	void GraphicsCore::CreateVideoLibrary()
	{
		HRESULT hr = CoInitialize(NULL);
		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IFilterGraph2, reinterpret_cast<void**>(mpGraphBuilder.GetAddressOf()));
		AssertEx(SUCCEEDED(hr), L"GraphicsCore::CreateVideoLibrary() - GraphBuilder ���� ����");

		hr = mpGraphBuilder->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(mpMediaControl.GetAddressOf()));
		AssertEx(SUCCEEDED(hr), L"GraphicsCore::CreateVideoLibrary() - MediaControl ���� ����");

		hr = mpGraphBuilder->QueryInterface(IID_IMediaPosition, reinterpret_cast<void**>(mpMediaPosition.GetAddressOf()));
		AssertEx(SUCCEEDED(hr), L"GraphicsCore::CreateVideoLibrary() - MediaPosition ���� ����");

		hr = mpGraphBuilder->QueryInterface(IID_IMediaEvent, reinterpret_cast<void**>(mpMediaEvent.GetAddressOf()));
		AssertEx(SUCCEEDED(hr), L"GraphicsCore::CreateVideoLibrary() - MediaEvent ���� ����");

		hr = mpGraphBuilder->QueryInterface(IID_IVideoWindow, reinterpret_cast<void**>(mpVideoWindow.GetAddressOf()));
		AssertEx(SUCCEEDED(hr), L"GraphicsCore::CreateVideoLibrary() - VideoControl ���� ����");

	}
}

