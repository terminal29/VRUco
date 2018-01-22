#pragma once
#include <openvr_driver.h>
using namespace vr;
#include "HMD.h";
#include "DriverLog.h"

class ServerDriver : public IServerTrackedDeviceProvider
{
public:
	ServerDriver();
	virtual ~ServerDriver();

	EVRInitError Init(IVRDriverContext *pDriverContext) override;

	void Cleanup() override;

	const char * const *GetInterfaceVersions() override;

	void RunFrame() override;

	bool ShouldBlockStandbyMode() override;

	void EnterStandby() override;

	void LeaveStandby() override;
private:
	HMD hmd;
};

