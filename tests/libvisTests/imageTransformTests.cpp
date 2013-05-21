#include <gtest/gtest.h>
#include <Image.h>
#include <cstring>
#include <GImage.h>
#include <GImageTransform.h>
#include <ImageTransform.h>
#include <cuda_runtime.h>
#include "testFunctions.h"

TEST(ImageTransformations,ImageStretch_GPU){
	const int w = 800, h=600,s=5;
	GImage first(w,h);
	randomize(first.data(),first.size());
	GImageTransform transform(&first);
	transform.stretch(s);
	ASSERT_EQ(w+2*s,first.width());
	ASSERT_EQ(h+2*s,first.height());
	ASSERT_EQ(3*(w+2*s)*(h+2*s),first.size());
//	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}

TEST(ImageTransformations,ImageStretch_CPU){
	const int w = 800, h=600,s=5;
	Image first(w,h);
	randomizeU(first.data(),first.size());
	ImageTransform transform(&first);
	transform.stretch(s);
	ASSERT_EQ(w+2*s,first.width());
	ASSERT_EQ(h+2*s,first.height());
	ASSERT_EQ(3*(w+2*s)*(h+2*s),first.size());
	//	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}

TEST(ImageTransformations,ImageStretch_compare_CPU_and_GPU){
	const int w = 800, h=600,s=5;
	Image first(w,h);
	randomizeU(first.data(),first.size());
	ImageTransform transform(&first);
	GImage second(first);
	GImageTransform transform2(&second);
	transform2.stretch(s);
	transform.stretch(s);
	ASSERT_EQ(second.width(),first.width());
	ASSERT_EQ(second.height(),first.height());
	ASSERT_EQ(second.size(),first.size());
//	printPix(second.constData(),second.width(),second.height());
	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}
TEST(ImageTransformations,ImageCut_CPU){
	const int w = 800, h=600,s=5;
	Image first(w,h);
	randomizeU(first.data(),first.size());
	Image second(first);
	ImageTransform transform(&second);
	transform.stretch(s);
	transform.stretch(-s);
	ASSERT_EQ(second.width(),first.width());
	ASSERT_EQ(second.height(),first.height());
	ASSERT_EQ(second.size(),first.size());
	//	printPix(second.constData(),second.width(),second.height());
	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}

TEST(ImageTransformations,ImageCut_GPU){
	const int w = 800, h=600,s=5;
	GImage first(w,h);
	randomize(first.data(),first.size());
	GImage second(first);
	GImageTransform transform(&second);
	transform.stretch(s);
	transform.stretch(-s);
	ASSERT_EQ(second.width(),first.width());
	ASSERT_EQ(second.height(),first.height());
	ASSERT_EQ(second.size(),first.size());
	//	printPix(second.constData(),second.width(),second.height());
	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}

TEST(ImageTransformations,ImageCut_compare_CPU_and_GPU){
	const int w = 800, h=600,s=5;
	Image first(w,h);
	ImageTransform transform2(&first);
	randomizeU(first.data(),first.size());
	GImage second(first);
	GImageTransform transform(&second);
	transform.stretch(s);
	transform.stretch(-s);
	transform2.stretch(s);
	transform2.stretch(-s);
	ASSERT_EQ(second.width(),first.width());
	ASSERT_EQ(second.height(),first.height());
	ASSERT_EQ(second.size(),first.size());
	//	printPix(second.constData(),second.width(),second.height());
	ASSERT_EQ(0,memcmp(first.constData(),second.constData(),first.size()));
}
