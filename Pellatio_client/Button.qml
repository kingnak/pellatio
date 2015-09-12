import QtQuick 1.1

/****************************************************************************
 **
 ** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the QtDeclarative module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Licensees holding valid Qt Enterprise licenses may use this file in
 ** accordance with the Qt Enterprise License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Digia.
 **
 ** If you have questions regarding the use of this file, please use
 ** contact form at http://qt.digia.com
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 import QtQuick 1.0

 BorderImage {
     id: button

     property alias operation: buttonText.text
     property bool enabled: true

     //property string color: ""

     signal clicked

     source: "images/button.png"; clip: true
     border { left: 10; top: 10; right: 10; bottom: 10 }

     Rectangle {
         id: shade
         anchors.fill: button; radius: 10; color: "black"; opacity: 0
     }
     Rectangle {
         id: deactivateShade
         anchors.fill: button; radius: 10; color: "black"; opacity: button.enabled ? 0 : 0.4
         z:2
     }

     Text {
         id: buttonText
         anchors.centerIn: parent; anchors.verticalCenterOffset: -1
         font.pixelSize: parent.width > parent.height ? parent.height * .5 : parent.width * .5
         style: Text.Sunken; styleColor: "black"; smooth: true
         //color: button.enabled ? "white" : "gray";
         color: "white"
     }

     MouseArea {
         id: mouseArea
         anchors.fill: parent
         onClicked: {
             if (button.enabled) {
                //doOp(operation)
                button.clicked()
             }
         }
     }

     states: State {
         name: "pressed"; when: mouseArea.pressed == true && button.enabled == true
         PropertyChanges { target: shade; opacity: .4 }
     }
 }
