# VRUco
An attempt at making a SteamVR driver + standalone program which uses ArUco markers placed in the room to track head position and rotation.

It uses:
- ArUco
- ArUco MarkerMapper
- OpenCV
- libusb (To use PS3 Eye as camera)
- Ps3EyeDriver (Same as above)
- Boost (for ipc between driver and standalone)

Marker sizes are hard coded and camera calibration is set up for the PS3 Eye camera, but in theory it should work with any camera mounted to your head. In saying this however, I would recommend against using it in its current state as there is considerable jitter in the tracking making it almost unusable, I'm just putting it up here in the hope that someone might figure out how to make it better in the future.
