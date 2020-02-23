#include "pch.h"
#include "CreateBrushShapeAndTexture.h"
#if __has_include("CreateBrushShapeAndTexture.g.cpp")
#include "CreateBrushShapeAndTexture.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::DrawingCanvas::implementation
{
    CreateBrushShapeAndTexture::CreateBrushShapeAndTexture()
        :filePicker({ ".jpg", ".png", ".jpeg" })
    {
        InitializeComponent();
    }

    winrt::Windows::Foundation::IAsyncAction CreateBrushShapeAndTexture::PickFile(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap storageFile = co_await filePicker.PickImageAsync();

        if (storageFile == nullptr) {
            co_return;
        }

        auto piselWidth = { storageFile.PixelWidth() };
        // auto p{ bitmap.PixelBuffer().data() };
        // https://social.msdn.microsoft.com/Forums/windowsapps/en-US/5ff10c14-51d4-4760-afe6-091624adc532/sample-code-for-making-a-bitmapimage-grayscale?forum=winappswithcsharp
    }
}
