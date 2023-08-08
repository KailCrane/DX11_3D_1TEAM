#pragma once
#include "Object.h"

namespace hm
{
	class Texture :
		public Object
	{
    public:
        Texture();
        virtual ~Texture();
        // Resources�� ���� ȣ��Ǹ� �ܺ� �̹����� �ε��ϴ� �Լ�
        virtual void Load(const wstring& _path) override;

    public:

        /* ��ü������ �̹����� �����ϴ� �Լ�
        * _type : ���� �̹����� ���� Ÿ�� (RTV, SRV, DSV ...)
        * _eFormat : �ؽ��İ� �������� ���� (ex R8G8B8 ...)
        * _width : �ؽ����� ���� ũ��
        * _height : �ؽ����� ���� ũ��
        */
        void Create(UINT _type, DXGI_FORMAT _eFormat, int _width, int _height);

        /* ���ҽ��� �����ϴ� ��� �� ���ҽ��� �ؽ��ĸ� ����� �Լ�
        * _type : ���� �̹����� ���� Ÿ�� (RTV, SRV, DSV ...)
        * _eFormat : �ؽ��İ� �������� ���� (ex R8G8B8 ...)
        * _pTex2D : ���ҽ�
        */
        void CreateFromTexture(UINT _type, DXGI_FORMAT _eFormat, ComPtr<ID3D11Texture2D> _pTex2D);

    public:
        Vec3 GetTexSize() { return mTexSize; }

    public:
        ComPtr<ID3D11Texture2D>           GetTex2D() const { return mpTex2D; }
        ComPtr<ID3D11RenderTargetView>    GetRTV()   const { return mpRTV; }
        ComPtr<ID3D11ShaderResourceView>  GetSRV()   const { return mpSRV; }
        ComPtr<ID3D11DepthStencilView>    GetDSV()   const { return mpDSV; }
        ComPtr<ID3D11UnorderedAccessView> GetUAV()   const { return mpUAV; }

    private:
        UINT                                meTextureType;
        Vec3                                mTexSize;

        ScratchImage                        mScratchImage;
        ComPtr<ID3D11Texture2D>             mpTex2D;

        ComPtr<ID3D11RenderTargetView>      mpRTV;
        ComPtr<ID3D11ShaderResourceView>    mpSRV;
        ComPtr<ID3D11DepthStencilView>      mpDSV;
        ComPtr<ID3D11UnorderedAccessView>   mpUAV;
	};

}

