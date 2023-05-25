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
esat::Vec3 g_star[kNPoints];

void InitStar() {
  float angle = 6.28f / (float) kNPoints;
  for (int i = 0; i < kNPoints; ++i) {
    if (i % 2 == 0) {
      g_star[i] = { (float) cos(angle * (float) i),
                    (float) sin(angle * (float) i),
                    1.0f };
    }
    else {
      g_star[i] = { (float) cos(angle * (float) i) * 0.6f,
                    (float) sin(angle * (float) i) * 0.6f,
                    1.0f };
    }
  }
}

esat::Mat3 UpdateStar(esat::Vec2 scale = { 50.0f, 50.0f },
                      esat::Vec2 pos = { 400.0f, 300.0f }) {
  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(- 3.1415f / 2.0f /*+ esat::Time() * 0.001f*/), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(pos.x, pos.y), m);
  return m;
}

esat::Mat3 UpdateDerivedStar1(esat::Mat3 base, esat::Vec2 pos,
                              esat::Vec2 scale = { 0.25f, 0.25f }) {
  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(3.1415f), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(0.25f, 0.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time() * 0.001f), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(pos.x, pos.y), m);
  m = esat::Mat3Multiply(base, m);
  return m;
}

esat::Mat3 UpdateDerivedStar2(esat::Mat3 base, esat::Vec2 pos,
                              esat::Vec2 scale = { 0.25f, 0.25f }) {
  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(3.1415f), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(0.25f, 0.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(3.1415f + esat::Time() * 0.001f), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(pos.x, pos.y), m);
  m = esat::Mat3Multiply(base, m);
  return m;
}

void DrawStar(esat::Mat3 base) {
  esat::Vec2 tr_points[kNPoints];
  for (int i = 0; i < kNPoints; ++i) {
    esat::Vec3 tmp = esat::Mat3TransformVec3(base, g_star[i]);
    tr_points[i] = { tmp.x, tmp.y };
  }
  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(&tr_points[0].x, kNPoints);
}

const int kNSquarePoints = 4;
esat::Vec3 g_square[kNSquarePoints] = { {  1.0f, -1.0f, 1.0f },
                                        {  1.0f,  1.0f, 1.0f },
                                        { -1.0f,  1.0f, 1.0f },
                                        { -1.0f, -1.0f, 1.0f } };
const int kNArrowPoints = 4;
esat::Vec3 g_arrow[kNArrowPoints] = { { -1.0f,  0.0f, 1.0f },
                                        {  0.0f, -0.5f, 1.0f },
                                        {  0.5f,  0.0f, 1.0f },
                                        {  0.0f,  0.5f, 1.0f } };

esat::Mat3 UpdateSquareBorder(esat::Vec2 offset, float angle) {
  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(20.0f, 10.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(offset.x, offset.y), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(),
                                             esat::MousePositionY()), m);
  return m;
}

void DrawFigure(esat::Mat3 base, esat::Vec3* figure, const int n_points) {
  esat::Vec2 tr_points[30];
  for (int i = 0; i < n_points; ++i) {
    esat::Vec3 tmp = esat::Mat3TransformVec3(base, figure[i]);
    tr_points[i] = { tmp.x, tmp.y };
  }
  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(&tr_points[0].x, n_points);
}

int esat::main(int argc, char** argv) {
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;

  esat::WindowInit(kWindowWidth, kWindowHeight);
  esat::WindowSetMouseVisibility(true);
  InitStar();

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
         esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(120, 120, 120);

    
    esat::Mat3 base = UpdateStar();
    DrawStar(base);
    for (int i = 0; i < kNPoints; ++i) {
      esat::Vec2 pos;
      if (i % 2 == 0) {
        pos = { cosf(6.28f / (float) kNPoints * (float) i),
                sinf(6.28f / (float) kNPoints * (float) i) };
      }
      else {
        pos = { cosf(6.28f / (float) kNPoints * (float) i) * 0.6f,
                sinf(6.28f / (float) kNPoints * (float) i) * 0.6f };
      }
      esat::Mat3 derived_1 = UpdateDerivedStar1(base, pos);
      esat::Mat3 derived_2 = UpdateDerivedStar2(base, pos);
      DrawStar(derived_1);
      DrawStar(derived_2);
    }
    

    for (int j = 0; j < 4; ++j) {
      for (int i = 0; i < 5; ++i) {
        esat::Vec2 offset_square = { 150.0f, 30.0f * i - 30.0f * 2.0f};
        esat::Mat3 square_border = UpdateSquareBorder(offset_square,
                                                      6.28f / 4.0f * (float) j);
        DrawFigure(square_border, g_square, kNSquarePoints);

        esat::Vec2 offset_arrow = { 100.0f, 30.0f * i - 30.0f * 2.0f};
        esat::Mat3 arrow_border = UpdateSquareBorder(offset_arrow,
                                                      6.28f / 4.0f * (float) j);
        DrawFigure(arrow_border, g_arrow, kNArrowPoints);
      }
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
