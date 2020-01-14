//
// BrushCreator.xaml.h
// Declaration of the BrushCreator class
//

#pragma once

#include "BrushCreator.g.h"
#include "BrushCreatorViewModel.h"

namespace DrawingCanvas
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class BrushCreator sealed
	{
	public:
		BrushCreator();

		property BrushCreatorViewModel^ Vm {
			BrushCreatorViewModel^ get() {
				return this->ViewModel;
			}
		};

		void CreateBrush(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	private:
		void InitializeBindings();
		BrushCreatorViewModel^ ViewModel;
	};
}
