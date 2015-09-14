import QtQuick 1.1

Rectangle {
    width: (visualDef.tileSize+visualDef.tileSpace)*def.boardSize + visualDef.tileSpace
    height: width
    color: "brown"

    Grid {
        rows: def.boardSize; columns: def.boardSize; spacing: visualDef.tileSpace
        x: visualDef.tileSpace; y: visualDef.tileSpace

        Repeater {
            id: field_repeater
            model: fieldModel

            Rectangle {
                id: field
                width: visualDef.tileSize
                height: visualDef.tileSize
                //color: isMovableTo ? "lightblue" : "white"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        field_repeater.model.select(index)
                    }
                }

                states: [
                    State { name: "normal"; PropertyChanges {
                            target: field; color: "antiquewhite"
                        }
                    },
                    State { name: "movable"; PropertyChanges {
                            target: field; color: "lightblue"
                        }
                    },
                    State { name: "paradeMovable"; PropertyChanges {
                            target: field; color: "#D6A296"
                        }
                    },
                    State { name: "parade"; PropertyChanges {
                            target: field; color: "tomato"
                        }
                    },
                    State { name: "selected"; PropertyChanges {
                            target: field; color: "yellowgreen"
                        }
                    },
                    State { name: "selectable"; PropertyChanges {
                            target: field; color: "lightgreen"
                        }
                    }
                ]
                //state: isMovableTo ? "movable" : "normal"
                state: stateStringFromFlags
            }
        }
    }

    Repeater {
        id: piece_repeater
        model: pieceModel
        Piece {
            z:1
        }
    }

    Repeater {
        id: preview_repeater
        model: previewModel
        MovePreview {
            z: 3
            id: prev_move
        }
    }

    Repeater {
        id: flank_repeater
        model: flankModel
        Rectangle {
            id: theFlank
            color: "transparent"
            //color: "#8000ffff"
            property int fx: field % def.boardSize
            property int fy: Math.floor(field / def.boardSize)

            z: 4

            x: (visualDef.tileSpace+visualDef.tileSize)*fx - (visualDef.tileSize+visualDef.tileSpace)/2
            y: (visualDef.tileSpace+visualDef.tileSize)*fy - (visualDef.tileSize+visualDef.tileSpace)/2
            width: 2*(visualDef.tileSpace*2+visualDef.tileSize)
            height: 2*(visualDef.tileSpace*2+visualDef.tileSize)

            Rectangle {
                id: theFlankBar
                anchors.centerIn: parent
                width: 4
                height: parent.height
                color: "red"
                rotation: ((direction+4)%8)*45

                SequentialAnimation {
                    PropertyAnimation {
                        target: theFlankBar;
                        properties: "height"
                        from: 4; to: theFlank.height * ((direction%2 == 1) ? Math.SQRT2 : 1)
                        duration: 250
                    }
                    PauseAnimation { duration: 250 }
                    running: true
                    onRunningChanged: {
                        if (running)
                            animationModel.animationStarted()
                        else
                            animationModel.animationFinished()
                    }
                }
            }


        }
    }

}
