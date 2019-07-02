#include "pch.h"
#include "GazeDevice.h"

#include "GazePointer.h"

BEGIN_NAMESPACE_GAZE_INPUT

using namespace Windows::Devices::Input::Preview;

GazeDevice::GazeDevice(GazePointer^ gazePointer, GazeDevicePreview^ device)
	: _device(device)
{
	_isReady = device->ConfigurationState == GazeDeviceConfigurationStatePreview::Ready;

	if (_isReady)
	{
		gazePointer->IncrementDeviceReadyCount();
	}
}

unsigned int GazeDevice::Id::get() { return _device->Id; }

IAsyncOperation<bool>^ GazeDevice::RequestCalibrationAsync(GazePointer^ gazePointer)
{ 
	if (_isReady)
	{
		_isReady = false;
		gazePointer->DecrementDeviceReadyCount();
	}

	return _device->RequestCalibrationAsync(); 
}

void GazeDevice::OnUpdated(GazePointer^ gazePointer, GazeDeviceWatcherUpdatedPreviewEventArgs^ args)
{
	if (args->Device->ConfigurationState == GazeDeviceConfigurationStatePreview::Ready)
	{
		if (!_isReady)
		{
			_isReady = true;
			gazePointer->IncrementDeviceReadyCount();
		}
	}
	else if (_isReady)
	{
		_isReady = false;
		gazePointer->DecrementDeviceReadyCount();
	}
}


GazeDevice^ GazeDevice::Create(GazePointer^ gazePointer, GazeDevicePreview^ device)
{
	auto value = device != nullptr && device->CanTrackEyes ? ref new GazeDevice(gazePointer, device) : nullptr;
	return value;
}

void GazeDevice::Destroy(GazePointer^ gazePointer)
{
	if (_isReady)
	{
		_isReady = false;
		gazePointer->DecrementDeviceReadyCount();
	}
}

END_NAMESPACE_GAZE_INPUT
