#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	Mesh* CreateMesh(const char *name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	glm::vec3 backgroundColor;

protected:
	glm::mat3 modelMatrix;
	glm::mat3 modelMatrix2;
	glm::mat3 modelMatrix3;
	float translateX, translateY;
	float translate_totalX, translate_totalY;
	float scaleX, scaleY;
	float angularStep;
	float rotate = 0;
	float scale = 0;
	int translateY_space = 0;
	int speed = 0;
	int step = 0;
	int step2 = 0;
	float length = 0;
	float lenghts[40];
	float lengths2[40];
	float move_obs = 1000;
	float wing_move = 0;
	int flag = 0;
	float transl_steps[10] = { 0 };
	float transl_steps2[10] = { 0 };
	int score = 0;
	int i = 0;
	int speed_step = 150;
	float obst_jos_pos[6];
	float obst_sus_pos[6];
	bool crash = false;
	int flag_scale[6] = { 0 };
	int flag_scale2[6] = { 0 };
};
