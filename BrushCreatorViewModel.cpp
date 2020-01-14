#include "pch.h"
#include "BrushCreatorViewModel.h"
#include "StringUtils.h"

BrushCreatorViewModel::BrushCreatorViewModel()
	: ActiveBrushSize(ref new BrushSize(5, 5)),
	AllBrushesList(ref new Platform::Collections::Vector<BrushData^>()),
	FilteredBrushes(ref new Platform::Collections::Vector<BrushData^>()),
	FilterValue(L"")
{
}

void BrushCreatorViewModel::AddNewBrush() {
	BrushData^ brush = ref new BrushData(
		L"New brush",
		ActiveBrushSize,
		WinInk::PenTipShape::Circle,
		WinNumerics::float3x2()
	);
	AllBrushesList->Append(brush);
	FilterValue = "";
	ActiveBrush = brush;
	ApplyFilter();
}

void BrushCreatorViewModel::ApplyFilter()
{
	FilteredBrushes->Clear();
	if (FilterValue == "") {
		for (auto b : AllBrushesList) {
			FilteredBrushes->Append(b);
		}
		return;
	}

	std::wstring filter = StringUtils::PlatformStringToWString(FilterValue);

	for (auto brush : AllBrushesList) {
		auto brushName = StringUtils::PlatformStringToWString(brush->Name);
		if (brushName.find(filter)) {
			FilteredBrushes->Append(brush);
		}
	}
}

