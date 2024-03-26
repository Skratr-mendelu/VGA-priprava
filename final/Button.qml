import QtQuick 2.0

Rectangle{
    property alias labelText: labelText.text
    height: 40
    width: 40
    radius: 10
    color: Qt.rgba(1.0, 1.0, 1.0, 0.8)

    Text{
        id: labelText
        text: ">"
        anchors.centerIn: parent
    }
}
