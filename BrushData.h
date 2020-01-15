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
			Platform::String^ id,
			Platform::String^ name,
			BrushSize^ size,
			WinInk::PenTipShape penTipShape,
			WinNumerics::float3x2 penTipTransform
		);
	public:
		property Platform::String^ Id {
			Platform::String^ get() {
				return StringUtils::WStringToPlatformString(_Id);
			}
		}
		property Platform::String^ Name {
			Platform::String^ get() {
				return StringUtils::WStringToPlatformString(_Name);
			};
			void set(Platform::String^ value) {
				_Name = StringUtils::PlatformStringToWString(value);
			}
		};
		property BrushSize^ Size {
			BrushSize^ get() {
				return _Size;
			};
			void set(BrushSize^ value) {
				_Size = value;
			}
		};
		property WinInk::PenTipShape PenTipShape {
			WinInk::PenTipShape get() {
				return _PenTipShape;
			};
			void set(WinInk::PenTipShape value) {
				_PenTipShape = value;
			}
		};
		property WinNumerics::float3x2 PenTipTransform {
			WinNumerics::float3x2 get() {
				return _PenTipTransform;
			};
			void set(WinNumerics::float3x2 value) {
				_PenTipTransform = value;
			}
		};
	private:
		std::wstring _Id;
		std::wstring _Name;
		BrushSize^ _Size;
		WinInk::PenTipShape _PenTipShape;
		WinNumerics::float3x2 _PenTipTransform;
	};
};
