﻿#include "pch.h"
#include "Engine.h"
#include "GraphicsCore.h"
#include "Timer.h"
#include "SceneManager.h"
#include "Resources.h"
#include "Input.h"
#include "Light.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "FontManager.h"
#include "CollisionManager.h"
#include "Tool.h"
#include "SoundManager.h"

namespace hm
{
	Engine::~Engine()
	{
		SAFE_DELETE(mpTool);
		SAFE_DELETE(mpGraphicsCore);
		SAFE_DELETE(mpSwapChain);
		SAFE_DELETE(mpPhysics);
		SAFE_DELETE(mpFont);

		for (int i = 0; i < CONSTANT_BUFFER_TYPE_COUNT; ++i)
		{
			SAFE_DELETE(mConstantBufferGroup[i]);
		}

		for (int i = 0; i < MULTI_RENDER_TARGET_TYPE_COUNT; ++i)
		{
			SAFE_DELETE(mMultiRenderTargets[i]);
		}
	}
	void Engine::Initialize(const WindowInfo& _windowInfo)
	{
		mWindowInfo = _windowInfo;
		mViewport = { 0, 0,
			static_cast<FLOAT>(mWindowInfo.width),
			static_cast<FLOAT>(mWindowInfo.height),
			0.0f,
			1.0f
		};

		mScissorRect = CD3D11_RECT(0, 0, mWindowInfo.width, mWindowInfo.height);
		ResizeWindow(mWindowInfo.width, mWindowInfo.height);

		mpGraphicsCore = new GraphicsCore;
		mpSwapChain = new SwapChain;
		mpPhysics = new Physics;
		mpFont = new Font;
		mpTool = new Tool;

		mpGraphicsCore->Initialize();
		mpSwapChain->Initialize();
		mpPhysics->Initialize();
		mpFont->Initialize(mWindowInfo, mpGraphicsCore->GetDevice(), mpGraphicsCore->GetContext());
		mpTool->Initialize(mWindowInfo.hwnd, DEVICE.Get(), CONTEXT.Get());

		mpGraphicsCore->Create2DRenderTarget();

		CreateMultiRenderTarget();
		CreateConstantBuffer(RegisterCBV::b0, sizeof(TransformParams));
		CreateConstantBuffer(RegisterCBV::b1, sizeof(MaterialParams));
		CreateConstantBuffer(RegisterCBV::b2, sizeof(LightParams));
		CreateConstantBuffer(RegisterCBV::b3, sizeof(BloomParams));
		CreateConstantBuffer(RegisterCBV::b4, sizeof(NoiseParams));
		CreateConstantBuffer(RegisterCBV::b5, sizeof(DistortionParams));
		CreateConstantBuffer(RegisterCBV::b6, sizeof(ReflectParams));

		GET_SINGLE(FontManager)->Initialize();
		GET_SINGLE(Resources)->Initialize();
		GET_SINGLE(Input)->Initialize();
		GET_SINGLE(SceneManager)->Initialize();
		GET_SINGLE(Timer)->Initialize();
		GET_SINGLE(RenderManager)->Initialize();
		GET_SINGLE(SoundManager)->Initialize();
	}

	void Engine::ResizeWindow(int _width, int _height)
	{
		mWindowInfo.width = _width;
		mWindowInfo.height = _height;

		RECT rect = { 0, 0, _width, _height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mWindowInfo.hwnd, 0, 0, 0, _width, _height, 0);
	}

	void Engine::CreateMultiRenderTarget()
	{
		shared_ptr<Texture> pDepthStencilTexture =
			GET_SINGLE(Resources)->CreateTexture(
				L"DepthStencil", DXGI_FORMAT_D24_UNORM_S8_UINT, 
				D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL, mWindowInfo.width, mWindowInfo.height);

		// Swap Chain
		{
			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			std::vector<RenderTarget> renderTargets(SWAP_CHAIN_BUFFER_COUNT);
			for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; ++i)
			{
				wstring name = L"SwapChainTarget_" + std::to_wstring(i);
				ComPtr<ID3D11Texture2D> pResource = {};

				HRESULT hr = mpSwapChain->GetSwapChain()->GetBuffer(i, IID_PPV_ARGS(&pResource));
				AssertEx(SUCCEEDED(hr), L"Engine::CreateMultiRenderTarget() - GetBuffer Failed");

				renderTargets[i].pTarget = GET_SINGLE(Resources)->CreateTextureFromResource(name, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE, pResource);
				memcpy(renderTargets[i].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));
			}

			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::SwapChain)] = new MultiRenderTarget;
			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::SwapChain)]->Create(MultiRenderTargetType::SwapChain, renderTargets, pDepthStencilTexture);
		}

		// G-Buffer
		{
			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			std::vector<RenderTarget> renderTargets(G_BUFFER_GROUP_COUNT);

			renderTargets[0].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"PositionTarget",
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);

			renderTargets[1].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"NormalTarget",
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);

			renderTargets[2].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"DiffuseTarget",
				DXGI_FORMAT_R8G8B8A8_UNORM,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);

			renderTargets[3].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"BloomTarget",
				DXGI_FORMAT_R8G8B8A8_UNORM,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);

			renderTargets[4].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"DepthTarget",
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);

			renderTargets[5].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"VelocityTarget",
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);

			memcpy(renderTargets[0].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));
			memcpy(renderTargets[1].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));
			memcpy(renderTargets[2].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));
			memcpy(renderTargets[3].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));
			memcpy(renderTargets[4].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));
			memcpy(renderTargets[5].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));

			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::G_Buffer)] = new MultiRenderTarget;
			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::G_Buffer)]->Create(MultiRenderTargetType::G_Buffer, renderTargets, pDepthStencilTexture);
		}

		// Lighting
		{
			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			std::vector<RenderTarget> renderTargets(LIGHTING_GROUP_COUNT);

			renderTargets[0].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"DiffuseLightTarget",
				DXGI_FORMAT_R8G8B8A8_UNORM,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS,
				mWindowInfo.width, mWindowInfo.height);

			renderTargets[1].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"SpecularLightTarget",
				DXGI_FORMAT_R8G8B8A8_UNORM,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);


			memcpy(renderTargets[0].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));
			memcpy(renderTargets[1].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));

			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::Light)] = new MultiRenderTarget;
			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::Light)]->Create(MultiRenderTargetType::Light, renderTargets, pDepthStencilTexture);
		}

		// Rim Lighting
		{
			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			std::vector<RenderTarget> renderTargets(RIM_LIGHTING_GROUP_COUNT);

			renderTargets[0].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"RimLightingTarget",
				DXGI_FORMAT_R8G8B8A8_UNORM,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);

			memcpy(renderTargets[0].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));

			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::RimLighting)] = new MultiRenderTarget;
			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::RimLighting)]->Create(MultiRenderTargetType::RimLighting, renderTargets, pDepthStencilTexture);
		}

		// Light Blend
		{
			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			std::vector<RenderTarget> renderTargets(LIGHTBLEND_GROUP_COUNT);

			renderTargets[0].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"LightBlendTarget",
				DXGI_FORMAT_R8G8B8A8_UNORM,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);

			memcpy(renderTargets[0].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));

			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::LightBlend)] = new MultiRenderTarget;
			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::LightBlend)]->Create(MultiRenderTargetType::LightBlend, renderTargets, pDepthStencilTexture);
		}

		// Screen Effect
		{
			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			std::vector<RenderTarget> renderTargets(EFFECT_GROUP_COUNT);

			renderTargets[0].pTarget = GET_SINGLE(Resources)->CreateTexture(
				L"ScreenEffectTarget",
				DXGI_FORMAT_R8G8B8A8_UNORM,
				D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
				mWindowInfo.width, mWindowInfo.height);

			memcpy(renderTargets[0].clearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));

			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::ScreenEffect)] = new MultiRenderTarget;
			mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::ScreenEffect)]->Create(MultiRenderTargetType::ScreenEffect, renderTargets, pDepthStencilTexture);
		}
	}

	void Engine::CreateConstantBuffer(RegisterCBV _eRegister, int _size)
	{
		int index = static_cast<int>(_eRegister);
		if (CBV_REGISTER_COUNT <= index)
			AssertEx(false, L"Engine::CreateConstantBuffer() - ConstantBuffer 생성 실패, 잘못된 레지스터 전달");

		mConstantBufferGroup[index] = new ConstantBuffer;
		mConstantBufferGroup[index]->Create(_eRegister, _size);
	}

	void Engine::SetSwapChainRTVClearColor(Vec4 _color)
	{
		AssertEx(mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::G_Buffer)], L"Engine::SetSwapChainRTVClearColor() - SwapChain이 생성되지 않음");
		mMultiRenderTargets[static_cast<int>(MultiRenderTargetType::G_Buffer)]->SetClearColor(2, _color);
	}


	void Engine::Update()
	{
		GET_SINGLE(Timer)->Update();
		GET_SINGLE(Input)->Update();
		GET_SINGLE(SceneManager)->Update();
		GET_SINGLE(SceneManager)->FixedUpdate();
		GET_SINGLE(SceneManager)->FinalUpdate();
		GET_SINGLE(CollisionManager)->Update();
		GET_SINGLE(SoundManager)->Update();
		mpPhysics->Update();

		mpTool->Update();
	}
	void Engine::Render()
	{
		RenderBegin();
		// Scene Rendering
		GET_SINGLE(SceneManager)->Render();
		mpTool->Render();
		RenderEnd();

	}
	void Engine::RenderBegin()
	{
		//CONTEXT->RSSetViewports(1, &mViewport);
		//CONTEXT->RSSetScissorRects(1, &mScissorRect);
	}
	void Engine::RenderEnd()
	{
		GET_SINGLE(Timer)->Render();
		mpSwapChain->Present();
		GET_SINGLE(EventManager)->Process();
	}
	void Engine::Destroy()
	{
		GET_SINGLE(SceneManager)->Destroy();
	}
}