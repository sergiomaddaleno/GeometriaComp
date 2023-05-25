//                                                                                         
//                       //////////////                                      ffffffffffffffff       
//                      /::::://:::::/                                      f::::::::::::::::f      
//                     /::::://:::::/                                      f::::::::::::::::::f     
//                    /::::://:::::/                                       f::::::fffffff:::::f     
//                   /::::://:::::/  ssssssssss      mmmmmmm    mmmmmmm    f:::::f       ffffff     
//                  /::::://:::::/ ss::::::::::s   mm:::::::m  m:::::::mm  f:::::f                  
//                 /::::://:::::/ss:::::::::::::s m::::::::::mm::::::::::mf:::::::ffffff            
//                /::::://:::::/ s::::::ssss:::::sm::::::::::::::::::::::mf::::::::::::f            
//               /::::://:::::/   s:::::s  ssssss m:::::mmm::::::mmm:::::mf::::::::::::f            
//              /::::://:::::/      s::::::s      m::::m   m::::m   m::::mf:::::::ffffff            
//             /::::://:::::/          s::::::s   m::::m   m::::m   m::::m f:::::f                  
//            /::::://:::::/     ssssss   s:::::s m::::m   m::::m   m::::m f:::::f                  
//           /::::://:::::/      s:::::ssss::::::sm::::m   m::::m   m::::mf:::::::f                 
//          /::::://:::::/       s::::::::::::::s m::::m   m::::m   m::::mf:::::::f                 
//         /::::://:::::/         s:::::::::::ss  m::::m   m::::m   m::::mf:::::::f                 
//        //////////////           sssssssssss    mmmmmm   mmmmmm   mmmmmmfffffffff                 
//
#include <math.h>
#include <stdio.h>

namespace smf{

    struct Vec2{float x, y;};
    struct Vec3{float x, y, z;};
    struct Vec4{float x, y, z, w;};

    struct Mat2{float d[4];};
    struct Mat3{float d[9];};
    struct Mat4{float d[16];};

    

    //Add Vectors
    Vec2 Vec2AddVec2(Vec2 v, Vec2 w){return{ v.x + w.x, v.y + w.y};}

    Vec3 Vec3AddVec3(Vec3 v, Vec3 w){return{ v.x + w.x, v.y + w.y, v.z + w.z};}

    Vec4 Vec4AddVec4(Vec4 v, Vec4 w){return{ v.x + w.x, v.y + w.y, v.z + w.z, q.x + q.y};}

    //Subtract Vectors
    Vec2 Vec2SubtractVec2(Vec2 v, Vec2 w){return{ v.x - w.x, v.y - w.y};}

    Vec3 Vec3SubtractVec3(Vec3 v, Vec3 w){return{ v.x - w.x, v.y - w.y, v.z - w.z};}

    Vec4 Vec4SubtractVec4(Vec4 v, Vec4 w){return{ v.x - w.x, v.y - w.y, v.z - w.z, q.x - q.y};}

    //----------------------------------------------------------------------------------------------------------------------------------

    //Multiply Vector Scalar
    Vec2 Vez2MultiplyVec2(Vec2 v, Vec2 w){return{v.x * w.x, v.y * w.y};}

    Vec3 Vez3MultiplyVec3(Vec3 v, Vec3 w){return{v.x * w.x, v.y * w.y, v.z * w.z};}

    Vec4 Vez4MultiplyVec4(Vec4 v, Vec4 w){return{v.x * w.x, v.y * w.y, v.z * w.z, q.x * q.y};}

    //Division Vector Scalar
    Vec2 Vez2DivideVec2(Vec2 v, Vec2 w){return{v.x / w.x, v.y / w.y};}

    Vec3 Vez3DivideVec3(Vec3 v, Vec3 w){return{v.x / w.x, v.y / w.y, v.z / w.z};}

    Vec4 Vez4DivideVec4(Vec4 v, Vec4 w){return{v.x / w.x, v.y / w.y, v.z / w.z, q.x / q.y};}

    //----------------------------------------------------------------------------------------------------------------------------------
    
    //Magnitude Vector (length)
    float Vec2Magnitude(Vec2 v){
        float m=sqrt((v.x*v.x)+(w.y*w.y));
        return m;
    }
    float Vec2Magnitude(Vec3 v){
        float m=sqrt((v.x*v.x)+(w.y*w.y)+(v.z*v.z));
        return m;
    }
    float Vec2Magnitude(Vec4 v){
        float m=sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z)+(v.q*v.q));
        return m;
    }

    //print Vec2
    void Vec2Print(Vec2 v){
        printf("%f %f\n", v.x, v.y);}

    void Vec3Print(Vec3 v){
        printf("%f %f %f\n", v.x, v.y, v.z);}

    void Vec4Print(Vec4 v){
        printf("%f %f %f %f\n", v.x, v.y, v.z, v.q);}

    //----------------------------------------------------------------------------------------------------------------------------------
    
    //Normalize Vector
    float Vec2NormalizeVec2(Vec2 v){
        float q=(v.x, w.y * v.x, w.y) + (v.x, w.y * v.x, w.y)
        return q;
    }

    float Vec3NormalizeVec3(Vec2 v){
        float q=(v.x, w.y * v.x, w.y) + (v.x, w.y * v.x, w.y)
        return q;
    }

    float Vec3NormalizeVec3(Vec2 v){
        float q=(v.x, w.y * v.x, w.y) + (v.x, w.y * v.x, w.y)
        return q;
    }
    
    //Check if normalized
    float Vec2CheckNormalizeVec2(Vec2 v){
        float q=(v.x, w.y * v.x, w.y) + (v.x, w.y * v.x, w.y)
        return q;
    }

    float Vec3CheckNormalizeVec3(Vec2 v){
        float q=(v.x, w.y * v.x, w.y) + (v.x, w.y * v.x, w.y)
        return q;
    }

    float Vec3CheckNormalizeVec3(Vec2 v){
        float q=(v.x, w.y * v.x, w.y) + (v.x, w.y * v.x, w.y)
        return q;
    }

    //----------------------------------------------------------------------------------------------------------------------------------

    //Perpendicular 2D vector (method 1). To find the perpendicular of (3,4), 
    //we swap the components and negate one of them: So the perpendicular vector of (3, 4) is (-4, 3).

    float Vec2PerpendicularVec2(Vec2 v){}
    float Vec3PerpendicularVec3(Vec2 v){}
    float Vec4PerpendicularVec4(Vec2 v){}

    //Perpendicular 2D vector (method 2). Another method to calculate the perpendicular
    //of a 2D vector is to rotate the original vector by 90 degrees counterclockwise. 
    //This can be done by multiplying the vector by the 2x2 rotation matrix: [ 0 -1 ] [ 1 0 ]

    float Vec2Perpendicular2MethodVec2(Vec2 v){}
    float Vec3Perpendicular2MethodVec3(Vec2 v){}
    float Vec4Perpendicular2MethodVec4(Vec2 v){}

    //----------------------------------------------------------------------------------------------------------------------------------

    //Method to initialize
    float Vec2InitializeVec2(Vec2 v){}
    float Vec3InitializeVec3(Vec2 v){}
    float Vec4InitializeVec4(Vec2 v){}
}

int main(int argc, char** argv){

    

    return 0;
}