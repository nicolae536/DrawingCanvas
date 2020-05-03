#include "pch.h"
#include "CanvasBrush.h"
#include <random>
#include <math.h>

Rendering::CanvasBrush::CanvasBrush()
{
}

void Rendering::CanvasBrush::Draw(Rendering::CanvasPoint const& point, winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& ds)
{
}

void Rendering::CanvasBrush::ShapeBitmap(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& originBitmap)
{
	brushSource.SetBitmap(originBitmap);
	brushSource.ConvertToGrayScale();
	CombineShapeAndGrain();
}

void Rendering::CanvasBrush::GrainBitmap(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& originBitmap)
{
	brushGrain.SetBitmap(originBitmap);
	brushGrain.ConvertToGrayScale();
	CombineShapeAndGrain();
}

winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap Rendering::CanvasBrush::ShapeBitmap() const
{
	return brushSource.Bitmap();
}

winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap Rendering::CanvasBrush::GrainBitmap() const
{
	return brushGrain.Bitmap();
}

winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap Rendering::CanvasBrush::Texture() const
{
	return brushTexture.Bitmap();
}

void Rendering::CanvasBrush::CombineShapeAndGrain()
{
	if (!brushSource.IsBitmapSet() || !brushGrain.IsBitmapSet()) {
		return;
	}

	brushTexture = {
		brushSource.Bitmap(),
		brushSource.PixelFormat(),
		brushSource.AlphaMode()
	};

	auto brushIt = brushTexture.begin();
	auto grainIt = brushGrain.begin();

	while (brushIt != brushTexture.end() && grainIt != brushGrain.end())
	{
		if (brushIt.A() != 0) {
			brushIt.R(grainIt.R());
			brushIt.G(grainIt.G());
			brushIt.B(grainIt.B());
			grainIt++;
		}
		brushIt++;
	}
}
