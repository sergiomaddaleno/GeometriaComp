#include <stdlib.h>
#include <time.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"

#include "math_library/mmath_mine.h"
#include <thread>
#include <iostream>

const unsigned int kNWindowWidth = 800;
const unsigned int kNWindowHeight = 800;

unsigned char fps = 60;
double current_time, last_time;

bool g_exit = false;

Vector2 g_mouse = Vector2();
Vector2 g_screen_center = Vector2(kNWindowWidth / 2, kNWindowHeight / 2);

void Start() {

}

void FixedUpdate() {
    while (!g_exit) {
        //std::cout << "Manolo\n";
    }
}

void Update() {
    g_mouse.x = esat::MousePositionX();
    g_mouse.y = esat::MousePositionY();

    Vector2 norm = g_mouse.Substract(g_screen_center).Normalize();
    float distance = g_screen_center.Distance(g_mouse) * 0.75f;
    Vector2 mpoint = Vector2(g_screen_center.x + ( norm.x * distance), g_screen_center.y + (norm.y * distance));
    Vector2 ipoint = g_mouse.Rotate(mpoint, 90.0f);
    Vector2 dpoint = g_mouse.Rotate(mpoint, -90.0f);

    Vector2 v1 = g_mouse.Scale( 0.75f );
    //Vector2 square[5] = { {g_screen_center.x, g_screen_center.y}, {g_mouse.x, g_screen_center.y}, {g_mouse.x, g_mouse.y}, {g_screen_center.x, g_mouse.y}, {g_screen_center.x, g_screen_center.y} };
    esat::DrawSetStrokeColor(255,255,255,255);
    //esat::DrawPath(&square[0].x, 5);
    esat::DrawLine(g_screen_center.x, g_screen_center.y, mpoint.x, mpoint.y);
    esat::DrawLine(mpoint.x, mpoint.y, ipoint.x, ipoint.y);
    esat::DrawLine(g_mouse.x, g_mouse.y, ipoint.x, ipoint.y);
    esat::DrawLine(mpoint.x, mpoint.y, dpoint.x, dpoint.y);
    esat::DrawLine(g_mouse.x, g_mouse.y, dpoint.x, dpoint.y);
}

void LateUpdate() {

}

void Input() {

}

int esat::main(int argc, char** argv) {
    esat::WindowInit(kNWindowWidth, kNWindowHeight);
    WindowSetMouseVisibility(true);

    Start();

    std::thread t1(&FixedUpdate);

    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
        last_time = esat::Time();

        esat::DrawBegin();
        esat::DrawClear(0, 0, 0, 255);

        Update();

        esat::DrawEnd();

        //Control fps
        do {
            current_time = esat::Time();
        } while ((current_time - last_time) <= 1000.0 / fps);
        esat::WindowFrame();
    }

    g_exit = true;
    t1.join();

    esat::WindowDestroy();

    return 0;
}