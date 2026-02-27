/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2024 T3 Foundation
 */

#ifndef DFUDRIVERINSTALLER_H
#define DFUDRIVERINSTALLER_H

class DfuDriverInstaller
{
public:
    /* Check if WinUSB driver is installed for VID:0451/PID:6165.
     * Returns true if device is not connected OR driver is already installed. */
    static bool isDriverInstalled();

    /* Install WinUSB driver via wdi-simple.exe (libwdi) — requires UAC elevation. */
    static bool installDriver();
};

#endif // DFUDRIVERINSTALLER_H
