#include "pch.h"
#include "ImageHelpers.h"

Rendering::PixalValue GetPixel(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& bitmap, int const x, int const y)
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

void Rendering::SetPixel(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& bitmap, int const x, int const y, winrt::Windows::UI::Color col)
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