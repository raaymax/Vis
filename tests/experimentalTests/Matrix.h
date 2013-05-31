#ifndef CUDA_MATRIX_H_
#define CUDA_MATRIX_H_

typedef unsigned int uint;
typedef enum { CPU , GPU} MatrixType;

struct Matrix{
	uint width;
	uint height;
	uint size;
	float * data;
	MatrixType type;
};

Matrix create(uint w, uint h , MatrixType type = GPU);
void randomize(Matrix & m);
Matrix copy(const Matrix & m, cudaMemcpyKind kind);
void print(const Matrix &c);

#endif
