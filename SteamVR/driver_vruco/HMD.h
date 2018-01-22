#pragma once
#include <openvr_driver.h>
using namespace vr;
#include "DriverLog.h"
#include <SharedPacket.h>


class HMD : public ITrackedDeviceServerDriver, public IVRDisplayComponent
{
public:
	HMD();
	virtual ~HMD();
	virtual void update();

	// Inherited via ITrackedDeviceServerDriver
	virtual EVRInitError Activate(uint32_t unObjectId) override;
	virtual void Deactivate() override;
	virtual void EnterStandby() override;
	virtual void * GetComponent(const char * pchComponentNameAndVersion) override;
	virtual void DebugRequest(const char * pchRequest, char * pchResponseBuffer, uint32_t unResponseBufferSize) override;
	virtual DriverPose_t GetPose() override;

	// Inherited via IVRDisplayComponent
	virtual void GetWindowBounds(int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight) override;
	virtual bool IsDisplayOnDesktop() override;
	virtual bool IsDisplayRealDisplay() override;
	virtual void GetRecommendedRenderTargetSize(uint32_t * pnWidth, uint32_t * pnHeight) override;
	virtual void GetEyeOutputViewport(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight) override;
	virtual void GetProjectionRaw(EVREye eEye, float * pfLeft, float * pfRight, float * pfTop, float * pfBottom) override;
	virtual DistortionCoordinates_t ComputeDistortion(EVREye eEye, float fU, float fV) override;
private:
	uint32_t _object_id;
	int _window_width = 1024;
	int _window_height = 768;
	DriverPose_t _hmd_pose;
	SharedPacket::DataPacket* _shared_data;
};

