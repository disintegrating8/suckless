// slstatus/components/volume.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../util.h"

const char *
vol_perc(const char *unused)
{
    static char vol[16];
    FILE *fp;

    // Get volume
    if (!(fp = popen("pamixer --get-volume", "r")))
        return NULL;
    if (fgets(vol, sizeof(vol), fp) == NULL) {
        pclose(fp);
        return NULL;
    }
    pclose(fp);

    // Strip newline
    vol[strcspn(vol, "\n")] = 0;

    // Check mute status
    FILE *mutefp = popen("pamixer --get-mute", "r");
    if (mutefp) {
        char muted[8];
        if (fgets(muted, sizeof(muted), mutefp)) {
            if (strncmp(muted, "true", 4) == 0) {
                snprintf(vol, sizeof(vol), "MUTE");
            }
        }
        pclose(mutefp);
    }

    return bprintf("%s", vol);
}
