import QtQuick 2.9
import QtQuick.Controls

ComboBox {
    font.family: notosans.name
    Material.background: "#dddddd"
    Material.foreground: "#18224f"
    background: Rectangle {
        color: "#dddddd"
        radius: 5
    }
    Material.roundedScale: Material.ExtraSmallScale
    Accessible.onPressAction: clicked()
    Keys.onEnterPressed: clicked()
    Keys.onReturnPressed: clicked()
}
