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
const int kNVerticesArrow=7;

struct TCoords{
  float x,y;
};

TCoords g_arrow[14]={ 300.0f, 200.0f,
                    500.0f, 200.0f,
                    500.0f, 100.0f,
                    650.0f, 250.0f,
                    500.0f, 400.0f,
                    500.0f, 300.0f,
                    300.0f, 300.0f };


//float max_x, max_y;
//float min_x, min_y;

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


void DrawArrow(){
  esat::DrawSetStrokeColor(0,255,0);
  esat::DrawSetFillColor(0,0,0);
  esat::DrawSolidPath(g_arrow, kNVerticesArrow);
}

void GlobalToLocal(float max, float min, float global_coord){
  float newPoints1=0;
  newPoints1 = (min+local_coord) * (max-min);
}

void LocalToGloabl(loat max, float min, float local_coord){
  float newPoints2=0;
  newPoints2 = (local_coord+-min) / (max-min);
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

    DrawArrow();

    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}
