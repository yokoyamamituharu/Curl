#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    float4 texColor = tex.Sample(smp, input.uv);
    const float shininess = 4.0f;
    float3 eyeDir = normalize(cameraPos - input.worldpos.xyz);
    float3 ambient = m_ambient;
    float4 shadeColor = float4(ambientColor * ambient, m_alpha);
    
    if (DirLightNum != 0)
    {
        for (int i = 0; i < DirLightNum; i++)
        {
            if (dirLights[i].isActive)
            {
                float3 dotLightNormal = dot(dirLights[i].lightVec, input.normal);
                float3 reflect = normalize(-dirLights[i].lightVec + 2 * dotLightNormal * input.normal);
                float3 diffuse = dotLightNormal * m_diffuse;
                float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * m_specular;
            
                shadeColor.rgb += (diffuse + specular) * dirLights[i].lightColor;
            }
        }
    }
    
    if (PointLightNum != 0)
    {
        for (int i = 0; i < PointLightNum; i++)
        {
            if (pointLights[i].isActive)
            {
                float3 lightVec = pointLights[i].lightPos - input.worldpos.xyz;
                float d = length(lightVec);
                lightVec = normalize(lightVec);
            
                float atten = 1.0f / (pointLights[i].lightAtten.x + pointLights[i].lightAtten.y * d + pointLights[i].lightAtten.z * d * d);
                float3 dotLightNormal = dot(lightVec, input.normal);
                float3 reflect = normalize(-lightVec + 2 * dotLightNormal * input.normal);
                float3 diffuse = dotLightNormal * m_diffuse;
                float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * m_specular;
            
                shadeColor.rgb += atten * (diffuse + specular) * pointLights[i].lightColor;
            }
        }
    }
    
    if (SpotLightNum != 0)
    {
        for (int i = 0; i < SpotLightNum; i++)
        {
            if (spotLights[i].isActive)
            {
                float3 lightVec = spotLights[i].lightPos - input.worldpos.xyz;
                float d = length(lightVec);
                lightVec = normalize(lightVec);
            
                float atten = saturate(1.0f / (spotLights[i].lightAtten.x + spotLights[i].lightAtten.y * d + spotLights[i].lightAtten.z * d * d));
                float cos = dot(lightVec, spotLights[i].lightVec);
                float angleAtten = smoothstep(spotLights[i].lightAngle.y, spotLights[i].lightAngle.x, cos);
                atten *= angleAtten;
            
                float3 dotLightNormal = dot(lightVec, input.normal);
                float3 reflect = normalize(-lightVec + 2 * dotLightNormal * input.normal);
                float3 diffuse = dotLightNormal * m_diffuse;
                float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * m_specular;
                shadeColor.rgb += atten * (diffuse + specular) * spotLights[i].lightColor;
            }
        }
    }
    
    if (CircleShadowNum != 0)
    {
        for (int i = 0; i < CircleShadowNum; i++)
        {
            if (circleShadows[i].isActive)
            {
                float3 casterVec = circleShadows[i].casterPos - input.worldpos.xyz;
                float d = dot(casterVec, circleShadows[i].dir);
                float atten = saturate(1.0f / (circleShadows[i].atten.x + circleShadows[i].atten.y * d + circleShadows[i].atten.z * d * d));
                atten *= step(0, d);
                float3 lightPos = circleShadows[i].casterPos + circleShadows[i].dir * circleShadows[i].distanceCasterLight;
                float3 lightVec = normalize(lightPos - input.worldpos.xyz);
                float cos = dot(lightVec, circleShadows[i].dir);
                float angleAtten = smoothstep(circleShadows[i].factorAngle.y, circleShadows[i].factorAngle.x, cos);
                atten *= angleAtten;
            
                shadeColor.rgb -= atten;
            }
        }
    }
    
    if (ShadowMapNum != 0)
    {
        for (int i = 0; i < ShadowMapNum; i++)
        {
            if (shadowMaps[i].isActive)
            {
                float zValue = input.svpos.z / input.svpos.w;
                float2 transTexCoord;
                transTexCoord.x = (1.0f + input.svpos.x / input.svpos.w) * 0.5f;
                transTexCoord.y = (1.0f + input.svpos.y / input.svpos.w) * 0.5f;

                float sm_z = tex.Sample(smp, transTexCoord);
                shadeColor.rgb = float4(0.0, 0.6, 1.0, 1.0) * (0.3 + dot(normalize(input.worldpos).xyz, -shadowMaps[i].dir) * (1 - 0.3f));
                texColor = shadeColor;
                if (zValue > sm_z + 0.005f)
                {
                    shadeColor.rgb = shadeColor.rgb * 0.5f;
                }
            }
        }

    }
    
    return shadeColor * texColor * color;
}