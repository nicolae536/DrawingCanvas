#include "pch.h"
#include "BrushSizeModel.h"
#if __has_include("BrushSizeModel.g.cpp")
#include "BrushSizeModel.g.cpp"
#endif

namespace winrt::DrawingCanvas::implementation
{
	BrushSizeModel::BrushSizeModel()
		:m_width(0),
		m_height(0)
	{
	}

	BrushSizeModel::BrushSizeModel(float width, float height)
		: m_width(width),
		m_height(height)
	{
	}

	float BrushSizeModel::Width()
	{
		return m_width;
	}

	void BrushSizeModel::Width(float value)
	{
		m_width = value;
	}

	float BrushSizeModel::Height()
	{
		return m_height;
	}

	void BrushSizeModel::Height(float value)
	{
		m_height = value;
	}

	winrt::event_token BrushSizeModel::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}

	void BrushSizeModel::PropertyChanged(winrt::event_token const& token)
	{
		m_propertyChanged.remove(token);
	}
}
