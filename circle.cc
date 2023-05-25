#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"

const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;

const int kNPoints = 10;
const float kRadius = 180.0f;
esat::Vec3 g_circle[kNPoints];

void InitCircle() {
  float angle = 6.28f / (float) kNPoints;
  for (int i = 0; i < kNPoints; ++i) {
    g_circle[i] = { (float) cos(angle * i),
                    (float) sin(angle * i),
                    0.0f };
  }
}

void UpdateDrawCircle() {
  float tr_points[kNPoints * 2];

  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(kRadius, kRadius), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time() * 0.001f), m);
  m = esat::Mat3Multiply(esat::Mat3Translate((float) esat::MousePositionX(),
                                             (float) esat::MousePositionY()), m);
  for (int i = 0; i < kNPoints; ++i) {
    esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_circle[i]);
    tr_points[i * 2] = tmp.x;
    tr_points[i * 2 + 1] = tmp.y;
  }

  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(tr_points, kNPoints);
}

int esat::main(int argc, char** argv) {
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;

  esat::WindowInit(kWindowWidth, kWindowHeight);
  esat::WindowSetMouseVisibility(true);
  InitCircle();

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
         esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(120, 120, 120);

    UpdateDrawCircle();

    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}
