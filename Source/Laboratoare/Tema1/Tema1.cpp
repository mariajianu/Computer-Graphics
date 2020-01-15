#include "Tema1.h"

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

#include <Core/Engine.h>
#include <Laboratoare/Laborator3/Object2D.h>
#include <Laboratoare/Laborator3/Transform2D.h>

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	srand(static_cast <unsigned> (time(0)));

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	glm::vec3 corner2 = glm::vec3(0, 0, 0);
	float triangSide = 40;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;


	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	translate_totalX = 0;
	translate_totalY = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;
	for (int i = 0; i < 40; i++) {
		if (i % 2 == 0)
			lenghts[i] = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.5 - 1)));
		else
			lenghts[i] = 2.8 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 - 2.8)));
	}

	for (int i = 0; i < 40; i++) {
		if(i % 2 == 0)
			lengths2[i] = 2.8 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 - 2.8)));
		else
			lengths2[i] = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.5 - 1)));
	}
		

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0.9, 0.8, 0.1), true);
	AddMeshToList(square1);

	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide + 50, glm::vec3(0.9, 0.7, 0.1), true);
	AddMeshToList(square2);

	Mesh* tri = Object2D::CreateTriangle("tri", corner2, triangSide, glm::vec3(0.9, 0, 0), true);
	AddMeshToList(tri);

	Mesh* tri2 = Object2D::CreateTriangle("tri2", corner2, triangSide, glm::vec3(1, 0.5, 0), true);
	AddMeshToList(tri2);

	Mesh* square3 = Object2D::CreateSquare2("square3", corner, squareSide, glm::vec3(0.2, 0.5, 0), true);
	AddMeshToList(square3);

	Mesh* square4 = Object2D::CreateSquareRight("square4", corner, squareSide, glm::vec3(0.2, 0.5, 0), true);
	AddMeshToList(square4);

	transl_steps[6] = { 0 };
	for (int i = 1; i < 6; i++)
		transl_steps[i] = transl_steps[i - 1] + 300;
	transl_steps2[6] = { 0 };
	for (int i = 1; i < 6; i++)
		transl_steps2[i] = transl_steps2[i - 1] + 300;
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	float r = (float)64 / (float)255;
	float g = (float)224 / (float)255;
	float b = (float)208 / (float)255;
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(r,g,b,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{	
	score += 1;
	if (!crash)
		cout << "Score: " << score << "\n";
	else {
		cout << "GAME OVER" << endl;
		cout << "Final score: " << score << "\n";
		Exit();
	}

	if (score % 500 == 0) {
		speed_step *= 1.2;
	}
		
	move_obs -= deltaTimeSeconds * speed_step;
	step = 0;

	glm::ivec2 resolution = window->GetResolution();
	
	//pentru obstacolele de jos
	modelMatrix3 = glm::mat3(1);
	int j = 0;
	int count = 6;
	i = 0;
	while (count != 0) {
		if (j % 2 == 0 && score >= 500) {
			if (flag_scale[j] == 0) {
				lenghts[j] += deltaTimeSeconds;
			}
			else {
				lenghts[j] -= deltaTimeSeconds;
			}
			if (lenghts[j] > 2.5) {
				flag_scale[j] = 1;
			}
			if(lenghts[j] < 1) {
				flag_scale[j] = 0;
			}
		}
		modelMatrix3 *= Transform2D::Scale(1, lenghts[j]);

		modelMatrix3 *= Transform2D::Translate(transl_steps[j], 0);

		modelMatrix3 *= Transform2D::Translate(move_obs, 0);
		
		obst_jos_pos[j] = transl_steps[j] + move_obs;
		
		if (transl_steps[j] + move_obs <= -100) {
			transl_steps[j] += resolution.x + 480;
			if (j % 2 == 0)
				lenghts[j] = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.5 - 1)));
			else {
				lenghts[j] = 2.8 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 - 2.8)));
			}
				
		}
		
		RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix3);
	
		
		i++;
		j++;

		modelMatrix3 = glm::mat3(1);
		count--;
	}
	step2 = 0;
	
	//pentru obstacolele de sus
	modelMatrix2 = glm::mat3(1);
	
	i = 0;
	j = 0;
	count = 6;
	while (count != 0) {
		if (j % 2 == 0 && score >= 500) {
			if (flag_scale2[j] == 0) {
				lengths2[j] += deltaTimeSeconds;
			}
			else {
				lengths2[j] -= deltaTimeSeconds;
			}
			if (lengths2[j] > 2.5) {
				flag_scale2[j] = 1;
			}
			if (lengths2[j] < 1) {
				flag_scale2[j] = 0;
			}
		}
		modelMatrix2 *= Transform2D::Translate(0, resolution.y);

		modelMatrix2 *= Transform2D::Scale(1, lengths2[j]);
		modelMatrix2 *= Transform2D::Translate(transl_steps2[j], 0);

		modelMatrix2 *= Transform2D::Translate(move_obs, 0);

		obst_sus_pos[j] = transl_steps2[j] + move_obs;

		if (transl_steps2[j] + move_obs <= -100) {
			transl_steps2[j] += resolution.x + 480;
			if (j % 2 == 0)
				lengths2[j] = 2.8 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 - 2.8)));
			else
				lengths2[j] = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.5 - 1)));
		}

		RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix2);
		
		i++;
		if (i == 39)
			i = 0;
		j++;
		modelMatrix2 = glm::mat3(1);
		count--;
	}
	step2 = 0;
	
	//desenarea pasarii
	if (rotate > -0.8)
		rotate += deltaTimeSeconds * -0.09f;
	
	if(flag == 0)
		wing_move += deltaTimeSeconds * 3;
	else 
		wing_move -= deltaTimeSeconds * 3;

	if (wing_move > .785 * 2)
		flag = 1;
	if (wing_move < 0)
		flag = 0;
	

	modelMatrix = glm::mat3(1);

	scaleX = .3;
	scaleY = .3;

	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	
	translateX = 1000;
	translateY = 1500 + translateY_space + speed;
		

	modelMatrix *= Transform2D::Translate(translateX, translateY);
	
	
	modelMatrix *= Transform2D::Rotate(rotate);
	
	// ------------
	modelMatrix *= Transform2D::Scale(2.5, 2.5);
	modelMatrix *= Transform2D::Translate(170, 330);
	modelMatrix *= Transform2D::Rotate(.785);
	modelMatrix *= Transform2D::Rotate(wing_move);
	// -----------

	//aripa exterior
	if(!crash)
		RenderMesh2D(meshes["tri2"], shaders["VertexColor"], modelMatrix);
	
	// -----------
	modelMatrix *= Transform2D::Rotate(-.785);
	modelMatrix *= Transform2D::Rotate(- wing_move);
	modelMatrix *= Transform2D::Scale(0.4, 0.4);
	modelMatrix *= Transform2D::Translate(-170, -330);
	// -----------

	modelMatrix *= Transform2D::Translate(250, 270);

	//cap
	if (!crash)
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	for (int k = 0; k < 6; k++) {
		if (modelMatrix[2][0] + 30 >= obst_sus_pos[k] &&
			modelMatrix[2][0] <= obst_sus_pos[k] + 100) {
			//e in dreptul stalpului de sus
			if (modelMatrix[2][1] + 30 >= (720 - 100 * lengths2[k]))
				crash = true;
		}
		if (modelMatrix[2][0] + 30 >= obst_sus_pos[k] &&
			modelMatrix[2][0] <= obst_sus_pos[k] + 100) {
			//e in dreptul stalpului de jos
			if (modelMatrix[2][1] + 30 <= 100 * lenghts[k])
				crash = true;
		}

	}
	
	modelMatrix *= Transform2D::Translate(100, 20);

	float rotate2 = 0.785;
	modelMatrix *= Transform2D::Rotate(rotate2);

	//cioc
	if (!crash)
		RenderMesh2D(meshes["tri"], shaders["VertexColor"], modelMatrix);
	
	rotate2 = - 0.785;
	modelMatrix *= Transform2D::Rotate(rotate2);
	modelMatrix *= Transform2D::Translate(-250, -40);
	
	//corp
	if (!crash)
		RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
	
	if (modelMatrix[2][1] < 0 || modelMatrix[2][1] > resolution.y - 45)
		crash = true;

	for (int k = 0; k < 6; k++) {
		if (modelMatrix[2][0] + 45 >= obst_jos_pos[k] &&
			modelMatrix[2][0] < obst_jos_pos[k] + 100) {
			//e in dreptul stalpului de jos
			if (modelMatrix[2][1] <= 100 * lenghts[k])
				crash = true;
			//e in dreptul stalpului de sus
			if (modelMatrix[2][1] + 30 >= (720 - 100 * lengths2[k]))
				crash = true;
		}
			
	}
	
	modelMatrix *= Transform2D::Translate(100, 100);
	modelMatrix *= Transform2D::Rotate(.785);
	modelMatrix *= Transform2D::Rotate(wing_move);
	modelMatrix *= Transform2D::Scale(2.5, 2.5);

	//aripa interior
	if (!crash)
		RenderMesh2D(meshes["tri2"], shaders["VertexColor"], modelMatrix);
	
	for (int i = 0; i < 6; i++) {
		obst_jos_pos[i] = 0;
		obst_sus_pos[i] = 0;
	}
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_SPACE)) {
		if (rotate < 0)
			rotate += .6f * deltaTime;
		translateY_space +=  2200 * deltaTime;
	}
	else
		speed -= 1200 * deltaTime ;

}

