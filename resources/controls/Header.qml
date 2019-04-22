import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4

Rectangle {
    property string title: ""
    property alias content: leftHeaderOptions.children
    height: 40
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.top: parent.top
    color: "#40E0D0"
    z: 98

    Rectangle {
        id: leftHeaderOptions
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 0.33 * parent.width
        color: "transparent"
        z:99
    }

    Rectangle{
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: leftHeaderOptions.right
        anchors.right: rightHeaderOptions.left
        color: "transparent"
        Rectangle{
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "transparent"
            width: childrenRect.width
            Image{
                id: logo
                source: "../icons/logo.png"
                height: 0.66 * parent.height
                width: height
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                text: title
                anchors.left: logo.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                anchors.leftMargin: 10
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 14
            }
        }
    }
    Rectangle {
        id: rightHeaderOptions
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 0.33 * parent.width
        color: "transparent"
        z:99

        Rectangle{
            property string buttonColor: "#2c9c91"
            property string borderColor: "#000000"
            property string buttonColorHovered: "#237d75"
            property string buttonColorClicked: "#1b5f58"
            property int yModifier: 5
            id: windowOptions
            y: parent.y - yModifier
            anchors.right: parent.right
            height: 0.85 * parent.height
            anchors.rightMargin: 10
            color: borderColor
            width: 120
            radius: 5
            Button{
                id: minimiseAppButton
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.leftMargin: 2
                anchors.bottomMargin: 2
                anchors.rightMargin: 1
                width: 0.33 * parent.width
                height: parent.height
                z: 99
                Image{
                    source: "../icons/minimize_1px.png"
                    x: 0.3 * parent.width
                    y: windowOptions.yModifier + 0.5 * (parent.height - windowOptions.yModifier)
                    width: 0.4 * parent.width
                }
                background: Rectangle {
                    color:  if(minimiseAppButton.pressed){windowOptions.buttonColorClicked}
                            else if(minimiseAppButton.hovered){windowOptions.buttonColorHovered}
                            else {windowOptions.buttonColor}
                    radius: 5
                    Rectangle{
                        color:  if(minimiseAppButton.pressed){windowOptions.buttonColorClicked}
                                else if(minimiseAppButton.hovered){windowOptions.buttonColorHovered}
                                else {windowOptions.buttonColor}
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.top: parent.top
                        width: parent.width * 0.5
                    }
                }
                onClicked: {
                    app.visibility = ApplicationWindow.Minimized
                }
            }
            Button{
                id: fullScreenButton
                anchors.left: minimiseAppButton.right
                anchors.right: quitAppButton.left
                anchors.bottom: parent.bottom
                height: parent.height
                anchors.leftMargin: 1
                anchors.bottomMargin: 2
                anchors.rightMargin: 1
                z: 99
                Image{
                    source: "../icons/fullscreen_2px.png"
                    x: 0.2 * parent.width
                    y: windowOptions.yModifier + 0.2 * (parent.height - windowOptions.yModifier)
                    width: height
                    height: 0.6 * (parent.height - windowOptions.yModifier)
                }
                background: Rectangle {
                    color:  if(fullScreenButton.pressed){windowOptions.buttonColorClicked}
                            else if(fullScreenButton.hovered){windowOptions.buttonColorHovered}
                            else {windowOptions.buttonColor}
                }
                onClicked: {
                    toggleFullscreen()
                }
            }
            Button{
                id: quitAppButton
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 1
                anchors.rightMargin: 2
                anchors.bottomMargin: 2
                width: 0.33 * parent.width
                height: parent.height
                Image{
                    source: "../icons/exit_2px.png"
                    x: 0.3 * parent.width
                    y: windowOptions.yModifier + 0.25 * (parent.height - windowOptions.yModifier)
                    width: height
                    height: 0.5 * (parent.height - windowOptions.yModifier)
                }
                z: 99
                background: Rectangle {
                    color:  if(quitAppButton.pressed){windowOptions.buttonColorClicked}
                            else if(quitAppButton.hovered){windowOptions.buttonColorHovered}
                            else {windowOptions.buttonColor}
                    radius: 5
                    Rectangle{
                        color:  if(quitAppButton.pressed){windowOptions.buttonColorClicked}
                                else if(quitAppButton.hovered){windowOptions.buttonColorHovered}
                                else {windowOptions.buttonColor}
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        anchors.top: parent.top
                        width: parent.width * 0.5
                    }
                }

                onClicked: {
                    Qt.quit()
                }
            }
        }
    }
    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.bottom
        anchors.right: parent.right
        height: 4
        color: "#1b5f58"
        z:99
    }
    MouseArea {
        anchors.fill: parent;
        z: 98
        property point clickPos: Qt.point(1, 1)

        onPressed: {
            clickPos = Qt.point(mouse.x,mouse.y)
        }

        onPositionChanged: {
            var newPosition = getNewPosition(mouse.x, mouse.y)
            if (newPosition.y <= 0){
                //app.visibility = ApplicationWindow.Maximized
            }
            else
            {
                //app.visibility = ApplicationWindow.Windowed
                app.x = newPosition.x
                app.y = newPosition.y
            }
        }

        function getNewPosition(newX, newY){
            var delta = Qt.point(newX-clickPos.x, newY-clickPos.y)
            return Qt.point(app.x + delta.x, app.y + delta.y)
        }
    }

    function toggleFullscreen(){
        switch(app.visibility){
        case ApplicationWindow.Maximized:
            app.visibility = ApplicationWindow.Windowed
            break
        case ApplicationWindow.Windowed:
            app.visibility = ApplicationWindow.Maximized
            break
        }
    }
}
