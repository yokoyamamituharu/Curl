#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float WhiteNoise(float2 coord)
{
    return frac(sin(dot(coord, float2(18.12, 12.72))) * 827.02);
}

float4 main(VSOutput input) : SV_TARGET
{
    float2 uvPoint = input.uv;
    float4 texcolor = tex0.Sample(smp, input.uv);
    float uvTimer = time;
    float vignetteTimer = time;
    float noise = WhiteNoise(input.uv * time) - 0.5f;
    float vignette = length(float2(0.5, 0.5) - input.uv);
    if (uvTimer % 2 == 1)
    {
        uvTimer *= -1;
    }
  
    if (vignetteTimer < 30.0f)
    {
        uvPoint.x += 0.01 * uvTimer * 0.01;
        texcolor.r = tex0.Sample(smp, uvPoint).r;
        
        vignette = clamp(vignette - (0.001 + (vignetteTimer * 0.02)), 0, 1);
        texcolor.r += vignette;
        texcolor.gb -= vignette * 0.5;
    }
    else
    {
        texcolor = tex0.Sample(smp, uvPoint);
        vignette = clamp(vignette - (1.0 - (vignetteTimer * 0.015)), 0, 1);
        texcolor.rgb -= vignette;
    }
        
    float sinv = sin(input.uv.y * 16 + time * -0.5);
    float steped = step(0.99, sinv * sinv);
    texcolor.rgb -= (1 - steped) * abs(sin(input.uv.y * 50.0 + time * 1.0)) * 0.001;
    texcolor.rgb -= (1 - steped) * abs(sin(input.uv.y * 100.0 - time * 2.0)) * 0.002;
    texcolor.rgb += steped * 0.01;
    
    return float4(texcolor.rgb, 1);
}