#include "CMatrix.h"


CMatrix::CMatrix():
	IMatrix(){
	
}
CMatrix::CMatrix(uint x, uint y):
	IMatrix(x,y){
	
}
CMatrix::CMatrix(const CMatrix &){
	
}
//CMatrix(const IMatrix &);

void CMatrix::set(int x , int y, MType value){
	get(x,y) = value;
}
CMatrix::MType & CMatrix::get(int x , int y){
	return matrix[y*width+x];
}
CMatrix::MType & CMatrix::get(int i){
	return matrix[i];
}


CMatrix CMatrix::operator*(const CMatrix &a){
	if(getWidth() == a.getHeight()){
		CMatrix m(a.getWidth(), getHeight());
		for(int x = 0 ; x < m.getWidth() ; x++){
			for(int y = 0 ; y < m.getHeight() ; y++){
				MType v= 0;
				for(int i = 0 ; i < getWidth() ; i++){
					v+=get(i,y)*a.get(x,i);
				}
				m.set(x,y,v);
			}
		}
		return m;
	}else{
		throw; //TODO
	}
}
CMatrix CMatrix::operator+(const CMatrix &a){
	if(getWidth() == a.getWidth() && getHeight() == a.getHeight()){
		CMatrix m(a);
		for(int i = 0 ; i < getCount() ; i++){
			m.get(i)+=get(i);
		}
		return m;
	}else{
		throw; //TODO
	}

}
CMatrix & CMatrix::operator=(const CMatrix &a){
	width = a.getWidth();
	height = a.getHeight();
	delete[] matrix;
	matrix = new MType[getCount()]();
	for(int i = 0 ; i < getCount() ; i++){
		get(i)=a.get(i);
	}
}
CMatrix & CMatrix::operator-(){
	for(int i = 0 ; i < getCount() ; i++){
		get(i)=-get(i);
	}
}
CMatrix CMatrix::operator/(const MType &a){
	for(int i = 0 ; i < getCount() ; i++){
		get(i)=get(i)/a;
	}
}
CMatrix CMatrix::operator+(const MType &a){
	CMatrix n(getWidth(),getHeight());
	for(int i = 0 ; i < getCount() ; i++){
		n.get(i)=get(i)+a;
	}
	return n;
}
