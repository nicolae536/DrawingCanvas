#pragma once

#include "CanvasBoard.g.h"

namespace winrt::DrawingCanvas::implementation
{
    struct CanvasBoard : CanvasBoardT<CanvasBoard>
    {
        CanvasBoard();

        /*std::unique_ptr<Rendering::DrawingQueue> drawingQueue;
        std::unique_ptr<Rendering::CanvasBrush> canvasBrush;*/

	public:		
		void CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);		
		void Page_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);		
        void CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args);
		void OpenMenu(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
	};
}

namespace winrt::DrawingCanvas::factory_implementation
{
    struct CanvasBoard : CanvasBoardT<CanvasBoard, implementation::CanvasBoard>
    {
    };
}
