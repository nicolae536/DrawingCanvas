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
        auto srcBitmap = co_await filePicker.PickImageAsync();

        if (srcBitmap == nullptr) {
            co_return;
        }

        auto bitmapSize = srcBitmap.PixelWidth() * srcBitmap.PixelHeight() * 4;
        uint8_t* srcPixels{ srcBitmap.PixelBuffer().data() };
        
        auto dstBitmap = Windows::UI::Xaml::Media::Imaging::WriteableBitmap(srcBitmap.PixelWidth(), srcBitmap.PixelHeight());
        uint8_t* dstPixels{ dstBitmap.PixelBuffer().data() };       


        for (int i = 0; i < bitmapSize; i+=4) {
            auto b = srcPixels[i];
            auto g = srcPixels[i + 1];
            auto r = srcPixels[i + 2];
            auto a = srcPixels[i + 3];

            auto f = (r + g + b) / 3;


            dstPixels[i] = f;
            dstPixels[i + 1] = f;
            dstPixels[i + 2] = f;
            dstPixels[i + 3] = a;
            
                //(int)((pixel & 0xFF000000) | average << 16 | average << 8 | average);
        }

        
        brushShape().Source(dstBitmap);


        // auto p{ bitmap.PixelBuffer().data() };
        // https://social.msdn.microsoft.com/Forums/windowsapps/en-US/5ff10c14-51d4-4760-afe6-091624adc532/sample-code-for-making-a-bitmapimage-grayscale?forum=winappswithcsharp
    }
}
