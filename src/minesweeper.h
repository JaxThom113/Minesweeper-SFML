#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Toolbox.h"
#include "GameState.h"
#include "Button.h"

using namespace std;

Toolbox &toolbox = Toolbox::getInstance();
bool debug = false;

void toggleDebugMode();

bool getDebugMode();

void loadTest1();

void loadTest2();

void loadTest3();

void render();

int launch();

void restart();