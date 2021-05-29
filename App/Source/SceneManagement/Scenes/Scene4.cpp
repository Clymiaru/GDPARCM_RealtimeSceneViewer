#include "pch.h"
#include "Scene4.h"

Scene4::Scene4() :
	AScene{ STRINGIFY(Scene4) }
{
}

Scene4::~Scene4()
{
}

void Scene4::RenderUI()
{
}

void Scene4::RenderMeshes()
{
	this->mesh->Draw(m_Camera->GetViewProjectionMatrix());
}

void Scene4::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	this->mesh = Mesh::Load("Content/3D_Models/", "Grenade", *this->shader);
}

void Scene4::UnloadResources()
{
}
