cbuffer CBuf
{
	float4 faceColors;
}

float4 main() : SV_TARGET
{
	return faceColors;
}