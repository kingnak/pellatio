/****************************************************************************
**
** Copyright (C) 2012 Research In Motion.
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 1.1

Item {
    id: button
    property alias text: txt.text
    property bool buttonEnabled: true

    signal toggled(bool on)

    width: 140
    height: 40
    x: 5
    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: {
            if (buttonEnabled)
                buttonEnabled = false;
            else
                buttonEnabled = true;
            toggled(buttonEnabled)
        }
    }
    Rectangle {
        id: checkbox
        width: 23
        height: 23
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        border.color: "gray"
        border.width: 1
        radius: 2
        color: "transparent"
        Rectangle {
            anchors.fill: parent
            anchors.margins: 4
            radius: 1
            color: mouse.pressed || buttonEnabled ? "gray" : "transparent"
        }
    }
    Text {
        id: txt
        anchors.left: checkbox.right
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        color: "gray"
        font.pixelSize: 20
    }
}
