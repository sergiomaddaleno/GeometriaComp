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

double current_time,last_time;
unsigned char fps=60;

float kCircunference = 2*PI;
float cont=0;

const int kNumberPoints = 50;
const int kNumberPointsStar = 10;
float circle_coords[2 * kNumberPoints] = {0.0f};
float transformed_coords[2 * kNumberPoints] = {0.0f};

float star_coords[2 * kNumberPointsStar] = {0.0f};
float transformed_star[2 * kNumberPointsStar] = {0.0f};

void InitCircle(){
    float portion = kCircunference / kNumberPoints;
    for(int i=0; i<kNumberPoints; i++){
        circle_coords[2 * i] = cos(portion * i);
        circle_coords[2 * i + 1] = sin(portion * i);
    }
}

void InitStar(){
    float portion = kCircunference / kNumberPointsStar;
    for(int i=0; i<kNumberPointsStar; i++){
        if(i%2 == 0){
            star_coords[i * 2] = cos(portion * i);
            star_coords[i * 2 + 1] = sin(portion * i);
        }else{
            star_coords[i * 2] = cos(portion * i) * 0.5;
            star_coords[i * 2 + 1] = sin(portion * i) * 0.5;
        }
    }
}

void DrawStar(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();
    float portion = kCircunference / 3;

    cont = cont + 0.2;
    if(cont>kNumberPoints){cont=0;}

    for(int j=0; j<3; j++){

        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Scale(15.0f, 15.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Translate(transformed_coords[(int)cont * 2], transformed_coords[(int)cont * 2 + 1]), m);

        for(int i=0; i<kNumberPointsStar; i++){
            esat::Vec3 p = {star_coords[2 * i], star_coords[2 * i + 1], 1.0f};
            esat::Vec3 result = Mat3TransformVec3(m,p);
            transformed_star[2 * i] = result.x;
            transformed_star[2 * i + 1] = result.y;
        }
        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSetFillColor(0,0,0,0);
        esat::DrawSolidPath(transformed_star, kNumberPointsStar);
    }
}


void DrawCircle(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(15.0f, 15.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(0.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

    for(int i=0; i<kNumberPoints; i++){
        esat::Vec3 p = {circle_coords[2 * i], circle_coords[2 * i + 1], 1.0f};
        esat::Vec3 result = Mat3TransformVec3(m,p);
        transformed_coords[2 * i] = result.x;
        transformed_coords[2 * i + 1] = result.y;
    }
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(transformed_coords, kNumberPoints);
}

void DrawThreeCircle(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCircunference / 3;

    for(int j=0; j<3; j++){

        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Scale(25.0f, 70.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j), m);
        m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

        for(int i=0; i<kNumberPoints; i++){
            esat::Vec3 p = {circle_coords[2 * i], circle_coords[2 * i + 1], 1.0f};
            esat::Vec3 result = Mat3TransformVec3(m,p);
            transformed_coords[2 * i] = result.x;
            transformed_coords[2 * i + 1] = result.y;
        }
        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSetFillColor(0,0,0,0);
        esat::DrawSolidPath(transformed_coords, kNumberPoints);
        DrawStar();
    }
}


int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

    InitCircle();
    InitStar();
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawCircle();
    DrawThreeCircle();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}