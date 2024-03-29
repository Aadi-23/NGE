//---------------------------------------------------------------------
//---------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Prim.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
class Lsys : protected Prim {
protected:
    //-------------------------------------------------------
    int     Get_DrawCounter();
    //-------------------------------------------------------
private:
    //-------------------------------------------------------
    void    Draw_RedCarpet();
    
    void    Draw_Cyl(double r, double height);

protected:
    void    Draw_Link();
    void    Draw_Node();
    void    F();
    //-------------------------------------------------------
    void    Roll(double alpha);
    void    Roll();
    void    RevRoll();
    void    Pitch(double alpha);
    void    Pitch();
    void    RevPitch();
    void    Yaw(double alpha);
    void    Yaw();
    void    RevYaw();
    //-------------------------------------------------------
    void    SpaceWarp(double * p);
    void    GetPos(double * p);
    //-------------------------------------------------------
protected:
    //-------------------------------------------------------
    void    Lsys_Axiom1();
    void    Lsys_Axiom2();
    void    Lsys_Axiom3();
    //-------------------------------------------------------
private:
    void    FX1(int depth);
    void    FX2(int depth);
    void    FX3(int depth);
    void    FX4(int depth);
    //-------------------------------------------------------
   
    double  mAlpha = 90.;
    double  mHScale = 1.;
    //-------------------------------------------------------
protected:
    double  mLength = 3.;
    int     mRec = 3;

    bool    mLsys_16_9 = true;
    int     mDrawCounter = 0;
    //-------------------------------------------------------
private:
    double  mRCyl = .15;
    //-------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
