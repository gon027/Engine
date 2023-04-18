#include <Header.hlsli>

PS_INPUT_3D main(VS_INPUT_3D _In)
{
	PS_INPUT_3D o = (PS_INPUT_3D)0;

	float4 w = mul(world, _In.position);
	float4 v = mul(view, w);
	float4 p = mul(proj, v);

	o.position = p;
	o.normal = _In.normal;
	o.uv = _In.uv;

	return o;
}