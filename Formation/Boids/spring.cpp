#include "spring.h"

Spring::Spring()
{
	// Create initial state.
	InitState[StateCurrentTime] = 0.0;
	InitState[StatePositionX] = 0.65;
	InitState[StateVelocityX] = 0.0;

	// Copy initial state to current state.
	// notice that this does not need to know what the meaning of the
	// state elements is, and would work regardless of the state's size.


	PixelsPerMeter = ((float)WindowWidthHeight) / WorldSize;
	OriginPixelsX = 0.5 * (float)WindowWidthHeight;
	OriginPixelsY = 0.5 * (float)WindowWidthHeight;



	for (int i = 0; i < StateSize; i++)
	{
		State[i] = InitState[i];
	}
}


void Spring::DrawState(sf::RenderWindow& w)
{
	// Compute end of arm.
	float SpringEndX = State[StatePositionX];

	//// Compute the CORRECT position.
	float sqrtKoverM = sqrt(Stiffness / BobMass);
	float x0 = InitState[StatePositionX];
	float v0 = InitState[StateVelocityX];
	float t = State[StateCurrentTime];
	float CorrectPositionX = (x0 * cos(sqrtKoverM * t)) +
		((v0 / sqrtKoverM) * sin(sqrtKoverM + t));

	// Compute draw pos for "correct"
	float CorrectEndX = PixelsPerMeter * CorrectPositionX;


	sf::VertexArray lines(sf::LinesStrip, 4);


	lines[0].color = sf::Color::Red;
	lines[1].color = sf::Color::Blue;
	lines[2].color = sf::Color::Green;
	lines[3].color = sf::Color::Red;


	lines[0].position = sf::Vector2f(10, 10);
	lines[1].position = sf::Vector2f(200, 15);
	lines[2].position = sf::Vector2f(300, 250);
	lines[3].position = sf::Vector2f(SpringEndX, 350);

	w.draw(lines);


	// Draw the spring.
	//w.draw(sf::Drawable )
	//line(0.0, 0.0, SpringEndX, 0.0);

	//// Draw the spring pivot
	//fill(0.0);
	//ellipse(0.0, 0.0,
	//	PixelsPerMeter * 0.03,
	//	PixelsPerMeter * 0.03);

	//// Draw the spring bob
	//fill(1.0, 0.0, 0.0);
	//ellipse(SpringEndX, 0.0,
	//	PixelsPerMeter * 0.1,
	//	PixelsPerMeter * 0.1);

	//// Draw the correct bob in blue
	//fill(0.0, 0.0, 1.0);
	//ellipse(CorrectEndX, -PixelsPerMeter * 0.25,
	//	PixelsPerMeter * 0.1,
	//	PixelsPerMeter * 0.1);

}

// Acceleration from Position.
float Spring::A_from_X(float i_x)
{
	return -(Stiffness / BobMass) * i_x;
}

// Time Step function.
void Spring::TimeStep(float i_dt)
{
	float vStar1 = State[StateVelocityX];
	float aStar1 = A_from_X(State[StatePositionX]);

	float vStar2 = State[StateVelocityX] + (i_dt * aStar1);
	float xTmp = State[StatePositionX] + (i_dt * vStar1);
	float aStar2 = A_from_X(xTmp);

	State[StatePositionX] += (i_dt / 2.0) * (vStar1 + vStar2);
	State[StateVelocityX] += (i_dt / 2.0) * (aStar1 + aStar2);

	// Update current time.
	State[StateCurrentTime] += i_dt;
}

// Processing Draw function, called every time the screen refreshes.
//void draw()
//{
//	// Time Step.
//	TimeStep(1.0 / 24.0);
//
//	// Clear the display to a constant color.
//	background(0.75);
//
//	// Label.
//	fill(1.0);
//	text("RK2", 10, 30);
//
//	pushMatrix();
//
//	// Translate to the origin.
//	translate(OriginPixelsX, OriginPixelsY);
//
//	// Draw the simulation
//	DrawState();
//}

// Reset function. If the key 'r' is released in the display, 
// copy the initial state to the state.
//void keyReleased()
//{
//	if (key == 114)
//	{
//		for (int i = 0; i < StateSize; ++i)
//		{
//			State[i] = InitState[i];
//		}
//	}
//}
