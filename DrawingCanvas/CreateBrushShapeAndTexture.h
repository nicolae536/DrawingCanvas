#pragma once

#include "CreateBrushShapeAndTexture.g.h"
#include "FilePicker.h"

namespace winrt::DrawingCanvas::implementation
{
    struct CreateBrushShapeAndTexture : CreateBrushShapeAndTextureT<CreateBrushShapeAndTexture>
    {
    public:
        CreateBrushShapeAndTexture();
    private:
        PlatformServices::FilePicker filePicker;

    public:
        winrt::Windows::Foundation::IAsyncAction PickFile(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::DrawingCanvas::factory_implementation
{
    struct CreateBrushShapeAndTexture : CreateBrushShapeAndTextureT<CreateBrushShapeAndTexture, implementation::CreateBrushShapeAndTexture>
    {
    };
}
