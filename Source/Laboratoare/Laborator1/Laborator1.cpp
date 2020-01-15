#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{	
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	backgroundColor = glm::vec3(0.0f);
	playerPos = glm::vec3(-1, 0, 0.6f);
	
	{
		Mesh* mesh = new Mesh("batman");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Characters/Batman", "batman70.fbx");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("archer");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Characters/Archer", "Archer.fbx");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("bamboo");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Vegetation/Bamboo", "bamboo.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

}

void Laborator1::FrameStart()
{
	if (window->KeyHold(GLFW_KEY_P)) {
		backgroundColor.r = (float)(rand() % 100) * 0.01f;
		backgroundColor.b = (float)(rand() % 100) * 0.01f;
		backgroundColor.g = (float)(rand() % 100) * 0.01f;
	}
}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	string names[3] = { "bamboo", "batman", "archer" };
	
	RenderMesh(meshes["bamboo"], glm::vec3(1, 0.02f, 0), glm::vec3(0.08f));

	// render the object again but with different properties
	RenderMesh(meshes["batman"], playerPos, glm::vec3(1));

	RenderMesh(meshes["archer"], glm::vec3(0.2f, -0.03, 0.3f), glm::vec3(0.01f));

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (window->KeyHold(GLFW_KEY_W)) {
		playerPos -= glm::vec3(0, 0, 1) * .5f * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_S)) {
		playerPos += glm::vec3(0, 0, 1) * .5f * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_A)) {
		playerPos -= glm::vec3(1, 0, 0) * .5f * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_D)) {
		playerPos += glm::vec3(1, 0, 0) * .5f * deltaTime;
	}
	
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		backgroundColor.r = (float)(rand() % 100) * 0.01f;
		backgroundColor.b = (float)(rand() % 100) * 0.01f;
		backgroundColor.g = (float)(rand() % 100) * 0.01f;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
