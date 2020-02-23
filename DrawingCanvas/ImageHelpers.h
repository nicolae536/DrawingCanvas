#pragma once
#include "pch.h"
#include "PixalValue.h"

namespace Rendering {
	Rendering::PixalValue GetPixel(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& bitmap, int const x, int const y);
	void SetPixel(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& bitmap, int const x, int const y, winrt::Windows::UI::Color col);
}

