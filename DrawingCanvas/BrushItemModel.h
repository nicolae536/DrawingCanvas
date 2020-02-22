#pragma once

#include "BrushItemModel.g.h"

namespace winrt::DrawingCanvas::implementation
{
    struct BrushItemModel : BrushItemModelT<BrushItemModel>
    {
        BrushItemModel() = default;

        hstring Name();

        void Name(hstring value);

        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Preview();

        void Preview(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage value);

    private:
        hstring brushName;

        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage brushPreview;
    };
}

namespace winrt::DrawingCanvas::factory_implementation
{
    struct BrushItemModel : BrushItemModelT<BrushItemModel, implementation::BrushItemModel>
    {
    };
}
