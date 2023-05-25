#include <esat/math.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/window.h>
#include <esat/time.h>
#include <time.h>


const float kWindow_X = 800;
const float kWindow_Y = 600;

const int kNumberPoints = 10;
const float kRadius = 100.0f;
const float kCircunference = 6.283185f;
float g_angle = 0.0f;


void InitShapeCoords(float* circle) {
	float portion = kCircunference / kNumberPoints;
	for (int i = 0; i < kNumberPoints; ++i) {
		circle[i * 2] = cos(portion * i);
		circle[i * 2 + 1] = sin(portion * i);
	}
}

void TransformAndDraw(const float* shape_coords) {
	g_angle += 0.05f;

	esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(kRadius, kRadius), m);
	m = esat::Mat3Multiply(esat::Mat3Rotate(g_angle), m);
	m = esat::Mat3Multiply(esat::Mat3Translate((float) esat::MousePositionX(),
	 																					 (float) esat::MousePositionY()),
																						 m);

	float transformed_coords[kNumberPoints * 2] = { 0.0f };
	for (int i = 0; i < kNumberPoints; ++i) {
		esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_coords[i * 2] = result.x;
		transformed_coords[i * 2 + 1] = result.y;
	}

	esat::DrawSetStrokeColor(255, 255, 255, 255);
	esat::DrawSetFillColor(0, 0, 0, 0);
	esat::DrawSolidPath(transformed_coords, kNumberPoints, true);
}


int esat::main(int argc, char **argv) {
  double current_time = 0.0;
	double last_time = 0.0;
  unsigned char fps = 25;

  esat::WindowInit(kWindow_X, kWindow_Y);
  WindowSetMouseVisibility(true);

  //Shape vertices initialization.
  float circle_coords[kNumberPoints * 2] = { 0.0f };
  InitShapeCoords(circle_coords);


	//Main loop.
  while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
		last_time = esat::Time();

		esat::DrawBegin();
		esat::DrawClear(0,0,0);

    TransformAndDraw(circle_coords);

		esat::DrawEnd();
		esat::WindowFrame();

		do{
    	current_time = esat::Time();
    } while ((current_time - last_time) <= 1000.0 / fps);
  }

  esat::WindowDestroy();
  return 0;
}
