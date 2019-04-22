import QtQuick 2.11
import QtQuick.Controls 2.3

Rectangle{
    id: searchArea
    signal search(string value)
    signal searchRandom(string value)
    property alias content: extraSearchArea.children
    property string searchValue: extendedSearchField.text
    property var searchDelegate: searchPressed
    property var searchRandomDelegate: searchRandomPressed
    property int maxWidth: 0
    Button{
        id: searchButton
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        icon.source: "../icons/search.png"
        icon.color: "transparent"
        icon.width: width
        icon.height: height
        background:Rectangle{color:"transparent"}
        onClicked: {
            if(maxWidth > width){
                searchArea.parent.parent.state = "expanded"
            }
        }
        Rectangle {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            width: searchArea.state != "" ? 1 : 0
            color: "black"
        }
    }

    Button{
        id: searchRandomButton
        anchors.top: parent.top
        anchors.left: searchButton.right
        width: 0
        height: parent.height
        icon.source: "../icons/dice_black.png"
        icon.color: "transparent"
        icon.width: width
        icon.height: height
        background:Rectangle{color:"transparent"}
        onReleased: {
            searchRandomDelegate();
        }
    }
    TextField{
        id: extendedSearchField
        placeholderText: "Search"
        font.pointSize: 11
        anchors.left: searchRandomButton.right
        anchors.right: searchArea.right
        anchors.top: searchArea.top
        height: searchButton.height
        clip: true
        background: Rectangle {}
    }

    Rectangle{
        id: filterArea
        anchors.left: searchArea.left
        anchors.right: searchArea.right
        anchors.top: searchButton.bottom
        height: 0
        clip: true
        TextField{
            id: fullyExtendedSearchField
            placeholderText: "Search"
            font.pointSize: 11
            anchors.left: filterArea.left
            anchors.right: filterArea.right
            anchors.top: filterArea.top
            height: searchButton.height
            background: Rectangle {}
            Rectangle {
                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "black"
            }
        }
        Rectangle{
            id: extraSearchArea
            anchors.left: filterArea.left
            anchors.right: filterArea.right
            anchors.top: fullyExtendedSearchField.bottom
            anchors.topMargin: 1
            height: childrenRect.height
        }
    }

    Button{
        id: advancedButton
        anchors.left: searchArea.left
        anchors.right: searchArea.right
        anchors.top: filterArea.bottom
        icon.source: "../icons/expand.png"
        height: 0
        icon.height: height
        icon.width: height * 3
        onClicked: {
            switch(searchArea.state){
                case "expanded": searchArea.state = "fullyExpanded";
                    fullyExtendedSearchField.text = extendedSearchField.text;
                    fullyExtendedSearchField.text = fullyExtendedSearchField.text;
                    extendedSearchField.text = "";
                    break;
                case "fullyExpanded": searchArea.state = "expanded";
                    extendedSearchField.text = fullyExtendedSearchField.text;
                    extendedSearchField.text = extendedSearchField.text;
                    fullyExtendedSearchField.text = "";
                    break;
                default: break;
            }
        }
    }

    states: [
        State{
            name: "expanded"
            AnchorChanges{
                target: searchButton
                anchors.right: undefined
                anchors.bottom: undefined
            }
            PropertyChanges{
                target: searchButton
                width: searchArea.parent.minWidth
                onClicked: searchDelegate()
            }
            PropertyChanges{
                target: searchArea
                height: height
            }
            PropertyChanges{
                target: advancedButton
                height: 17 // TODO probably a variable as well
                icon.source: "../icons/expand.png"
            }
            PropertyChanges{
                target: filterArea
                height: 0 // TODO probably a variable as well
            }
        },

        State{
            name: "fullyExpanded"
            AnchorChanges{
                target: searchButton
                anchors.right: undefined
                anchors.bottom: undefined
            }
            PropertyChanges{
                target: searchButton
                height: searchButton.height
                width: searchArea.width / 2
                onClicked: searchDelegate()
            }
            AnchorChanges{
                target: searchRandomButton
                anchors.right: searchArea.right
            }
            PropertyChanges{
                target: searchRandomButton
                width: width
            }
            PropertyChanges{
                target: searchArea
                height: height
            }
            PropertyChanges{
                target: advancedButton
                height: 17
                spacing: -1 // TODO probably a variable as well
                icon.source: "../icons/reduce.png"
            }
            PropertyChanges{
                target: filterArea
                height: childrenRect.height
            }
            PropertyChanges {
                target: searchArea
                searchValue: fullyExtendedSearchField.text
            }
        }
    ]


    function searchPressed(){
        searchArea.search(searchValue)
    }

    function searchRandomPressed(){
        searchArea.searchRandom(searchValue)
    }
}
