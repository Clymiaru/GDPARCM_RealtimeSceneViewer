#include "pch.h"
#include "Scene3.h"

Scene3::Scene3() :
	AScene{ STRINGIFY(Scene3) }
{
}

Scene3::~Scene3()
{
}

void Scene3::RenderUI()
{
}

void Scene3::RenderMeshes()
{
	this->mesh->Draw(m_Camera->GetViewProjectionMatrix());
}

void Scene3::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	this->mesh = Mesh::Load("Content/3D_Models/", "Chair", *this->shader);
}

void Scene3::UnloadResources()
{
}