#include "pch.h"
#include "BrushCreatorViewModel.h"

ViewModels::BrushCreatorViewModel::BrushCreatorViewModel()
	: FilteredBrushes(),
	AllBrushes(),
	SearchTerm(),
	SelectedBrushIndex(-1)
{
}

void ViewModels::BrushCreatorViewModel::CreateBrush()
{
	auto newBrush = ref new Models::BrushData();
	AllBrushes->Append(newBrush);
	SearchTerm = "";
	ApplyFilter();
}

int ViewModels::BrushCreatorViewModel::GetSelectedBrushIndex()
{
	return SelectedBrushIndex;
}

void ViewModels::BrushCreatorViewModel::SelectBrush(int index)
{
	auto brush = VmBrushes->GetAt(index);

	if (brush != nullptr) {
		ActiveBrush = safe_cast<Models::BrushData^>(brush);
	}
}

void ViewModels::BrushCreatorViewModel::FilterBrushes(Platform::String^ searchTerm)
{
	SearchTerm = ref new Platform::String(searchTerm);
	ApplyFilter();
}

void ViewModels::BrushCreatorViewModel::ApplyFilter()
{
	if (SearchTerm->IsEmpty()) {
		FilteredBrushes = AllBrushes;
		return;
	}

	FilteredBrushes = ref new Platform::Collections::Vector<Models::BrushData^>();
	auto searchTerm = SearchTerm->Data();
	for (auto brush : AllBrushes) {
		auto brushName = brush->GetName();
		int foundIndex = brushName->find(searchTerm);
		if (foundIndex >= 0 && foundIndex <= brushName->size()) {
			FilteredBrushes->Append(brush);
		}
	}
}
