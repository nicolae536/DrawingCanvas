#pragma once
#include "CanvasPoint.h"
#include "BrushImagePart.h"

namespace Rendering {
	class CanvasBrush
	{
	public:
		CanvasBrush();

		void Draw(Rendering::CanvasPoint const& point, winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& ds);

		void ShapeBitmap(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& originBitmap);

		void GrainBitmap(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& originBitmap);

		winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap ShapeBitmap() const;

		winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap GrainBitmap() const;

		winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap Texture() const;
	private:
		void CombineShapeAndGrain();
	private:
		BrushImagePart brushSource;
		BrushImagePart brushGrain;
		BrushImagePart brushTexture;
	};
}

