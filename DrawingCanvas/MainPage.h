#pragma once

#include "MainPage.g.h"

namespace winrt::DrawingCanvas::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
    };
}

namespace winrt::DrawingCanvas::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
