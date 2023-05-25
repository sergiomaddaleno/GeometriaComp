
/*
    Autor
    Subject
    Brief
*/

#ifndef __MATH_LIB_H__
#define __MATH_LIB_H__ 1

namespace smf{

    struct Vec2{float x, y;}; // x = longitud horizontal, y = longitud vertical
    struct Vec3{float x, y, z;}; // x = longitud horizontal, y = longitud vertical
    struct Vec4{float x, y, z, w;};

    struct Mat2{float d[4];};
    struct Mat3{float d[9];};
    struct Mat4{float d[16];};

    //Add vectors
    Vec2 Vec2AddVec2(Vec2 v, Vec2 w); //suma 2 vectores de 2 dimensiones
    Vec3 Vec3AddVec3(Vec3 v, Vec3 w); //suma 2 vectores de 3 dimensiones
    Vec4 Vec4AddVec4(Vec4 v, Vec4 w); //suma 2 vectores de 4 dimensiones

    //Subtract vectors
    Vec2 Vec2SubtractVec2(Vec2 v, Vec2 w); //resta 2 vectores de 2 dimensiones
    Vec3 Vec3SubtractVec3(Vec3 v, Vec3 w);
    Vec4 Vec4SubtractVec4(Vec4 v, Vec4 w);

    //Multiply Vector Scalar
    Vec2 Vec2MultiplyVec2(Vec2 v, Vec2 w);
    Vec3 Vec3MultiplyVec3(Vec3 v, Vec3 w);
    Vec4 Vec4MultiplyVec4(Vec4 v, Vec4 w);

    //Division Vector Scalar
    Vec2 Vec2DivideVec2(Vec2 v, Vec2 w);
    Vec3 Vec3DivideVec3(Vec3 v, Vec3 w);
    Vec4 Vec4DivideVec4(Vec4 v, Vec4 w);

    //Magnitude Vector (length)
    float Vec2Magnitude(Vec2 v, Vec2 w); //resta 2 vectores de 2 dimensiones
    float Vec3Magnitude(Vec3 v, Vec3 w);
    float Vec4Magnitude(Vec4 v, Vec4 w);

    //print Vectors
    void Vec2Print(Vec2 v, Vec2 w);
    void Vec3Print(Vec3 v, Vec3 w);
    void Vec4Print(Vec4 v, Vec4 w);

    //Normalize Vector
    Vec2 Vec2Normalize(Vec2 v, Vec2 w); //normaliza 2 vectores de 2 dimensiones
    Vec3 Vec3Normalize(Vec3 v, Vec3 w);
    Vec4 Vec4Normalize(Vec4 v, Vec4 w);

    //Perpendicular
    Vec2 Vec2Perpendicular(Vec2 v, Vec2 w);

    void Mat3Print(Mat3 m);

    //Add matrix
    Mat2 Mat2AddMat2(Mat2 v, Mat2 w); //suma 2 matrices de 2x2
    Mat3 Mat3AddMat3(Mat3 v, Mat3 w);
    Mat4 Mat4AddMat4(Mat4 v, Mat4 w);

    //Subtract matrix
    Mat2 Mat2SubtractMat2(Mat2 v, Mat2 w);
    Mat3 Mat3SubtractMat3(Mat3 v, Mat3 w);
    Mat4 Mat4SubtractMat4(Mat4 v, Mat4 w);

    //multiply matrix
    Mat2 Mat2MultiplyMat2(Mat2 v, Mat2 w);
    Mat3 Mat3MultiplyMat3(Mat3 v, Mat3 w);
    Mat4 Mat4MultiplyMat4(Mat4 v, Mat4 w);

    //matrix Translate 2D
    Mat3 Mat3Translate(Mat3 m, float tx, float ty); //traslada 1 matriz de 3x3, tx unidades hor, ty unidades vert
    void Mat3PrintTranslate(Mat3 m);

    //matrix Rotate 2D
    Mat3 Mat3Rotate(Mat3 m, float angle); //rota 1 matriz de 3x3, angle grados
    Mat3 printMat3Rotate(Mat3 m, float angle);

    //matrix Scale 2D
    Mat3 Mat3Scale(Mat3 m, float sx, float sy); //multiplica 1 matriz de 3x3, sx hor, sy vert

    float Mat2Determinant(Mat2 m);
    float Mat3Determinant(Mat3 m);
    Mat2 Mat2Inverse(Mat2 m);
    Mat3 Mat3Inverse(Mat3 m);
}

#endif //__MATH_LIB_H__
