#pragma once

#include "BrushCreatorViewModel.g.h"
#include "BrushDataModel.h"
#include <vector>
#include <iterator>

namespace winrt::DrawingCanvas::implementation
{
	struct BrushCreatorViewModel : BrushCreatorViewModelT<BrushCreatorViewModel>
	{
		BrushCreatorViewModel();

		winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);

		void PropertyChanged(winrt::event_token const& token);

		Windows::Foundation::Collections::IObservableVector<DrawingCanvas::BrushDataModel> VmFilteredBrushes();

		hstring VmFilter();

		void VmFilter(hstring value);

		void CreateBrush();

		DrawingCanvas::BrushSizeModel BrushSize();

	private:
		winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

		Windows::Foundation::Collections::IObservableVector<DrawingCanvas::BrushDataModel> m_filteredBrushes;

		std::shared_ptr<std::vector<DrawingCanvas::BrushDataModel>> m_allBrushesList;

		hstring m_filter;

		DrawingCanvas::BrushSizeModel m_brushSize;

	private:
		void ApplyFilter();
	};
}

namespace winrt::DrawingCanvas::factory_implementation
{
	struct BrushCreatorViewModel : BrushCreatorViewModelT<BrushCreatorViewModel, implementation::BrushCreatorViewModel>
	{
	};
}
