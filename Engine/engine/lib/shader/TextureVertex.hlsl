#include "Header.hlsli"

PS_INPUT_UV main(VS_INPUT_UV _In)
{
	PS_INPUT_UV o = (PS_INPUT_UV)0;

	float4 w = mul(world, _In.position);
	float4 v = mul(view, w);
	float4 p = mul(proj, v);

	// p.z = 1.0f;
	
	o.position = p;
	o.uv = _In.uv;

	return o;
}