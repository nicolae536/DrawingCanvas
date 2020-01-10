#pragma once

namespace Models {
	ref class BrushSize sealed {
	public:
		BrushSize(float width, float height);
		float GetWidth();
		float GetHeight();
		void SetWidth(float width);
		void SetHeight(float height);
	private:
		float Width;
		float Height;
	};
};