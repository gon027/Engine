
// Buffer
cbuffer MatrixBuffer : register(b0) {
	matrix view  : packoffset(c0);
	matrix proj  : packoffset(c4);
}

cbuffer WorldMatrixBuffer : register(b1) {
	matrix world : packoffset(c0);
}

cbuffer Material : register(b2) {
	float4 diffuse;
	float3 specular;
	float specularCoefficient;
	float3 ambient;
}

Texture2D<float4> tex0 : register(t0);
Texture2D<float4> tex1 : register(t1);

SamplerState   samp0 : register(s0);

// Vertex
struct VS_INPUT {
	float4 position : POSITION;
	float4 color    : COLOR;
};

struct VS_INPUT_UV {
	float4 position : POSITION;
	float2 uv    : TEXCOORD;
};

struct VS_INPUT_3D {
	float4 position : POSITION;
	float4 normal   : NORMAL;
	float2 uv       : TEXCOORD;
};

// Pixel
struct PS_INPUT {
	float4 position : SV_POSITION;
	float4 color    : COLOR;
};

struct PS_INPUT_UV {
	float4 position : SV_POSITION;
	float2 uv    : TEXCOORD;
};

struct PS_INPUT_3D {
	float4 position : SV_POSITION;
	float4 normal   : NORMAL;
	float2 uv       : TEXCOORD;
};

float4 transform(float4 _position) {
	float4 w = mul(world, _position);
	float4 v = mul(view, w);
	float4 p = mul(proj, v);

	return p;
}