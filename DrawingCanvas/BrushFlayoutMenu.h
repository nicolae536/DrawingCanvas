#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "BrushFlayoutMenu.g.h"

namespace winrt::DrawingCanvas::implementation
{
    struct BrushFlayoutMenu : BrushFlayoutMenuT<BrushFlayoutMenu>
    {
        BrushFlayoutMenu();

        void Set_Brushes_Tab(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        void Set_Pencils_Tab(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        
        void Add_New_Brush(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private: 
        std::vector<winrt::Windows::UI::Xaml::Interop::TypeName> tabsList;

        void ChangeActiveTab(winrt::Windows::UI::Xaml::Interop::TypeName tabActive);
    };
}

namespace winrt::DrawingCanvas::factory_implementation
{
    struct BrushFlayoutMenu : BrushFlayoutMenuT<BrushFlayoutMenu, implementation::BrushFlayoutMenu>
    {
    };
}
