#include <gtest/gtest.h>
#include <Image.h>
#include <cstring>
#include <GImage.h>
#include <cuda_runtime.h>
#include "testFunctions.h"


TEST(ImageCreation,NullImage_CPU){
	Image nullImg;
	ASSERT_EQ(NULL,nullImg.constData());
	ASSERT_EQ(0,nullImg.width());
	ASSERT_EQ(0,nullImg.height());
	ASSERT_EQ(0,nullImg.size());
}

TEST(ImageCreation,BlackImage_CPU){
	const int w = 800, h=600;
	Image blackImg(w,h);
	uchar * tab = new uchar[w*h*3]();
	ASSERT_EQ(0,memcmp(tab,blackImg.constData(),blackImg.size()));
	ASSERT_EQ(w,blackImg.width());
	ASSERT_EQ(h,blackImg.height());
	ASSERT_EQ(w*h*3,blackImg.size());
}

TEST(ImageCreation,NullImage_GPU){
	GImage nullImg;
	ASSERT_EQ(NULL,nullImg.constData());
	ASSERT_EQ(0,nullImg.width());
	ASSERT_EQ(0,nullImg.height());
	ASSERT_EQ(0,nullImg.size());
}

TEST(ImageCreation,BlackImage_GPU){
	const int w = 800, h=600;
	GImage blackImg(w,h);
	uchar * tab = new uchar[w*h*3]();
	ASSERT_EQ(w,blackImg.width());
	ASSERT_EQ(h,blackImg.height());
	ASSERT_EQ(w*h*3,blackImg.size());
	ASSERT_EQ(0,memcmp(tab,blackImg.constData(),blackImg.size()));
}
TEST(ImageCreation,ImageCopy_GPU){
	const int w = 800, h=600;
	GImage first(w,h);
	randomize(first.data(),first.size());
	GImage second(first);
	ASSERT_EQ(first.width(),second.width());
	ASSERT_EQ(first.height(),second.height());
	ASSERT_EQ(first.size(),second.size());
	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}
TEST(ImageCreation,ImageCopy_CPU){
	const int w = 800, h=600;
	Image first(w,h);
	for(int i = 0 ; i < first.size() ; i ++){
		first.data()[i] = i%256;
	}
	Image second(first);
	ASSERT_EQ(first.width(),second.width());
	ASSERT_EQ(first.height(),second.height());
	ASSERT_EQ(first.size(),second.size());
	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}

TEST(ImageCreation,ImageCopy_CPU_to_GPU){
	const int w = 800, h=600;
	Image first(w,h);
	for(int i = 0 ; i < first.size() ; i ++){
		first.data()[i] = i%256;
	}
	GImage second(first);
	ASSERT_EQ(first.width(),second.width());
	ASSERT_EQ(first.height(),second.height());
	ASSERT_EQ(first.size(),second.size());
	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}

TEST(ImageCreation,ImageCopy_GPU_to_CPU){
	const int w = 800, h=600;
	GImage first(w,h);
	randomize(first.data(),first.size());
	Image second(first);
	ASSERT_EQ(first.width(),second.width());
	ASSERT_EQ(first.height(),second.height());
	ASSERT_EQ(first.size(),second.size());
	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}

