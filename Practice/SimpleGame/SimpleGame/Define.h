#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <chrono>
#include "CFactory.h"

using namespace std;
using namespace chrono;

static const float CHARACTER_LIFE = 10.0f;
static const float CHARACTER_SPEED = 300.0f;
static const float CHARACTER_SIZE = 10.0f;

static const float BUILDING_LIFE = 500.0f;
static const float BUILDING_SPEED = 0.0f;
static const float BUILDING_SIZE = 100.0f;

static const float BULLET_LIFE = 20.0f;
static const float BULLET_SPEED = 600.0f;
static const float BULLET_SIZE = 2.0f;

static const float ARROW_LIFE = 10.0f;
static const float ARROW_SPEED = 100.0f;
static const float ARROW_SIZE = 2.0f;

static const float LIFE_TIME = 1000.0f;
static const float RGB = 255.0f;

static const unsigned int MAX_OBJECTS_COUNT = 50;
static const unsigned int MAX_NUM_OF_CHARACTER = 10;
static const unsigned int WINDOW_WIDTH = 500;
static const unsigned int WINDOW_HEIGHT = 700;
static const unsigned int COLOR_ROLL_BACK_TIME = 400;
static const unsigned int BULLET_SPAWN_TIME = 1000; // This will be 1 sec
static const unsigned int ARROW_SPAWN_TIME = 1000; // This will be 1 sec

static const float BUILDING_LEFT_XPOS = (WINDOW_WIDTH / 4.0f);
static const float NORTH_BUILDING_YPOS = (WINDOW_HEIGHT / 3.0f);

#define FACTORYMANAGER CFactory::GetInstance()
#define SCENEMANAGER CSceneMgr::GetInstance()
#define IMAGEMANAGER CImageMgr::GetInstance()