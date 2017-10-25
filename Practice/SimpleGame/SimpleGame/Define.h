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

const float SPEED = 80.0f;
const float LIFE = 10.0f;

const unsigned int MAX_OBJECTS_COUNT = 50;
const unsigned int WINDOW_WIDTH = 500;
const unsigned int WINDOW_HEIGHT = 500;
const unsigned int COLOR_ROLL_BACK_TIME = 400;

#define FACTORYMANAGER CFactory::GetInstance()