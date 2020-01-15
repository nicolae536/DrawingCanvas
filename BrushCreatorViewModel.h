#pragma once
#include "BrushData.h"

using namespace DrawingCanvas;

namespace DrawingCanvas {
	[Windows::UI::Xaml::Data::Bindable]
	public ref class BrushCreatorViewModel sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
	{
	public:
		BrushCreatorViewModel();

		void AddNewBrush();
	
		void OnPropertyChanged(Platform::String^ propertyName);

	public:
		virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

	public:
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
				ApplyFilter();
				OnPropertyChanged("VmFilter");
			};
		}

	private:
		void ApplyFilter();

	private:
		BrushSize^ ActiveBrushSize;
		BrushData^ ActiveBrush;
		Platform::Collections::Vector<BrushData^>^ AllBrushesList;
		Platform::Collections::Vector<BrushData^>^ FilteredBrushes;
		Platform::String^ FilterValue;
	};
}