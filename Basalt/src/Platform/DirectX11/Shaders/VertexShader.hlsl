struct VertexOut
{
	float4 color : COLOR;
	float4 pos : SV_POSITION;
};

cbuffer CBuf
{
	row_major matrix transform;
};

VertexOut main( float2 pos : POSITION, float4 color : COLOR )
{
	VertexOut vsO;
	vsO.pos = mul(float4(pos, 0.0f, 1.0f), transform);
	vsO.color = color;
	return vsO;
}