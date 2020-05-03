#pragma once

#include "CreateBrushShapeAndTexture.g.h"
#include "FilePicker.h"
#include "CanvasBrush.h"

namespace winrt::DrawingCanvas::implementation
{
    struct CreateBrushShapeAndTexture : CreateBrushShapeAndTextureT<CreateBrushShapeAndTexture>
    {
    public:
        CreateBrushShapeAndTexture();
    private:
        PlatformServices::FilePicker filePicker;
        Rendering::CanvasBrush brush;
    public:
        winrt::Windows::Foundation::IAsyncAction PickBrushShape(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction PickBrushGrain(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);       
    };
}

namespace winrt::DrawingCanvas::factory_implementation
{
    struct CreateBrushShapeAndTexture : CreateBrushShapeAndTextureT<CreateBrushShapeAndTexture, implementation::CreateBrushShapeAndTexture>
    {
    };
}
