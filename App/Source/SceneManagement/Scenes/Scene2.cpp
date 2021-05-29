#include "pch.h"
#include "Scene2.h"

Scene2::Scene2() :
	AScene{ STRINGIFY(Scene2) }
{
}

Scene2::~Scene2()
{
}

void Scene2::RenderUI()
{
}

void Scene2::RenderMeshes()
{
	this->mesh->Draw(m_Camera->GetViewProjectionMatrix());
}

void Scene2::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	this->mesh = Mesh::Load("Content/3D_Models/", "bunny", *this->shader);
}

void Scene2::UnloadResources()
{
}
