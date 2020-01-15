#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

#include "Laboratoare/Laborator5/LabCamera.h"

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, int type, const glm::vec3 &color = glm::vec3(1));
	Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void drawClouds();

	glm::vec3 lightPosition;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;
	Laborator::Camera *camera;
	glm::mat4 sceneMatrix = glm::mat4(1);
	glm::vec3 rockPos;
	float radius = 1.7;
	int nrOfSph[4] = { 5, 6, 3, 4 };
	float cloudSpeed[20] = { 0 };
	float cloudMoveX[20] = { 0 };
	float cloudMoveY[20] = { 0 };
	float combMove[20] = { 0 };
	bool crash0[40] = { false };
	bool crash1[40] = { false };
	bool crash2[40] = { false };
	bool crash3[40] = { false };
	float stepXc = 0;
	float stepYc = 0;
	float newComb[4] = { 0 };
	float randomStep[4] = { 0 };
	float newObs[4] = { 0 };
	bool restart = false;
	bool seaCrash = false;
	bool obsCrash[10] = { false };
	float planeMove = 0;
	float scaleFactor = 1;
	float speed = 0;
	float rot = 0;
	int lives = 3;
	int countFuel = 35;
	float planeOY = 0;
	float angle = 0;
	int countTimes;
	float obsX = 0;
	float obsY = 0;
	
};
