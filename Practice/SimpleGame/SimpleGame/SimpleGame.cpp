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


high_resolution_clock::time_point g_lastTime = high_resolution_clock::now();

void RenderScene(void)
{
	high_resolution_clock::time_point  curr = high_resolution_clock::now();
	milliseconds elpsedTime = duration_cast<milliseconds>(curr - g_lastTime);
	g_lastTime = curr;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Renderer Test
	SCENEMANAGER->Render();
	SCENEMANAGER->Update(static_cast<float>(elpsedTime.count()));
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (SCENEMANAGER->GetNorthObjects().size() != MAX_NUM_OF_CHARACTER + 1) {
			Pos pos(static_cast<float>(x), static_cast<float>(y));
			pos.x = static_cast<float>(x) - (WINDOW_WIDTH / 2.0f);
			pos.y = (WINDOW_HEIGHT / 2.0f) - static_cast<float>(y);
			if (pos.y > 0.0f || !SCENEMANAGER->CanCreateSouthCharacter()) return;
			ObjectInfo info(SCENEMANAGER->GetID(), OWNER::NONE, SOUTH, OBJTYPE::OBJECT_CHARACTER, pos, CHARACTER_SIZE, Color(0.0f, 0.0f, 1.0f, 1.0f));
			SCENEMANAGER->AddSouthObject(FACTORYMANAGER->CreateObj(info));
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
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	srand(static_cast<unsigned int>(time(NULL)));
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	SCENEMANAGER->InitRenderer();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

    return 0;
}

