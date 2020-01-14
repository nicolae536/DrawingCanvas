//
// BrushCreator.xaml.cpp
// Implementation of the BrushCreator class
//

#include "pch.h"
#include "BrushCreator.xaml.h"

using namespace DrawingCanvas;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

BrushCreator::BrushCreator()
	:ViewModel(ref new BrushCreatorViewModel())
{
	InitializeComponent();

}

void BrushCreator::InitializeBindings()
{
	/*brushesList->ItemsSource = vm->VmFilteredBrushes;
	brushSearch->Text = vm->VmFilter;

	auto binding = ref new Binding();
	binding->Mode = BindingMode::TwoWay;
	binding->Source = vm->VmFilter;
	brushSearch->SetBinding(TextBlock::TextProperty, binding);*/
}
void BrushCreator::CreateBrush(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	ViewModel->AddNewBrush();
}