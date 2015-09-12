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

}
