#pragma once
#include "TimerObject.h"
namespace hm
{


	enum class HotKeyType
	{
		UP_LEFT,
		UP_RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT,
		
		WA,
		WD,
		AS,
		SD,
	};

	enum class KeyState
	{
		None,
		Press,
		Down,
		Up,
		End
	};

	enum
	{
		KEY_TYPE_COUNT = static_cast<int>(UINT8_MAX + 1),
		KEY_STATE_COUNT = static_cast<int>(KeyState::End),
	};


	class Input
	{
		DECLARE_SINGLE(Input);

	public:
		// �� Ű�� ���¸� �ʱ�ȭ�ϴ� �Լ�
		void Initialize();
		// �� Ű�� ���¸� ������Ʈ�ϴ� �Լ�
		void Update();
		void HotKeyUpdate();
		void ClearHotkey();
		// Ű�� �����ִ��� üũ�ϴ� �Լ�
		bool GetButtonPress(KeyType _eKey)     const { return KeyState::Press == GetState(_eKey); }
		// Ű�� ��� ���ȴ��� üũ�ϴ� �Լ�
		bool GetButtonDown(KeyType _eKey)      const { return KeyState::Down == GetState(_eKey); }
		// Ű�� ��� �������� �Լ�
		bool GetButtonUp(KeyType _eKey)        const { return KeyState::Up == GetState(_eKey); }
		// Ű�� �������� ������ �Լ�
		bool GetButtonNone(KeyType _eKey)      const { return KeyState::None == GetState(_eKey); }
		// ���� ���콺 ��ġ�� ��ȯ�Ѵ�.
		const POINT& GetMousePos() const { return mMousePos; }
		const POINT& GetPrevMousePos() const { return mPrevMousePos; }

		bool GetHotKeyPress(HotKeyType _eKey) const { return KeyState::Press == mHotkeyStates[static_cast<int>(_eKey)]; }
		bool GetHotKeyUp(HotKeyType _eKey) const { return KeyState::Up == mHotkeyStates[static_cast<int>(_eKey)]; }



	private:
		// Ư�� Ű�� ���¸� ��ȯ�ϴ� �Լ�
		KeyState GetState(KeyType _eKeyType) const { return mStates[static_cast<int>(_eKeyType)]; }

	private:
		HWND				  mHwnd;
		std::vector<KeyState> mStates;
		std::vector<KeyState> mHotkeyStates;
		POINT				  mMousePos = {};
		POINT				  mPrevMousePos = {};
		TimerObject			  mTimer;
	};
}




