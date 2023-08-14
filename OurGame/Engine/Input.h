#pragma once

namespace hm
{
	enum class KeyType
	{
		UP = VK_UP,
		DOWN = VK_DOWN,
		LEFT = VK_LEFT,
		RIGHT = VK_RIGHT,

		W = 'W',
		A = 'A',
		S = 'S',
		D = 'D',
		Q = 'Q',
		E = 'E',
		Z = 'Z',
		C = 'C',
		N = 'N',
		G = 'G',
		H = 'H',
		X = 'X',
		F = 'F',
		P = 'P',
		T = 'T',
		O = 'O',
		R = 'R',
		L = 'L',
		K = 'K',

		ENTER = VK_RETURN,
		SPACE = VK_SPACE,
		TAB = VK_TAB,

		LBUTTON = MK_LBUTTON,
		RBUTTON = MK_RBUTTON,
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

	private:
		// Ư�� Ű�� ���¸� ��ȯ�ϴ� �Լ�
		KeyState GetState(KeyType _eKeyType) const { return mStates[static_cast<int>(_eKeyType)]; }

	private:
		HWND				  mHwnd;
		std::vector<KeyState> mStates;
		POINT				  mMousePos = {};
		POINT				  mPrevMousePos = {};
	};
}




