#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>

#include <aruco/aruco.h>
#include <aruco/aruco.h>
#include <markermapper.h>
#include "ps3eye_context.h"

namespace RoomSetup {
	extern bool has_completed_setup; // = false;

	extern aruco::MarkerMap GetMarkerMap(ps3eye_context& camera_ctx, const aruco::CameraParameters& camera_params, std::string dictionary_name, float aruco_square_dims);
}

