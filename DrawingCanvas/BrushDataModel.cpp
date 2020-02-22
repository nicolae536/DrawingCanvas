#include "pch.h"
#include "BrushDataModel.h"
#if __has_include("BrushDataModel.g.cpp")
#include "BrushDataModel.g.cpp"
#endif

namespace winrt::DrawingCanvas::implementation
{
	BrushDataModel::BrushDataModel()
		: m_id(L"NO_ID"),
		m_name(L"NO_NAME"),
		m_penTipShape(Windows::UI::Input::Inking::PenTipShape::Circle)
	{
		m_size = winrt::make<DrawingCanvas::implementation::BrushSizeModel>();
	}

	BrushDataModel::BrushDataModel(hstring id, hstring name, DrawingCanvas::BrushSizeModel size, Windows::UI::Input::Inking::PenTipShape penTipShape)
		: m_id(id),
		m_name(name),
		m_size(size),
		m_penTipShape(penTipShape)
	{
	}
	hstring BrushDataModel::Id()
	{
		return m_id;
	}
	void BrushDataModel::Id(hstring value)
	{
		m_id = value;
	}
	hstring BrushDataModel::Name()
	{
		return m_name;
	}
	void BrushDataModel::Name(hstring value)
	{
		m_name = value;
	}
	DrawingCanvas::BrushSizeModel BrushDataModel::Size()
	{
		return m_size;
	}
	void BrushDataModel::Size(DrawingCanvas::BrushSizeModel value)
	{
		m_size = value;
	}
	Windows::UI::Input::Inking::PenTipShape BrushDataModel::PenTipShape()
	{
		return m_penTipShape;
	}
	void BrushDataModel::PenTipShape(Windows::UI::Input::Inking::PenTipShape value)
	{
		m_penTipShape = value;
	}

	winrt::event_token BrushDataModel::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}

	void BrushDataModel::PropertyChanged(winrt::event_token const& token)
	{
		m_propertyChanged.remove(token);
	}
}
