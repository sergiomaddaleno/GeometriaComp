#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "esat/window.h"
#include "esat/input.h"
#include "esat/draw.h"
#include "esat/math.h"
#include "esat/time.h"

const unsigned int kWindow_X = 800;
const unsigned int kWindow_Y = 600;

//Some global variables?
float kCricunfernece = 2 * 3.1415;
const int kNumPointsTriangle = 3;
const int kNumPointsArrow = 9;
const int kNumPointsCircle = 40;

float circle_coords[2 * kNumPointsCircle] = {0.0f};
float transformed_circle[2 * kNumPointsCircle] = {0.0f};

float triangle_coords[2 * kNumPointsTriangle] = {0.0f};
float transformed_triangle[2 * kNumPointsTriangle] = {0.0f};

float points[18]={ 
                 0.0f,0.0f,
                 0.0f,0.5f,
                 1.0f,0.5f,
                 1.0f,1.0f,
                 2.0f,0.0f,
                 1.0f,-1.0f,
                 1.0f,-0.5f,
                 0.0f,-0.5f,     
                 0.0f,0.0f               
};

float transformed_arrow[2 * kNumPointsTriangle] = {0.0f};

//Create other functions?
void InitShape(float *shape_coords, int knPoints){
  float portion = kCricunfernece / knPoints;
  for(int i=0; i<knPoints; i++){
      shape_coords[i * 2] = cos(portion * i);
      shape_coords[i * 2 + 1] = sin(portion * i);
  }
}

//------------------------------------------------------
//pregunta 1
void DrawArrow(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCricunfernece / 3;

    for(int j=0; j<3; j++){
      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Scale(50.0f, 50.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate(0.5f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

      for(int i=0; i<kNumPointsArrow; i++){
        esat::Vec3 p = {points[i * 2], points[i * 2 + 1], 1.0f};
        esat::Vec3 result = Mat3TransformVec3(m,p);
        transformed_arrow[i * 2] = result.x;
        transformed_arrow[i * 2 + 1] = result.y;
      }

      esat::DrawSetStrokeColor(255,255,255);
      esat::DrawSetFillColor(0,0,0,0);
      esat::DrawSolidPath(transformed_arrow, kNumPointsArrow);
    }
}

void DrawTriangle(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(100.0f, 100.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(0.51f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

    for(int i=0; i<kNumPointsTriangle; i++){
      esat::Vec3 p = {triangle_coords[i * 2], triangle_coords[i * 2 + 1], 1.0f};
      esat::Vec3 result = Mat3TransformVec3(m,p);
      transformed_triangle[i * 2] = result.x;
      transformed_triangle[i * 2 + 1] = result.y;
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(transformed_triangle, kNumPointsTriangle);
}

//------------------------------------------------------
//pregunta 2
void DrawOutCircles(){
	  float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    //float portion = kCricunfernece / 3;

    for(int j=0; j<4; j++){
      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Scale(70.0f, 70.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Scale(j, j), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

      for(int i=-1; i<39; i++){
        esat::Vec3 p = {circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f};
        esat::Vec3 result = Mat3TransformVec3(m,p);
        transformed_circle[i * 2] = result.x;
        transformed_circle[i * 2 + 1] = result.y;
      }

      esat::DrawSetStrokeColor(255,255,255);
      esat::DrawSetFillColor(0,0,0,0);
      esat::DrawSolidPath(transformed_circle, 39);
    }
}

void DrawArrows(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCricunfernece / 10;
    for(int j=0; j<10; j++){
      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Translate(-1.0f, 8.7f), m);
      m = esat::Mat3Multiply(esat::Mat3Scale(20.0f, 20.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

      for(int i=0; i<kNumPointsArrow; i++){
        esat::Vec3 p = {points[i * 2], points[i * 2 + 1], 1.0f};
        esat::Vec3 result = Mat3TransformVec3(m,p);
        transformed_arrow[i * 2] = result.x;
        transformed_arrow[i * 2 + 1] = result.y;
      }

      esat::DrawSetStrokeColor(255,255,255);
      esat::DrawSetFillColor(0,0,0,0);
      esat::DrawSolidPath(transformed_arrow, kNumPointsArrow);
    }
}

void DrawArrows2(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCricunfernece / 10;
    for(int j=0; j<10; j++){
      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Rotate(3.1415/2), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(-0.2f, 4.3f), m);
      m = esat::Mat3Multiply(esat::Mat3Scale(20.0f, 20.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

      for(int i=0; i<kNumPointsArrow; i++){
        esat::Vec3 p = {points[i * 2], points[i * 2 + 1], 1.0f};
        esat::Vec3 result = Mat3TransformVec3(m,p);
        transformed_arrow[i * 2] = result.x;
        transformed_arrow[i * 2 + 1] = result.y;
      }

      esat::DrawSetStrokeColor(255,255,255);
      esat::DrawSetFillColor(0,0,0,0);
      esat::DrawSolidPath(transformed_arrow, kNumPointsArrow);
    }
}

void DrawInCircles1(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCricunfernece / 3;

    for(int j=0; j<2; j++){
      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Translate(0.1f,0.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(-0.1f, -1.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Scale(20.0f, 35.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate(-0.77f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j*1.5), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

      for(int i=0; i<39; i++){
        esat::Vec3 p = {circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f};
        esat::Vec3 result = Mat3TransformVec3(m,p);
        transformed_circle[i * 2] = result.x;
        transformed_circle[i * 2 + 1] = result.y;
      }

      esat::DrawSetStrokeColor(255,255,255);
      esat::DrawSetFillColor(0,0,0,0);
      esat::DrawSolidPath(transformed_circle, 39);
    }
}

void DrawInCircles2(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCricunfernece / 3;

    for(int j=0; j<2; j++){
      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Translate(0.2f, -1.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Scale(20.0f, 35.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate(0.62f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j*-1.5), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

      for(int i=0; i<39; i++){
        esat::Vec3 p = {circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f};
        esat::Vec3 result = Mat3TransformVec3(m,p);
        transformed_circle[i * 2] = result.x;
        transformed_circle[i * 2 + 1] = result.y;
      }

      esat::DrawSetStrokeColor(255,255,255);
      esat::DrawSetFillColor(0,0,0,0);
      esat::DrawSolidPath(transformed_circle, 39);
    }
}

int esat::main(int argc, char **argv) {
  double current_time = 0.0;
	double last_time = 0.0;
  double fps = 30.0;

  esat::WindowInit(kWindow_X, kWindow_Y);
  esat::WindowSetMouseVisibility(true);
  int scene_index = 0;

	//Some data initialization in this point?
  InitShape(triangle_coords, kNumPointsTriangle);
  InitShape(circle_coords, kNumPointsCircle);

	//Main loop.
  while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
		last_time = esat::Time();

		esat::DrawBegin();
		esat::DrawClear(0,0,0);

    //Scene up!!
    if (esat::MouseButtonUp(0)) {
      scene_index = scene_index + 1 > 2 ? 0 : scene_index + 1;
    } //Scene down!!
    else if (esat::MouseButtonUp(1)) {
      scene_index = scene_index - 1 < 0 ? 2 : scene_index - 1;
    }

		//It's allowed to add parameters to any function.
    switch(scene_index) {
      case 0:
        DrawArrow();
        DrawTriangle();
        break;
      case 1:
        DrawOutCircles();
        DrawArrows();
        DrawArrows2();
        DrawInCircles1();
        DrawInCircles2();
        break;
      case 2:
        
        break;
    }

		esat::DrawEnd();
		esat::WindowFrame();

		do {
    	current_time = esat::Time();
    } while ((current_time - last_time) <= 1000.0 / fps);
  }

  esat::WindowDestroy();
  return 0;
}
