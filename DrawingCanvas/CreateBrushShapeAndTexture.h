#pragma once

#include "CreateBrushShapeAndTexture.g.h"

namespace winrt::DrawingCanvas::implementation
{
    struct CreateBrushShapeAndTexture : CreateBrushShapeAndTextureT<CreateBrushShapeAndTexture>
    {
        CreateBrushShapeAndTexture();
    };
}

namespace winrt::DrawingCanvas::factory_implementation
{
    struct CreateBrushShapeAndTexture : CreateBrushShapeAndTextureT<CreateBrushShapeAndTexture, implementation::CreateBrushShapeAndTexture>
    {
    };
}
