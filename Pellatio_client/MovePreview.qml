import QtQuick 1.1
import Pellatio 1.0

Item {
    property int fx: field % def.boardSize
    property int fy: Math.floor(field / def.boardSize)

    x: board.x
    y: board.y
    width: board.width
    height: board.height

    Image {
        //id: piece_move
        visible: (type == MoveType.Move) ? true : false

        property int addLength: (direction%2)*20*length

        x: visualDef.tileSpace + fx*(visualDef.tileSize+visualDef.tileSpace) + (visualDef.tileSize-width)/2
        y: visualDef.tileSpace + (fy-length+1)*(visualDef.tileSize+visualDef.tileSpace) - (visualDef.tileSize)/2 - addLength
        width: 30
        height: length * visualDef.tileSize  + addLength

        rotation: direction*45
        transformOrigin: Item.Bottom
        source: "/images/move2.png"
        smooth: true
    }

    Image {
        //id: piece_rot
        visible: (type == MoveType.Rotate) ? true : false
        source: "/images/rot.png"

        x: visualDef.tileSpace + fx*(visualDef.tileSize+visualDef.tileSpace)
        y: visualDef.tileSpace + fy*(visualDef.tileSize+visualDef.tileSpace)
        width: visualDef.tileSize
        height: visualDef.tileSize
        mirror: (rotationDirection == Rotation.CounterClockWise) ? true : false

        // Rotate back if board is rotated
        rotation: -board.rotation
    }
}
