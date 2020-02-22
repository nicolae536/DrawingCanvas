#pragma once

#include "BrushDataModel.g.h"
#include "BrushSizeModel.h"

namespace winrt::DrawingCanvas::implementation
{
	struct BrushDataModel : BrushDataModelT<BrushDataModel>
	{
		BrushDataModel();

		BrushDataModel(
			hstring id,
			hstring name,
			DrawingCanvas::BrushSizeModel size,
			Windows::UI::Input::Inking::PenTipShape penTipShape
		);

		hstring Id();
		void Id(hstring value);

		hstring Name();
		void Name(hstring value);

		DrawingCanvas::BrushSizeModel Size();
		void Size(DrawingCanvas::BrushSizeModel value);

		Windows::UI::Input::Inking::PenTipShape PenTipShape();
		void PenTipShape(Windows::UI::Input::Inking::PenTipShape value);

		winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);

		void PropertyChanged(winrt::event_token const& token);

	private:
		static Windows::UI::Xaml::DependencyProperty m_IsMovableProperty;
		
		hstring m_id;
		hstring m_name;
		DrawingCanvas::BrushSizeModel m_size;
		Windows::UI::Input::Inking::PenTipShape m_penTipShape;
	
		winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}

namespace winrt::DrawingCanvas::factory_implementation
{
	struct BrushDataModel : BrushDataModelT<BrushDataModel, implementation::BrushDataModel>
	{
	};
}
