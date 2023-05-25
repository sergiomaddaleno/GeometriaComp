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

const int kNPoints = 30;
//esat::Vec2 scale = {10.0f, 10.0f}; //Tamaño hor y vert
esat::Vec3 g_circle[kNPoints];

void InitCircle() {
  float angle = 6.28f / (float) kNPoints;
  for (int i = 0; i < kNPoints; ++i) {
    g_circle[i] = { (float) cos(i * angle),
                    (float) sin(i * angle),
                    1.0f };
  }
}

void DrawCircle(esat::Mat3 m) {
  esat::Vec2 tr_points[kNPoints];
  for (int i = 0; i < kNPoints; ++i) {
    esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_circle[i]);
    tr_points[i] = { tmp.x, tmp.y };
  }
  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(&tr_points[0].x, kNPoints);
}

esat::Mat3 UpdateBase(){
  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(15.0f, 15.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(0.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(400.0f, 300.0f), m);

  return m;
}

esat::Mat3 UpdateBase2(esat::Mat3 base, float i){
  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(80.0f, 25.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(3.1415f * 0.001f * i), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(400.0f, 300.0f), m);

  return m;
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

    esat::Mat3 base = UpdateBase();
    DrawCircle(base);
    for (int i = 0; i < 3; ++i) {
      esat::Mat3 base2 = UpdateBase2(base, (float) (i + 1));
      DrawCircle(base2);
    }

    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}
