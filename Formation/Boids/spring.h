#pragma once
#include "Pvector.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

using namespace std;

#ifndef SPRING_H_
#define SPRING_H_



class Spring
{
public:

	Spring();

	void Spring::TimeStep(float i_dt);
	float Spring::A_from_X(float i_x);
	void Spring::SpringConstraints();
	void Spring::DrawState(sf::RenderWindow& w);

	float Stiffness = 5.0;
	float BobMass = 0.5;
	int StateSize = 3;

	float InitState[3];
	float State[3];

	int StateCurrentTime = 0;
	int StatePositionX = 1;
	int StateVelocityX = 2;

	int WindowWidthHeight = 300;
	float WorldSize = 2.0;
	float PixelsPerMeter;
	float OriginPixelsX;
	float OriginPixelsY;


};

#endif