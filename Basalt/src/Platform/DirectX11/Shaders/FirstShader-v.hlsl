struct VertexOut
{
	float4 color : Color;
	float4 pos : SV_POSITION;
};

cbuffer CBuf
{
	matrix transform;
};

VertexOut main( float2 pos : Position, float4 color : Color )
{
	VertexOut vsO;
	vsO.pos = mul(float4(pos, 0.0f, 1.0f), transform);
	vsO.color = color;
	return vsO;
}