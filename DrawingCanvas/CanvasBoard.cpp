#include "pch.h"
#include "CanvasBoard.h"
#if __has_include("CanvasBoard.g.cpp")
#include "CanvasBoard.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::DrawingCanvas::implementation
{
    CanvasBoard::CanvasBoard()
    {
        InitializeComponent();        
    }
    
    void CanvasBoard::CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        /*drawingQueue->ActivatePointer();
        Rendering::CanvasPoint point(e.GetCurrentPoint(canvasControl()));
        drawingQueue->Add(point);
        canvasControl().Invalidate();*/
    }
    
    void CanvasBoard::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        /*Rendering::CanvasPoint point(e.GetCurrentPoint(canvasControl()));
        drawingQueue->Add(point);
        canvasControl().Invalidate();*/
    }
    
    void CanvasBoard::CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        /*Rendering::CanvasPoint point(e.GetCurrentPoint(canvasControl()));
        drawingQueue->Add(point);
        drawingQueue->DeactivatePointer();
        canvasControl().Invalidate();*/
    }

    void CanvasBoard::Page_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        canvasControl().RemoveFromVisualTree();
        canvasControl(NULL);
    }
    
    void CanvasBoard::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
    {
        //auto pointsToDraw = drawingQueue->GetPoints();

        //winrt::Microsoft::Graphics::Canvas::Geometry::CanvasGradientMesh mesh;

        /*for (auto p : *pointsToDraw) {
            canvasBrush->Draw(p, args.DrawingSession());*/
            //args.DrawingSession().DrawInk();
            //args.DrawingSession().FillCircle(p.X(), p.Y(), 10, winrt::Windows::UI::Colors::Beige());
            //args.DrawingSession().DrawGeometry
        //}
    }

    void CanvasBoard::OpenMenu(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        configPanel().IsPaneOpen(!configPanel().IsPaneOpen());
    }
}
