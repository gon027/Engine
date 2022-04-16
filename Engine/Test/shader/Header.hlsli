
// Buffer
cbuffer MatrixBuffer : register(b0) {
	// matrix world : packoffset(c0);
	// matrix view  : packoffset(c4);
	// matrix proj  : packoffset(c8);

	matrix view  : packoffset(c0);
	matrix proj  : packoffset(c4);
}

cbuffer WorldMatrixBuffer : register(b1) {
	matrix world : packoffset(c0);
}

Texture2D<float4> tex0 : register(t0);

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

// Pixel
struct PS_INPUT {
	float4 position : SV_POSITION;
	float4 color    : COLOR;
};

struct PS_INPUT_UV {
	float4 position : SV_POSITION;
	float2 uv    : TEXCOORD;
};

float4 transform(float4 _position) {
	float4 w = mul(world, _position);
	float4 v = mul(view, w);
	float4 p = mul(proj, v);

	return p;
}