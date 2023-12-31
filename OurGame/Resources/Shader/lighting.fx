#ifndef _LIGHTING_FX_
#define _LIGHTING_FX_

#include "params.fx"
#include "utils.fx"

static const float2 offsets[9] =
{
    float2(-1, -1), float2(0, -1), float2(1, -1),
            float2(-1, 0), float2(0, 0), float2(1, 0),
            float2(-1, +1), float2(0, +1), float2(1, +1)
};

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


VS_OUT VS_DirLight(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    output.pos = float4(_in.pos, 1.f);
    output.uv = _in.uv;
    
    return output;
}

// Lighting Params
// g_int_0 : Light Index
// g_tex_0 : Position RenderTarget
// g_tex_1 : Normal   RenderTarget
// g_tex_2 : Emissive RenderTarget

struct PS_OUT
{
    float4 diffuse : SV_Target0;
    float4 specular : SV_Target1;
};

PS_OUT PS_DirLight(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;

    float4 viewPos = g_tex_0.Sample(g_sam_0, _in.uv);
    //if (viewPos.z <= 0.f)
    //    clip(-1);
    
    float3 viewNormal = g_tex_1.Sample(g_sam_0, _in.uv).xyz;

    LightColor color = CalculateLightColor(g_int_0, viewNormal, viewPos.xyz);
    
    if (length(color.diffuse) != 0)
    {
        matrix shadowCameraVP = g_mat_0;

        float4 worldPos = mul(float4(viewPos.xyz, 1.f), g_matViewInv);
        float4 shadowClipPos = mul(worldPos, shadowCameraVP);
        float depth = shadowClipPos.z / shadowClipPos.w;

        // x [-1 ~ 1] -> u [0 ~ 1]
        // y [1 ~ -1] -> v [0 ~ 1]
        float2 uv = shadowClipPos.xy / shadowClipPos.w;
        uv.y = -uv.y;
        uv = uv * 0.5 + 0.5;
        float bias = 0.00018f;
        if (0 < uv.x && uv.x < 1 && 0 < uv.y && uv.y < 1)
        {
            float shadowFactor = g_tex_2.SampleCmpLevelZero(g_sam_2, uv, depth - bias).r;
            shadowFactor = 1.f - shadowFactor;
            if (0 < shadowFactor)
            {
                color.diffuse *= 0.5;
            }
            else
            {
                shadowFactor = g_tex_3.SampleCmpLevelZero(g_sam_2, uv, depth - 0.05f).r;
                
                if (0 < shadowFactor)
                {
                    color.diffuse *= 0.5;
                }
            }

        }
    }
    
    output.diffuse = color.diffuse + color.ambient;
    //output.specular = color.specular;
    float isViewPos = viewPos.x + viewPos.y + viewPos.z;
    if (0 == isViewPos)
        output.diffuse = float4(1.f, 1.f, 1.f, 1.f);

    return output;
}

// Point Params
// g_int_0 : Light Index
// g_vec2_0 : RenderTarget Resolution
// g_tex_0 : Position RenderTarget
// g_tex_1 : Diffuse Light RenderTarget

VS_OUT VS_PointLight(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.uv = _in.uv;
    
    return output;
}

PS_OUT PS_PointLight(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;

    // _in.pos = SV_Position = Screen ��ǥ
    float2 uv = float2(_in.pos.x / g_vec2_0.x, _in.pos.y / g_vec2_0.y);
    float3 viewPos = g_tex_0.Sample(g_sam_0, uv).xyz;
    if (viewPos.z <= 0.f)
        discard;

    int lightIndex = g_int_0;
    float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.f), g_matView).xyz;
    float distance = length(viewPos - viewLightPos);
    if (distance > g_light[lightIndex].range)
        discard;

    float3 viewNormal = g_tex_1.Sample(g_sam_0, uv).xyz;
    LightColor color = CalculateLightColor(g_int_0, viewNormal, viewPos);
    
    if (length(color.diffuse) != 0)
    {
        matrix shadowCameraVP = g_mat_0;

        float4 worldPos = mul(float4(viewPos.xyz, 1.f), g_matViewInv);
        float4 shadowClipPos = mul(worldPos, shadowCameraVP);
        float depth = shadowClipPos.z / shadowClipPos.w;

        // x [-1 ~ 1] -> u [0 ~ 1]
        // y [1 ~ -1] -> v [0 ~ 1]
        float2 uv = shadowClipPos.xy / shadowClipPos.w;
        uv.y = -uv.y;
        uv = uv * 0.5 + 0.5;
        float bias = 0.0018f;
        if (0 < uv.x && uv.x < 1 && 0 < uv.y && uv.y < 1)
        {
            float shadowFactor = g_tex_2.SampleCmpLevelZero(g_sam_2, uv, depth - bias).r;
            shadowFactor = 1 - shadowFactor;
            if (0 < shadowFactor)
            {
                color.diffuse *= 0.5;
            }
            else
            {
                shadowFactor = g_tex_3.SampleCmpLevelZero(g_sam_2, uv, depth - bias).r;
                shadowFactor = 1 - shadowFactor;
                if (0 < shadowFactor)
                {
                    color.diffuse *= 0.5;
                }
            }

        }
    }
   
    output.diffuse = color.diffuse + color.ambient;
    return output;
}
#endif