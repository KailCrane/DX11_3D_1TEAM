#ifndef _FINAL_FX_
#define _FINAL_FX_

#include "params.fx"
#include "utils.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    output.pos = float4(_in.pos, 1.f);
    output.uv = _in.uv;
    
    return output;
}

// Final Shader
// g_tex_0   : Diffuse Color RenderTarget
// g_tex_1   : Light Color RenderTarget
// g_tex_2   : Specular Color RenderTarget

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float4 output = (float4) 0;
    
    float4 color = g_tex_0.Sample(g_sam_0, _in.uv);
    return color;
}
#endif