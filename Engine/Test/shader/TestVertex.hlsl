#include <Header.hlsli>

PS_INPUT main(VS_INPUT _In)
{
	PS_INPUT o = (PS_INPUT)0;

	float4 w = mul(world, _In.position);
	float4 v = mul(view, w);
	float4 p = mul(proj, v);
	
	// float4 w = mul(_In.position, world);
	// float4 v = mul(w, view);
	// float4 p = mul(v, proj);
	
	//o.position = _In.position;
	o.position = p;
	o.color = _In.color;

	return o;
}