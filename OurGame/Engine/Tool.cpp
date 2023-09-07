#include "pch.h"
#include "Tool.h"
#include "Engine.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Resources.h"
#include "GameObject.h"
#include "Input.h"
#include "Mesh.h"
#include "Animator.h"

namespace hm
{
	Tool::Tool()
		: mHwnd(0)
		, mpGameObject(nullptr)
		, meCurrentOperation(ImGuizmo::ROTATE)
		, meCurrentMode(ImGuizmo::WORLD)
		, mSnaps{ 0.1f, 0.1f, 0.1f }
	{
	}

	Tool::~Tool()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void Tool::Initialize(HWND _hwnd, ComPtr<ID3D11Device> _pDevice, ComPtr<ID3D11DeviceContext> _pContext)
	{
		mHwnd = _hwnd;
		mpDevice = _pDevice;
		mpContext = _pContext;

		InitGui();
	}
	void Tool::Update()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();


		if (true == mbUseGizmo)
			UpdateGizmo();

		else if (true == mbUseAnimGui)
			UpdateAnimation();

	}
	void Tool::Render()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void Tool::InitGui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(mHwnd);
		ImGui_ImplDX11_Init(mpDevice.Get(), mpContext.Get());

		if (true == mbUseGizmo)
			InitGizmoGui();

		else if (true == mbUseAnimGui)
			InitAnimGui();

	}

	void Tool::InitGizmoGui()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(1600, 900);

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(0, 0);
		style.FramePadding = ImVec2(0, 0);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	}

	void Tool::UpdateGizmo()
	{
		Vec2 Resolution = gpEngine->GetResolution();
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(Resolution.x, Resolution.y));

		if (ImGui::Begin("Gizmo", nullptr,
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
		{
			ImVec2 panelSize = ImGui::GetWindowSize();
			shared_ptr<Texture> pSwapChainTarget = GET_SINGLE(Resources)->Get<Texture>(L"SwapChainTarget_0");
			if (nullptr != pSwapChainTarget)
				ImGui::Image(pSwapChainTarget->GetSRV().Get(), panelSize);

			if (nullptr != mpGameObject)
			{
				EditTransform();
				ShowTransform();
			}
		}
		ImGui::End();
	}

	void Tool::EditTransform()
	{
		if (IS_DOWN(KeyType::N_3))
			meCurrentOperation = ImGuizmo::TRANSLATE;
		if (IS_DOWN(KeyType::N_2))
			meCurrentOperation = ImGuizmo::ROTATE;
		if (IS_DOWN(KeyType::N_1))
			meCurrentOperation = ImGuizmo::SCALE;
		if (IS_DOWN(KeyType::SQUARE_BKT_L))
			mSnaps *= 0.1f;
		if (IS_DOWN(KeyType::SQUARE_BKT_R))
			mSnaps *= 10.f;
		if (IS_PRESS(KeyType::LCTRL))
		{
			if (IS_DOWN(KeyType::Y) && false == mRedoStack.empty())
			{
				Matrix currentMat = mpGameObject->GetTransform()->GetWorldMatrix();
				mUndoStack.push_back(currentMat);

				if (20 < mUndoStack.size())
					mUndoStack.pop_back();

				Matrix beforeMat = mRedoStack.back();
				mRedoStack.pop_back();
				mpGameObject->GetTransform()->SetWorldMatrix(beforeMat);
				return;
			}

			if (IS_DOWN(KeyType::Z) && false == mUndoStack.empty())
			{
				Matrix currentMat = mpGameObject->GetTransform()->GetWorldMatrix();
				mRedoStack.push_back(currentMat);

				if (20 < mRedoStack.size())
					mRedoStack.pop_back();

				Matrix beforeMat = mUndoStack.back();
				mUndoStack.pop_back();
				mpGameObject->GetTransform()->SetWorldMatrix(beforeMat);
				return;
			}
		}

		mSnaps.x = std::clamp(mSnaps.x, 0.01f, 10.f);
		mSnaps.y = std::clamp(mSnaps.y, 0.01f, 10.f);
		mSnaps.z = std::clamp(mSnaps.z, 0.01f, 10.f);

		Scene* pActiveScene = GET_SINGLE(SceneManager)->GetActiveScene();
		Matrix viewMat = pActiveScene->GetMainCamera()->GetViewMatrix();
		Matrix projMat = pActiveScene->GetMainCamera()->GetProjectionMatrix();
		Matrix worldMat = mpGameObject->GetTransform()->GetWorldMatrix();
		Matrix identityMat = Matrix::Identity;

		ImGui::Begin("Gizmo");
		ImGuizmo::SetDrawlist();
		float windowWidth = static_cast<float>(ImGui::GetWindowWidth());
		float windowHeight = static_cast<float>(ImGui::GetWindowHeight());
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

		ImGuizmo::Manipulate(&viewMat._11, &projMat._11, meCurrentOperation, meCurrentMode, &worldMat._11, &identityMat._11, &mSnaps.x);

		if (ImGuizmo::SCALE == meCurrentOperation)
			EditScaleFromKeyboard(worldMat);

		if (ImGuizmo::TRANSLATE == meCurrentOperation)
			EditTranslationFromKeyboard(worldMat);

		if (IS_DOWN(KeyType::LBUTTON))
		{
			mUndoStack.push_back(worldMat);

			if (20 < mUndoStack.size())
				mUndoStack.pop_front();
		}

		mpGameObject->GetTransform()->SetWorldMatrix(worldMat);

		ImGui::End();
	}

	void Tool::EditScaleFromKeyboard(Matrix& _mat)
	{
		float offset = mSnaps.x;

		if (IS_PRESS(KeyType::ALT))
			offset *= 10.f;

		if (IS_DOWN(KeyType::UP))
			_mat._33 += offset;
		if (IS_DOWN(KeyType::DOWN))
			_mat._33 -= offset;
		if (IS_DOWN(KeyType::LEFT))
			_mat._11 -= offset;
		if (IS_DOWN(KeyType::RIGHT))
			_mat._11 += offset;

		if (IS_NONE(KeyType::LCTRL))
		{
			if (IS_DOWN(KeyType::Z))
				_mat._22 += offset;
			if (IS_DOWN(KeyType::X))
				_mat._22 -= offset;
		}
	}

	void Tool::EditTranslationFromKeyboard(Matrix& _mat)
	{
		float offset = mSnaps.x;

		if (IS_PRESS(KeyType::ALT))
			offset *= 10.f;

		if (IS_DOWN(KeyType::UP))
			_mat._43 += offset;
		if (IS_DOWN(KeyType::DOWN))
			_mat._43 -= offset;
		if (IS_DOWN(KeyType::LEFT))
			_mat._41 -= offset;
		if (IS_DOWN(KeyType::RIGHT))
			_mat._41 += offset;

		if (IS_NONE(KeyType::LCTRL))
		{
			if (IS_DOWN(KeyType::Z))
				_mat._42 += offset;
			if (IS_DOWN(KeyType::X))
				_mat._42 -= offset;
		}
	}

	void Tool::ShowTransform()
	{
		Transform* pTransform = mpGameObject->GetTransform();

		Vec3 transform = {};
		wstring transformName = {};
		UINT32 color = 0xff0000ff;
		switch (meCurrentOperation)
		{
		case ImGuizmo::TRANSLATE:
			transform = pTransform->GetPosition();
			transformName = L"POSITION";
			color = 0xff0000ff;
			break;
		case ImGuizmo::SCALE:
			transform = pTransform->GetScale();
			transformName = L"SCALE";
			color = 0xffff0000;
			break;
		case ImGuizmo::ROTATE:
			transform = pTransform->GetRotation();
			transformName = L"ROTATION";
			color = 0xff00ff00;
			break;
		}

		wstring strTransform = {};
		strTransform += L"x = " + std::to_wstring(transform.x) + L"\n";
		strTransform += L"y = " + std::to_wstring(transform.y) + L"\n";
		strTransform += L"z = " + std::to_wstring(transform.z) + L"\n";

		wstring strUnit = L"SNAP : " + std::to_wstring(mSnaps.x);

		/*
		* ���� ������ ��Ʈ�� �ӽ÷� ����ϴ� �ڵ��̱� ������ ������� �����ּ���
		* ������ ���� �ֽ��ϴ�.
		*/
		FONT->DrawString(transformName, 30.f, Vec3(50.f, 890.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, color, FONT_ALIGN::LEFT);
		FONT->DrawString(strTransform, 20.f, Vec3(50.f, 850.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff7f7f7f, FONT_ALIGN::LEFT);
		FONT->DrawString(strUnit, 15.f, Vec3(50.f, 765.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, color, FONT_ALIGN::LEFT);
	}

	void Tool::InitAnimGui()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(500, 500);
	}

	void Tool::UpdateAnimation()
	{
		if (nullptr == mpGameObject)
			return;

		Animator* pAnimator = mpGameObject->GetAnimator();

		Vec2 Resolution = gpEngine->GetResolution();
		ImGui::SetNextWindowPos(ImVec2(Resolution.x - 300.f, 0));
		ImGui::SetNextWindowSize(ImVec2(300.f, 400.f));

		std::vector<AnimClipInfo>* clipInfo = pAnimator->GetAnimClip();
		std::vector<string> animNames = {};
		for (int i = 0; i < clipInfo->size(); ++i)
		{
			animNames.push_back(ws2s((*clipInfo)[i].animName));
		}

		if (ImGui::Begin("AnimGui", nullptr,
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::Text("Animation Tool");

			static int selectItemIdx = 0;
			ImGui::Text("Items:");

			ImGui::BeginChild("ListBox", ImVec2(250, 200), true);
			for (int i = 0; i < animNames.size(); i++) {
				if (ImGui::Selectable((std::to_string(i) + " : " + animNames[i]).c_str(), i == selectItemIdx)) {
					selectItemIdx = i;
					pAnimator->Play(selectItemIdx);
				}
			}
			ImGui::EndChild();
			

			if (selectItemIdx != -1) 
			{
				AnimClipInfo& clip = (*clipInfo)[selectItemIdx];
				ImGui::Text("Anim Index : %d", selectItemIdx);
				ImGui::Text("Anim Name : %s", animNames[selectItemIdx].c_str());
				ImGui::Text("Frame count : %d", clip.frameCount);
				ImGui::Text("Duration : %f", clip.duration);
				ImGui::Text("Loop : %s", clip.bLoop ? "True" : "False");
				ImGui::Text("HasExit : %s", clip.bHasExit ? "True" : "False");
				ImGui::Text("IsFinished : %s", pAnimator->IsFinished() ? "True" : "False");
				ImGui::ProgressBar(static_cast<float>(pAnimator->GetFrameRatio()), ImVec2(200.f, 20.f));
			}
		}
		ImGui::End();
	}

	void Tool::SetGameObject(GameObject* _pGameObject)
	{
		if (nullptr != mpGameObject)
		{
			mpGameObject->GetTransform()->SetUpdateByMat(false);
		}

		AssertEx(nullptr != _pGameObject, L"Tool::SetGameObject() - ���ӿ�����Ʈ�� nullptr�̴�.");
		AssertEx(nullptr != _pGameObject->GetTransform(), L"Tool::SetGameObject() - ���ӿ�����Ʈ�� Ʈ������ ������Ʈ�� �������� ����");
		mpGameObject = _pGameObject;
	}

	LRESULT Tool::DispatchWndMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
	}
}