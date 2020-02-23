#include "pch.h"
#include "ImageHelpers.h"

Rendering::PixalValue GetPixel(WriteableBitmap const& bitmap, int const x, int const y)
{
	auto w{ bitmap.PixelWidth() };
	// Get pointer to in-memory buffer
	auto p{ bitmap.PixelBuffer().data() };
	// Calculate memory offset (4 bytes per pixel)
	auto offset{ w * y * 4 + x * 4 };
	// Write pixel
	auto pixel_address{ p + offset };

	Rendering::PixalValue pixelValue;
	pixelValue.B = *(pixel_address + 0);
	pixelValue.G = *(pixel_address + 1);
	pixelValue.R = *(pixel_address + 2);
	pixelValue.A = *(pixel_address + 3);
	return pixelValue;
}

void Rendering::SetPixel(WriteableBitmap const& bitmap, int const x, int const y, winrt::Windows::UI::Color col)
{
	auto w{ bitmap.PixelWidth() };
	// Get pointer to in-memory buffer
	auto p{ bitmap.PixelBuffer().data() };
	// Calculate memory offset (4 bytes per pixel)
	auto offset{ w * y * 4 + x * 4 };
	// Write pixel
	auto pixel_address{ p + offset };

	Rendering::PixalValue pixelValue;
	*(pixel_address + 0) = col.B;
	*(pixel_address + 1) = col.G;
	*(pixel_address + 2) = col.R;
	*(pixel_address + 3) = col.A;
}

WriteableBitmap Rendering::ConvertToGrayScale(WriteableBitmap const& bitmap)
{
	auto p{ bitmap.PixelBuffer().data() };
	//bitmap.PixelBuffer().
	// https://social.msdn.microsoft.com/Forums/windowsapps/en-US/5ff10c14-51d4-4760-afe6-091624adc532/sample-code-for-making-a-bitmapimage-grayscale?forum=winappswithcsharp

	/*for (int i =0; i < *p)*/
}