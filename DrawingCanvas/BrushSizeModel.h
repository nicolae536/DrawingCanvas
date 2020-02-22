#pragma once

#include "BrushSizeModel.g.h"

namespace winrt::DrawingCanvas::implementation
{
    struct BrushSizeModel : BrushSizeModelT<BrushSizeModel>
    {
        BrushSizeModel();

        BrushSizeModel(float width, float height);

        float Width();
        void Width(float value);

        float Height();
        void Height(float value);

        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

    private:
        float m_width;
        float m_height;

        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::DrawingCanvas::factory_implementation
{
    struct BrushSizeModel : BrushSizeModelT<BrushSizeModel, implementation::BrushSizeModel>
    {
    };
}
