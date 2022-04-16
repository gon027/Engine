#include "Header.hlsli"

float4 main(PS_INPUT _In) : SV_TARGET
{
	return _In.color;
}