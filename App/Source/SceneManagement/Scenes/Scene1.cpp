#include "pch.h"
#include "Scene1.h"

Scene1::Scene1() :
	AScene{ STRINGIFY(Scene1) }
{
}

Scene1::~Scene1()
{
}

void Scene1::RenderUI()
{
}

void Scene1::RenderMeshes()
{
	this->mesh->Draw(m_Camera->GetViewProjectionMatrix());
}

void Scene1::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	this->mesh = Mesh::Load("Content/3D_Models/", "A2", *this->shader);
}

void Scene1::UnloadResources()
{
}
