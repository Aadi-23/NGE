//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Common.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
Common::Common(){
    mQuadratic = gluNewQuadric();
    gluQuadricNormals(mQuadratic, GLU_SMOOTH);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
Common::~Common(){
    gluDeleteQuadric(mQuadratic);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#ifdef _WIN64
int Common::sW = 3840/4;
int Common::sH = 2160/4;

#elif __APPLE__
int Common::sW = 3840;
int Common::sH = 2160;

#endif
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Common::Rand(){
    //C Programming Language, 2nd ed., Kernighan and Ritchie, 1988
    mRandSeed = mRandSeed * 1103515245 + 12345;
    return UINT(mRandSeed/65536) % 32768;//return 0-32767
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
double Common::RandF(){
    return double(Rand())/32768.;//return [0,1[
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
