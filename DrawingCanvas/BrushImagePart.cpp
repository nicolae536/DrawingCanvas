#include "pch.h"
#include "BrushImagePart.h"

Rendering::BrushImagePart::BrushImagePart()
	:pixelFormat(winrt::Windows::Graphics::Imaging::BitmapPixelFormat::Bgra8),
	alphaMode(winrt::Windows::Graphics::Imaging::BitmapAlphaMode::Straight),
	activeBitmap({ nullptr })
{
}

Rendering::BrushImagePart::BrushImagePart(
	winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& originBitmap,
	winrt::Windows::Graphics::Imaging::BitmapPixelFormat const& pixelFormat,
	winrt::Windows::Graphics::Imaging::BitmapAlphaMode const& alphaMode)
	:pixelFormat(pixelFormat),
	alphaMode(alphaMode),
	activeBitmap(originBitmap.PixelWidth(), originBitmap.PixelHeight())
{
	SetBitmap(originBitmap);
}

//Rendering::BrushImagePart::BrushImagePart(BrushImagePart const& rhs)
//	:pixelFormat(rhs.pixelFormat),
//	alphaMode(alphaMode)
//{
//	if (rhs.IsBitmapSet()) {
//		SetBitmap(rhs.Bitmap());
//	}
//}

void Rendering::BrushImagePart::SetBitmap(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& originBitmap)
{
	auto bitmapSize = PixelCount(originBitmap);
	activeBitmap = { originBitmap.PixelWidth(), originBitmap.PixelHeight() };
	uint8_t* originBitmapPixelBuffer{ originBitmap.PixelBuffer().data() };
	uint8_t* activeBitmapPixelBuffer{ activeBitmap.PixelBuffer().data() };


	for (int i = 0; i < bitmapSize; i++) {
		activeBitmapPixelBuffer[i] = originBitmapPixelBuffer[i];
	}
}

bool Rendering::BrushImagePart::IsBitmapSet() const
{
	return activeBitmap != nullptr;
}

int Rendering::BrushImagePart::PixelCount() const
{
	return PixelCount(activeBitmap);
}

void Rendering::BrushImagePart::ConvertToGrayScale()
{
	/*uint8_t* activeBitmapBuffer{ activeBitmap.PixelBuffer().data() };


	for (int i = 0; i < PixelCount(); i += 4) {
		auto b = activeBitmapBuffer[i];
		auto g = activeBitmapBuffer[i + 1];
		auto r = activeBitmapBuffer[i + 2];
		auto a = activeBitmapBuffer[i + 3];

		auto f = (r + g + b) / 3;


		activeBitmapBuffer[i] = f;
		activeBitmapBuffer[i + 1] = f;
		activeBitmapBuffer[i + 2] = f;
		activeBitmapBuffer[i + 3] = a;
	}*/

	for (auto it = begin(); it != end(); it++) {
		auto b = it.B();
		auto g = it.G();
		auto r = it.R();
		auto a = it.A();

		auto f = (r + g + b) / 3;
		it.B(f);
		it.G(f);
		it.R(f);
		it.A(a);
	}
}

winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap Rendering::BrushImagePart::Bitmap() const
{
	return activeBitmap;
}

winrt::Windows::Graphics::Imaging::BitmapPixelFormat const& Rendering::BrushImagePart::PixelFormat()
{
	return pixelFormat;
}

winrt::Windows::Graphics::Imaging::BitmapAlphaMode const& Rendering::BrushImagePart::AlphaMode()
{
	return alphaMode;
}

Rendering::BrushImagePart& Rendering::BrushImagePart::operator=(BrushImagePart const& rhs)
{
	this->activeBitmap = rhs.activeBitmap;
	this->pixelFormat = rhs.pixelFormat;
	this->alphaMode = rhs.alphaMode;

	return *this;
}

Rendering::BgraBitmapPixelIterator Rendering::BrushImagePart::begin()
{
	return Rendering::BgraBitmapPixelIterator(activeBitmap.PixelBuffer().data());
}

Rendering::BgraBitmapPixelIterator Rendering::BrushImagePart::end()
{
	return Rendering::BgraBitmapPixelIterator(activeBitmap.PixelBuffer().data() + PixelCount());
}

int Rendering::BrushImagePart::PixelCount(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& bitmap) const
{
	return bitmap.PixelWidth() * bitmap.PixelHeight() * 4;
}
