/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2022 Raspberry Pi Ltd
 */

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.2

/* old=cd2355 red=ad152a b4=18224f */

Button {
    font.family: notosans.name
    font.capitalization: Font.AllUppercase
    Material.background: activeFocus ? "#d1dcfb" : "#ffffff"
    Material.foreground: "#18224f"
    Material.roundedScale: Material.ExtraSmallScale
    Accessible.onPressAction: clicked()
    Keys.onEnterPressed: clicked()
    Keys.onReturnPressed: clicked()
}
