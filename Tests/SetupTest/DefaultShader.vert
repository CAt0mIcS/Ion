struct VSOut
{
	float4 pos : SV_POSITION;
	float3 color;
}

VSOut main(float3 pos, float3 color)
{
	VSOut out;
	out.pos = float4(pos, 1.0f);
	out.color = color;
	return out;
}
