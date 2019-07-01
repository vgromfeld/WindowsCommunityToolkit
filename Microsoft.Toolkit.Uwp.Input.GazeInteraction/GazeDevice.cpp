#include "pch.h"
#include "GazeDevice.h"

BEGIN_NAMESPACE_GAZE_INPUT

using namespace Windows::Devices::Input::Preview;

GazeDevice::GazeDevice(GazeDevicePreview^ device)
	: _device(device)
{
}

unsigned int GazeDevice::Id::get() { return _device->Id; }

IAsyncOperation<bool>^ GazeDevice::RequestCalibrationAsync() 
{ 
	return _device->RequestCalibrationAsync(); 
}

GazeDevice^ GazeDevice::Create(GazeDevicePreview^ device)
{
	auto value = device != nullptr && device->CanTrackEyes ? ref new GazeDevice(device) : nullptr;
	return value;
}

void GazeDevice::Destroy()
{
}

END_NAMESPACE_GAZE_INPUT
