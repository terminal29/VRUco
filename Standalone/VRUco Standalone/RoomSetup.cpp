#include "RoomSetup.h"

namespace RoomSetup {
	bool has_completed_setup = false;

	auto WriteLog = [](std::string info) {std::cout << info << std::endl;};

	aruco::MarkerMap GetMarkerMap(ps3eye_context& camera_ctx, const aruco::CameraParameters& camera_params, std::string dictionary_name, float aruco_square_dims) {
		WriteLog("Calibration!");
		auto mapper = aruco_mm::MarkerMapper::create();

		mapper->setParams(camera_params, aruco_square_dims, 58, true);
		mapper->getMarkerDetector().setDictionary(dictionary_name);
		mapper->getMarkerDetector().setDetectionMode(aruco::DetectionMode::DM_NORMAL);

		const int CAMERA_WIDTH = 640;
		const int CAMERA_HEIGHT = 480;

		uint8_t* camera_data_raw = new uint8_t[CAMERA_WIDTH * CAMERA_HEIGHT * 3];
		IplImage* camera_data_ipl = cvCreateImage(cvSize(CAMERA_WIDTH, CAMERA_HEIGHT), 8, 3);
		cv::Mat current_frame;
		cv::namedWindow("Calibration");

		aruco::MarkerDetector marker_detector;
		marker_detector.setDictionary(aruco::Dictionary::ARUCO_MIP_36h12);


		long frame_count = 0;

		WriteLog("Press e to end calibration");
		while (true) {
			char c = cv::waitKey(10);
			if (c == 'e')
				break;

			// Get next frame
			camera_ctx.eye->getFrame(camera_data_raw);
			cvSetData(camera_data_ipl, camera_data_raw, camera_data_ipl->widthStep);
			current_frame = cv::cvarrToMat(camera_data_ipl);

			std::vector<aruco::Marker> markers = marker_detector.detect(current_frame, camera_params, aruco_square_dims);

			
			if (markers.size() > 3) {
				mapper->process(current_frame, frame_count++, true);
				WriteLog("Frame count " + std::to_string(frame_count));
			}
			mapper->drawDetectedMarkers(current_frame, 3);
			imshow("Calibration", current_frame);
		}
		mapper->optimize();

		cv::destroyWindow("Calibration");
		
		delete[] camera_data_raw;
		WriteLog("Done!");
		return mapper->getMarkerMap();
	}
};