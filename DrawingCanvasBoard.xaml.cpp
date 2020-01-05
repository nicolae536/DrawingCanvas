//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************
#include "pch.h"
#include "DrawingCanvasBoard.xaml.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Input::Inking;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Input::Inking::Core;
using namespace Windows::UI::Input::Inking;
using namespace DrawingCanvas;

// InkCanvas has a limit for the content width/height to be no more than 2^21 physical pixels.
// Here we set the large canvas’s size according to that limit.
const float LARGE_CANVAS_WIDTH = 1 << 21;
const float LARGE_CANVAS_HEIGHT = 1 << 21;

DrawingCanvas::DrawingCanvasBoard::DrawingCanvasBoard() : rootPage(MainPage::Current)
{
	InitializeComponent();

	// Configure the message logging to log all types. User can filter them later using the menuflyout.
	_isLoggingEnabled = false;
	_eventLogger = new InkEventLogger();
	if (_eventLogger != nullptr)
	{
		_eventLogger->SetConfiguration((LogEventTypes)(LogEventTypes::IndependentInputEventType |
			LogEventTypes::InkingEventType |
			LogEventTypes::StrokeEventType |
			LogEventTypes::UnprocessedInputEventType));
	}

	// Page specific handlers
	this->SizeChanged +=
		ref new Windows::UI::Xaml::SizeChangedEventHandler(
			this, &DrawingCanvas::DrawingCanvasBoard::OnSizeChanged);

	this->Loaded +=
		ref new Windows::UI::Xaml::RoutedEventHandler(
			this, &DrawingCanvas::DrawingCanvasBoard::OnLoaded);

	// DPI change event handler
	Windows::Graphics::Display::DisplayInformation^ displayInformation = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
	displayInformation->DpiChanged += ref new Windows::Foundation::TypedEventHandler<
		Windows::Graphics::Display::DisplayInformation^, Platform::Object^>(
			this, &DrawingCanvas::DrawingCanvasBoard::OnDpiChanged);

	// Suspending event handler
	Windows::ApplicationModel::Core::CoreApplication::Suspending += ref new EventHandler<
		Windows::ApplicationModel::SuspendingEventArgs^>(
			this, &DrawingCanvas::DrawingCanvasBoard::OnSuspending);

	// VSIS has a limit for it width/height to be no more
	// than 2^24 physical pixels. Therefore, we should 
	// ensure to be within that limit by taking into consideration of
	// the ink canvas size, pinch zoom ratio, and DPI scaling ratio. The 
	// physical pixel width/height of the virtual surface used to draw dry 
	// ink is computed as
	// VirtualSurfacePixelWidth/Height = 
	//     LARGE_CANVAS_Width/Height * Zoom_Factor * DPI_Scaling_Factor 
	// 
	// Given the large canvas’s width/height specified above, we set the
	// ScrollViewer's maximum zoom factor to 4 to accommodate the VSIS
	// limit when DPI scaling is up to 200%.
	inkScrollViewer->MaxZoomFactor = 4.0f;
	inkScrollViewer->MinZoomFactor = 0.25f;   // 1/4

	// ScrollViewer event handler for pinch-zoom related scenario
	inkScrollViewer->ViewChanged += ref new Windows::Foundation::EventHandler<Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs^>(
		this, &DrawingCanvas::DrawingCanvasBoard::OnViewChanged);

	// Configure Gesture Recognizer to get gestures that will bring up the context menu for cut/copy/paste
	_gestureRecognizer = ref new Windows::UI::Input::GestureRecognizer();
	_gestureRecognizer->GestureSettings = Windows::UI::Input::GestureSettings::Hold | Windows::UI::Input::GestureSettings::RightTap;
	_gestureRecognizer->ShowGestureFeedback = false;

	// Gesture recognizer event handlers
	_gestureRecognizer->RightTapped +=
		ref new Windows::Foundation::TypedEventHandler<
		Windows::UI::Input::GestureRecognizer^, Windows::UI::Input::RightTappedEventArgs^>(
			this, &DrawingCanvas::DrawingCanvasBoard::OnRightTapped);

	_gestureRecognizer->Holding +=
		ref new Windows::Foundation::TypedEventHandler<
		Windows::UI::Input::GestureRecognizer^, Windows::UI::Input::HoldingEventArgs^>(
			this, &DrawingCanvas::DrawingCanvasBoard::OnHolding);

	// Activate custom drying and retrieve an InkSynchronizer that will be used to dry ink seamlessly
	Windows::UI::Input::Inking::InkSynchronizer^ inkSynchronizer = inkCanvas->InkPresenter->ActivateCustomDrying();

	// InkCanvas and input processing configuration. Note that we cache the configuration in a member variable 
	// because the InkPresenter->InputProcessingConfiguration can be queried only from the XAML UI thread.
	// Having retrieved it from there, we will then be able to access it from another thread, such as from the
	// independent input handler which runs on a background thread.
	// We don't need a lock to protect the configuration mode here because no other thread will have access to it
	// at the root page loading time.
	_config = inkCanvas->InkPresenter->InputProcessingConfiguration;

	// Initially the mode is set to inking since we don't have a need to process the input through unprocessed handlers.
	// There is just one special case where we want unprocessed input in inking mode, and that is when the user wants to do
	// selection using barrel button. For this scenario we specify the right drag action to leave unprocessed.
	_config->Mode = Windows::UI::Input::Inking::InkInputProcessingMode::Inking;
	_config->RightDragAction = Windows::UI::Input::Inking::InkInputRightDragAction::LeaveUnprocessed;

	_inputMode = InputModes::InkingMode;

	// Add Handlers
	EnableInkingEventHandlers();
	EnableIndependentInputEventHandlers();
	EnableUnprocessedInputEventHandlers();
	EnableLoggingIndependentInputEventHandlers(true);
	EnableLoggingUnprocessedInputEventHandlers(true);
	EnableLoggingStrokeEventHandlers(true);

	// Collection of points for creating the selection rectangle
	_selectionPoints = ref new Platform::Collections::Vector<Windows::Foundation::Point>();

	// Main component to render ink and shape objects
	_sceneComposer = std::make_unique<SceneComposer>();

	assert(_sceneComposer != nullptr && inkSynchronizer != nullptr);
	_sceneComposer->SetInkSynchronizer(inkSynchronizer);

	// Create the context menu flyout for copy, cut, and paste
	_contextMenuFlyout = ref new ContextMenuFlyout(_sceneComposer);

	// Event handler for selection change in the input mode combobox
	InputMode->SelectionChanged += ref new Windows::UI::Xaml::Controls::SelectionChangedEventHandler(this, &DrawingCanvas::DrawingCanvasBoard::InkingModeSelectionChanged);
}


//-----------------------------------------------------------------------------
// Navigation And sizing
//-----------------------------------------------------------------------------

void DrawingCanvasBoard::OnNavigatedTo(NavigationEventArgs^ e)
{
}

void DrawingCanvas::DrawingCanvasBoard::OnSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e)
{
	assert(_sceneComposer != nullptr);
	_sceneComposer->OnViewSizeChanged(Windows::Foundation::Size(e->NewSize.Width, e->NewSize.Height));
}

//-----------------------------------------------------------------------------
// Scenario UI Handlers  (Called on UI thread)
//-----------------------------------------------------------------------------

void DrawingCanvas::DrawingCanvasBoard::OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Point canvasSize = { 0, 0 };

	// Get the viewport size of current window
	canvasSize.X = (float)(Window::Current->Bounds.Width);
	canvasSize.Y = (float)(Window::Current->Bounds.Height);

	assert(_sceneComposer != nullptr);

	// Set the VirtualSurfaceImageSource to the background of the Output grid
	_imageSource = _sceneComposer->Initialize(Windows::Foundation::Size(0, 0),
		Windows::Foundation::Size(canvasSize.X, canvasSize.Y));

	ImageBrush^ imageBrush = ref new ImageBrush();
	imageBrush->ImageSource = _imageSource;
	Output->Background = imageBrush;

	_sceneComposer->SetContentSize(Windows::Foundation::Size(LARGE_CANVAS_WIDTH, LARGE_CANVAS_HEIGHT));

	// Set grid to the same size of the content
	Output->Width = LARGE_CANVAS_WIDTH;
	Output->Height = LARGE_CANVAS_HEIGHT;
}

void DrawingCanvas::DrawingCanvasBoard::OnDpiChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^)
{
	assert(_sceneComposer != nullptr);
	_sceneComposer->SetDPI(sender->LogicalDpi);
}

void DrawingCanvas::DrawingCanvasBoard::OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e)
{
	assert(_sceneComposer != nullptr);
	_sceneComposer->Trim();
}

void DrawingCanvas::DrawingCanvasBoard::OnClear(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	assert(_sceneComposer != nullptr);
	_sceneComposer->ClearScene();

	if (_eventLogger != nullptr)
	{
		_eventLogger->ClearLog();
		MessageLog->Text = "";
	}
}

void DrawingCanvas::DrawingCanvasBoard::OnInsertShape(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	assert(_sceneComposer != nullptr);
	_sceneComposer->UpdateShape();
}

void DrawingCanvas::DrawingCanvasBoard::InkingModeSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	assert(_sceneComposer != nullptr);
	if (!_sceneComposer->GetSceneSelectionRect().IsEmpty)
	{
		_sceneComposer->UnselectSceneObjects();
	}

	Concurrency::critical_section::scoped_lock lock(_criticalSection);

	if (InputMode->SelectedIndex == 3)
	{
		// Show InkToolbar
		inkToolbar->Visibility = Windows::UI::Xaml::Visibility::Visible;
		_inputMode = InputModes::InkToolbarMode;
	}
	else
	{
		inkToolbar->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		if (InputMode->SelectedIndex == 0)
		{
			_config->Mode = Windows::UI::Input::Inking::InkInputProcessingMode::Inking;
			// We set the right drag action to leave unprocessed so that we can enable barrel button selection
			_config->RightDragAction = Windows::UI::Input::Inking::InkInputRightDragAction::LeaveUnprocessed;
			_inputMode = InputModes::InkingMode;
		}
		else if (InputMode->SelectedIndex == 1)
		{
			_config->Mode = Windows::UI::Input::Inking::InkInputProcessingMode::None;
			_inputMode = InputModes::ErasingMode;
		}
		else if (InputMode->SelectedIndex == 2)
		{
			_config->Mode = Windows::UI::Input::Inking::InkInputProcessingMode::None;
			_inputMode = InputModes::SelectingMode;
		}
	}
}

void DrawingCanvas::DrawingCanvasBoard::TouchInking_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	inkCanvas->InkPresenter->InputDeviceTypes = Windows::UI::Core::CoreInputDeviceTypes::Pen |
		Windows::UI::Core::CoreInputDeviceTypes::Mouse |
		Windows::UI::Core::CoreInputDeviceTypes::Touch;
}

void DrawingCanvas::DrawingCanvasBoard::TouchInking_Unchecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	inkCanvas->InkPresenter->InputDeviceTypes = Windows::UI::Core::CoreInputDeviceTypes::Pen |
		Windows::UI::Core::CoreInputDeviceTypes::Mouse;
}

void DrawingCanvas::DrawingCanvasBoard::InkingEvent_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (_eventLogger != nullptr)
	{
		_eventLogger->EnableLoggingConfiguration(InkingEventType, InkingEvent->IsChecked);
		// Don't enable/disable inking event handlers here since the strokes collected event is needs to be always on for custom dry.
	}
}

void DrawingCanvas::DrawingCanvasBoard::IndependentEvent_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (_eventLogger != nullptr)
	{
		_eventLogger->EnableLoggingConfiguration(IndependentInputEventType, IndependentEvent->IsChecked);
		EnableLoggingIndependentInputEventHandlers(IndependentEvent->IsChecked);
	}
}

void DrawingCanvas::DrawingCanvasBoard::UnprocessedEvent_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (_eventLogger != nullptr)
	{
		_eventLogger->EnableLoggingConfiguration(UnprocessedInputEventType, UnprocessedEvent->IsChecked);
		EnableLoggingUnprocessedInputEventHandlers(UnprocessedEvent->IsChecked);
	}
}

void DrawingCanvas::DrawingCanvasBoard::StrokeEvent_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (_eventLogger != nullptr)
	{
		_eventLogger->EnableLoggingConfiguration(StrokeEventType, StrokeEvent->IsChecked);
		EnableLoggingStrokeEventHandlers(StrokeEvent->IsChecked);
	}
}

void DrawingCanvas::DrawingCanvasBoard::LogToggleSwitch_Toggled(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	_isLoggingEnabled = LogToggleSwitch->IsOn;
	MessageFilter->Visibility = _isLoggingEnabled ? Windows::UI::Xaml::Visibility::Visible : Windows::UI::Xaml::Visibility::Collapsed;
	LogBorder->Visibility = _isLoggingEnabled ? Windows::UI::Xaml::Visibility::Visible : Windows::UI::Xaml::Visibility::Collapsed;
}

//-----------------------------------------------------------------------------
// Inking Event Handlers  (Called on UI thread)
//-----------------------------------------------------------------------------

void DrawingCanvas::DrawingCanvasBoard::OnStrokesCollected(Windows::UI::Input::Inking::InkPresenter^ sender, Windows::UI::Input::Inking::InkStrokesCollectedEventArgs^ args)
{
	assert(_sceneComposer != nullptr);
	_sceneComposer->DoCustomDry();

	Log(StrokeCollected);
}

//-----------------------------------------------------------------------------
// Unprocessed Input Event Handlers  (Called on UI thread)
//-----------------------------------------------------------------------------

void DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerEntered(Windows::UI::Input::Inking::InkUnprocessedInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(UnprocessedInputEntered);
}

void DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerHovered(Windows::UI::Input::Inking::InkUnprocessedInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(UnprocessedInputHover);
}

void DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerPressed(Windows::UI::Input::Inking::InkUnprocessedInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;
	_pointerId = pointerPoint->PointerId;
	_initialPointerPoint = pointerPoint;

	_currentHitTestState = GetHitTestState(pointerPoint->Position);
	switch (_currentHitTestState)
	{
	case PointerHitTestStates::InsideSelectionRect:
		// If we are inside the selection rectangle we allow two types of interaction to bring up the context menu:
		// 1. Press and hold using touch
		// 2. Right click using pen and barrel button
		_gestureRecognizer->ProcessDownEvent(pointerPoint);
		break;

	case PointerHitTestStates::InsideInkingArea:
		// There are two ways we reach this point:
		// 1. We are in selection mode and start a new selection
		// 2. We are in inking mode and start a right drag action using pen

		// Note that when Paste is enabled we need to feed the gesture reco 
		// as well as start a lasso selection since we don't know the intention 
		// of the user yet.
		_currentHitTestSubState = GetInkingSubstate(args);
		switch (_currentHitTestSubState)
		{
		case InkingAreaSubStates::Erasing:
			_prevErasingPoint = pointerPoint->Position;
			break;
		case InkingAreaSubStates::Selecting:
			// In this state we are in barrel button selection and
			// paste is not enabled, so just do selection.
			StartStrokeSelection(pointerPoint->Position);
			break;
		case InkingAreaSubStates::SelectingOrPasting:
			// The user could be starting a selection or starting a
			// gesture to bring up the context menu to paste. So we
			// start selection but also feed the gesture recognizer.
			_gestureRecognizer->ProcessDownEvent(pointerPoint);
			StartStrokeSelection(pointerPoint->Position);
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	Log(UnprocessedInputPressed);
}

void DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerMoved(Windows::UI::Input::Inking::InkUnprocessedInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

	if (_pointerId == pointerPoint->PointerId)
	{
		Windows::Foundation::Collections::IVector<Windows::UI::Input::PointerPoint^>^ pointerPoints = args->GetIntermediatePoints();
		assert(_sceneComposer != nullptr);

		switch (_currentHitTestState)
		{
		case PointerHitTestStates::InsideSelectionRect:
			_gestureRecognizer->ProcessMoveEvents(pointerPoints);
			break;

		case PointerHitTestStates::InsideInkingArea:
			switch (_currentHitTestSubState)
			{
			case InkingAreaSubStates::Erasing:
				_sceneComposer->DoErase(_prevErasingPoint, args->CurrentPoint->Position);
				_prevErasingPoint = pointerPoint->Position;
				break;
			case InkingAreaSubStates::SelectingOrPasting:
				_gestureRecognizer->ProcessMoveEvents(pointerPoints);
				// We cascade to the logic of selecting below
				// since we also want to do lasso selection
			case InkingAreaSubStates::Selecting:
				_sceneComposer->DrawLasso(pointerPoint->Position);
			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	Log(UnprocessedInputMoved);
}

void DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerReleased(Windows::UI::Input::Inking::InkUnprocessedInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;
	assert(_sceneComposer != nullptr);

	if (_pointerId == pointerPoint->PointerId)
	{
		switch (_currentHitTestState)
		{
		case PointerHitTestStates::InsideSelectionRect:
			_gestureRecognizer->ProcessUpEvent(pointerPoint);
			break;

		case PointerHitTestStates::InsideInkingArea:
			switch (_currentHitTestSubState)
			{
			case InkingAreaSubStates::SelectingOrPasting:
				_gestureRecognizer->ProcessUpEvent(pointerPoint);
				// We cascade to the logic of selecting below
				// since we also want to finish lasso selection
			case InkingAreaSubStates::Selecting:
				assert(_selectionPoints != nullptr);
				_selectionPoints->Clear();
				// Create a rectangle with the initial and last position. This will be passed to the selectwithpolyline function
				// on the stroke container, to determine the strokes within the rectangle and mark them as selected.
				_selectionPoints->Append(_initialPointerPoint->Position);
				_selectionPoints->Append(Windows::Foundation::Point(_initialPointerPoint->Position.X, pointerPoint->Position.Y));
				_selectionPoints->Append(pointerPoint->Position);
				_selectionPoints->Append(Windows::Foundation::Point(pointerPoint->Position.X, _initialPointerPoint->Position.Y));

				_sceneComposer->SelectSceneObjects(_selectionPoints);
				_sceneComposer->Invalidate();
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	Log(UnprocessedInputReleased);
}

void DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerExited(Windows::UI::Input::Inking::InkUnprocessedInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(UnprocessedInputExited);
}

void DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerLost(Windows::UI::Input::Inking::InkUnprocessedInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	// If we were maintaining any state that we would clean up on PointerReleased, we would also do it on PointerLost.
	// The only difference is that PointerReleased completes the operation while PointerLost aborts the operation.
	// Here we force an invalidation to remove any temporary drawing, e.g. the selection lasso.
	assert(_sceneComposer != nullptr);
	_sceneComposer->Invalidate();
	Log(UnprocessedInputLost);
}

//-----------------------------------------------------------------------------
// Independent Input Event Handlers  (Called on Background thread)
//-----------------------------------------------------------------------------

void DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerPressing(CoreInkIndependentInputSource^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	assert(_sceneComposer != nullptr);

	PointerHitTestStates currentHitTestState = GetHitTestState(args->CurrentPoint->Position);
	// When input is inside a selection rect, we don't want InkPresenter to handle it, e.g. generate ink.
	// Instead we want to treat it as unprocessed input so it can be handled by our own logic in unprocessed
	// input handler, such as used to move or resize selected ink (code not covered in this sample).
	if (currentHitTestState == PointerHitTestStates::InsideSelectionRect)
	{
		{
			Concurrency::critical_section::scoped_lock lock(_criticalSection);
			_config->Mode = Windows::UI::Input::Inking::InkInputProcessingMode::None;
		}
	}
	else
	{
		// If input is outside of a selection rect, we need to restore the configuration mode based on the 
		// UI setting since we may have changed it if the previous input was inside a selection rect.
		{
			Concurrency::critical_section::scoped_lock lock(_criticalSection);
			if (_inputMode == InputModes::InkingMode)
			{
				_config->Mode = Windows::UI::Input::Inking::InkInputProcessingMode::Inking;
			}
			else if (_inputMode != InputModes::InkToolbarMode)
			{
				_config->Mode = Windows::UI::Input::Inking::InkInputProcessingMode::None;
			}
		}
		// We will always dismiss the selection rect if a new input is received outside of it, e.g. when user
		// starts to write a new stroke.
		if (!_sceneComposer->GetSceneSelectionRect().IsEmpty)
		{
			Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this]()
				{
					_sceneComposer->UnselectSceneObjects();
				}));
		}
	}

	Log(IndependentInputPressed);
}

void DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerMoving(CoreInkIndependentInputSource^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(IndependentInputMoved);
}

void DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerReleasing(CoreInkIndependentInputSource^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(IndependentInputReleased);
}

void DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerExiting(Windows::UI::Input::Inking::Core::CoreInkIndependentInputSource^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(IndependentInputExited);
}

void DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerEntering(Windows::UI::Input::Inking::Core::CoreInkIndependentInputSource^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(IndependentInputEntered);
}

void DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerHovering(Windows::UI::Input::Inking::Core::CoreInkIndependentInputSource^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(IndependentInputHover);
}

void DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerLost(Windows::UI::Input::Inking::Core::CoreInkIndependentInputSource^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(IndependentInputLost);
}

//-----------------------------------------------------------------------------
// Stroke Event Handlers  (Called on UI thread)
//-----------------------------------------------------------------------------

void DrawingCanvas::DrawingCanvasBoard::OnStrokeStarted(Windows::UI::Input::Inking::InkStrokeInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	// get contact area
	// update brush color
	Log(StrokeStarted);
}

void DrawingCanvas::DrawingCanvasBoard::OnStrokeContinued(Windows::UI::Input::Inking::InkStrokeInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	// get contact area
	// update brush color
	Log(StrokeContinued);
}

void DrawingCanvas::DrawingCanvasBoard::OnStrokeEnded(Windows::UI::Input::Inking::InkStrokeInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(StrokeEnded);
}

void DrawingCanvas::DrawingCanvasBoard::OnStrokeCanceled(Windows::UI::Input::Inking::InkStrokeInput^ sender, Windows::UI::Core::PointerEventArgs^ args)
{
	Log(StrokeCanceled);
}

//-----------------------------------------------------------------------------
// Gesture Recognizer Event Handlers  (Called on UI thread)
//-----------------------------------------------------------------------------

void DrawingCanvas::DrawingCanvasBoard::OnRightTapped(Windows::UI::Input::GestureRecognizer^ sender, Windows::UI::Input::RightTappedEventArgs^ args)
{
	LaunchContextMenu(_initialPointerPoint->Position);
}

void DrawingCanvas::DrawingCanvasBoard::OnHolding(Windows::UI::Input::GestureRecognizer^ sender, Windows::UI::Input::HoldingEventArgs^ args)
{
	// We only allow touch hold gesture to bring up context menu.
	if (args->PointerDeviceType == Windows::Devices::Input::PointerDeviceType::Touch && args->HoldingState == Windows::UI::Input::HoldingState::Started)
	{
		LaunchContextMenu(_initialPointerPoint->Position);
		_gestureRecognizer->CompleteGesture();
	}
}

//-----------------------------------------------------------------------------
// View Event Handlers  (Called on UI thread)
//-----------------------------------------------------------------------------

void DrawingCanvas::DrawingCanvasBoard::OnViewChanged(Platform::Object^, Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs^ e)
{
	assert(_sceneComposer != nullptr);
	assert(inkScrollViewer->ZoomFactor >= 0.25 && inkScrollViewer->ZoomFactor <= 4);
	if (!e->IsIntermediate)
	{
		// content has been scaled during manipulation
		_sceneComposer->SetContentZoomFactor(inkScrollViewer->ZoomFactor);
	}
}

//-----------------------------------------------------------------------------
// Helper Methods
//-----------------------------------------------------------------------------

void DrawingCanvas::DrawingCanvasBoard::EnableInkingEventHandlers()
{
	_strokesCollectedToken = inkCanvas->InkPresenter->StrokesCollected +=
		ref new Windows::Foundation::TypedEventHandler<
		Windows::UI::Input::Inking::InkPresenter^, Windows::UI::Input::Inking::InkStrokesCollectedEventArgs^>(
			this, &DrawingCanvas::DrawingCanvasBoard::OnStrokesCollected);
}

// Enable the PointerPressing handler for hit-testing.
void DrawingCanvas::DrawingCanvasBoard::EnableIndependentInputEventHandlers()
{
	if (_independentInput == nullptr)
	{
		// Create Independent Input Source to handle input in background thread needed for
		// gesture detection
		_independentInput = CoreInkIndependentInputSource::Create(inkCanvas->InkPresenter);
	}

	assert(_independentInput != nullptr);
	_independentInputPressingToken = _independentInput->PointerPressing +=
		ref new Windows::Foundation::TypedEventHandler<
		CoreInkIndependentInputSource^, Windows::UI::Core::PointerEventArgs^>(
			this, &DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerPressing);
}

// Enable/disable the handlers that are used only for logging. The rest we
// need in order to preserve inking functionality.
void DrawingCanvas::DrawingCanvasBoard::EnableLoggingIndependentInputEventHandlers(bool enable)
{
	if (_independentInput == nullptr)
	{
		// Create Independent Input Source to handle input in background thread needed for
		// gesture detection
		_independentInput = CoreInkIndependentInputSource::Create(inkCanvas->InkPresenter);
	}

	assert(_independentInput != nullptr);
	if (enable)
	{
		_independentInputMovingToken = _independentInput->PointerMoving +=
			ref new Windows::Foundation::TypedEventHandler<
			CoreInkIndependentInputSource^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerMoving);

		_independentInputReleasingToken = _independentInput->PointerReleasing +=
			ref new Windows::Foundation::TypedEventHandler<
			CoreInkIndependentInputSource^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerReleasing);

		_independentInputExitingToken = _independentInput->PointerExiting +=
			ref new Windows::Foundation::TypedEventHandler<
			CoreInkIndependentInputSource^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerExiting);

		_independentInputEnteringToken = _independentInput->PointerEntering +=
			ref new Windows::Foundation::TypedEventHandler<
			CoreInkIndependentInputSource^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerEntering);

		_independentInputHoveringToken = _independentInput->PointerHovering +=
			ref new Windows::Foundation::TypedEventHandler<
			CoreInkIndependentInputSource^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerHovering);

		_independentInputLostToken = _independentInput->PointerLost +=
			ref new Windows::Foundation::TypedEventHandler<
			CoreInkIndependentInputSource^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::IndependentInputOnPointerLost);
	}
	else
	{
		_independentInput->PointerMoving -= _independentInputMovingToken;
		_independentInput->PointerReleasing -= _independentInputReleasingToken;
		_independentInput->PointerExiting -= _independentInputExitingToken;
		_independentInput->PointerEntering -= _independentInputEnteringToken;
		_independentInput->PointerHovering -= _independentInputHoveringToken;
		_independentInput->PointerLost -= _independentInputLostToken;
	}
}

// Enable unprocessed input handlers used for interacting with ink.
void DrawingCanvas::DrawingCanvasBoard::EnableUnprocessedInputEventHandlers()
{
	_unprocessedInputPressedToken = inkCanvas->InkPresenter->UnprocessedInput->PointerPressed +=
		ref new Windows::Foundation::TypedEventHandler<
		InkUnprocessedInput^, Windows::UI::Core::PointerEventArgs^>(
			this, &DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerPressed);

	_unprocessedInputMovedToken = inkCanvas->InkPresenter->UnprocessedInput->PointerMoved +=
		ref new Windows::Foundation::TypedEventHandler<
		InkUnprocessedInput^, Windows::UI::Core::PointerEventArgs^>(
			this, &DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerMoved);

	_unprocessedInputReleasedToken = inkCanvas->InkPresenter->UnprocessedInput->PointerReleased +=
		ref new Windows::Foundation::TypedEventHandler<
		InkUnprocessedInput^, Windows::UI::Core::PointerEventArgs^>(
			this, &DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerReleased);

	_unprocessedInputLostToken = inkCanvas->InkPresenter->UnprocessedInput->PointerLost +=
		ref new Windows::Foundation::TypedEventHandler<
		Windows::UI::Input::Inking::InkUnprocessedInput^, Windows::UI::Core::PointerEventArgs^>(
			this, &DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerLost);
}

// Enable/disable the handlers that are used only for logging. The rest we
// need in order to preserve inking functionality.
void DrawingCanvas::DrawingCanvasBoard::EnableLoggingUnprocessedInputEventHandlers(bool enable)
{
	if (enable)
	{
		_unprocessedInputEnteredToken = inkCanvas->InkPresenter->UnprocessedInput->PointerEntered +=
			ref new Windows::Foundation::TypedEventHandler<
			InkUnprocessedInput^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerEntered);

		_unprocessedInputHoveredToken = inkCanvas->InkPresenter->UnprocessedInput->PointerHovered +=
			ref new Windows::Foundation::TypedEventHandler<
			InkUnprocessedInput^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerHovered);

		_unprocessedInputExitedToken = inkCanvas->InkPresenter->UnprocessedInput->PointerExited +=
			ref new Windows::Foundation::TypedEventHandler<
			InkUnprocessedInput^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::UnprocessedInputOnPointerExited);
	}
	else
	{
		inkCanvas->InkPresenter->UnprocessedInput->PointerEntered -= _unprocessedInputEnteredToken;
		inkCanvas->InkPresenter->UnprocessedInput->PointerHovered -= _unprocessedInputHoveredToken;
		inkCanvas->InkPresenter->UnprocessedInput->PointerExited -= _unprocessedInputExitedToken;
	}
}

void DrawingCanvas::DrawingCanvasBoard::EnableLoggingStrokeEventHandlers(bool enable)
{
	if (enable)
	{
		_strokeStartedToken = inkCanvas->InkPresenter->StrokeInput->StrokeStarted +=
			ref new Windows::Foundation::TypedEventHandler<
			InkStrokeInput^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::OnStrokeStarted);

		_stokeContinuedToken = inkCanvas->InkPresenter->StrokeInput->StrokeContinued +=
			ref new Windows::Foundation::TypedEventHandler<
			InkStrokeInput^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::OnStrokeContinued);

		_strokeEndedToken = inkCanvas->InkPresenter->StrokeInput->StrokeEnded +=
			ref new Windows::Foundation::TypedEventHandler<
			InkStrokeInput^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::OnStrokeEnded);

		_strokeCanceledToken = inkCanvas->InkPresenter->StrokeInput->StrokeCanceled +=
			ref new Windows::Foundation::TypedEventHandler<
			Windows::UI::Input::Inking::InkStrokeInput^, Windows::UI::Core::PointerEventArgs^>(
				this, &DrawingCanvas::DrawingCanvasBoard::OnStrokeCanceled);
	}
	else
	{
		inkCanvas->InkPresenter->StrokeInput->StrokeStarted -= _strokeStartedToken;
		inkCanvas->InkPresenter->StrokeInput->StrokeContinued -= _stokeContinuedToken;
		inkCanvas->InkPresenter->StrokeInput->StrokeEnded -= _strokeEndedToken;
		inkCanvas->InkPresenter->StrokeInput->StrokeCanceled -= _strokeCanceledToken;
	}
}

void DrawingCanvas::DrawingCanvasBoard::Log(LogEventAction action)
{
	if (_eventLogger != nullptr)
	{
		// Call dispatcher only if we are not in the UI Thread
		if (Dispatcher->HasThreadAccess)
		{
			UpdateMessageLog(action);
		}
		else
		{
			Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this, action]()
				{
					UpdateMessageLog(action);
				}));
		}
	}
}

void DrawingCanvas::DrawingCanvasBoard::UpdateMessageLog(LogEventAction action)
{
	if (_isLoggingEnabled)
	{
		_eventLogger->Log(action);
		MessageLog->Text = ref new Platform::String(_eventLogger->GetLog().c_str());
	}
}

// Note that this method can be called on either UI thread (unprocessed input handlers) or Background thread (independent input handlers)
DrawingCanvasBoard::PointerHitTestStates DrawingCanvas::DrawingCanvasBoard::GetHitTestState(Windows::Foundation::Point position)
{
	Concurrency::critical_section::scoped_lock lock(_criticalSection);

	PointerHitTestStates currentMode = PointerHitTestStates::None;

	// Determine the area and mode where the point landed
	if (_sceneComposer->GetSceneSelectionRect().Contains(position))
	{
		currentMode = PointerHitTestStates::InsideSelectionRect;
	}
	else
	{
		currentMode = PointerHitTestStates::InsideInkingArea;
	}
	return currentMode;
}

// This method is used to determine the substate of inking when the input is not inside a selection rectangle.
// It could be either 
// 1) Erasing with eraser button or in erasing mode;
// 2) In inking mode with barrel button or in selection mode. The user could be starting a new selection or doing 
//    a paste if paste is enabled, i.e. user has performed copy/cut before.
DrawingCanvasBoard::InkingAreaSubStates DrawingCanvas::DrawingCanvasBoard::GetInkingSubstate(Windows::UI::Core::PointerEventArgs^ args)
{
	InkingAreaSubStates state = InkingAreaSubStates::AreaNone;

	if (_inputMode == InputModes::ErasingMode || args->CurrentPoint->Properties->IsEraser)
	{
		state = InkingAreaSubStates::Erasing;
	}
	else if ((_inputMode == InputModes::InkToolbarMode) &&
		(inkToolbar->ActiveTool == inkToolbar->GetToolButton(InkToolbarTool::Eraser)))
	{
		state = InkingAreaSubStates::Erasing;
	}
	else
	{
		// We're either in inking mode with barrel button or in selection mode so 
		// determine the substate based on whether we can paste
		if (_sceneComposer->CanPaste())
		{
			state = InkingAreaSubStates::SelectingOrPasting;
		}
		else
		{
			state = InkingAreaSubStates::Selecting;
		}
	}

	return state;
}

void DrawingCanvas::DrawingCanvasBoard::StartStrokeSelection(Windows::Foundation::Point position)
{
	assert(_sceneComposer != nullptr);
	_sceneComposer->UnselectSceneObjects();
	_sceneComposer->StartLassoSelection(position);
}

void DrawingCanvas::DrawingCanvasBoard::LaunchContextMenu(Windows::Foundation::Point contextMenuPosition)
{
	if (_contextMenuFlyout != nullptr)
	{
		// We enable Copy and Cut (but no Paste) over a selection. Everywhere else we enable only Paste.
		bool enablePasteMenuItem = (_currentHitTestState != PointerHitTestStates::InsideSelectionRect);
		_contextMenuFlyout->EnablePasteItemOnly(enablePasteMenuItem, contextMenuPosition);
		_contextMenuFlyout->ShowAt(inkCanvas, contextMenuPosition);
	}
}