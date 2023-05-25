
#include "smfLibrary.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

//compiler_mathLib.bat smfLibrary.h archivo para compilar 

namespace smf{

    //Add Vectors
    Vec2 Vec2AddVec2(Vec2 v, Vec2 w){return{ v.x + w.x, v.y + w.y};}

    Vec3 Vec3AddVec3(Vec3 v, Vec3 w){return{ v.x + w.x, v.y + w.y, v.z + w.z};}

    Vec4 Vec4AddVec4(Vec4 v, Vec4 w){return{ v.x + w.x, v.y + w.y, v.z + w.z, v.w + w.w};}

    //Subtract Vectors
    Vec2 Vec2SubtractVec2(Vec2 v, Vec2 w){return{ v.x - w.x, v.y - w.y};}

    Vec3 Vec3SubtractVec3(Vec3 v, Vec3 w){return{ v.x - w.x, v.y - w.y, v.z - w.z};}

    Vec4 Vec4SubtractVec4(Vec4 v, Vec4 w){return{ v.x - w.x, v.y - w.y, v.z - w.z, v.w - w.w};}

    //----------------------------------------------------------------------------------------------------------------------------------

    //Multiply Vector Scalar
    Vec2 Vec2MultiplyVec2(Vec2 v, Vec2 w){return{v.x * w.x, v.y * w.y};}

    Vec3 Vec3MultiplyVec3(Vec3 v, Vec3 w){return{v.x * w.x, v.y * w.y, v.z * w.z};}

    Vec4 Vec4MultiplyVec4(Vec4 v, Vec4 w){return{v.x * w.x, v.y * w.y, v.z * w.z, v.w * w.w};}

    //Division Vector Scalar
    Vec2 Vec2DivideVec2(Vec2 v, Vec2 w){return{v.x / w.x, v.y / w.y};}

    Vec3 Vec3DivideVec3(Vec3 v, Vec3 w){return{v.x / w.x, v.y / w.y, v.z / w.z};}

    Vec4 Vec4DivideVec4(Vec4 v, Vec4 w){return{v.x / w.x, v.y / w.y, v.z / w.z, v.w / w.w};}

    //----------------------------------------------------------------------------------------------------------------------------------
    
    //Magnitude Vector (length)
    float Vec2Magnitude(Vec2 v, Vec2 w){
        return sqrt((exp(v.x - w.x),2) + (exp(v.y - w.y),2));
    }

    float Vec3Magnitude(Vec3 v, Vec3 w){
        return sqrt((exp(v.x - w.x),2) + (exp(v.y - w.y),2) + (exp(v.z - w.z),2));
    }

    float Vec4Magnitude(Vec4 v, Vec4 w){
        return sqrt((exp(v.x - w.x),2) + (exp(v.y - w.y),2) + (exp(v.z - w.z),2) + (exp(v.w - w.w),2));
    }

    //print Vectors
    void Vec2Print(Vec2 v, Vec2 w){
        printf("%f %f\n", v.x, v.y);}

    void Vec3Print(Vec3 v, Vec3 w){
        printf("%f %f %f\n", v.x, v.y, v.z);}

    void Vec4Print(Vec4 v, Vec4 w){
        printf("%f %f %f %f\n", v.x, v.y, v.z, v.w);}

    //----------------------------------------------------------------------------------------------------------------------------------
    
    //Normalize Vector
    Vec2 Vec2Normalize(Vec2 v, Vec2 w){
        float m = sqrt(pow(v.x - w.x, 2) + pow(v.y - w.y, 2));
        return{ (v.x-w.x)/m, (v.y-w.y)/m};
    }

    Vec3 Vec3Normalize(Vec3 v, Vec3 w){
        float m = sqrt(pow(v.x - w.x,2) + pow(v.y - w.y,2) + pow(v.z - w.z,2));
        return{ (v.x-w.x)/m, (v.y-w.y)/m, (v.z-w.z)/m};
    }

    Vec4 Vec4Normalize(Vec4 v, Vec4 w){
        float m = sqrt(pow(v.x - w.x,2) + pow(v.y - w.y,2) + pow(v.z - w.z,2) + pow(v.w - w.w,2));
        return{ (v.x-w.x)/m, (v.y-w.y)/m, (v.z-w.z)/m, (v.w-w.w)/m};
    }
    
    //Check if normalized?

    //----------------------------------------------------------------------------------------------------------------------------------

    //Perpendicular 2D vector. To find the perpendicular of (3,4), 
    //we swap the components and negate one of them: So the perpendicular vector of (3, 4) is (-4, 3).

    Vec2 Vec2Perpendicular(Vec2 v, Vec2 w){
        float m = v.x;
        v.x = -v.y;
        v.y = m;
        return{v.x, v.y};
    }

    //----------------------------------------------------------------------------------------------------------------------------------

    void Mat3Print(Mat3 m) {
        for (int i = 0; i < 3; i++) {
            printf("%.2f %.2f %.2f\n", m.d[i], m.d[i+3], m.d[i+6]);
        }
    }

    //Add matrix
    Mat2 Mat2AddMat2(Mat2 v, Mat2 w){

        return{ v.d[0] + w.d[0], v.d[1] + w.d[1], 
                v.d[2] + w.d[2], v.d[3] + w.d[3] };}

    Mat3 Mat3AddMat3(Mat3 v, Mat3 w){

        return{ v.d[0] + w.d[0], v.d[1] + w.d[1], v.d[2] + w.d[2], 
                v.d[3] + w.d[3], v.d[4] + w.d[4], v.d[5] + w.d[5], 
                v.d[6] + w.d[6], v.d[7] + w.d[7], v.d[8] + w.d[8] };}

    Mat4 Mat4AddMat4(Mat4 v, Mat4 w){

        return{ v.d[0] + w.d[0], v.d[1] + w.d[1], v.d[2] + w.d[2], v.d[3] + w.d[3], 
                v.d[4] + w.d[4], v.d[5] + w.d[5], v.d[6] + w.d[6], v.d[7] + w.d[7], 
                v.d[8] + w.d[8], v.d[9] + w.d[9], v.d[10] + w.d[10], v.d[11] + w.d[11],
                v.d[12] + w.d[12], v.d[13] + w.d[13], v.d[14] + w.d[14], v.d[15] + w.d[15] };}


    //Subtract matrix
    Mat2 Mat2SubtractMat2(Mat2 v, Mat2 w){

        return{ v.d[0] - w.d[0], v.d[1] - w.d[1], 
                v.d[2] - w.d[2], v.d[3] - w.d[3] };}

    Mat3 Mat3SubtractMat3(Mat3 v, Mat3 w){

        return{ v.d[0] - w.d[0], v.d[1] - w.d[1], v.d[2] - w.d[2], 
                v.d[3] - w.d[3], v.d[4] - w.d[4], v.d[5] - w.d[5], 
                v.d[6] - w.d[6], v.d[7] - w.d[7], v.d[8] - w.d[8] };}

    Mat4 Mat4SubtractMat4(Mat4 v, Mat4 w){

        return{ v.d[0] - w.d[0], v.d[1] - w.d[1], v.d[2] - w.d[2], v.d[3] - w.d[3], 
                v.d[4] - w.d[4], v.d[5] - w.d[5], v.d[6] - w.d[6], v.d[7] - w.d[7], 
                v.d[8] - w.d[8], v.d[9] - w.d[9], v.d[10] - w.d[10], v.d[11] - w.d[11],
                v.d[12] - w.d[12], v.d[13] - w.d[13], v.d[14] - w.d[14], v.d[15] - w.d[15] };}

    //----------------------------------------------------------------------------------------------------------------------------------

    //multiply matrix
    Mat2 Mat2MultiplyMat2(Mat2 v, Mat2 w) {
        Mat2 result;
            result.d[0] = v.d[0] * w.d[0] + v.d[1] * w.d[2];
            result.d[1] = v.d[0] * w.d[1] + v.d[1] * w.d[3];
            result.d[2] = v.d[2] * w.d[0] + v.d[3] * w.d[2];
            result.d[3] = v.d[2] * w.d[1] + v.d[3] * w.d[3];
        
        return result;
    }


    Mat3 Mat3MultiplyMat3(struct Mat3 v, struct Mat3 w) {
        Mat3 result;

        result.d[0] = v.d[0]*w.d[0] + v.d[1]*w.d[3] + v.d[2]*w.d[6];
        result.d[1] = v.d[0]*w.d[1] + v.d[1]*w.d[4] + v.d[2]*w.d[7];
        result.d[2] = v.d[0]*w.d[2] + v.d[1]*w.d[5] + v.d[2]*w.d[8];

        result.d[3] = v.d[3]*w.d[0] + v.d[4]*w.d[3] + v.d[5]*w.d[6];
        result.d[4] = v.d[3]*w.d[1] + v.d[4]*w.d[4] + v.d[5]*w.d[7];
        result.d[5] = v.d[3]*w.d[2] + v.d[4]*w.d[5] + v.d[5]*w.d[8];

        result.d[6] = v.d[6]*w.d[0] + v.d[7]*w.d[3] + v.d[8]*w.d[6];
        result.d[7] = v.d[6]*w.d[1] + v.d[7]*w.d[4] + v.d[8]*w.d[7];
        result.d[8] = v.d[6]*w.d[2] + v.d[7]*w.d[5] + v.d[8]*w.d[8];

        return result;
    }   

    Mat4 Mat4MultiplyMat4(Mat4 v, Mat4 w){
        Mat4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.d[i*4 + j] = 0;
                for (int k = 0; k < 4; k++) {
                    result.d[i*4 + j] += v.d[i*4 + k] * w.d[k*4 + j];
                }
            }
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------------------------

    //divide matrix by scalar

    //----------------------------------------------------------------------------------------------------------------------------------

    //vector multiply matrix

    //----------------------------------------------------------------------------------------------------------------------------------

    //identity of a matrix
    /*Mat2 Mat2Identity(Mat2 v, Mat2 w){
    }

    Mat3 Mat3Identity(Mat3 v, Mat3 w){
    }

    Mat4 Mat4Identity(Mat4 v, Mat4 w){
    }*/

    //----------------------------------------------------------------------------------------------------------------------------------

    //matrix Translate 2D----------------------------------
    Mat3 Mat3Translate(Mat3 m, float tx, float ty) {
        Mat3 translateMatrix = {
            m.d[0], m.d[1], m.d[2],
            m.d[3], m.d[4], m.d[5],
            m.d[6] + tx * m.d[0] + ty * m.d[3],
            m.d[7] + tx * m.d[1] + ty * m.d[4],
            m.d[8] + tx * m.d[2] + ty * m.d[5]
        };
        return translateMatrix;
    }

    void Mat3PrintTranslate(Mat3 m) {
        for (int i = 0; i < 9; i++) {
            printf("%f ", m.d[i]);
            if ((i+1) % 3 == 0) {
                printf("\n");
            }
        }
    }

    //matrix Rotate 2D-------------------------------------
    Mat3 Mat3Rotate(Mat3 m, float angle) {
        float c = cos(angle * PI / 180.0);
        float s = sin(angle * PI / 180.0);

        Mat3 rotateMatrix = {
            m.d[0] * c + m.d[3] * s, m.d[1] * c + m.d[4] * s, m.d[2] * c + m.d[5] * s,
            m.d[3] * c - m.d[0] * s, m.d[4] * c - m.d[1] * s, m.d[5] * c - m.d[2] * s,
            m.d[6], m.d[7], m.d[8]
        };
        return rotateMatrix;
    }

    Mat3 printMat3Rotate(Mat3 m, float angle) {
        float rad = angle * PI / 180.0f;
        float c = cos(rad);
        float s = sin(rad);
        smf::Mat3 rotateMatrix = {
            c, -s, 0,
            s, c, 0,
            0, 0, 1
        };
        smf::Mat3 rotatedMatrix = Mat3MultiplyMat3(rotateMatrix, m);
        printf("\nprint for matrix rotated:\n\n");
        printf("Rotation angle: %f degrees\n\n", angle);
        printf("Rotation matrix:\n");
        Mat3Print(rotateMatrix);
        return rotatedMatrix;
    }

    //matrix Scale 2D-------------------------------------
    Mat3 Mat3Scale(Mat3 m, float sx, float sy) {
        Mat3 scaleMatrix = {
            sx, 0, 0,
            0, sy, 0,
            0, 0, 1
        };
        return Mat3MultiplyMat3(m, scaleMatrix);
    }

    //----------------------------------------------------------------------------------------------------------------------------------

    float Mat2Determinant(Mat2 m) {
        return m.d[0]*m.d[3] - m.d[1]*m.d[2];
    }


    float Mat3Determinant(Mat3 m) {
        float det = 0;
        det += m.d[0] * (m.d[4] * m.d[8] - m.d[5] * m.d[7]);
        det -= m.d[1] * (m.d[3] * m.d[8] - m.d[5] * m.d[6]);
        det += m.d[2] * (m.d[3] * m.d[7] - m.d[4] * m.d[6]);
    return det;
    }


    Mat2 Mat2Inverse(Mat2 m) {
        float det = m.d[0]*m.d[3] - m.d[1]*m.d[2];
        Mat2 inv;

        if (det != 0.0f) {
            inv.d[0] = m.d[3]/det;
            inv.d[1] = -m.d[1]/det;
            inv.d[2] = -m.d[2]/det;
            inv.d[3] = m.d[0]/det;
        }else{
            // handle singular matrix
            printf("Cannot calculate inverse of singular matrix");
        }
        return inv;
    }


    Mat3 Mat3Inverse(Mat3 m) {
        float det = Mat3Determinant(m);
        if (det == 0) {
            printf("Cannot invert matrix, determinant is zero.\n");
            return m;
        }
        Mat3 inv;
        inv.d[0] = (m.d[4]*m.d[8] - m.d[5]*m.d[7]) / det;
        inv.d[1] = (m.d[2]*m.d[7] - m.d[1]*m.d[8]) / det;
        inv.d[2] = (m.d[1]*m.d[5] - m.d[2]*m.d[4]) / det;
        inv.d[3] = (m.d[5]*m.d[6] - m.d[3]*m.d[8]) / det;
        inv.d[4] = (m.d[0]*m.d[8] - m.d[2]*m.d[6]) / det;
        inv.d[5] = (m.d[2]*m.d[3] - m.d[0]*m.d[5]) / det;
        inv.d[6] = (m.d[3]*m.d[7] - m.d[4]*m.d[6]) / det;
        inv.d[7] = (m.d[1]*m.d[6] - m.d[0]*m.d[7]) / det;
        inv.d[8] = (m.d[0]*m.d[4] - m.d[1]*m.d[3]) / det;
        return inv;
    }


}


int main(int argc, char** argv){

    //Print for Vec2 Normalized
    //------------------------------------------------------
    printf("\n\n-------------------------------------\n\n");

    printf("print for normalize vector 2x2:\n\n");
    smf::Vec2 v = {1.0f, 1.0f};
    smf::Vec2 w = {4.0f, 5.0f};
    smf::Vec2 normalized = Vec2Normalize(v, w);
    printf("Input vectors:\n");
    printf("v = (%f, %f)\n", v.x, v.y);
    printf("w = (%f, %f)\n\n", w.x, w.y);

    printf("Normalized vector:\n");
    printf("n = (%f, %f)\n", normalized.x, normalized.y);

    printf("\n-------------------------------------\n");
    //------------------------------------------------------


    //Print for mat3x3
    //------------------------------------------------------
    smf::Mat3 A = {{1, 2, 3,                            
                      4, 5, 6,                              
                      7, 8, 9}};                    
    smf::Mat3 B = {{9, 8, 7,    
                      6, 5, 4, 
                      3, 2, 1}};

    smf::Mat3 C = Mat3MultiplyMat3(A, B);
    
    printf("\nprint for matrix multiplied 3x3:\n\n");
    printf("%f %f %f\n", C.d[0], C.d[1], C.d[2]);
    printf("%f %f %f\n", C.d[3], C.d[4], C.d[5]);
    printf("%f %f %f\n\n", C.d[6], C.d[7], C.d[8]);
    printf("-------------------------------------\n\n");
    //------------------------------------------------------


    //Print for mat4x4
    //------------------------------------------------------
    smf::Mat4 a = {{
            1, 0, 0, 3,
            0, 1, 0, 0,
            8, 0, 1, 0,
            0, 2, 0, 1}};
    smf::Mat4 b = {{
            1, 0, 0, 1,
            0, 1, 5, 2,
            4, 0, 1, 3,
            0, 2, 0, 1}};
    
    smf::Mat4 c = Mat4MultiplyMat4(a, b);

    printf("print for matrix multiplied 4x4:\n\n");
    printf("%f %f %f %f\n", c.d[0], c.d[1], c.d[2], c.d[3]);
    printf("%f %f %f %f\n", c.d[4], c.d[5], c.d[6], c.d[7]);
    printf("%f %f %f %f\n", c.d[8], c.d[9], c.d[10], c.d[11]);
    printf("%f %f %f %f\n\n", c.d[12], c.d[13], c.d[14], c.d[15]);
    printf("-------------------------------------\n\n");
    //------------------------------------------------------


    //print for matrix translated
    //------------------------------------------------------
    smf::Mat3 m = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    printf("print for matrix translated:\n\n");
    printf("Original matrix:\n");
    Mat3PrintTranslate(m);

    smf::Mat3 translated = Mat3Translate(m, 2.0, 3.0);
    printf("\nMatrix after translation:\n");
    Mat3PrintTranslate(translated);
    printf("\n-------------------------------------\n\n");
    //------------------------------------------------------


    //print for matrix rotated
    //------------------------------------------------------
    smf::Mat3 f = {1, 0, 0, 0, 0, 0, 0, 0, 0};
    float angle = 90.0f;
    printf("Matrix before rotation:\n");
    Mat3Print(f);
    smf::Mat3 rotatedMatrix = printMat3Rotate(f, angle);

    printf("\nMatrix after rotation:\n");
    Mat3Print(rotatedMatrix);
    printf("\n-------------------------------------\n\n");
    //------------------------------------------------------

    //print for matrix scaled
    //------------------------------------------------------
    smf::Mat3 s = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    float sx = 2.0f;
    float sy = 2.0f;

    smf::Mat3 scaledMatrix = Mat3Scale(s, sx, sy);

    printf("print for matrix scaled:\n\n");
    printf("Scale sx: %f     Scale sy: %f \n\n", sx, sy);
    printf("Matrix before scaling:\n");
    Mat3Print(s);
    printf("\nMatrix after scaling:\n");
    Mat3Print(scaledMatrix);
    printf("\n-------------------------------------\n\n");
    //------------------------------------------------------


    return 0;
}