import QtQuick 2.3

Item {
    id: container
    width: 360
    height: 360

    Text {
        id: title
        text: "Pellatio"
        font.pixelSize: 36
        anchors.horizontalCenter: parent.horizontalCenter
        height: 50
    }

    Item {
        width: parent.width
        height: parent.height-title.height
        anchors.top: title.bottom
        Column {
            spacing: 10
            id: typeChooser
            anchors.fill: parent
            Button {
                operation: "Local Game"
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    typeChooser.visible = false;
                    localChooser.visible = true;
                }
            }
            Button {
                operation: "Network Game"
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                //enabled: false
                onClicked: {
                    typeChooser.visible = false;
                    networkChooser.visible = true;
                }
            }
            Button {
                operation: "Tutorial"
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: false
            }
            Button {
                operation: "Test Game"
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                visible: window.allowTestBoard
                onClicked: {
                    window.startTestWindow()
                }
            }
        }

        Column {
            id: localChooser
            anchors.fill: parent
            visible: false
            spacing: 10
            Button {
                operation: "Single Window"
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: window.startLocalSingleWindow()
            }
            Button {
                operation: "Multiple Windows"
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: window.startLocalMultipleWindow()
            }
        }

        Column {
            id: networkChooser
            anchors.fill: parent
            visible: false
            spacing: 10
            Button {
                operation: "Host Game"
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: window.hostGame()
            }
            Button {
                operation: "Join Game"
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: window.jointGame(host.text)
            }
            TextEdit{
                id: host
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                text: "localhost"
            }
        }
    }
}
