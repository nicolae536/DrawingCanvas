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

winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap> PlatformServices::FilePicker::PickImageAsync()
{
	// TODO modify this to use corutines recheck intellisense when it gets better
	winrt::Windows::Storage::StorageFile storageFile = filePicker.PickSingleFileAsync().get();

	if (storageFile != nullptr) {
		auto fileStream = storageFile.OpenAsync(winrt::Windows::Storage::FileAccessMode::ReadWrite).get();
		winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage;
		bitmapImage.DecodePixelWidth(200);
		bitmapImage.SetSourceAsync(fileStream).get();

		winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap wb(bitmapImage.PixelWidth(), bitmapImage.PixelHeight());
		fileStream.Seek(0);
		wb.SetSourceAsync(fileStream);

		co_return wb;
	}

	co_return nullptr;
}
