#pragma once
#include <vector>
#include "BrushData.h"

using namespace DrawingCanvas;

namespace DrawingCanvas {
	public ref class BrushCreatorViewModel sealed
	{
	public:
		BrushCreatorViewModel();

		void AddNewBrush();

		property Windows::Foundation::Collections::IObservableVector<BrushData^>^ VmFilteredBrushes {
			Windows::Foundation::Collections::IObservableVector<BrushData^>^ get() {
				return this->FilteredBrushes;
			}
		}

		property Platform::String^ VmFilter
		{
			Platform::String^ get() {
				return this->FilterValue;
			};

			void set(Platform::String^ value) {
				this->FilterValue = value;
				void ApplyFilter();
			};
		}
	private:
		BrushSize^ ActiveBrushSize;
		BrushData^ ActiveBrush;
		Platform::Collections::Vector<BrushData^>^ AllBrushesList;
		Platform::Collections::Vector<BrushData^>^ FilteredBrushes;
		Platform::String^ FilterValue;
	private:
		void ApplyFilter();
	};
}