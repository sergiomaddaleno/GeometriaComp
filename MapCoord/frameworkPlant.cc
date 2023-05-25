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



    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}
