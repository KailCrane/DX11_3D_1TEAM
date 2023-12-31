#ifndef _SPAWN_PAPER_BURN_FX_
#define _SPAWN_PAPER_BURN_FX_

#include "params.fx"
#include "utils.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 weight : WEIGHT;
    float4 indices : INDICES;
    
    row_major matrix matWorld : W;
    row_major matrix matWV : WV;
    row_major matrix matWVP : WVP;
    uint instanceID : SV_InstanceID;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
    float3 viewPos : POSITION;
    float3 viewNormal : NORMAL;
    float3 viewTangent : TANGENT;
    float3 viewBinormal : BINORMAL;
};

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    int instancingFlag = g_int_0;
    
    if (1 == instancingFlag)
    {
        if (g_int_1 == 1)
            Skinning(_in.pos, _in.normal, _in.tangent, _in.weight, _in.indices);
        
        output.pos = mul(float4(_in.pos, 1.f), _in.matWVP);
        output.uv = _in.uv;
        output.viewPos = mul(float4(_in.pos, 1.f), _in.matWV).xyz;
        output.viewNormal = normalize(mul(float4(_in.normal, 0.f), _in.matWV)).xyz;
        output.viewTangent = normalize(mul(float4(_in.tangent, 0.f), _in.matWV)).xyz;
        output.viewBinormal = normalize(cross(output.viewTangent, output.viewNormal));
    }
    else
    {
        if (g_int_1 == 1)
            Skinning(_in.pos, _in.normal, _in.tangent, _in.weight, _in.indices);
        
        output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
        output.uv = _in.uv;
        output.viewPos = mul(float4(_in.pos, 1.f), g_matWV).xyz;
        output.viewNormal = normalize(mul(float4(_in.normal, 0.f), g_matWV)).xyz;
        output.viewTangent = normalize(mul(float4(_in.tangent, 0.f), g_matWV)).xyz;
        output.viewBinormal = normalize(cross(output.viewTangent, output.viewNormal));
    }
    
    return output;
}

// Paper Burn Shader
// g_tex_0 : Color texture
// g_tex_1 : Noise texture
// g_float_0 : Elapsed time
float4 PS_Main(VS_OUT _in) : SV_Target
{
    if (g_float_0 > 5.0f)
        discard;
    
    float2 uv = _in.uv;
 
    float3 fireshape = g_tex_1.Sample(g_sam_0, uv).rrr;
    float3 materialColor = float3(1.f, 0.6f, 1.f);
    
    //LightColor totalColor = (LightColor) 0.f;
    //for (int i = 0; i < g_lightCount; ++i)
    //{
    //    LightColor color = CalculateLightColor(i, _in.viewNormal, _in.viewPos);
    //    totalColor.diffuse += color.diffuse;
    //    totalColor.ambient += color.ambient;
    //}

    //materialColor.xyz = (totalColor.diffuse.xyz * materialColor.xyz)
    //    + (totalColor.ambient.xyz * materialColor.xyz);
    
    float time = frac(g_float_0 * -0.2);
    float erosion = smoothstep(time - 0.2, time, fireshape.r);
    float border = smoothstep(0.0, 0.7, erosion) - smoothstep(0.5, 1.0, erosion);

    float3 initialColor = float3(1.0, 0.5, 0.1);
    float3 finalColor = float3(0.5, 0.0, 0.5);
    float3 burningColor = lerp(initialColor, finalColor, smoothstep(0.7, 1.0, border)) * 3.0;
    
    float3 finalColorWithBurn = lerp(materialColor, float3(1.0, 0.5, 1.0), erosion) + border * burningColor * 1.5;

    float alpha = 1;
    if (finalColorWithBurn.r == 1 && finalColorWithBurn.g == 0.5 && finalColorWithBurn.b == 1)
        discard;
    
    finalColor = finalColorWithBurn;
    return float4(finalColor, alpha);
}
#endif