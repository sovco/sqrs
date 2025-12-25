#include <stdio.h>
#include <stdlib.h>
#define SCLIP_IMPL
#include "options.h"

#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

// struct v4l2_capability
// {
//     __u8 driver[16];
//     __u8 card[32];
//     __u8 bus_info[32];
//     __u32 version;
//     __u32 capabilities;
//     __u32 device_caps;
//     __u32 reserved[3];
// };

void print_webcam_capabilities(const struct v4l2_capability *restrict const cap)
{
    printf("%s driver\n", cap->driver);
    printf("%s card\n", cap->card);
    printf("%s bus_info\n", cap->bus_info);
    printf("%d version\n", cap->version);
    printf("%X capabilities\n", cap->capabilities);
    printf("%d device_caps\n", cap->device_caps);
}

int main(int argc, const char *argv[])
{
    sclip_parse(argc, argv);
    int camerafd = -1;
    struct v4l2_capability webcamcap;
    memset(&webcamcap, 0x00, sizeof(webcamcap));
    if ((camerafd = open(sclip_opt_device_get_value(), O_RDWR, 0)) < 0) {
        fprintf(stderr, "Unable to open device \"%s\"\n", sclip_opt_device_get_value());
        return EXIT_FAILURE;
    }
    if (ioctl(camerafd, VIDIOC_QUERYCAP, &webcamcap) < 0) {
        fprintf(stderr, "Unable to get device capabilites at \"%s\"\n", sclip_opt_device_get_value());
        close(camerafd);
        return EXIT_FAILURE;
    }
    if (!(webcamcap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        fprintf(stderr, "Device \"%s\" is not a webcam\n", sclip_opt_device_get_value());
        close(camerafd);
        return EXIT_FAILURE;
    }
    print_webcam_capabilities(&webcamcap);
    close(camerafd);
    return EXIT_SUCCESS;
}
