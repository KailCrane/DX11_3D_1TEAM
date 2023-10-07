#pragma once
#include "Object.h"

namespace hm
{
    enum class ShaderType
    {
        Forward,
        Deferred,
        Shadow,
        Light,
        Particle,
        Compute,
        Masking,
        Mirror,
        MotionBlur,
    };

    enum class DepthStencilType
    {
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        LessNoWrite, // ���� �׽�Ʈ O + ���� ��� X
        NoDepthTest, // ���� �׽�Ʈ X + ���� ��� O
        NoDepthTestNoWrite, // ���� �׽�Ʈ X + ���� ��� X
        MaskStencil,
        LessStencil,
        LessEqualStencil,
        GreaterStencil,
        GreaterEqualStencil,
        NoDepthTestStencil,
    };

    enum class RasterizerType
    {
        CullNone,
        CullFront,
        CullBack,
        WireFrame,
        CullNoneCCW,
        CullFrontCCW,
        CullBackCCW,
        WireFrameCCW,
    };

    enum class BlendType
    {
        Default,
        AlphaBlend,
        OneToOneBlend,
        CustumBlend,
        End,
    };
    
    enum class SamplerType
    {
        Wrap,
        Clamp,
        WrapClamp,
        End,
    };

    struct ShaderArg
    {
        string vsFuncName = "VS_Main";
        string gsFuncName = "";
        string psFuncName = "PS_Main";
    };

    struct ShaderInfo
    {
        ShaderInfo(ShaderType _eShaderType = ShaderType::Forward,
            DepthStencilType _eDepthStencilType = DepthStencilType::Less,
            RasterizerType _eRasterizerType = RasterizerType::CullBack,
            BlendType _eBlendType = BlendType::Default,
            D3D_PRIMITIVE_TOPOLOGY _eTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
            : eShaderType(_eShaderType)
            , eDepthStencilType(_eDepthStencilType)
            , eRasterizerType(_eRasterizerType)
            , eBlendType(_eBlendType)
            , eTopology(_eTopology)
        {}

        ShaderType eShaderType;
        DepthStencilType eDepthStencilType;
        RasterizerType eRasterizerType;
        BlendType eBlendType;
        D3D_PRIMITIVE_TOPOLOGY eTopology;
    };


	class Shader :
		public Object
	{
    public:
        Shader();
        virtual ~Shader();
        virtual void Load(const wstring& _path) override;

        /* ���� ���� ���ڵ��� ���� ���������� CreateXXXShader ���� �Լ����� ȣ���Ͽ� ���̴��� �����ϴ� �Լ�
        * _path : ���̴� ������ �ּ�
        * _shaderInfo : ���̴��� ����(DepthStencilType, BlendType, RasterizerType ���)
        * _shaderArg : ���̴� �Լ����� �̸� (VS_Main, PS_Main ...)
        */
        void CreateGraphicsShader(const wstring& _path, ShaderInfo _shaderInfo = ShaderInfo(), ShaderArg _shaderArg = ShaderArg());

        /* �׸��⿡ �ʿ��� ���� ���µ��� �����Ѵ�.
        * DepthStencilState 
        * BlendState
        * RasterizerState
        * PrimitiveTopology 
        * InputLayout
        */
        void Update();

        void UpdateShaderAndSampler();
        void UpdateTopology();
        void UpdateInputLayout();
        void UpdateRenderState();

    public:
        void CreateComputeShader(const wstring& _path, const string& _name, const string& _version);
        void CreateVertexShader(const wstring& _path, const string& _name, const string& _version);
        void CreatePixelShader(const wstring& _path, const string& _name, const string& _version);
        void CreateGeometryShader(const wstring& _path, const string& _name, const string& _version);

        void SetSamplerType(SamplerType _eSamplerType);
        void SetBackfaceCulling(bool _bBackfaceCulling);
        void PushInputLayout();

        ComPtr<ID3D11VertexShader> GetVertexShader() { return mpVertexShader; }
        ComPtr<ID3D11PixelShader> GetPixelShader() { return mpPixelShader; }


    public:
        ShaderType GetShaderType() const { return mShaderInfo.eShaderType; }

    private:
        /* ���޹��� ���ڵ�� Shader�� �����ϴ� �Լ�*/
        void CreateShader(const wstring& _path, const string& _name, const string& _version, ComPtr<ID3DBlob>& _pBlob);
        // ���÷��� �����ϴ� �Լ�
        void CreateSampler();

    private:
        ShaderInfo                      mShaderInfo;

        SamplerType                     meSamplerType;

        ComPtr<ID3D11VertexShader>      mpVertexShader;
        ComPtr<ID3D11GeometryShader>    mpGeometryShader;
        ComPtr<ID3D11PixelShader>       mpPixelShader;
        ComPtr<ID3D11ComputeShader>     mpComputeShader;

        ComPtr<ID3D11InputLayout>       mpInputLayout;

        ComPtr<ID3D11SamplerState>      mpLinearWrapSamplerState;
        ComPtr<ID3D11SamplerState>      mpPointWrapSamplerState;
        ComPtr<ID3D11SamplerState>      mpPointClampSamplerState;
        ComPtr<ID3D11SamplerState>      mpLinearClampSamplerState;
        ComPtr<ID3D11SamplerState>      mpShadowSamplerState;

        ComPtr<ID3D11DepthStencilState> mpDepthStencilState;
        ComPtr<ID3D11RasterizerState>   mpRasterizerState;
        ComPtr<ID3D11BlendState>        mpBlendState;

        ComPtr<ID3DBlob>                mpVSBlob;
        ComPtr<ID3DBlob>                mpPSBlob;
        ComPtr<ID3DBlob>                mpGSBlob;
        ComPtr<ID3DBlob>                mpCSBlob;
        ComPtr<ID3DBlob>                mpErrBlob;
	};
}


