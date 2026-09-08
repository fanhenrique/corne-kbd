#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Internal imports
#include "keymap/layers.h"

#define VID "4653"
#define PID "0004"
#define INTERFACE "1"

#define REPORT_SIZE 32
#define PAYLOAD_MARK 0x90
#define PAYLOAD_MARK_INDEX 24
#define LAYER_INDEX 25


#define DEFINE_LAYER_NAME(name) [name] = #name,

static const char *layer_names[] = {
    LAYER_LIST(DEFINE_LAYER_NAME)
};

#undef DEFINE_LAYER_NAME

#define LAYER_COUNT (sizeof(layer_names) / sizeof(layer_names[0]))

static char *find_hidraw(char *device_path, size_t size)
{
    static char path[PATH_MAX];

    DIR *dir = opendir("/dev");

    if (!dir)
        return NULL;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, "hidraw", 6) != 0)
            continue;

        snprintf(
            path,
            sizeof(path),
            "/sys/class/hidraw/%s/device",
            entry->d_name
        );

        char real_path[PATH_MAX];

        if (!realpath(path, real_path))
            continue;

        /*
         * Verifica VID/PID
         *
         * Exemplo:
         * .../0003:4653:0004.000A
         */
        char device_id[64];

        snprintf(
            device_id,
            sizeof(device_id),
            ":%s:%s.",
            VID,
            PID
        );

        if (!strstr(real_path, device_id))
            continue;

        /*
         * Verifica a interface USB.
         *
         * Exemplo:
         * .../3-2:1.1/...
         */
        char interface_id[32];

        snprintf(
            interface_id,
            sizeof(interface_id),
            ":1.%s/",
            INTERFACE
        );

        if (!strstr(real_path, interface_id))
            continue;

        snprintf(
            device_path,
            size,
            "/dev/%s",
            entry->d_name
        );

        closedir(dir);

        return device_path;
    }

    closedir(dir);

    return NULL;
}

int main(void)
{
    char device[PATH_MAX];

    if (!find_hidraw(device, sizeof(device)))
        return 1;

    int fd = open(device, O_RDONLY);

    if (fd < 0)
        return 1;

    unsigned char report[REPORT_SIZE];

    while (1) {
        ssize_t bytes = read(fd, report, sizeof(report));

        if (bytes <= 0)
            continue;

        /*
         * Garante que temos os bytes necessários.
         */
        if (bytes <= LAYER_INDEX)
            continue;

        /*
         * Byte 24 = marcador 0x90
         */
        if (report[PAYLOAD_MARK_INDEX] != PAYLOAD_MARK)
            continue;

        /*
         * Byte 25 = número da camada
         */
        unsigned int layer = report[LAYER_INDEX];

        /*
         * Verifica se a camada existe.
         */
        if (layer >= LAYER_COUNT)
            continue;

        // printf("%s\n", LAYERS[layer]);
        printf("%s\n", layer_names[layer]);
        fflush(stdout);
    }

    close(fd);

    return 0;
}
