#include "pch.h"
#include "BrushFlayoutMenu.h"
#if __has_include("BrushFlayoutMenu.g.cpp")
#include "BrushFlayoutMenu.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::DrawingCanvas::implementation
{
	BrushFlayoutMenu::BrushFlayoutMenu()
		:tabsList()
	{
		InitializeComponent();

		tabsList.push_back({ L"DrawingCanvas.BrushesList", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom });
		tabsList.push_back({ L"DrawingCanvas.PencilsList", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom });
		tabsList.push_back({ L"DrawingCanvas.CreateBrushShapeAndTexture", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom });

		ChangeActiveTab(tabsList[0]);
	}

	void BrushFlayoutMenu::Set_Brushes_Tab(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		ChangeActiveTab(tabsList[0]);
	}

	void BrushFlayoutMenu::Set_Pencils_Tab(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		ChangeActiveTab(tabsList[1]);
	}

	void BrushFlayoutMenu::Add_New_Brush(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		ChangeActiveTab(tabsList[2]);
	}

	void BrushFlayoutMenu::ChangeActiveTab(winrt::Windows::UI::Xaml::Interop::TypeName tabActive)
	{
		TabContent().Navigate(tabActive);
	}
}



