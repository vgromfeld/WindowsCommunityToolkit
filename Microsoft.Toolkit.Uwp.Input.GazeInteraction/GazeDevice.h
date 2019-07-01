//Copyright (c) Microsoft. All rights reserved. Licensed under the MIT license.
//See LICENSE in the project root for license information.

#pragma once

BEGIN_NAMESPACE_GAZE_INPUT

using namespace Windows::Devices::Input::Preview;

ref class GazeDevice
{
private:
	GazeDevice(GazeDevicePreview^ device);
internal:
	property unsigned int Id { unsigned int get(); }
	IAsyncOperation<bool>^ RequestCalibrationAsync();

	static GazeDevice^ Create(GazeDevicePreview^ device);
	void Destroy();
private:
	GazeDevicePreview^ const _device;
};

END_NAMESPACE_GAZE_INPUT

