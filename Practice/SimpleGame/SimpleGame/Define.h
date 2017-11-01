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

static const float SPEED = 80.0f;
static const float BULLET_SPEED = 300.0f;
static const float LIFE = 500.0f;
static const float CHARACTER_LIFE = 1.0f;
static const float BULLET_LIFE = 20.0f;
static const float LIFE_TIME = 10.0f;
static const float RGB = 255.0f;

static const unsigned int MAX_OBJECTS_COUNT = 50;
static const unsigned int MAX_NUM_OF_CHARACTER = 10;
static const unsigned int WINDOW_WIDTH = 500;
static const unsigned int WINDOW_HEIGHT = 500;
static const unsigned int COLOR_ROLL_BACK_TIME = 400;

#define FACTORYMANAGER CFactory::GetInstance()