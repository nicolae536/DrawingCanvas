#include "pch.h"
#include "BrushItemModel.h"
#if __has_include("BrushItemModel.g.cpp")
#include "BrushItemModel.g.cpp"
#endif

namespace winrt::DrawingCanvas::implementation
{
	hstring BrushItemModel::Name()
	{
		return brushName;
	}
	void BrushItemModel::Name(hstring value)
	{
		brushName = value;
	}
	winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage BrushItemModel::Preview()
	{
		return brushPreview;
	}
	void BrushItemModel::Preview(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage value)
	{
		brushPreview = value;
	}
}
