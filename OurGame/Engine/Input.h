#pragma once
#include "TimerObject.h"
namespace hm
{
	enum class KeyType
	{
		UP = VK_UP,
		DOWN = VK_DOWN,
		LEFT = VK_LEFT,
		RIGHT = VK_RIGHT,

		Q = 'Q', W = 'W', E = 'E', R = 'R', T = 'T', Y = 'Y', U = 'U', I = 'I', O = 'O', P = 'P',
		A = 'A', S = 'S', D = 'D', F = 'F', G = 'G', H = 'H', J = 'J', K = 'K', L = 'L',
		Z = 'Z', X = 'X', C = 'C', V = 'V', B = 'B', N = 'N', M = 'M',

		NUM_0 = VK_NUMPAD0, NUM_1 = VK_NUMPAD1, NUM_2 = VK_NUMPAD2,
		NUM_3 = VK_NUMPAD3, NUM_4 = VK_NUMPAD4, NUM_5 = VK_NUMPAD5,
		NUM_6 = VK_NUMPAD6, NUM_7 = VK_NUMPAD7, NUM_8 = VK_NUMPAD8,
		NUM_9 = VK_NUMPAD9,

		N_0 = '0', N_1 = '1', N_2 = '2', N_3 = '3', N_4 = '4', N_5 = '5',
		N_6 = '6', N_7 = '7', N_8 = '8', N_9 = '9',

		ENTER = VK_RETURN,
		SPACE = VK_SPACE,
		TAB = VK_TAB,
		LCTRL = VK_LCONTROL,
		ALT = VK_MENU,
		SHIFT_L = VK_LSHIFT,

		LBUTTON = MK_LBUTTON,
		RBUTTON = MK_RBUTTON,

		SQUARE_BKT_L = VK_OEM_4,
		SQUARE_BKT_R = VK_OEM_6,
	};

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




