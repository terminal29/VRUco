#include "ServerDriver.h"


ServerDriver::ServerDriver()
{
}


ServerDriver::~ServerDriver()
{
}

EVRInitError ServerDriver::Init(IVRDriverContext * pDriverContext)
{
	VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
	InitDriverLog(vr::VRDriverLog());
	DriverLog("===============================================================================\n");
	DriverLog("=============================== ARUcoVR Startup ===============================\n");
	DriverLog("===============================================================================\n");
	VRServerDriverHost()->TrackedDeviceAdded("hmd", vr::TrackedDeviceClass_HMD, &hmd);




}

void ServerDriver::Cleanup()
{
}

const char * const * ServerDriver::GetInterfaceVersions()
{
	return k_InterfaceVersions;
}

void ServerDriver::RunFrame()
{
	hmd.update();
}

bool ServerDriver::ShouldBlockStandbyMode()
{
	return false;
}

void ServerDriver::EnterStandby()
{
}

void ServerDriver::LeaveStandby()
{
}
