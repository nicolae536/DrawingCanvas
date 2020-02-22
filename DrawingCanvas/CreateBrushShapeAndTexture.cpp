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
    {
        InitializeComponent();
    }
}
