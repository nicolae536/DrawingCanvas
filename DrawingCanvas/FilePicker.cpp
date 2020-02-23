#include "pch.h"
#include "FilePicker.h"


PlatformServices::FilePicker::FilePicker(std::vector<std::string> const& fileTypes)
	:filePicker()
{
	filePicker.ViewMode(winrt::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
	filePicker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::ComputerFolder);
	for (auto fileType : fileTypes) {
		filePicker.FileTypeFilter().Append(winrt::to_hstring(fileType));
	}
}

winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> PlatformServices::FilePicker::PickFileAsync()
{
	return filePicker.PickSingleFileAsync();	
}

winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage> PlatformServices::FilePicker::PickImageAsync()
{
	winrt::Windows::Storage::StorageFile storageFile = co_await filePicker.PickSingleFileAsync();

	if (storageFile != nullptr) {
		auto fileStream = co_await storageFile.OpenAsync(winrt::Windows::Storage::FileAccessMode::Read);
		winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage;
		bitmapImage.DecodePixelHeight(100);
		bitmapImage.DecodePixelWidth(100);
		co_await bitmapImage.SetSourceAsync(fileStream);
		co_return bitmapImage;
	}

	co_return nullptr;
}
