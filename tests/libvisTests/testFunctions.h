#ifndef TESTFUNCTIONS_H_
#define TESTFUNCTIONS_H_

#include <IImage.h>
#include <cstdio>

void randomize(float * gpu , int size);
void randomizeU(uchar * cpu , int size);

void printU(const uchar * data , int size);
void printPix(const uchar *data , int width , int height);
#endif
