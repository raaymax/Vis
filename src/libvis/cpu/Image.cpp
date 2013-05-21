#include "Image.h"
#include <cstring>


const unsigned char* Image::constData() const
{
	return (const unsigned char*)data_.get();
}

unsigned char* Image::data()
{
	return data_.get();
}

unsigned int Image::size() const
{
	return size_;
}

unsigned int Image::height() const
{
	return height_;
}

unsigned int Image::width() const
{
	return width_;
}

Image::Image():
	width_(0),
	height_(0),
	size_(0),
	data_(NULL)
{

}

Image::Image(unsigned int w, unsigned int h):
	width_(w),
	height_(h),
	size_(w*h*3),
	data_(new unsigned char[w*h*3]())
{
	
}
Image::Image(const Image& other):
	width_(other.width()),
	height_(other.height()),
	size_(other.size()),
	data_(new unsigned char[other.size()]())
{
	memcpy(data(),other.constData(),size_);
}
Image::Image(const IImage& other):
	width_(other.width()),
	height_(other.height()),
	size_(other.size()),
	data_(new unsigned char[other.size()]())
{
	memcpy(data(),other.constData(),size_);
}

Image::~Image()
{
	//nothing
}

Image& Image::operator=(const Image& other)
{
	width_ = other.width();
	height_ = other.height();
	size_ = other.size();
	data_.reset(new unsigned char[size_]);
	memcpy(data(),other.constData(),size_);
    return *this;
}

bool Image::operator==(const Image& other) const
{
	if(width() != other.width())return false;
	if(height() != other.height())return false;
	if(memcmp(constData(),other.constData(),size())!=0)return false;
	return true;
}

