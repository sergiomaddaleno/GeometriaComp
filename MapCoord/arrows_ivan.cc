#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"


const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;


//Arrow coords
//300.0f, 200.0f
//500.0f, 200.0f
//500.0f, 100.0f
//650.0f, 250.0f
//500.0f, 400.0f
//500.0f, 300.0f
//300.0f, 300.0f

//Destiny box 1:
//[Min x]: 40
//[Max x]: 150
//[Min y]: 40
//[Max y]: 150

//Destiny box 2:
//[Min x]: 100
//[Max x]: 200
//[Min y]: 300
//[Max y]: 540

//Destiny box 3:
//[Min x]: 240
//[Max x]: 800
//[Min y]: 420
//[Max y]: 600

const int kNVerticesArrow = 7;
esat::Vec2 g_arrow[kNVerticesArrow] = {
  300.0f, 200.0f,
  500.0f, 200.0f,
  500.0f, 100.0f,
  650.0f, 250.0f,
  500.0f, 400.0f,
  500.0f, 300.0f,
  300.0f, 300.0f,
};

float LocalToGlobal(float local_coord, float min, float max) {
  return min + local_coord * (max - min);
}

float GlobalToLocal(float global_coord, float min, float max) {
  return (global_coord - min) / (max - min);
}

void DrawArrowInNewReferenceSystem(float min_x, float max_x, float min_y, float max_y) {
  float ref_system[8] = { min_x, min_y,
                          max_x, min_y,
                          max_x, max_y,
                          min_x, max_y };
  esat::DrawSetStrokeColor(255, 255, 255);
  esat::DrawSetFillColor(120, 120, 120);
  esat::DrawSolidPath(ref_system, 4);

  esat::Vec2 tr_points[kNVerticesArrow];
  for (int i = 0; i < kNVerticesArrow; ++i) {
    tr_points[i] = { GlobalToLocal(g_arrow[i].x, 0.0f, (float) kWindowWidth),
                     GlobalToLocal(g_arrow[i].y, 0.0f, (float) kWindowHeight) };
    tr_points[i] = { LocalToGlobal(tr_points[i].x, min_x, max_x),
                     LocalToGlobal(tr_points[i].y, min_y, max_y) };
  }
  esat::DrawSetStrokeColor(255, 255, 255);
  esat::DrawSetFillColor(255, 255, 255);
  esat::DrawSolidPath(&tr_points[0].x, kNVerticesArrow);
}

int esat::main(int argc, char** argv) {
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;

  esat::WindowInit(kWindowWidth, kWindowHeight);
  WindowSetMouseVisibility(true);


  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
         esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(120, 120, 120);
    esat::DrawSolidPath(&g_arrow[0].x, kNVerticesArrow);

    DrawArrowInNewReferenceSystem(40.0f, 150.0f, 40.0f, 150.0f);
    DrawArrowInNewReferenceSystem(100.0f, 200.0f, 300.0f, 540.0f);
    DrawArrowInNewReferenceSystem(240.0f, 800.0f, 420.0f, 600.0f);

    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}
