#pragma once
#include <WindowsNumerics.h>
#include <string.h>
#include "BrushSize.h"

namespace Models {
	ref class BrushData sealed
	{
	public:
		BrushData();
		BrushData(const BrushSize size, const Windows::UI::Input::Inking::PenTipShape penTipShape, const Windows::Foundation::Numerics::float3x2 penTipTransform);

		std::shared_ptr<std::wstring> GetName();

		void UpdateSize(BrushSize size);
		void UpdatePenTipShape(Windows::UI::Input::Inking::PenTipShape penTipShape);
		void UpdatePenTipTransform(Windows::Foundation::Numerics::float3x2 penTipTransform);

		Windows::Foundation::Size GetInkSize();
	private:
		std::shared_ptr<std::wstring> _Name;
		BrushSize^ Size;
		Windows::UI::Input::Inking::PenTipShape PenTipShape;
		Windows::Foundation::Numerics::float3x2 PenTipTransform;
	};
};

