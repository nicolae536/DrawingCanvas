#pragma once

#include "BrushesList.g.h"
#include "BrushItemModel.h"

namespace winrt::DrawingCanvas::implementation
{
    struct BrushesList : BrushesListT<BrushesList>
    {
        BrushesList();

        winrt::Windows::Foundation::Collections::IObservableVector<DrawingCanvas::BrushItemModel> Brushes();

    private:
        winrt::Windows::Foundation::Collections::IObservableVector<DrawingCanvas::BrushItemModel> brushesList;

    };
}

namespace winrt::DrawingCanvas::factory_implementation
{
    struct BrushesList : BrushesListT<BrushesList, implementation::BrushesList>
    {
    };
}
