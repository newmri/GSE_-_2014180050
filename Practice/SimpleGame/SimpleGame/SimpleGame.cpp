/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Define.h"
#include "Objects.h"

#pragma comment(lib, "winmm.lib")
Renderer *g_Renderer = NULL;

CSceneMgr g_SceneMgr;

high_resolution_clock::time_point g_lastTime = high_resolution_clock::now();

void RenderScene(void)
{
	high_resolution_clock::time_point  curr = high_resolution_clock::now();
	milliseconds elpsedTime = duration_cast<milliseconds>(curr - g_lastTime);
	g_lastTime = curr;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	g_SceneMgr.Render();
	g_SceneMgr.Update(static_cast<float>(elpsedTime.count()));
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (g_SceneMgr.GetObjects().size() != MAX_NUM_OF_CHARACTER + 1) {
			Pos pos(x, y);
			pos.x = x - 250.0f;
			pos.y = 250.0f - y;
			ObjectInfo info(OBJTYPE::OBJECT_CHARACTER, pos, CHARACTER_SIZE, Color(1.0f, 1.0f, 1.0f, 1.0f));
			g_SceneMgr.AddObject(FACTORYMANAGER->CreateObj(info));
		}
		
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	srand(time(NULL));
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	//g_Renderer = new Renderer(500, 500);
	g_SceneMgr.InitRenderer();




	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

