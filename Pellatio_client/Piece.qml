import QtQuick 2.3
import Pellatio 1.0

Rectangle {
    id: thePiece
    width: 50
    height: 50
    color: "transparent"
    visible: field >= 0

    property int cx: field % def.boardSize
    property int cy: Math.floor(field / def.boardSize)

    x: cx * (visualDef.tileSize+visualDef.tileSpace)+visualDef.tileSpace
    y: cy * (visualDef.tileSize+visualDef.tileSpace)+visualDef.tileSpace
    rotation: direction*45

    Image {
        source: {
            var s;
            switch (type) {
            case PieceType.Aggressor: s = "a"; break;
            case PieceType.Phalangit: s = "p"; break;
            case PieceType.Kavalerist: s = "k"; break;
            case PieceType.General: s = "g"; break;
            }
            s = (pieceColor == Color.Black ? "b" : "r") + s;
            return "/images/"+s+".png";
        }
        anchors.centerIn: parent
        smooth: true
    }

    Item {
        anchors.fill: parent
        opacity: isCaptured ? 1 : 0
        rotation: -parent.rotation
        Rectangle {
            color: "red"
            x: 2; y: parent.height/2-2
            width: parent.width-4; height: 4
            rotation: 45
        }
        Rectangle {
            color: "red"
            x: 2; y: parent.height/2-2
            width: parent.width-4; height: 4
            rotation: 135
        }
        Behavior on opacity {
            NumberAnimation {
                duration: 250
                onRunningChanged: {
                    if (running)
                        animationModel.animationStarted()
                    else
                        animationModel.animationFinished()
                }
            }
        }
    }

    Behavior on x {
        NumberAnimation {
            duration: 500
            onRunningChanged: {
                if (running)
                    animationModel.animationStarted()
                else
                    animationModel.animationFinished()
            }
        }
    }
    Behavior on y {
        NumberAnimation {
            duration: 500
            onRunningChanged: {
                if (running)
                    animationModel.animationStarted()
                else
                    animationModel.animationFinished()
            }
        }
    }
    Behavior on rotation {
        RotationAnimation {
            direction: RotationAnimation.Shortest;
            duration: 500
            onRunningChanged: {
                if (running)
                    animationModel.animationStarted()
                else
                    animationModel.animationFinished()
            }
        }
    }
}
