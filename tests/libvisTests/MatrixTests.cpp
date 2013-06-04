#include <gtest/gtest.h>
#include <Image.h>
#include <cstring>


class TestMatrix : public ::testing::Test{
public:
	typedef enum{SMALL,BIG} Size;
protected:
	
	void SetUp(){
		test = matrix_create(3,3,CPU);
		test.data[1] = 0.5;
		test.data[5] = 0.5;
		test.data[4] = 1.0;
		test.data[3] = 0.5;
		test.data[7] = 0.5;
		gtest = matrix_copy(test,GPU);
	}
	void TearDown(){
		matrix_destroy(c);
		matrix_destroy(g);
		matrix_destroy(cc);
		matrix_destroy(gg);
		matrix_destroy(test);
		matrix_destroy(gtest);
	}
	void create(uint w,uint h){
		c = matrix_create(w,h,CPU);
		matrix_randomize(c);
		g = matrix_copy(c,GPU);
	}
	void create(Size s){
		if(s == BIG){
			create(257,257);
		}else{
			create(20,20);
		}
	}
	
	void check(Size s ,const Matrix & A,const Matrix & B){
		Matrix dc = matrix_copy(A,CPU);
		Matrix dg = matrix_copy(B,CPU);
		bool r = matrix_compare(dc,dg);
		if(r==false && s==SMALL){
			matrix_print(dc);
			matrix_print(dg);
		}
		matrix_destroy(dc);
		matrix_destroy(dg);
		ASSERT_TRUE(r);
	}
	
	void testCopying(Size s){
		create(s);
		Matrix cg = matrix_copy(g,CPU);
		ASSERT_TRUE(matrix_compare(c,cg));
		matrix_destroy(cg);
	}
	
	void testResizing(Size s){
		create(s);
		cc = matrix_resize(c,c.width+4,c.height+4);
		gg = matrix_resize(g,g.width+4,g.height+4);
		check(s,cc,gg);
		matrix_destroy(c);
		matrix_destroy(g);
		c = matrix_resize(cc,cc.width-4,cc.height-4);
		g = matrix_resize(gg,gg.width-4,gg.height-4);
		check(s,c,g);

	}
	
	void testDividing(Size s){
		create(s);
		matrix_divide(c,2);
		matrix_divide(g,2);
		check(s,c,g);
	}
	
	void testConvolution(Size s){
		create(s);
		check(s,c,g);
		cc = matrix_convolution(c,test);
		gg = matrix_convolution(g,gtest);
		check(s,cc,gg);		
	}
	Matrix cc,gg;
	Matrix c;
	Matrix g; 
	Matrix test;
	Matrix gtest;
};
class MatrixTest : public TestMatrix,
				   public ::testing::WithParamInterface<TestMatrix::Size>  {
	
};


TEST_P(MatrixTest,Copying){
	testCopying(GetParam());
}
TEST_P(MatrixTest,Resizing){
	testResizing(GetParam());
}
TEST_P(MatrixTest,Dividing){
	testDividing(GetParam());
}
TEST_P(MatrixTest,Convolution){
	testConvolution(GetParam());
}

INSTANTIATE_TEST_CASE_P(I1,MatrixTest,::testing::Values(TestMatrix::BIG, TestMatrix::SMALL));

