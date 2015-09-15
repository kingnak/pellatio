import QtQuick 1.1
import Pellatio 1.0

Item {
    Item {
        id: visualDef
        property int tileSize: 50
        property int tileSpace: 5
    }

    Board {
        id: board
        rotation: infoModel.thisPlayer == Color.Red ? 180 : 0
    }

    Item {
        id: controls
        anchors.left: board.right
        y: 0
        width: 200
        height: parent.height

        Column {
            spacing: 5
            Row {
                spacing: 5
                ImageButton {
                    id: rotLeft
                    source: "/images/rot.png"
                    height: 40
                    mirrorImage: true
                    width: controls.width/2-5
                    enabled: rotationModel.canRotateCCW
                    onClicked: rotationModel.rotateCCW()
                }
                ImageButton {
                    id: rotRight
                    source: "/images/rot.png"
                    height: 40
                    width: controls.width/2-5
                    enabled: rotationModel.canRotateCW
                    onClicked: rotationModel.rotateCW()
                }
            }

            CheckBox {
                id: autoCommit
                text: "Auto Confim"
                buttonEnabled: confirmModel.autoConfirm
                onToggled: confirmModel.autoConfirm = on
            }

            Button {
                id: resetMove
                operation: "Reset"
                height: 40
                width: controls.width
                enabled: confirmModel.canReset
                onClicked: confirmModel.reset()
            }

            Button {
                id: confirmMove
                operation: "Confirm"
                height: 40
                width: controls.width
                enabled: confirmModel.canConfirm
                onClicked: confirmModel.confirm()
            }

            Grid {
                rows: 4; columns: 2
                spacing: 5
                Text {
                    text: "You"
                }
                Rectangle {
                    width: 20
                    height: 20
                    color: infoModel.thisPlayer == Color.Red ? "red" : "black"
                }

                Text {
                    text: "Current Player"
                }
                Rectangle {
                    width: 20
                    height: 20
                    color: infoModel.currentPlayer == Color.Red ? "red" : "black"
                }

                Rectangle {
                    width: 20
                    height: 20
                    color: "black"
                }
                Text {
                    text: infoModel.blackPoints
                }

                Rectangle {
                    width: 20
                    height: 20
                    color: "red"
                }
                Text {
                    text: infoModel.redPoints
                }
            }
        }
    }

    width: board.width+controls.width
    height: board.height

    GameMessage {
        onWon: {
            messageLayer.message = "You have won!"
            messageLayer.visible = true;
        }
        onLost: {
            messageLayer.message = "You have lost!"
            messageLayer.visible = true;
        }
        onMessage: {
            messageLayer.message = msg;
            messageLayer.visible = true;
        }
    }

    Item {
        id: messageLayer
        anchors.fill: parent
        visible: false
        z: 10
        property alias message: messageLayer_text.text
        MouseArea {
            anchors.fill: parent
        }
        Rectangle {
            anchors.fill: parent
            color: "#80000000"
        }
        Text {
            id: messageLayer_text
            anchors.centerIn: parent
        }
    }


}
