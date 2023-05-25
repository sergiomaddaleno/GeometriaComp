#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <conio.h>


const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;

const int kNVertices = 30;
float g_circle[kNVertices * 2];

void InitShape{

  float angle_bwn_vertices = 6.28f / (float) kNVertices;
  float sin_a = 0.0f;
  float cos_a = 1.0f;
  float sin_b = sin(angle_bwn_vertices);
  float cos_b = cos(angle_bwn_vertices);

  for(int i=0; i< kNVertices; i++){
        g_circle[i * 2] = cos_a * cos_b - sin_a * sin_b; //x
        g_circle[i * 2 + 1] = sin_a * cos_b + cos_a * sin_b; //y
    }

  sin_a = g_circle[i * 2 + 1];
  cos_a = g_circle[i * 2];
  
  //update
  for(int i=0; i< kNVertices; i++){
        g_circle[i * 2] = g_circle[i * 2] * 180.0f + 400.0f; //x
        g_circle[i * 2 + 1] = g_circle[i * 2 + 1] * 180.0f + 300.0f; //y
    }
}

void DrawShape{

  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(255, 255, 255, 0);
  esat::DrawSolidPath(g_circle, kNVertices);
}


int esat::main(int argc, char** argv) {
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;
  esat::WindowInit(kWindowWidth, kWindowHeight);

  WindowSetMouseVisibility(true);

  InitShape();

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
         esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(120, 120, 120);

    DrawShape();

    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}