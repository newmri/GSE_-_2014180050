#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <Windows.h>
#include <time.h>
#include "CFactory.h"

using namespace std;

const float SPEED = 1000.0f;

const unsigned int MAX_OBJECTS_COUNT = 50;
const unsigned int WINDOW_WIDTH = 500;
const unsigned int WINDOW_HEIGHT = 500;
const unsigned int COLOR_ROLL_BACK_TIME = 400;

#define FACTORYMANAGER CFactory::GetInstance()