#pragma once
#include <vector>
#include "BrushData.h"

namespace ViewModels {
	ref class BrushCreatorViewModel
	{
	public:
		Models::BrushData^ ActiveBrush;
		Platform::String^ SearchTerm;

		property Windows::Foundation::Collections::IObservableVector<Models::BrushData^>^ VmBrushes
		{
			Windows::Foundation::Collections::IObservableVector<Models::BrushData^>^ get()
			{
				if (FilteredBrushes == nullptr) {
					FilteredBrushes = ref new Platform::Collections::Vector<Models::BrushData^>();
				};
				return FilteredBrushes;
			}
		}
	private:
		Platform::Collections::Vector<Models::BrushData^>^ AllBrushes;
		Platform::Collections::Vector<Models::BrushData^>^ FilteredBrushes;
		int SelectedBrushIndex;
	public:
		BrushCreatorViewModel();
		void CreateBrush();
		int GetSelectedBrushIndex();
		void SelectBrush(int index);
		void FilterBrushes(Platform::String^ searchTerm);
	private:
		void ApplyFilter();
	};
};

