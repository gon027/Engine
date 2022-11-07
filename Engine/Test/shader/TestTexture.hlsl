#include "Header.hlsli"

float4 main(PS_INPUT_UV _In) : SV_TARGET
{
	float4 color = tex0.Sample(samp0, _In.uv);
	return color;
}