#include "pch.h"
#include "CreateBrushShapeAndTexture.h"
#if __has_include("CreateBrushShapeAndTexture.g.cpp")
#include "CreateBrushShapeAndTexture.g.cpp"
#endif
#include "BrushImagePart.h"

namespace winrt::DrawingCanvas::implementation
{
    CreateBrushShapeAndTexture::CreateBrushShapeAndTexture()
        :filePicker({ ".jpg", ".png", ".jpeg" }),
        brush()
    {
        InitializeComponent();
    }

    winrt::Windows::Foundation::IAsyncAction CreateBrushShapeAndTexture::PickBrushShape(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        auto srcBitmap = co_await filePicker.PickImageAsync();

        if (srcBitmap == nullptr) {
            co_return;
        }

        brush.ShapeBitmap(srcBitmap);        
        brushShapeView().Source(brush.ShapeBitmap());
        brushView().Source(brush.Texture());
    }

    winrt::Windows::Foundation::IAsyncAction CreateBrushShapeAndTexture::PickBrushGrain(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        auto srcBitmap = co_await filePicker.PickImageAsync();

        if (srcBitmap == nullptr) {
            co_return;
        }

        brush.GrainBitmap(srcBitmap);
        brushGrainView().Source(brush.GrainBitmap());
        brushView().Source(brush.Texture());
    }
}
