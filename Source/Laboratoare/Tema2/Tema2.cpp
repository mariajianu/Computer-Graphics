#include "Tema2.h"
#include "Laboratoare/Laborator4/Transform3D.h"

#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <Core/Engine.h>

using namespace std;
float lifeStep = 0;
float lifeCrash = false;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("ring");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "ring.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("sea");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cylinder.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("tea");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("sea2");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sea.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	cloudMoveX[0] = -5.5;
	cloudMoveY[0] = 0.2;
	
	cloudMoveX[1] = -4.5;
	cloudMoveY[1] = -0.2;
	
	cloudMoveX[2] = -2;
	cloudMoveY[2] = -0.3;
	
	cloudMoveX[3] = -1;
	cloudMoveY[3] = 0.6;
	
	cloudMoveX[4] = -5.5;
	cloudMoveY[4] = -1.5;
	
	cloudMoveX[5] = -3;
	cloudMoveY[5] = -0.8;
	
	cloudMoveX[6] = 2;
	cloudMoveY[6] = 0.4;
	
	cloudMoveX[7] = 0;
	cloudMoveY[7] = 0;
	//Light & material properties
	{
		lightPosition = glm::vec3(0, 3, 2);
		materialShininess = 10;
		materialKd = .2;
		materialKs = .2;
	}
	combMove[0] = 0;
	combMove[1] = 0.5;
	combMove[2] = -0.5;
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.8, 0.7, 0.6, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::drawClouds() {
	glm::mat4 modelMatrix = glm::mat4(1);
	//norii
	for (int i = 0; i < 8; i++) {
		modelMatrix = glm::mat4(1);
		
		modelMatrix *= Transform3D::Translate(cloudMoveX[i], cloudMoveY[i], 0);
		modelMatrix *= Transform3D::Translate(2, 2, -1);
		modelMatrix *= Transform3D::Translate(-cloudSpeed[i], -0.2 * i, 0);
		if(i % 2 == 0)
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-rot * 5), glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-rot * 5), glm::vec3(0, 1, 0));
	
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 1.5, 1.5));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
		RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(.7, .7, .7));

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(cloudMoveX[i], cloudMoveY[i], 0);
	
		modelMatrix *= Transform3D::Translate(1.75, 1.96, -1);
		modelMatrix *= Transform3D::Translate(-cloudSpeed[i], -0.2 * i, 0);
		if (i % 2 == 1)
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-rot * 5), glm::vec3(0, 0, 1));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(rot * 10), glm::vec3(0, 1, 0));

		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 1.5, 1.5));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.15, 0.15));
		RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(.7, .7, .7));

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(cloudMoveX[i], cloudMoveY[i], 0);

		modelMatrix *= Transform3D::Translate(2.25, 1.96, -1);
		modelMatrix *= Transform3D::Translate(-cloudSpeed[i], -0.2 * i, 0);
		if (i % 2 == 1)
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-rot * 5), glm::vec3(0, 1, 0));
	
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 1.5, 1.5));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.15, 0.15));
		RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(.7, .7, .7));

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(cloudMoveX[i], cloudMoveY[i], 0);
	
		modelMatrix *= Transform3D::Translate(1.56, 1.93, -1);
		modelMatrix *= Transform3D::Translate(-cloudSpeed[i], -0.2 * i, 0);
		if (i % 2 == 0)
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-rot * 5), glm::vec3(0, 0, 1));

		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 1.5, 1.5));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 0.1));
		RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(.7, .7, .7));

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(cloudMoveX[i], cloudMoveY[i], 0);

		modelMatrix *= Transform3D::Translate(2.48, 1.93, -1);
		modelMatrix *= Transform3D::Translate(-cloudSpeed[i], -0.2 * i, 0);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(rot * 10), glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 1.5, 1.5));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 0.1));
		RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(.7, .7, .7));
		if (2.48 + cloudMoveX[i] - cloudSpeed[i] < -5)
			cloudMoveX[i] += 11;
	}
}

void Tema2::Update(float deltaTimeSeconds)
{
	if (restart == true) {
		planeMove = 0;
		planeOY = 0;
		angle = 0;
		countFuel = 35;
		lives = 3;
		crash0[10] = { false };
		crash1[10] = { false };
		crash2[10] = { false };
		crash3[10] = { false };
		stepXc = 0;
		stepYc = 0;
		newComb[4] = { 0 };
		randomStep[4] = { 0 };
		newObs[4] = { 0 };
		restart = false;
		obsCrash[5] = { false };
	}

	glm::mat4 modelMatrix;
	rot += deltaTimeSeconds * 5;
	speed += deltaTimeSeconds;
	for (int i = 0; i < 20; i++)
		cloudSpeed[i] += deltaTimeSeconds;
	
	countTimes++;
	if (countTimes % 80 == 0)
		countFuel--;
	
	planeOY = 1.1 + planeMove;
	if (planeOY < 0 && !seaCrash && lives != 0) {
		lives--;
		seaCrash = true;
	}
	if (planeOY > 0 && seaCrash) {
		seaCrash = false;
	}
	

	if (countFuel == 0 || lives == 0) {
		planeMove -= deltaTimeSeconds * 2;
		angle -= deltaTimeSeconds * 30;
	}
	float step = 2;
	//vietile
	for (int i = 0; i < lives; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Scale(0.1, 0.1, 0.1);
		modelMatrix *= Transform3D::Translate(-30 + i * step, 27, 0);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(80), glm::vec3(0, 1, 0));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(1, 0.2, 0.1));
	}
	float step2 = 0.03;
	//combustibil
	for(int j = 0; j < countFuel; j++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1.68 + (step2 * j), 2.699, 0.01);
		modelMatrix *= Transform3D::Scale(0.05, 0.1, 0.01);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(60), glm::vec3(0, 1, 0));
		RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0.7, 0.8, 0.6));
	}
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(2.2, 2.7, 0);
	modelMatrix *= Transform3D::Scale(0.8, 0.1, 0.01);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(60), glm::vec3(0, 1, 0));
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0, 0, 0));
	
	drawClouds();

	//corpul
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, planeOY, 0);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(0, 0, 1));
	modelMatrix *= Transform3D::Scale(0.2, 0.2, 0.2);
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0.7, 0.3, 0.2));
	
	//capul
	modelMatrix = glm::mat4(1);	
	modelMatrix *= Transform3D::Translate(0, planeOY, 0);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(0, 0, 1));
	modelMatrix *= Transform3D::Scale(0.2, 0.2, 0.2);
	modelMatrix *= Transform3D::Scale(0.3, 1, 1);
	modelMatrix *= Transform3D::Translate(0, -planeOY, 0);
	modelMatrix *= Transform3D::Translate(2.1, planeOY, 0);
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0.9, 0.6, 0.2));

	//coada
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, planeOY, 0);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(0, 0, 1));
	modelMatrix *= Transform3D::RotateOZ(RADIANS(30));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1 * 2, 1, 0.1 * 2));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.23, 0.9));
	modelMatrix *= Transform3D::Translate(0, -planeOY, 0);
	modelMatrix *= Transform3D::Translate(-0.8, planeOY + 0.35, 0.1);
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0.7, 0.3, 0.2));
	
	float planePosX;
	float planePosY;
	//varf pt elice
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, planeOY, 0);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05, 0.05, 0.05));
	modelMatrix *= Transform3D::Translate(0, -planeOY, 0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(3.65, planeOY, 0));
	planePosY = modelMatrix[3][1];
	planePosX = modelMatrix[3][0];
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0, 0, 0));

	//elicea1
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, planeOY, 0);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(0, 0, 1));
	modelMatrix *= Transform3D::RotateOX(rot);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.053, 0.053, 0.053));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1 * 0.3, 5, 1 * 0.3));
	modelMatrix *= Transform3D::Translate(0, -planeOY, 0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(13, planeOY, 0));
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0, 0, 0));
	
	//elicea2
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, planeOY, 0);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(0, 0, 1));
	modelMatrix *= Transform3D::RotateOX(RADIANS(80));
	modelMatrix *= Transform3D::RotateOX(rot);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.053, 0.053, 0.053));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1 * 0.3, 5, 1 * 0.3));
	modelMatrix *= Transform3D::Translate(0, -planeOY, 0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(13, planeOY, 0));
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0, 0, 0));
	
	//aripa fata
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, planeOY, 0.2);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(0, 0, 1));
	modelMatrix *= Transform3D::Scale(0.2, 0.2, 0.2);
	modelMatrix *= Transform3D::Scale(0.6, 0.1, 1);

	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0.8, 0.4, 0));
	
	//aripa spate
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, planeOY, -0.2);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(0, 0, 1));
	modelMatrix *= Transform3D::Scale(0.2, 0.2, 0.2);
	modelMatrix *= Transform3D::Scale(0.6, 0.1, 1);
	RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, 0, glm::vec3(0.8, 0.4, 0));

	float sea = rot * 0.3;
	//marea
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.08, 2.5));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01, 0.01, 0.01));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8 * 2, 1.8, 1));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(5, 1.6, 2));

	modelMatrix = glm::rotate(modelMatrix, RADIANS(rot), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-90), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(-90), glm::vec3(1, 0, 0));
	RenderSimpleMesh(meshes["sea2"], shaders["ShaderTema2"], modelMatrix, 1, glm::vec3(0.3, 0.8, 1));
	
	bool was;
	bool is;


	//extra life
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(10, 2, 0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-speed * 1.8 + lifeStep, 0.2* cos(speed), 0));
	modelMatrix *= Transform3D::Scale(0.08, 0.08, 0.08);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(rot * 20), glm::vec3(1, 0, 0));
	was = lifeCrash;
	if (modelMatrix[3][0] < -5) {
		lifeCrash = false;
		lifeStep = 20;
	}
	if (modelMatrix[3][0] < 0.15 && modelMatrix[3][0] > -0.09) {
		if (modelMatrix[3][1] - planePosY < 0
			&& modelMatrix[3][1] - planePosY >(-0.2)) {
			lifeCrash = true;
		}
		if (planePosY - modelMatrix[3][1] < 0
			&& planePosY - modelMatrix[3][1] > (-0.2)) {
			lifeCrash = true;
			
		}
	}
	is = lifeCrash;
	if (was == false && is == true) {
		if (lives < 3)
			lives++;
	}

	if(!lifeCrash)
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], modelMatrix, 1, glm::vec3(0.9, 1, 0.2));

	//obstacole
	for (int j = 0; j < 2; j++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(5 + randomStep[j], 0.5 + randomStep[j], 0);
		if (j == 0)
			modelMatrix *= Transform3D::Translate(j, 0, 0);
		if (j == 1)
			modelMatrix *= Transform3D::Translate(j + 1.7, -1, 0);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-speed * 3.5 + newObs[j], 0.2* cos(speed), 0));
		modelMatrix *= Transform3D::Scale(0.25, 0.25, 0.25);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(rot * 20), glm::vec3(1, 0, 0));
		was = obsCrash[j];
		if (modelMatrix[3][0] < -5) {
			newObs[j] += 9;
			if (obsCrash[j])
				obsCrash[j] = false;
			randomStep[j] = 0.8 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.8 + 0.1)));
		}
		if (lives > 0 && modelMatrix[3][0] < 0.15 && modelMatrix[3][0] > -0.09) {
			if (modelMatrix[3][1] - planePosY < 0 
				&& modelMatrix[3][1] - planePosY > (-0.2)) {
				obsCrash[j] = true;
				
			}
			if (planePosY - modelMatrix[3][1] < 0
				&& planePosY - modelMatrix[3][1] > (-0.2)) {
				obsCrash[j] = true;
			}
		}
		is = obsCrash[j];
		if (was == false && is == true)
			lives--;
		if(!obsCrash[j])
			RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], modelMatrix, 1, glm::vec3(0.8, 0.1, 0.1));
	}
	for (int j = 0; j < 4; j++) {
		//combustibil
		for (int i = 0; i < nrOfSph[j]; i++) {
			modelMatrix = glm::mat4(1);
			if(j == 0)
				modelMatrix *= Transform3D::Translate(j, 0, 0);
			if (j == 1)
				modelMatrix *= Transform3D::Translate(j + 1, -1, 0);
			if (j == 2)
				modelMatrix *= Transform3D::Translate(-1.5, -1.4, 0);
			if (j == 3)
				modelMatrix *= Transform3D::Translate(4, 0.4, 0);
			modelMatrix *= Transform3D::Translate(4 + newComb[j], 0.7, 0);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-speed * 2, 0, 0));
			// ---
			if (nrOfSph[j] == 2 && i == 0)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 0.95, 0));
			if (nrOfSph[j] == 2 && i == 1)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0.92, 1, 0));
			// -----
			if (nrOfSph[j] == 3 && i == 0)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 0.95, 0));
			if (nrOfSph[j] == 3 && i == 1)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0.92, 1, 0));
			if (nrOfSph[j] == 3 && i == 2)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.08, 0.90, 0));
			// -----
			if (nrOfSph[j] == 4 && i == 0)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 1, 0));
			if (nrOfSph[j] == 4 && i == 1)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.09, 1, 0));
			if (nrOfSph[j] == 4 && i == 2)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.16, 0.95, 0));
			if (nrOfSph[j] == 4 && i == 3)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.22, 0.90, 0));
			// -----
			if (nrOfSph[j] == 5 && i == 0)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 1, 0));
			if (nrOfSph[j] == 5 && i == 1)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.09, 1, 0));
			if (nrOfSph[j] == 5 && i == 2)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.16, 0.95, 0));
			if (nrOfSph[j] == 5 && i == 3)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.22, 0.90, 0));
			if (nrOfSph[j] == 5 && i == 4)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.3, 0.87, 0));
			// --
			if (nrOfSph[j] == 6 && i == 0)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 1, 0));
			if (nrOfSph[j] == 6 && i == 1)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.09, 1, 0));
			if (nrOfSph[j] == 6 && i == 2)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.16, 0.95, 0));
			if (nrOfSph[j] == 6 && i == 3)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.22, 0.90, 0));
			if (nrOfSph[j] == 6 && i == 4)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.3, 0.87, 0));
			if (nrOfSph[j] == 6 && i == 5)
				modelMatrix = glm::translate(modelMatrix, glm::vec3(1.38, 0.87, 0));
			// --
			modelMatrix *= Transform3D::Scale(0.09, 0.09, 0.09);
			modelMatrix = glm::rotate(modelMatrix, RADIANS(rot * 20), glm::vec3(1, 0, 0));
			if (j == 0)
				was = crash0[0];
			if (j == 1)
				was = crash1[0];
			if (j == 2)
				was = crash2[0];
			if (j == 3)
				was = crash3[0];
			if (modelMatrix[3][0] < -5) {
				newComb[j] += 9;
				nrOfSph[j] = (int)3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6 - 3)));
				if (j == 0) {
					for (int k = 0; k < nrOfSph[j]; k++)
						crash0[k] = false;
				}
					
				if (j == 1){
					for (int k = 0; k < nrOfSph[j]; k++)
						crash1[k] = false;
				}
				if (j == 2) {
					for (int k = 0; k < nrOfSph[j]; k++)
						crash2[k] = false;
				}
				if (j == 3) {
					for (int k = 0; k < nrOfSph[j]; k++)
						crash3[k] = false;
				}
			}
			if (modelMatrix[3][0] < 0.15 && modelMatrix[3][0] > -0.09) {
				if (modelMatrix[3][1] - planePosY < 0
					&& modelMatrix[3][1] - planePosY >(-0.2)) {
					if (j == 0) {
						crash0[i] = true;
						if (countFuel < 33)
							countFuel += 2;
					}
					if (j == 1) {
						crash1[i] = true;
						if (countFuel < 33)
							countFuel += 2;
					}
					if (j == 2) {
						crash2[i] = true;
						if (countFuel < 33)
							countFuel += 2;
					}
					if (j == 3) {
						crash3[i] = true;
						if (countFuel < 33)
							countFuel += 2;
					}
				}
				if (planePosY - modelMatrix[3][1] < 0
					&& planePosY - modelMatrix[3][1] > (-0.2)) {
					if (j == 0)
						crash0[i] = true;
					if (j == 1)
						crash1[i] = true;
					if (j == 2)
						crash2[i] = true;
					if (j == 3)
						crash3[i] = true;
				}
			}
			if (j == 0)
				is = crash0[1];
			if (j == 1)
				is = crash1[1];
			if (j == 2)
				is = crash2[1];
			if (j == 3)
				is = crash3[1];
			if(j == 0)
				if (!crash0[i])
					RenderSimpleMesh(meshes["tea"], shaders["ShaderTema2"], modelMatrix, 1, glm::vec3(0, 1, 0.9));
			if (j == 1)
				if (!crash1[i])
					RenderSimpleMesh(meshes["tea"], shaders["ShaderTema2"], modelMatrix, 1, glm::vec3(0, 1, 0.9));
			if (j == 2)
				if (!crash2[i])
					RenderSimpleMesh(meshes["tea"], shaders["ShaderTema2"], modelMatrix, 1, glm::vec3(0, 1, 0.9));
			if (j == 3)
				if (!crash3[i])
					RenderSimpleMesh(meshes["tea"], shaders["ShaderTema2"], modelMatrix, 1, glm::vec3(0, 1, 0.9));
		}
	}
}

	

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, int type, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	GLint loc_light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(loc_light_position, 1, glm::value_ptr(lightPosition));

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	GLint loc = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(loc, materialShininess);

	loc = glGetUniformLocation(shader->program, "material_kd");  // componenta difuza
	glUniform1f(loc, materialKd);

	loc = glGetUniformLocation(shader->program, "material_ks");  // componenta speculara
	glUniform1f(loc, materialKs);

	loc = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(loc, 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");

	int location_clock = glGetUniformLocation(shader->program, "Clock");
	if(type == 1)
		glUniform1f(location_clock, Engine::GetElapsedTime());
	else
		glUniform1f(location_clock, 1);

	int type_loc = glGetUniformLocation(shader->program, "type");
	glUniform1i(type_loc, type);

	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			camera->TranslateRight(deltaTime * cameraSpeed * (-1));
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->TranslateForward(deltaTime * cameraSpeed * (-1));
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			camera->TranslateUpword(deltaTime * cameraSpeed * (-1));
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			camera->TranslateUpword(deltaTime * cameraSpeed);;
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE) {
		restart = true;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (lives > 0 && restart == false)
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;
		planeMove += -sensivityOY * deltaY * 4;
		if (mouseY > 0)
			angle -= deltaY * 0.07;
		if (mouseY < 0)
			angle += deltaY * 0.07;
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
