import QtQuick 2.0

Item {
    default property alias content: optionsArea.children
    property var container: optionsArea
    property int expandedWidth: 300
    property int openedWidth: 50
    id: sideBar
    anchors.top: mainHeader.bottom
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    width: 40
    z: 60
    Rectangle{
        id: openOptionsArea
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        z: 50
        color: "black"
        opacity: 0.3
        visible: false
    }
    MouseArea {
        id: optionsMouseArea
        z: 51
        hoverEnabled: true
        anchors.fill: openOptionsArea
        onEntered: { openOptionsArea.visible = true }
        onExited: { openOptionsArea.visible = false }
        onReleased: {
            exited()
            sideBar.state = "opened"
        }
    }
    Rectangle{
        property int minWidth: openedWidth
        id: optionsArea
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        state: sideBar.state
        width: state == "opened" ? openedWidth : 0
        z: 55
        MouseArea{anchors.fill: parent}
        Rectangle {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.right
            width: sideBar.state == "opened" ? 1 : 0
            color: "black"
        }
    }
    states: [
            State{
            name: "opened"
            AnchorChanges{
                target: sideBar
                anchors.right: parent.right
            }
            AnchorChanges {
                target: optionsArea
                anchors.right: undefined
                anchors.left: parent.left
            }
            PropertyChanges {
                target: sideBar
                width: undefined
            }
            PropertyChanges {
                target: openOptionsArea
                anchors.left: optionsArea.right
                visible: true
            }
            PropertyChanges {
                target: optionsMouseArea
                onEntered: undefined
                onExited: undefined
                onReleased: { sideBar.state = "" }
            }
        },
        State{
            name: "expanded"
            extend: "opened"
            PropertyChanges {
                target: optionsArea
                width: expandedWidth
            }
        }
    ]

    onStateChanged:{
        setChildrenState();
    }

    onContentChanged:{
        setChildrenState();
    }

    function setChildrenState(){
        var childState = state == "expanded" ? state : ""
        for (var i = 0; i < optionsArea.children.length; i++) {
            optionsArea.children[i].state = childState
        }
    }

    transitions: Transition {
        from: ""; to: "opened"; reversible: true
        /*AnchorAnimation {
            targets: optionsArea.anchors
            duration: 500
            easing.type: Easing.InOutQuad
        }*/
    }
}
