#pragma once
#include <WindowsNumerics.h>
#include <string.h>
#include "BrushSize.h"

namespace Models {
	ref class BrushData sealed
	{
	public:
		BrushData();
		BrushData(BrushSize^ size,
			WinInk::PenTipShape penTipShape,
			WinNumerics::float3x2 penTipTransform
		);
		
		Platform::String^ GetName();
		BrushSize^ GetBrushSize();
		WinInk::PenTipShape GetPenTipShape();
		WinNumerics::float3x2 GetPenTipTransform();

		void UpdateSize(BrushSize^ size);
		void UpdatePenTipShape(WinInk::PenTipShape penTipShape);
		void UpdatePenTipTransform(WinNumerics::float3x2 penTipTransform);

		Windows::Foundation::Size GetInkSize();
	private:
		std::wstring _Name;
		Models::BrushSize^ Size;
		WinInk::PenTipShape PenTipShape;
		WinNumerics::float3x2 PenTipTransform;
	};
};

