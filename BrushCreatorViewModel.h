#pragma once
#include <vector>
#include "BrushData.h"

namespace ViewModels {
	ref class BrushCreatorViewModel sealed
	{
	public:
		BrushCreatorViewModel();

		void AddNewBrush();

		/*property Platform::Collections::Vector<Models::BrushData^>^ VmFilteredBrushes {
			Platform::Collections::Vector<Models::BrushData^>^ get() {
				return this->FilteredBrushes;
			}
		}*/

		property Platform::String^ VmFilter
		{
			Platform::String^ get() {
				return this->FilterValue;
			}
		}
	private:
		Models::BrushSize^ ActiveBrushSize;
		Models::BrushData^ ActiveBrush;
		Platform::Collections::Vector<Models::BrushData^>^ AllBrushesList;
		Platform::Collections::Vector<Models::BrushData^>^ FilteredBrushes;
		Platform::String^ FilterValue;
	private:
		void ApplyFilter();
	};
};

