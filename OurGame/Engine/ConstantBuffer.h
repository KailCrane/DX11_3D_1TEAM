#pragma once

namespace hm
{
	/*
	* ConstantBuffer�� �����ϴ� Ŭ����
	* Engine������ �� Ŭ������ �ν��Ͻ��� �迭�� ������ �ְ�,
	* ConstantBufferType�̶�� Enum������ �����ؼ� Transform, Material, Light�� ���� ������ ������ �� �ִ�.
	*/
	class ConstantBuffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();

	public:
		/* ConstantBuffer�� �����ϴ� �Լ�
		* _eReg : �� �� �������͸� ����� ������ �����ϴ� ����
		* _size : ����� ����ü�� ũ��
		*/
		void Create(RegisterCBV _eReg, int _size);

		/*mpBuffer�� ���ڷ� ���� ���� �����͸� �����ϴ� �Լ�
		* _pData : ���ۿ� ��� �� (�����δ� ConstantBufferType�� �´� ����ü�� �����Ͱ� ��)
		* _size : _pData�� ũ��
		*/
		void PushData(void* _pData, int _size);

		// mpBuffer�� ��� ���� ������ GPU�� �����ϴ� �Լ�
		void Mapping();

	private:
		RegisterCBV				 meReg;
		ComPtr<ID3D11Buffer>	 mpBuffer;

	};
}

