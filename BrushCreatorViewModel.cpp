#include "pch.h"
#include "BrushCreatorViewModel.h"
#include "StringUtils.h"
#include <windows.h>

BrushCreatorViewModel::BrushCreatorViewModel()
	: ActiveBrushSize(ref new BrushSize(5, 5)),
	AllBrushesList(ref new Platform::Collections::Vector<BrushData^>()),
	FilteredBrushes(ref new Platform::Collections::Vector<BrushData^>()),
	FilterValue(L"")
{
}

void BrushCreatorViewModel::OnPropertyChanged(Platform::String^ propertyName)
{
	PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
}

void BrushCreatorViewModel::AddNewBrush() {
	BrushData^ brush = ref new BrushData();
	brush->Name = L"New brush " + AllBrushesList->Size.ToString();
	AllBrushesList->Append(brush);
	FilterValue = "";
	ActiveBrush = brush;
	ApplyFilter();
}

void BrushCreatorViewModel::ApplyFilter()
{
	if (FilterValue == "") {
		FilteredBrushes = AllBrushesList;
		OnPropertyChanged("VmFilteredBrushes");
		return;
	}

	std::wstring filter = StringUtils::PlatformStringToWString(FilterValue);

	FilteredBrushes = ref new Platform::Collections::Vector<BrushData^>();
	for (auto brush : AllBrushesList) {
		auto brushName = StringUtils::PlatformStringToWString(brush->Name);
		auto findResult = brushName.find(filter);
		if (findResult != std::string::npos) {
			FilteredBrushes->Append(brush);
		}
	}
	OnPropertyChanged("VmFilteredBrushes");
}

