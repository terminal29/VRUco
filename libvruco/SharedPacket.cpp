#include "SharedPacket.h"

namespace SharedPacket {
	namespace local {
		boost::interprocess::shared_memory_object _shared_memory_space;
		boost::interprocess::mapped_region _mapped_region;
		bool _has_init = false;
	}

	DataPacket* getSharedDataPacket() {
		if (!local::_has_init) {
			local::_shared_memory_space = boost::interprocess::shared_memory_object(boost::interprocess::open_or_create, "VRUco", boost::interprocess::read_write);
			local::_shared_memory_space.truncate(sizeof(DataPacket));
			local::_mapped_region = boost::interprocess::mapped_region(local::_shared_memory_space, boost::interprocess::read_write);
			local::_has_init = true;
		}
		return static_cast<DataPacket*>(local::_mapped_region.get_address());
	}
}
