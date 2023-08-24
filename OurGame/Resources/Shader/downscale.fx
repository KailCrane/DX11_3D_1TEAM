#ifndef _DOWNSCALE_FX_
#define _DOWNSCALE_FX_

#include "params.fx"

// Input Texture
Texture2D<float4> InputTexture : register(t0);

// Output Texture
RWTexture2D<float4> DownscaledTexture : register(u1);

[numthreads(1, 1024, 1)] // 8x8 ������ �׷�
void CS_Main(uint3 dispatchThreadId : SV_DispatchThreadID)
{
    // �Է� �ؽ�ó�� ũ��
    uint2 inputSize = g_vec2_0;

    // �ٿ���ϵ� �ؽ�ó�� ũ��
    uint2 outputSize = uint2(400, 225);
    
    if (dispatchThreadId.y < outputSize.y)
    {
    // �ٿ���� ���� ���
        float2 scale = float2(inputSize) / float2(outputSize);

    // �ٿ���ϵ� �ȼ� ��ġ ���
        uint2 outputPixel = uint2(dispatchThreadId.xy * scale);

    // �Է� �ؽ�ó���� �ش� �ȼ��� ���ø��Ͽ� �ٿ���ϵ� �ؽ�ó�� ���
        DownscaledTexture[outputPixel] = InputTexture.Load(int3(outputPixel, 0));
    }
}
#endif