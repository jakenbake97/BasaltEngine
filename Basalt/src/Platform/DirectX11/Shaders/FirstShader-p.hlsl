struct VertexOut
{
	float4 pos : SV_POSITION;
	float4 color : Color;
};

float4 main(float4 color : Color) : SV_TARGET
{
	return color;
}