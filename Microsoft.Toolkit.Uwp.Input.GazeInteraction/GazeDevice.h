//Copyright (c) Microsoft. All rights reserved. Licensed under the MIT license.
//See LICENSE in the project root for license information.

#pragma once

BEGIN_NAMESPACE_GAZE_INPUT

using namespace Windows::Devices::Input::Preview;

ref class GazePointer;

ref class GazeDevice
{
private:
	GazeDevice(GazePointer^ gazePointer, GazeDevicePreview^ device);
internal:
	property unsigned int Id { unsigned int get(); }
	IAsyncOperation<bool>^ RequestCalibrationAsync(GazePointer^ gazePointer);
	void OnUpdated(GazePointer^ gazePointer, GazeDeviceWatcherUpdatedPreviewEventArgs^ args);
	void OnCalibrationTimeout();

	static GazeDevice^ Create(GazePointer^ gazePointer, GazeDevicePreview^ device);
	void Destroy(GazePointer^ gazePointer);
private:
	GazeDevicePreview^ const _device;
	bool _isReady;
};

END_NAMESPACE_GAZE_INPUT

