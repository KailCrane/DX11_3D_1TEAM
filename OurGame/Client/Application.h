#pragma once
namespace hm
{
	/*
	* Ŭ���̾�Ʈ�� �������� ������ �ϴ� Ŭ����
	* ������ �����ֱ� �Լ����� ����ؼ� �������Ѵ�
	*/
	class Application
	{
	public:
		/*
		* ������ �ʱ�ȭ�� ���� �Լ�
		*/
		void Initialize(const WindowInfo& _windowInfo);
		void Start();
		void Update();
		void Destroy();

	public:

	};
}


