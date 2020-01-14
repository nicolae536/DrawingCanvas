#pragma once
#include <WindowsNumerics.h>
#include <string.h>
#include "BrushSize.h"
#include "StringUtils.h"

namespace DrawingCanvas {
	public ref class BrushData sealed
	{
	public:
		BrushData();
		BrushData(
			Platform::String^ name,
			BrushSize^ size,
			WinInk::PenTipShape penTipShape,
			WinNumerics::float3x2 penTipTransform
		);

		property Platform::String^ Name {
			Platform::String^ get() {
				return StringUtils::WStringToPlatformString(_Name);
			}
		};
		BrushSize^ GetBrushSize();
		WinInk::PenTipShape GetPenTipShape();
		WinNumerics::float3x2 GetPenTipTransform();

		void UpdateSize(BrushSize^ size);
		void UpdatePenTipShape(WinInk::PenTipShape penTipShape);
		void UpdatePenTipTransform(WinNumerics::float3x2 penTipTransform);

		Windows::Foundation::Size GetInkSize();
	private:
		std::wstring _Name;
		BrushSize^ Size;
		WinInk::PenTipShape PenTipShape;
		WinNumerics::float3x2 PenTipTransform;
	};
};
