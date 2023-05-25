#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"
#include "esat/math.h"


const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;

const int kNTriangle = 3;
const int kNSquare = 4;
const int kNPentagon = 5;
const int kNStar = 10;
esat::Vec2 g_triangle[kNTriangle];
esat::Vec2 g_square[kNSquare];
esat::Vec2 g_pentagon[kNPentagon];
esat::Vec2 g_star[kNStar];

void InitCircle(esat::Vec2 circle[], int n_vertices, float offset) {
  float angle_between_radians = 6.28f / (float) n_vertices;
  if (kNStar == n_vertices) {
    for (int i = 0; i < n_vertices; ++i) {
      if (i % 2 == 0) {
        circle[i] = { (float) cos(angle_between_radians * i + offset),
                      (float) sin(angle_between_radians * i + offset) };
      }
      else {
        circle[i] = { (float) cos(angle_between_radians * i + offset) * 0.6f,
                      (float) sin(angle_between_radians * i + offset) * 0.6f };
      }
    }
  }
  else {
    for (int i = 0; i < n_vertices; ++i) {
      circle[i] = { (float) cos(angle_between_radians * i + offset),
                    (float) sin(angle_between_radians * i + offset) };
    }
  }
}

void DrawCircle(esat::Vec2* circle, int n_vertices,
                esat::Vec2 scale = { 180.0f, 180.0f },
                esat::Vec2 pos = { 400.0f, 300.0f}) {
  esat::Vec2 tr_points[kNStar];
  for (int i = 0; i < n_vertices; ++i) {
    tr_points[i] = { circle[i].x * scale.x + pos.x,
                     circle[i].y * scale.y + pos.y };
  }

  esat::DrawSetStrokeColor(255, 255, 255);
  esat::DrawSetFillColor(255, 255, 255, 0);
  esat::DrawSolidPath(&tr_points[0].x, n_vertices);
}

int esat::main(int argc, char** argv) {
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;

  esat::WindowInit(kWindowWidth, kWindowHeight);
  WindowSetMouseVisibility(true);
  InitCircle(g_triangle, kNTriangle, - 1.57f);
  InitCircle(g_square, kNSquare, - 0.78f);
  InitCircle(g_pentagon, kNPentagon, - 1.57f);
  InitCircle(g_star, kNStar, - 1.57f);

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
         esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(120, 120, 120);

    DrawCircle(g_triangle, kNTriangle);
    DrawCircle(g_square, kNSquare, { 100.0f, 100.0f }, { 200.0f, 200.0f });
    DrawCircle(g_pentagon, kNPentagon, { 50.0f, 50.0f }, { 400.0f, 500.0f });
    DrawCircle(g_star, kNStar, { 75.0f, 75.0f }, { 200.0f, 500.0f });

    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}