#pragma once
#include "pch.h"
#include <winrt/Windows.Storage.Pickers.h>

namespace PlatformServices {
	class FilePicker
	{
	public:
		FilePicker() = delete;
		FilePicker(std::vector<std::string> const& fileTypes);

		winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> PickFileAsync();
		
		winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap> PickImageAsync();
	private:
		winrt::Windows::Storage::Pickers::FileOpenPicker filePicker;
	};
}
