#include "pch.h"
#include "BrushCreatorViewModel.h"
#if __has_include("BrushCreatorViewModel.g.cpp")
#include "BrushCreatorViewModel.g.cpp"
#endif

namespace winrt::DrawingCanvas::implementation
{
	BrushCreatorViewModel::BrushCreatorViewModel()
		: m_filter(L""),
		m_allBrushesList(std::make_shared<std::vector<DrawingCanvas::BrushDataModel>>())
	{
		m_filteredBrushes = winrt::single_threaded_observable_vector<DrawingCanvas::BrushDataModel>();
		m_brushSize = winrt::make<DrawingCanvas::implementation::BrushSizeModel>(5.0, 5.0);
	}

	winrt::event_token BrushCreatorViewModel::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}

	void BrushCreatorViewModel::PropertyChanged(winrt::event_token const& token)
	{
		m_propertyChanged.remove(token);
	}
	Windows::Foundation::Collections::IObservableVector<DrawingCanvas::BrushDataModel> BrushCreatorViewModel::VmFilteredBrushes()
	{
		return m_filteredBrushes;
	}
	hstring BrushCreatorViewModel::VmFilter()
	{
		return m_filter;
	}
	void BrushCreatorViewModel::VmFilter(hstring value)
	{
		m_filter = value;
		ApplyFilter();
	}

	void BrushCreatorViewModel::CreateBrush() {
		auto brush = winrt::make<DrawingCanvas::implementation::BrushDataModel>(
			L"NEW_ID",
			L"This is a new brush",
			m_brushSize,
			Windows::UI::Input::Inking::PenTipShape::Circle
			);

		m_allBrushesList->push_back(brush);
		m_filter.clear();
		ApplyFilter();
	}

	DrawingCanvas::BrushSizeModel BrushCreatorViewModel::BrushSize()
	{
		return m_brushSize;
	}

	void BrushCreatorViewModel::ApplyFilter()
	{
		if (m_filter.empty() && m_filteredBrushes.Size() == m_allBrushesList->size()) {
			return;
		}

		if (m_filter.empty() && m_filteredBrushes.Size() != m_allBrushesList->size()) {
			m_filteredBrushes.Clear();
			for (auto brush : *m_allBrushesList) {
				m_filteredBrushes.Append(brush);
			}
			m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"VmFilteredBrushes" });
			return;
		}

		m_filteredBrushes = winrt::single_threaded_observable_vector<DrawingCanvas::BrushDataModel>();
		std::wstring filter = m_filter.c_str();
		for (auto brush : *m_allBrushesList) {
			std::wstring brushName = brush.Name().c_str();
			auto findResult = brushName.find(filter);
			if (findResult != std::string::npos) {
				m_filteredBrushes.Append(brush);
			}
		}

		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"VmFilteredBrushes" });

	}
}
