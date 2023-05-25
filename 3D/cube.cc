#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <conio.h>
#include <esat/window.h>

#define PI 3.14159265


const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;

const int kNPoints = 8;
esat::Vec3 g_cube[kNPoints] = { { -1.0f, -1.0f, 1.0f  },
                                { 1.0f, -1.0f, 1.0f   },
                                { 1.0f, 1.0f, 1.0f    },
                                { -1.0f, 1.0f, 1.0f   },

                                { -1.0f, -1.0f, -1.0f },
                                { 1.0f, -1.0f, -1.0f  },
                                { 1.0f, 1.0f, -1.0f   },
                                { -1.0f, 1.0f, -1.0f  }, };

esat::Mat4 UpdateCube() {

  //Point = T * S * Proj * T * Point
  esat::Mat4 m = esat::Mat4Identity();
  /*
  m = esat::Mat4Multiply(esat::Mat4Scale(1.0f, 1.0f, 4.0f), m);
  m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time() * 0.001), m);
  m = esat::Mat4Multiply(esat::Mat4Translate(0.0f, 0.0f, 6.0f), m);
  m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time() * 0.001), m);
  m = esat::Mat4Multiply(esat::Mat4Translate(0.0f, 0.0f, 12.0f), m);
  */

  m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time() * 0.001), m);
  m = esat::Mat4Multiply(esat::Mat4Translate(0.0f, 0.0f, 4.0f), m);
  m = esat::Mat4Multiply(esat::Mat4Projection(), m);
  m = esat::Mat4Multiply(esat::Mat4Scale(100.0f, 100.0f, 1.0f), m);
  m = esat::Mat4Multiply(esat::Mat4Translate(400.0f, 300.0f, 0.0f), m);

  return m;
}

esat::Mat4 UpdateDerivedCube1(esat::Mat4 base) {

  esat::Mat4 m = esat::Mat4Identity();
  m = esat::Mat4Multiply(esat::Mat4Scale(0.25f, 0.25f, 0.25f), m);
  m = esat::Mat4Multiply(esat::Mat4Translate(0.0f, 0.0f, cos(esat::Time() * 0.01f) * 0.75f), m);
  m = esat::Mat4Multiply(base, m);

  return m;
}

esat::Mat4 UpdateDerivedCube2(esat::Mat4 base) {

  esat::Mat4 m = esat::Mat4Identity();
  m = esat::Mat4Multiply(esat::Mat4Scale(0.25f, 0.25f, 0.25f), m);
  m = esat::Mat4Multiply(esat::Mat4Translate(2.0f, 0.0f, 0.0f), m);
  m = esat::Mat4Multiply(esat::Mat4RotateZ(esat::Time() * 0.001), m);
  m = esat::Mat4Multiply(base, m);

  return m;
}

void DrawFigure3D(esat::Mat4 m) {

  esat::Vec3 tr_points[kNPoints];
  for (int i = 0; i < kNPoints; ++i){
    tr_points[i] = esat::Mat4TransformVec3(m, g_cube[i]);
  }

  for (int i = 0; i < (kNPoints >> 1); ++i) {
    esat::DrawSetStrokeColor(255, 255, 255, 255);
    esat::DrawLine(tr_points[i].x, tr_points[i].y, tr_points[(i + 1) % 4].x, tr_points[(i + 1) % 4].y);
    esat::DrawLine(tr_points[i].x, tr_points[i].y, tr_points[i + 4].x, tr_points[i + 4].y);
    esat::DrawLine(tr_points[i + 4].x, tr_points[i + 4].y, tr_points[((i + 1) % 4) + 4].x, tr_points[((i + 1) % 4) + 4].y);
  }

}

int esat::main(int argc, char** argv) {
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;
  esat::WindowInit(kWindowWidth, kWindowHeight);

  WindowSetMouseVisibility(true);

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    esat::Mat4 base = UpdateCube();
    DrawFigure3D(base);
    //esat::Mat4 derived = UpdateDerivedCube1(base);
    //DrawFigure3D(derived);
    //esat::Mat4 derived2 = UpdateDerivedCube2(base);
    //DrawFigure3D(derived2);

    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}
