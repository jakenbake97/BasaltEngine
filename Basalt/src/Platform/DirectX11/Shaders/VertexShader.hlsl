struct VertexOut
{
	float4 color : COLOR;
	float4 pos : SV_POSITION;
};

VertexOut main( float2 pos : POSITION, float4 color : COLOR )
{
	VertexOut vsO;
	vsO.pos = float4(pos, 0.0f, 1.0f);
	vsO.color = color;
	return vsO;
}