#include "pch.h"
#include "BrushesList.h"
#if __has_include("BrushesList.g.cpp")
#include "BrushesList.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::DrawingCanvas::implementation
{
    BrushesList::BrushesList()
    {
        InitializeComponent();
        brushesList = winrt::single_threaded_observable_vector<DrawingCanvas::BrushItemModel>();
    }
    winrt::Windows::Foundation::Collections::IObservableVector<DrawingCanvas::BrushItemModel> BrushesList::Brushes()
    {
        return brushesList;
    }
}
