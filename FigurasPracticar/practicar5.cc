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

const int knPoints = 10;
float kCircunference = 2*PI;

float shape_coords[2 * knPoints] = {0.0f};
float transformed_coords[2 * knPoints] = {0.0f};

float circle_coords[2 * 30] = {0.0f};
float transformed_circle[2 * 30] = {0.0f};


void InitStar(){
    float portion = kCircunference / knPoints;
    for(int i=0; i<knPoints; i++){
        if(i%2==0){
            shape_coords[i * 2] = cos(portion * i);
            shape_coords[i * 2 + 1] = sin(portion * i);
        }else{
            shape_coords[i * 2] = cos(portion * i) * 0.5;
            shape_coords[i * 2 + 1] = sin(portion * i) * 0.5;
        }
    }
}

void InitCircle(){
    float portion = kCircunference / 30;
    for(int i=0; i<30; i++){
        circle_coords[i * 2] = cos(portion * i);
        circle_coords[i * 2 + 1] = sin(portion * i);
    }
}

void DrawPattern(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for(int j=0; j<4; j++){
        for(int k=0; k<2; k++){
            esat::Mat3 m = esat::Mat3Identity();
            m = esat::Mat3Multiply(esat::Mat3Rotate(-esat::Time()*0.001), m);
            m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, -3.0f), m);
            m = esat::Mat3Multiply(esat::Mat3Translate(j * 2, k * 2), m);
            m = esat::Mat3Multiply(esat::Mat3Translate(-2.7f, k * 6), m);
            m = esat::Mat3Multiply(esat::Mat3Scale(20.0f, 20.0f), m);
            m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

            for(int i=0; i<knPoints; i++){
                esat::Vec3 p = {shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f};
                esat::Vec3 result = esat::Mat3TransformVec3(m,p);
                transformed_coords[i * 2] = result.x;
                transformed_coords[i * 2 + 1] = result.y;
            }

            esat::DrawSolidPath(transformed_coords, knPoints);
        }
    }
}

void DrawPattern2(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for(int j=0; j<4; j++){
        for(int k=0; k<2; k++){
            esat::Mat3 m = esat::Mat3Identity();
            m = esat::Mat3Multiply(esat::Mat3Rotate(PI), m);
            m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, -3.0f), m);
            m = esat::Mat3Multiply(esat::Mat3Translate(k * 6,  j * 2), m);
            m = esat::Mat3Multiply(esat::Mat3Translate(-2.7f, k * 2), m);
            m = esat::Mat3Multiply(esat::Mat3Scale(20.0f, 20.0f), m);
            m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

            for(int i=0; i<knPoints; i++){
                esat::Vec3 p = {shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f};
                esat::Vec3 result = esat::Mat3TransformVec3(m,p);
                transformed_coords[i * 2] = result.x;
                transformed_coords[i * 2 + 1] = result.y;
            }

            esat::DrawSolidPath(transformed_coords, knPoints);
        }
    }
}

void DrawCircle(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCircunference / 15;

    for(int j=0; j<15; j++){

        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, 13.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Scale(15.0f, 15.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j), m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001), m);
        m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

        for(int i=0; i<30; i++){
            esat::Vec3 p = {circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f};
            esat::Vec3 result = esat::Mat3TransformVec3(m,p);
            transformed_circle[i * 2] = result.x;
            transformed_circle[i * 2 + 1] = result.y;
        }

        esat::DrawSolidPath(transformed_circle, 30);
    }
}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

    InitStar();
    InitCircle();
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawPattern();
    DrawPattern2();
    DrawCircle();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}