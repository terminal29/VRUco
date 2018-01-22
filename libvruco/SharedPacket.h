#pragma once
#include <memory>
#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace SharedPacket {

	struct DataPacket {
		bool new_data_available = false;
		float hmd_position[3] = { 0 }; // {x,y,z}
		float hmd_quaternion[4] = { 0,0,0,1 }; // {x,y,z,w}
	};


	DataPacket* getSharedDataPacket();

}



