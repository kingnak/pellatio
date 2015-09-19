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
            // Rotation
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

            // Confirm / Reset Move
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

            // State / Points
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

            // Remis / Give up
            Button {
                id: offerRemis
                operation: "Offer Remis"
                height: 40
                width: controls.width
                onClicked: optionModel.offerRemis()
            }
            Button {
                id: giveUp
                operation: "Give Up"
                height: 40
                width: controls.width
                onClicked: optionModel.giveUp()
            }
        }
    }

    width: board.width+controls.width
    height: board.height

    GameMessage {
        id: messageObject
        onShow: messageLayer.visible = true
        onHide: {
            messageLayer.visible = false;
            messageLayer_dialog.visible = false;
            messageLayer_question.visible = false;
        }
        onWon: messageLayer.message = "You have won!"
        onLost: messageLayer.message = "You have lost!"
        onRemis: messageLayer.message = "Remis!"
        onTerminated: messageLayer.message = "Connection was terminated"
        onMessage: messageLayer.message = msg
        onQuestion: {
            messageLayer.message = msg;
            messageLayer_op1.operation = op1;
            messageLayer_op2.operation = op2;
            messageLayer_question.visible = true;
        }
        onDialog: {
            messageLayer.message = msg;
            messageLayer_ok.operation = btn;
            messageLayer_dialog.visible = true;
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
        Column {
            anchors.centerIn: parent
            width: board.width
            Text {
                id: messageLayer_text
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 24
                color: "white"
            }

            Item {
                width: board.width
                anchors.horizontalCenter: parent.horizontalCenter
                id: messageLayer_dialog
                visible: false
                height:  messageLayer_ok.height
                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: board.width/2-5
                    id: messageLayer_ok
                    onClicked: {
                        messageObject.confirmDialog();
                    }
                }
            }

            Row {
                width: board.width
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5
                visible: false
                id: messageLayer_question
                Button {
                    width: parent.width/2-5
                    id: messageLayer_op1
                    onClicked: {
                        messageObject.chooseOption1();
                    }
                }
                Button {
                    width: parent.width/2-5
                    id: messageLayer_op2
                    onClicked: {
                        messageObject.chooseOption2();
                    }
                }
            }
        }
    }


}
