#include "pch.h"
#include "BushService.h"

using namespace DrawingCanvas;

DrawingCanvas::BushService::BushService()
	: BrushStore(ref new Platform::Collections::Vector<BrushData^>)
{
}

BrushData^ DrawingCanvas::BushService::AddBrush(BrushData^ brush)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

BrushData^ DrawingCanvas::BushService::DeleteBrush(BrushData^ brush)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

BrushData^ DrawingCanvas::BushService::UpdateBrush(BrushData^ brush)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}
