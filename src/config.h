#ifndef CONFIG_H
#define CONFIG_H

/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2020 Raspberry Pi Ltd
 */


/* Repository URL */
#define OSLIST_URL                        "https://packages.t3gemstone.org/images/list.json"

/* Time synchronization URL (only used on eglfs QPA platform, URL must be HTTP) */
#define TIME_URL                          "https://packages.t3gemstone.org/images/list.json?time_synchronization"

#define BOOTIMG_URL                       "http://packages.t3gemstone.org/images/boot/%1/%2" // %1: boardName %2: fileName

/* Phone home the name of images downloaded for image popularity ranking */
#define TELEMETRY_URL                     "https://gem-imager-stats.t3gemstone.org"

#define SER_BAUDRATE 921600

/* Hash algorithm for verifying (uncompressed image) checksum */
#define OSLIST_HASH_ALGORITHM             QCryptographicHash::Sha256

/* Update progressbar every 0.1 second */
#define PROGRESS_UPDATE_INTERVAL          100

/* Block size used for writes (currently used when using .zip images only) */
#define IMAGEWRITER_BLOCKSIZE             1*1024*1024

/* Block size used with uncompressed images */
#define IMAGEWRITER_UNCOMPRESSED_BLOCKSIZE 128*1024

/* Block size used when reading during verify stage */
#define IMAGEWRITER_VERIFY_BLOCKSIZE      128*1024

/* Enable caching */
#define IMAGEWRITER_ENABLE_CACHE_DEFAULT        true

/* Do not cache if it would bring free disk space under 5 GB */
#define IMAGEWRITER_MINIMAL_SPACE_FOR_CACHING   5*1024*1024*1024ll

/* Uniflash serial baud rate */
#define UNIFLASH_BAUD_RATE                     921600

#endif // CONFIG_H
