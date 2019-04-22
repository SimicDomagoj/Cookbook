import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQml 2.2
import CookbookApp 1.0
import QtWinExtras 1.0
import "./controls"

ApplicationWindow {
    flags: Qt.FramelessWindowHint
           | Qt.WindowSystemMenuHint
           | Qt.WindowMinimizeButtonHint
           | Qt.Window
    id: app
    width: 1080
    height: 920
    visible: true
    TaskbarButton { overlay.iconSource: "logo_turqoise.png" }
    background: Rectangle{
        border.color: app.activeFocusItem != null ? "#004E98" : "gray"
        border.width: 1
    }

    Header{
        id: mainHeader
        title: "Cookbook"
        anchors.leftMargin: 1
        anchors.rightMargin: 1
        anchors.topMargin: 1
    }

    StackView {
        id: stackView
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: mainHeader.bottom
        anchors.leftMargin: 1
        anchors.rightMargin: 1
        anchors.bottomMargin: 1
    }

    SideBar {
        id:sideBar
        anchors.leftMargin: 1
        anchors.bottomMargin: 1
        openedWidth: 60
        Button{
            height: 60
            width: parent.width
            id: shoppingListButton
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            icon.color: "transparent"
            icon.source: if(pressed){"../icons/shopping_list_clicked.png"} else if(hovered){"../icons/shopping_list_hover.png"} else {"../icons/shopping_list.png"}
            icon.width: 0.75 * width
            icon.height: 0.75 * height
            background:Rectangle{color:"transparent"}
            Rectangle {
                anchors.bottom: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "black"
            }
        }
    }

    Connections {
        target: CookbookApp
        onViewPushed: {
            stackView.push(viewName)
        }
    }

    Connections {
        target: CookbookApp
        onViewPopped: {
            stackView.pop()
        }
    }
}
