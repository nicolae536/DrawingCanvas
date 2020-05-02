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
	winrt::Windows::Storage::StorageFile storageFile = co_await filePicker.PickSingleFileAsync();

	if (storageFile != nullptr) {
		auto fileStream = co_await storageFile.OpenAsync(winrt::Windows::Storage::FileAccessMode::ReadWrite);
		auto decoder{ co_await Windows::Graphics::Imaging::BitmapDecoder::CreateAsync(fileStream) };	

		Windows::Graphics::Imaging::BitmapTransform transform;
		transform.ScaledWidth(decoder.PixelWidth());
		transform.ScaledHeight(decoder.PixelHeight());

		Windows::Graphics::Imaging::PixelDataProvider pixelData{ co_await decoder.GetPixelDataAsync(
			Windows::Graphics::Imaging::BitmapPixelFormat::Bgra8, // WriteableBitmap uses BGRA format 
			Windows::Graphics::Imaging::BitmapAlphaMode::Straight,
			transform,
			Windows::Graphics::Imaging::ExifOrientationMode::IgnoreExifOrientation, // This sample ignores Exif orientation 
			Windows::Graphics::Imaging::ColorManagementMode::DoNotColorManage
		) };
		winrt::com_array<uint8_t> sourcePixels{ pixelData.DetachPixelData() };
		
		auto m_writeableBitmap = Windows::UI::Xaml::Media::Imaging::WriteableBitmap(decoder.PixelWidth(), decoder.PixelHeight());
		uint8_t* pTargetBytes{ m_writeableBitmap.PixelBuffer().data() };
		for (auto& element : sourcePixels)
		{
			*(pTargetBytes++) = element;
		}

		co_return m_writeableBitmap;
	}

	co_return nullptr;
}
