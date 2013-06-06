#ifndef CUDA_MATRIX_H_
#define CUDA_MATRIX_H_

#include <stdio.h>

#ifdef DEBUG
#define debug(asd) printf("%s:%d %s # %s\n",__FILE__,__LINE__,__FUNCTION__,asd)
#else
#define debug(asd)
#endif

typedef unsigned int uint;
typedef unsigned char uchar;
typedef enum { CPU , GPU , NONE} MatrixType;
typedef enum
{
	H2H          =   0,      /**< Host   -> Host */
	H2D        =   1,      /**< Host   -> Device */
	D2H        =   2,      /**< Device -> Host */
	D2D      =   3,      /**< Device -> Device */
} cudaMCKind;

struct Matrix{
	uint width;
	uint height;
	uint size;
	uint count;
	float * data;
	MatrixType type;
};

Matrix matrix_create(uint w, uint h , MatrixType type = GPU);
void matrix_destroy(Matrix & A);
void matrix_randomize(Matrix & m);
Matrix matrix_copy(const Matrix & m, cudaMCKind kind);
Matrix matrix_copy(const Matrix & m, MatrixType type);
void matrix_print(const Matrix &c);
Matrix matrix_convolution(const Matrix & A ,const Matrix &f);
void matrix_divide(Matrix & A , float val);
void matrix_normalize(Matrix & A);
float matrix_sum(const Matrix &A);
Matrix matrix_resize(const Matrix &A , uint width , uint height);
bool matrix_compare(const Matrix &A ,const Matrix &B);


#endif
