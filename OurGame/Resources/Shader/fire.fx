#ifndef _FIRE_FX_
#define _FIRE_FX_

#include "params.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
};

struct GS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD0;
    float2 uv1 : TEXCOORD1;
    float2 uv2 : TEXCOORD2;
    float2 uv3 : TEXCOORD3;
    uint primID : SV_PrimitiveID;
};

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    // Noise Variables
    output.pos = float4(_in.pos, 1.f);

    return output;
}

[maxvertexcount(4)]
void GS_Main(point VS_OUT _in[1], uint primID : SV_PrimitiveID,
                              inout TriangleStream<GS_OUT> outputStream)
{
    GS_OUT output = (GS_OUT) 0;
   
    float3 eyeWorld = g_vec4_0.xyz;
    float width = g_float_0;
    
    float4 up = float4(0.0, 1.0, 0.0, 0.0);
    float4 front = float4(eyeWorld, 0.0) - _in[0].pos;
    front = normalize(front);
    float4 right = float4(cross(up.xyz, front.xyz), 0.0);
    
    float hw = 0.5 * width;
    
    output.pos = _in[0].pos - hw * right - hw * up;
    output.pos = mul(output.pos, g_matWVP);
    output.uv = float2(0.f, 1.f);
    output.primID = primID;
    output.uv1 = output.uv * g_scales.x;
    output.uv1.y = output.uv1.y + g_frameTime * g_scrollSpeeds.x;
    output.uv2 = output.uv * g_scales.y;
    output.uv2.y = output.uv2.y + g_frameTime * g_scrollSpeeds.y;
    output.uv3 = output.uv * g_scales.z;
    output.uv3.y = output.uv3.y + g_frameTime * g_scrollSpeeds.z;
    
    outputStream.Append(output);
    
    output.pos = _in[0].pos - hw * right + hw * up;
    output.pos = mul(output.pos, g_matWVP);
    output.uv = float2(0.f, 0.f);
    output.primID = primID;
    output.uv1 = output.uv * g_scales.x;
    output.uv1.y = output.uv1.y + g_frameTime * g_scrollSpeeds.x;
    output.uv2 = output.uv * g_scales.y;
    output.uv2.y = output.uv2.y + g_frameTime * g_scrollSpeeds.y;
    output.uv3 = output.uv * g_scales.z;
    output.uv3.y = output.uv3.y + g_frameTime * g_scrollSpeeds.z;
    
    outputStream.Append(output);
    
    output.pos = _in[0].pos + hw * right - hw * up;
    output.pos = mul(output.pos, g_matWVP);
    output.uv = float2(1.f, 1.f);
    output.primID = primID;
    output.uv1 = output.uv * g_scales.x;
    output.uv1.y = output.uv1.y + g_frameTime * g_scrollSpeeds.x;
    output.uv2 = output.uv * g_scales.y;
    output.uv2.y = output.uv2.y + g_frameTime * g_scrollSpeeds.y;
    output.uv3 = output.uv * g_scales.z;
    output.uv3.y = output.uv3.y + g_frameTime * g_scrollSpeeds.z;
    
    outputStream.Append(output);
    
    output.pos = _in[0].pos + hw * right + hw * up;
    output.pos = mul(output.pos, g_matWVP);
    output.uv = float2(1.f, 0.f);
    output.primID = primID;
    output.uv1 = output.uv * g_scales.x;
    output.uv1.y = output.uv1.y + g_frameTime * g_scrollSpeeds.x;
    output.uv2 = output.uv * g_scales.y;
    output.uv2.y = output.uv2.y + g_frameTime * g_scrollSpeeds.y;
    output.uv3 = output.uv * g_scales.z;
    output.uv3.y = output.uv3.y + g_frameTime * g_scrollSpeeds.z;
    
    outputStream.Append(output);
}



float4 PS_Main(GS_OUT _in) : SV_Target
{
    float4 noise1 = g_tex_1.Sample(g_sam_0, _in.uv1);
    float4 noise2 = g_tex_1.Sample(g_sam_0, _in.uv2);
    float4 noise3 = g_tex_1.Sample(g_sam_0, _in.uv3);

	// (0, 1) �������� (-1, +1) ������ ����� �̵��մϴ�.
    noise1 = (noise1 - 0.5f) * 2.0f;
    noise2 = (noise2 - 0.5f) * 2.0f;
    noise3 = (noise3 - 0.5f) * 2.0f;

	// 3 ���� ���� �ٸ� �ְ� x�� y ������ �� ���� ������ x�� y ��ǥ�� �ְ��մϴ�.
    noise1.xy = noise1.xy * g_distortion1.xy;
    noise2.xy = noise2.xy * g_distortion2.xy;
    noise3.xy = noise3.xy * g_distortion3.xy;

	// �� ���� �ְ� �� ������ ����� ��� �ϳ��� ������ ����� �����մϴ�.
    float4 finalNoise = noise1 + noise2 + noise3;

	// �ְ� ������ �� ���̾ ���� ���� �Է� �ؽ�ó Y ��ǥ�� �ְ��մϴ�.
	// ���� ȿ������ �Ҳ��� ���� �Ÿ��� �ؽ�ó�� ���� �����̸� ������ �������ϴ�.
    float perturb = ((1.0f - _in.uv.y) * g_distortionScale) + g_distortionBias;

	// ���� ȭ�� ���� �ؽ�ó�� ���ø��ϴ� �� ����� �����ǰ� �ְ� �� �ؽ�ó ���ø� ��ǥ�� ����ϴ�.
    float2 noiseCoords = (finalNoise.xy * perturb) + _in.uv.xy;

	// �����ǰ� �ְ� �� �ؽ�ó ���ø� ��ǥ�� ����Ͽ� ȭ�� �ؽ�ó���� ������ ���ø��մϴ�.
	// ȭ���� ���¸� ���δ� ��� Ŭ���� ���� ���¸� ����Ͽ� ȭ���� ���δ� ���� �����մϴ�.
    float4 fireColor = g_tex_0.Sample(g_sam_1, noiseCoords.xy);

	// �����ǰ� �ְ� �� �ؽ�ó ���ø� ��ǥ�� ����Ͽ� ���� �ؽ�ó���� ���� ���� ���ø��մϴ�.
	// �̰��� ���� ������ ���˴ϴ�.
	// ȭ���� ���¸� ���δ� ��� Ŭ���� ���� ���¸� ����Ͽ� ȭ���� ���δ� ���� �����մϴ�.
    float4 alphaColor = g_tex_2.Sample(g_sam_1, noiseCoords.xy);

    
    if (fireColor.r < 0.9f)
        discard;
    
	// ȭ���� ���� ������ �Ҿ����ϰ� �ְ� �� ���� �ؽ�ó ������ �����մϴ�.
    fireColor.a = alphaColor.r;
   
    return fireColor;
}



#endif