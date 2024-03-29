//---------------------------------------------------------------------
//---------------------------------------------------------------------
// The Nonlinear Game Engine (NGE) version 0.0.1 Beta
// (c) Mikael Fridenfalk
// All rights reserved
// Pending patent SE2330492-6
// The engine is a template for use in the course:
// Real-Time Graphics Programming for Games 1, 7.5 c, 2023
// Uppsala University, Sweden
// Other use requires a written permission from the copyright holder
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Lsys.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Lsys::Get_DrawCounter(){return mDrawCounter;}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Draw_RedCarpet(){
    //--------------------------------------------
    //--------------------------------------------
    double s = 100., s1 = .5*s, s2 = .1*s1;
    double y = 1.5;
    PRIM_STRUCT qd = {
        4,(TEX_IDX)(-1),PRIM_BLEND_OFF,PRIM_LIGHTS_OFF,(COLLKP)1,
        {
            {-s1,y,-s2},
            {-s1,y, s2},
            { s1,y, s2},
            { s1,y,-s2}},
        {255,0,0,255},
        {{0.,0.},{0.,1.},{1.,1.},{1.,0.}},
    };
    //--------------------------------------------
    //--------------------------------------------
    Add_Prim(qd);
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Draw_Link(){
    //--------------------------------------------
    //--------------------------------------------
    double p0[3], p1[3], p2[3], p3[3];
    //--------------------------------------------
    //--------------------------------------------
    glColor3ub(32,32,32);
    double deltaX = 0.;//### Z-fighting
    //double deltaX = .05 * (double(mDrawCounter % 23)/22.-0.5);
    double d = mLsys_16_9 ? 16./9. : 1.;
    glTranslated(deltaX,0.,0.);//"Rand" slide
    GetPos(p0);
    glTranslated(0.,mLength*mHScale,0.);//Move up
    GetPos(p1);
    glTranslated(0.,0.,d*mLength);//Move forward
    GetPos(p2);
    glTranslated(0.,-mLength*mHScale,0.);//Move down
    GetPos(p3);
    //--------------------------------------------
    glTranslated(-deltaX,0.,0.);//Restore slide
    //--------------------------------------------
    //--------------------------------------------
    double a = mTexTimeZoomON ? .7 + .3 * sin(.0001*double(SDL_GetTicks())+mDrawCounter) : 1;
    //UCHAR b = 256 * RandF();//###
    PRIM_STRUCT qd = {
        4,(TEX_IDX)0,PRIM_BLEND_ON,PRIM_LIGHTS_OFF,
        //(COLLKP)0,
        (COLLKP).1,//###
        {{0,0,0},{1,0,0},{1,1,0},{0,1,0}},
        //{255,b,255,b},//###
        {255,255,255,255},//###
        //{255,255,255,200},//###
        //{255,255,255,160},//###
        {{0,0},{a,0},{a,mHScale*a},{0,mHScale*a}},
     };
    //--------------------------------------------
    //--------------------------------------------
    For (i,3){
        qd.v[0][i] = p3[i];
        qd.v[1][i] = p0[i];
        qd.v[2][i] = p1[i];
        qd.v[3][i] = p2[i];
    }
    qd.texIdx = mDrawCounter % 3;
    //--------------------------------------------
    //--------------------------------------------
    Add_Prim(qd);
    //--------------------------------------------
    //--------------------------------------------
    
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Draw_Node(){
    //--------------------------------------------
    glPushMatrix();
    //--------------------------------------------
    glRotated(-90.,1.,0.,0.);
    Draw_Cyl(mRCyl,mHScale*3.);
    glTranslated(0.,0.,3.);
    //--------------------------------------------
    glPopMatrix();
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Draw_Cyl(double r, double height){
    //--------------------------------------------
    //--------------------------------------------
    double p0[3], p1[3], p2[3], p3[3];
    //--------------------------------------------
    //--------------------------------------------
    glPushMatrix();
    //--------------------------------------------
    //--------------------------------------------
    double x0 = r * cos(0.);
    double y0 = r * sin(0.);
    //--------------------------------------------
    //--------------------------------------------
    bool lowerCap = false;
    //--------------------------------------------
    //--------------------------------------------
    double X0[4][3];//Lower Cap
    double X3[4][3];//Upper Cap
    //--------------------------------------------
    //--------------------------------------------
    For (i,4){
        //----------------------------------------
        double alpha = double(i+1)*M_PI/2.;
        double x1 = r * cos(alpha);
        double y1 = r * sin(alpha);
        //----------------------------------------
        glTranslated(x0,y0,0.);
        GetPos(p0);
        //----------------------------------------
        glTranslated(x1-x0,y1-y0,0.);//Move up
        GetPos(p1);
        //----------------------------------------
        glTranslated(0,0,height);//Move forward
        GetPos(p2);
        //----------------------------------------
        glTranslated(x0-x1,y0-y1,0);//Move down
        GetPos(p3);
        glTranslated(-x0,-y0,-height);//Move down
        //----------------------------------------
        if (lowerCap) For (k,3) X0[i][k] = p0[k];
        For (k,3) X3[i][k] = p3[k];//Upper Cap
        //----------------------------------------
        PRIM_STRUCT qd = {
            4,(TEX_IDX)-1,PRIM_BLEND_OFF,PRIM_LIGHTS_OFF,(COLLKP)0,
            {{0,0,1},{1,0,1},{1,1,1},{0,1,1}},
            {5,5,5,255},
            {{0,0},{1,0},{1,1},{0,1}},
        };
        //----------------------------------------
        For (k,3){
            qd.v[0][k] = p3[k];
            qd.v[1][k] = p0[k];
            qd.v[2][k] = p1[k];
            qd.v[3][k] = p2[k];
        }
        //----------------------------------------
        Add_Prim(qd);
        //----------------------------------------
        x0 = x1; y0 = y1;
        //----------------------------------------
    }
    //--------------------------------------------
    //--------------------------------------------
    glPopMatrix();
    //--------------------------------------------
    //--------------------------------------------
    PRIM_STRUCT qd = {
        4,(TEX_IDX)-1,PRIM_BLEND_OFF,PRIM_LIGHTS_OFF,0,
        {{0,0,1},{1,0,1},{1,1,1},{0,1,1}},
        {5,5,5,255},
        {{0,0},{1,0},{1,1},{0,1}},
    };
    //--------------------------------------------
    //--------------------------------------------
    //                 Lower Cap
    //--------------------------------------------
    //--------------------------------------------
    if (lowerCap){
        //----------------------------------------
        For (k,3){
            qd.v[0][k] = X0[3][k];
            qd.v[1][k] = X0[2][k];
            qd.v[2][k] = X0[1][k];
            qd.v[3][k] = X0[0][k];
        }
        //----------------------------------------
        Add_Prim(qd);
        //----------------------------------------
    }
    //--------------------------------------------
    //--------------------------------------------
    //--------------------------------------------
    //--------------------------------------------
    //                 Upper Cap
    //--------------------------------------------
    //--------------------------------------------
    For (k,3){
        qd.v[0][k] = X3[3][k];
        qd.v[1][k] = X3[0][k];
        qd.v[2][k] = X3[1][k];
        qd.v[3][k] = X3[2][k];
    }
    //--------------------------------------------
    //--------------------------------------------
    Add_Prim(qd);
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                                Draw
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::F(){
    //--------------------------------------------
    Draw_Node();
    Draw_Link();
    mDrawCounter++;
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                              Rotation
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Roll(double alpha){glRotated(alpha,0,0,1);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Roll(){Roll(mAlpha);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::RevRoll(){Roll(-mAlpha);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Pitch(double alpha){glRotated(-alpha,1,0,0);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Pitch(){Pitch(mAlpha);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::RevPitch(){Pitch(-mAlpha);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Yaw(double alpha){glRotated(-alpha,0,1,0);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Yaw(){Yaw(mAlpha);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::RevYaw(){Yaw(-mAlpha);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                           Space-Time Warp
//---------------------------------------------------------------------
//---------------------------------------------------------------------
inline void Lsys::SpaceWarp(double * p){
    double alpha = double(mTimeWarp0)/5000.;
    double A = sin(alpha);
    double b = 10;
    p[0] += A*sin(b*p[0])*sin(b*p[1]);
    //p[0] += A*sin(b*p[0]);
    p[2] += A*sin(b*p[2]);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                       OpenGL Modelview Matrix
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::GetPos(double * p){
    double matrix[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
    p[0] = matrix[12];
    p[1] = matrix[13];
    p[2] = matrix[14];
    if (mTimeWarpFreezeModeON || mTimeWarpON) SpaceWarp(p);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------










//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                                Axiom
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::Lsys_Axiom1(){
    //-----------------------
    Prim_Clear();
    //-----------------------
    glPushMatrix();
    //-----------------------
    mDrawCounter = mTexAutoShiftON ? SDL_GetTicks() >> 10 : 0;
    //-----------------------
    mRec = 2;
    mAlpha = 90.;// + 2.*sin(.0002*double(SDL_GetTicks()));//###
    glRotated(90.,0.,1.,0.);
    //-----------------------
    mRandSeed = 0;//###
    //-----------------------
    Draw_Node();
    //-----------------------
    FX1(0); RevYaw(); FX1(0); RevYaw(); FX1(0); RevYaw(); FX1(0);
    //-----------------------
    //FX2(0); RevYaw(); FX2(0); RevYaw(); FX2(0); RevYaw(); FX2(0);
    //-----------------------
    //A2.1: Implement void Lsys::FX3(int depth)
    //FX3(0); RevYaw(); FX3(0); RevYaw(); FX3(0); RevYaw(); FX3(0);
    //-----------------------
    //FX4(0); RevYaw(); FX4(0); RevYaw(); FX4(0); RevYaw(); FX4(0);
    //-----------------------
    glPopMatrix();
    //-----------------------
}




void Lsys::Lsys_Axiom3() {
    Prim_Clear();
    glPushMatrix(); /* => */ int stackLevel = 1;
    mRec = 2;
    mAlpha = 45.;
    glRotated(90., 0., 1., 0.);
    mRandSeed = mDrawCounter = 0;
    Draw_Node();
    string x = "F-F-F-F", rule = "]]F[[-FF";
    For(i, mRec) x = regex_replace(x, regex("F"), rule);
    For(i, x.length()) {
        switch (x[i]) {
        case 'F': F(); break;
        case '+': Yaw(); break;
        case '-': RevYaw(); break;
        case '[': glPushMatrix(); stackLevel++; break;
        case ']': if (stackLevel > 0) { glPopMatrix(); stackLevel--; } break;
        }
    }
    while (stackLevel > 0) { glPopMatrix(); stackLevel--; }
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                        M1: F->F−F+F+FF−F−F+F
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::FX1(int depth){
    if (depth == mRec){
        F();
        return;
    }
    FX1(depth+1);
    RevYaw();
    FX1(depth+1);
    Yaw();
    FX1(depth+1);
    Yaw();
    FX1(depth+1);
    FX1(depth+1);
    RevYaw();
    FX1(depth+1);
    RevYaw();
    FX1(depth+1);
    Yaw();
    FX1(depth+1);

   /* FX1(depth + 1);
    RevYaw(); mLength *= .5;
    FX1(depth + 1);
    Yaw(); mLength *= 2.;
    FX1(depth + 1);
    Yaw(); mLength *= 2.;
    FX1(depth + 1);
    FX1(depth + 1);
    RevYaw(); mLength *= .5;
    FX1(depth + 1);
    RevYaw(); mLength *= .5;
    FX1(depth + 1);
    Yaw(); mLength *= 2.;
    FX1(depth + 1);*/
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                         M2: F->FF−F−F−F−FF
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::FX2(int depth){
    if (depth == mRec){
        F();
        return;
    }
    FX2(depth+1);
    FX2(depth+1);
    RevYaw();
    FX2(depth+1);
    RevYaw();
    FX2(depth+1);
    RevYaw();
    FX2(depth+1);
    RevYaw();
    FX2(depth+1);
    FX2(depth+1);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                          M3: F->F−F+F−F−F
//---------------------------------------------------------------------
//---------------------------------------------------------------------
SOLUTION void Lsys::FX3(int depth){
    //--------------------------------------------
    //--------------------------------------------
    if (depth == mRec){
        F();
        return;
    }
    //--------------------------------------------
    //--------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//[ A2.1
    FX3(depth + 1);
    RevYaw();
    FX3(depth + 1);
    Yaw();
    FX3(depth + 1);
    RevYaw();
    FX3(depth + 1);
    RevYaw();
    FX3(depth + 1);

    //--------------------------------------------
    //--------------------------------------------
    
    //--------------------------------------------
    //--------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//] A2.1
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                                 M4
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Lsys::FX4(int depth){
    if (depth == mRec){
        F();
        return;
    }
    FX4(depth+1);
    RevRoll();
    FX4(depth+1);
    Yaw();
    FX4(depth+1);
    Yaw();
    FX4(depth+1);
    FX4(depth+1);
    RevPitch();
    FX4(depth+1);
    RevYaw();
    FX4(depth+1);
    Yaw();
    FX4(depth+1);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
