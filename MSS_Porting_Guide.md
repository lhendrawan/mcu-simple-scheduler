# MSS Porting Guide #

MSS is designed to be highly portable. Most of the MSS source codes are written independently from the target platform/device.

There are basically only 4 files under which shall be adapted/modified when trying to port MSS to another platform/device. There are templates files which can be found under ROOT\_DIRECTORY/Source/mss/templates/target

  * dev\_types.h: contains the basic data type of the target platform. MSS uses the standard data types which are usually supported in stdint.h and stdbool.h. There is also some typedefs definitions which can be used to verify the correct data type assignments.

  * mss\_hal.h: contains device specific data types, macro functions and definitions which are visible to the application.

  * mss\_hal\_int.h: contains device specific data types and macro definitions which are not visible to the application.

  * mss\_hal.c: contains codes which need to be implemented according to the hardware