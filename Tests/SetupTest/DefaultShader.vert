#version 450 core

uniform(Frequency::PerObject) ObjectData
{
	matrix model;
} uboObj;

uniform(Frequency::PerScene) SceneData
{
	matrix view;
	matrix proj;
} uboScene;



struct VSOut
{
	float4 pos : SV_POSITION;
	float3 color;
}

VSOut main(float3 pos, float3 color)
{
	VSOut out;
	out.pos = uboScene.view * uboScene.proj * uboObj.model * float4(pos, 1.0f);
	out.color = color;
	return out;
}
