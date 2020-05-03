#pragma once
namespace Rendering {
	class BgraBitmapPixelIterator
	{
	public:
		BgraBitmapPixelIterator(uint8_t* pixelStart);
		uint8_t R();
		uint8_t G();
		uint8_t B();
		uint8_t A();

		void R(uint8_t r);
		void G(uint8_t g);
		void B(uint8_t b);
		void A(uint8_t a);

		BgraBitmapPixelIterator operator++();
		BgraBitmapPixelIterator operator++(int);
		BgraBitmapPixelIterator& operator*();
		BgraBitmapPixelIterator* operator->();
		bool operator==(const BgraBitmapPixelIterator& rhs);
		bool operator!=(const BgraBitmapPixelIterator& rhs);
	private:
		uint8_t* pixelStart;
	};
}