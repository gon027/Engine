#include "Header.hlsli"

float4 main(PS_INPUT_3D _In) : SV_TARGET
{
	// ランバート余弦
	float3 light = normalize(float3(1, -1, 1));
	float  brightness = dot(-light, _In.normal);
	float4 lb = float4(brightness, brightness, brightness, 1);

	float4 textureColor = tex0.Sample(samp0, _In.uv);

	//float4 sphereColor = tex1.Sample(samp0, _In.uv);

	float4 color = diffuse * textureColor;// +sphereColor;
	return color;
	//return _In.normal;
}