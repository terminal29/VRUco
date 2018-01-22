#include "HMD.h"



HMD::HMD()
{
	_shared_data = SharedPacket::getSharedDataPacket();
}


HMD::~HMD()
{
}

void HMD::update()
{
	if (_shared_data->new_data_available) {
		
		// Update translation
		_hmd_pose.vecPosition[0] = _shared_data->hmd_position[0];
		_hmd_pose.vecPosition[1] = _shared_data->hmd_position[1];
		_hmd_pose.vecPosition[2] = _shared_data->hmd_position[2];
		
		// Update rotation
		_hmd_pose.qRotation.x = _shared_data->hmd_quaternion[0];
		_hmd_pose.qRotation.y = _shared_data->hmd_quaternion[1];
		_hmd_pose.qRotation.z = _shared_data->hmd_quaternion[2];
		_hmd_pose.qRotation.w = _shared_data->hmd_quaternion[3];

		_shared_data->new_data_available = false;
	}
	VRServerDriverHost()->TrackedDevicePoseUpdated(_object_id, _hmd_pose, sizeof(DriverPose_t));
}

EVRInitError HMD::Activate(uint32_t unObjectId)
{
	_object_id = unObjectId;
	PropertyContainerHandle_t prop_handle = VRProperties()->TrackedDeviceToPropertyContainer(_object_id);
	VRProperties()->SetFloatProperty(prop_handle, Prop_UserIpdMeters_Float, 0.065f);
	VRProperties()->SetFloatProperty(prop_handle, Prop_UserHeadToEyeDepthMeters_Float, 0.f);
	VRProperties()->SetFloatProperty(prop_handle, Prop_DisplayFrequency_Float, 90.f);
	VRProperties()->SetFloatProperty(prop_handle, Prop_SecondsFromVsyncToPhotons_Float, 0.1f);
	VRProperties()->SetUint64Property(prop_handle, Prop_CurrentUniverseId_Uint64, 2);
	VRProperties()->SetBoolProperty(prop_handle, Prop_IsOnDesktop_Bool, false);

	_hmd_pose.poseIsValid = true;
	_hmd_pose.result = TrackingResult_Running_OK;
	_hmd_pose.deviceIsConnected = true;

	_hmd_pose.qWorldFromDriverRotation = { 1, 0, 0, 0 };
	_hmd_pose.qDriverFromHeadRotation = { 1, 0, 0, 0 };

	return EVRInitError::VRInitError_None;
}

void HMD::Deactivate()
{
}

void HMD::EnterStandby()
{
}

void * HMD::GetComponent(const char * pchComponentNameAndVersion)
{
	if (0 == strcmp(pchComponentNameAndVersion, vr::IVRDisplayComponent_Version))
	{
		return (vr::IVRDisplayComponent*)this;
	}

	return NULL;
}

void HMD::DebugRequest(const char * pchRequest, char * pchResponseBuffer, uint32_t unResponseBufferSize)
{
	if (unResponseBufferSize >= 1)
		pchResponseBuffer[0] = 0;
}

DriverPose_t HMD::GetPose()
{
	return _hmd_pose;
}

void HMD::GetWindowBounds(int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight)
{
	*pnX = 0;
	*pnY = -768;
	*pnWidth = _window_width;
	*pnHeight = _window_height;
}

bool HMD::IsDisplayOnDesktop()
{
	return true;
}

bool HMD::IsDisplayRealDisplay()
{
	return true;
}

void HMD::GetRecommendedRenderTargetSize(uint32_t * pnWidth, uint32_t * pnHeight)
{
	*pnWidth = _window_width;
	*pnHeight = _window_height;
}

void HMD::GetEyeOutputViewport(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight)
{
	float offset = 150;

	*pnY = 0;
	*pnWidth = (_window_width / 2) - offset;
	*pnHeight = _window_height;

	if (eEye == Eye_Left)
	{
		*pnX = offset;
	}
	else
	{
		*pnX = _window_width / 2;
	}
}

void HMD::GetProjectionRaw(EVREye eEye, float * pfLeft, float * pfRight, float * pfTop, float * pfBottom)
{
	*pfLeft = -1.0;
	*pfRight = 1.0;
	*pfTop = -1.0;
	*pfBottom = 1.0;
}

DistortionCoordinates_t HMD::ComputeDistortion(EVREye eEye, float fU, float fV)
{
	vr::DistortionCoordinates_t oDistortion{};
	oDistortion.rfBlue[0] = fU;
	oDistortion.rfBlue[1] = fV;
	oDistortion.rfGreen[0] = fU;
	oDistortion.rfGreen[1] = fV;
	oDistortion.rfRed[0] = fU;
	oDistortion.rfRed[1] = fV;
	return oDistortion;

}