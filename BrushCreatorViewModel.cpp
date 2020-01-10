#include "pch.h"
#include "BrushCreatorViewModel.h"
#include "StringUtils.h"

using namespace Models;
ViewModels::BrushCreatorViewModel::BrushCreatorViewModel()
	: ActiveBrushSize(ref new BrushSize(5, 5)),
	ActiveBrush(),
	AllBrushesList(),
	FilteredBrushes(),
	FilterValue()
{
	ActiveBrush->UpdateSize(ActiveBrushSize);
}

void ViewModels::BrushCreatorViewModel::AddNewBrush() {
	BrushData^ brush = ref new BrushData(
		ActiveBrushSize,
		WinInk::PenTipShape::Circle,
		WinNumerics::float3x2()
	);
	AllBrushesList->Append(brush);
	FilterValue = "";

}

void ViewModels::BrushCreatorViewModel::ApplyFilter()
{
	if (FilterValue == "") {
		FilteredBrushes = AllBrushesList;
		return;
	}

	FilteredBrushes = ref new Platform::Collections::Vector<Models::BrushData^>();
	std::wstring filter = StringUtils::PlatformStringToWString(FilterValue);

	for (auto brush : AllBrushesList) {
		auto brushName = StringUtils::PlatformStringToWString(brush->GetName());
		if (brushName.find(filter)) {
			FilteredBrushes->Append(brush);
		}
	}
}

