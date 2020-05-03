#include "pch.h"
#include "BgraBitmapPixelIterator.h"

Rendering::BgraBitmapPixelIterator::BgraBitmapPixelIterator(uint8_t* pixelStart)
	:pixelStart(pixelStart)
{
}

uint8_t Rendering::BgraBitmapPixelIterator::R()
{
	return *(pixelStart + 2);
}

uint8_t Rendering::BgraBitmapPixelIterator::G()
{
	return *(pixelStart + 1);
}

uint8_t Rendering::BgraBitmapPixelIterator::B()
{
	return *pixelStart;
}

uint8_t Rendering::BgraBitmapPixelIterator::A()
{
	return *(pixelStart + 3);
}

void Rendering::BgraBitmapPixelIterator::R(uint8_t r)
{
	auto rPx = pixelStart + 2;
	*rPx = r;
}

void Rendering::BgraBitmapPixelIterator::G(uint8_t g)
{
	auto gPx = pixelStart + 1;
	*gPx = g;
}

void Rendering::BgraBitmapPixelIterator::B(uint8_t b)
{
	*pixelStart = b;
}

void Rendering::BgraBitmapPixelIterator::A(uint8_t a)
{
	auto aPx = pixelStart + 3;
	*aPx = a;
}

Rendering::BgraBitmapPixelIterator Rendering::BgraBitmapPixelIterator::operator++(int) {
	pixelStart += 4;
	return *this;
}

Rendering::BgraBitmapPixelIterator& Rendering::BgraBitmapPixelIterator::operator*()
{
	return *this;
}

Rendering::BgraBitmapPixelIterator* Rendering::BgraBitmapPixelIterator::operator->()
{
	return this;
}

bool Rendering::BgraBitmapPixelIterator::operator==(const BgraBitmapPixelIterator& rhs)
{
	return this->pixelStart == rhs.pixelStart;
}

bool Rendering::BgraBitmapPixelIterator::operator!=(const BgraBitmapPixelIterator& rhs)
{
	return this->pixelStart != rhs.pixelStart;
}

Rendering::BgraBitmapPixelIterator Rendering::BgraBitmapPixelIterator::operator++() {
	auto i = *this;
	pixelStart += 4;
	return i;
}