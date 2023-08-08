#pragma once
/* SwapChain�� �������ִ� Ŭ����
* Back Buffer ���� 
* ������ BackBuffer�� �̿��ؼ� RenderTarget View ����
*/
namespace hm
{
	class SwapChain
	{
	public:
		// ���������� CreateSwapChain�� CreateRTV �Լ��� ȣ�����ش�.
		void Initialize();

		// ����ۿ� �׷��� ��ü���� ȭ�鿡 �ѷ��ִ� �Լ�
		void Present();

		ComPtr<IDXGISwapChain> GetSwapChain() { return mpSwapChain; }

	private:
		// SwapChain ����
		void CreateSwapChain();

		// BackBuffer�� �̿��Ͽ� RenderTarget View ����
		void CreateRTV();

	private:
		ComPtr<IDXGISwapChain>		   mpSwapChain;
		ComPtr<ID3D11RenderTargetView> mpRTV;
	};
}


