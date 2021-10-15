cbuffer CBuf
{
	float4 faceColors[6];
}

float4 main(uint tId : SV_PRIMITIVEID) : SV_TARGET
{
	return faceColors[tId / 2];
}