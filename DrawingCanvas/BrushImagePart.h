#pragma once
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <memory>
#include "BgraBitmapPixelIterator.h"

namespace Rendering {
	class BrushImagePart
	{
	public:
		BrushImagePart();
		BrushImagePart(
			winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& originBitmap,
			winrt::Windows::Graphics::Imaging::BitmapPixelFormat const& pixelFormat,
			winrt::Windows::Graphics::Imaging::BitmapAlphaMode const& alphaMode
		);
		//BrushImagePart(BrushImagePart const& rhs);

		int PixelCount() const;

		void ConvertToGrayScale();

		void SetBitmap(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& originBitmap);

		bool IsBitmapSet() const;

		winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap Bitmap() const;

		winrt::Windows::Graphics::Imaging::BitmapPixelFormat const& PixelFormat();

		winrt::Windows::Graphics::Imaging::BitmapAlphaMode const& AlphaMode();

		BrushImagePart& operator=(BrushImagePart const& rhs);

		Rendering::BgraBitmapPixelIterator begin();

		Rendering::BgraBitmapPixelIterator end();
	private:
		int PixelCount(winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap const& bitmap) const;

	private:
		winrt::Windows::Graphics::Imaging::BitmapPixelFormat pixelFormat;

		winrt::Windows::Graphics::Imaging::BitmapAlphaMode alphaMode;

		winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap activeBitmap;

	};


	/*class iterator
	{
	public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator(pointer ptr) : ptr_(ptr) { }
		self_type operator++() { self_type i = *this; ptr_++; return i; }
		self_type operator++(int junk) { ptr_++; return *this; }
		reference operator*() { return *ptr_; }
		pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
	private:
		pointer ptr_;
	};*/

}
