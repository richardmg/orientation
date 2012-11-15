import QtQuick 1.1

Rectangle {
    id: root
    width: 800
    height: 600
    color: "green"

    Connections {
        target: screen
        onOrientationChanged: console.log("orientationChanged:" + orientation)
    }

    Rectangle {
        width: 100
        height: 100
        color: "blue"
    }

}
