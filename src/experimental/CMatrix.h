#ifndef CMATRIX_H
#define CMATRIX_H

#include "IMatrix.h"


class CMatrix : public IMatrix<uchar>
{
public:
	CMatrix();
	CMatrix(uint x, uint y);
	CMatrix(const CMatrix &);
	//CMatrix(const IMatrix &);
	
	virtual void set(int x , int y, MType value);
	virtual MType & get(int x , int y);
	virtual const MType & get(int x , int y)const{return get(x,y);};
	virtual MType & get(int i);
	virtual const MType & get(int i)const{return get(i);};
	virtual CMatrix operator*(const CMatrix &);
	virtual CMatrix operator+(const CMatrix &);
	virtual CMatrix operator+(const MType &);
	virtual CMatrix & operator=(const CMatrix &);
	virtual CMatrix & operator-();
	virtual CMatrix operator/(const MType &);
	
private:
	
};

#endif // CMATRIX_H
