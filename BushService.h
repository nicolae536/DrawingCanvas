#pragma once
#include "BrushData.h"

namespace DrawingCanvas {
	ref class BushService sealed
	{
	public:
		BushService();
		BrushData^ AddBrush(BrushData^ brush);
		BrushData^ DeleteBrush(BrushData^ brush);
		BrushData^ UpdateBrush(BrushData^ brush);
		Windows::Foundation::Collections::IVector<BrushData^>^ GetBrushes();
	private:
		Platform::Collections::Vector<BrushData^>^ BrushStore;
	};
}

