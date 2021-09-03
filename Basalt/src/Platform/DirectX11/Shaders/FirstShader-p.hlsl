struct VertexOut
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

float4 main(float4 color : COLOR) : SV_TARGET
{
	return color * 0.5 + 0.5;
}