#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::DrawingCanvas::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();

        winrt::Windows::UI::Xaml::Interop::TypeName scenarioType = { L"DrawingCanvas.CanvasBoard", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom };
        this->RootFrame().Navigate(scenarioType);
    }
}
