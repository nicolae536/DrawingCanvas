#pragma once
#include "pch.h"
#include "PixalValue.h"

using namespace winrt::Windows::UI::Xaml::Media::Imaging;

namespace Rendering {
	Rendering::PixalValue GetPixel(WriteableBitmap const& bitmap, int const x, int const y);
	void SetPixel(WriteableBitmap const& bitmap, int const x, int const y, winrt::Windows::UI::Color col);

	WriteableBitmap ConvertToGrayScale(WriteableBitmap const & bitmap);
}

