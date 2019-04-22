import QtQuick 2.11
import QtQuick.Controls 2.4
import CustomComponents 1.0
import QtQuick.Dialogs 1.1
import "../controls"

Item {
    property var returnButton

    ListModel{id: recipeList}

    Component {
        id: listBaseDelegate
        Loader {
            property var index: model.index
            property var listElement: model.element
            asynchronous: true
            sourceComponent: {
                if(listElement) {
                    return listDelegate
                }
                return emptyDelegate
            }
        }
    }

    MessageDialog {
        id: deleteDialog
        property var recipeIndex
        title: "Delete"
        text: "Are you sure you want to delete this recipe?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            CppListView.deleteButtonClicked(recipeList.get(recipeIndex).element.id)
        }
        onNo: {
            recipeIndex = -1
        }
    }

    Component{
        id: listDelegate
        Button {
            text: listElement.name
            height: recipeListView.rowHeight
            width: recipeListView.width
            font.pointSize: 26
            onReleased: {
                CppListView.handleClickedElement(listElement.id);
            }
            contentItem: Text {
                text: parent.text
                font: parent.font
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            background: Rectangle {
                clip: true
                Image{
                    source: listElement.imagePath !== "" ? listElement.imagePath : "../placeholder.png"
                    width: parent.width
                    y: -100
                    asynchronous: true
                }
                Rectangle{
                    anchors.fill: parent
                    color: "black"
                    opacity: 0.6
                }
                Rectangle{
                    height: 1
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    color: "black"
                }
            }
            Button{
                anchors.left: parent.left
                anchors.top: parent.top
                width: parent.height
                height: parent.height
                icon.source: if(listElement.starred) {"../icons/star.png"}
                             else if(hovered){"../icons/star_hover.png"}
                             else {"../icons/star_empty.png"}
                icon.color: "transparent"
                icon.width: 0.75 * width
                icon.height: 0.75 * height
                opacity: listElement.starred || hovered ? 1.0 : 0.3
                background:Rectangle{color:"transparent"}
                onClicked: {
                    CppListView.handleStarredToggle(listElement.id);
                }
            }
            Button{
                width: parent.height
                height: parent.height
                anchors.right: parent.right
                anchors.top: parent.top
                icon.source: pressed ? "../icons/delete_turqoise_hover.png" : "../icons/delete_turqoise.png"
                opacity: hovered ? 1.0 : 0.1
                icon.color: "transparent"
                icon.width: 0.45 * width
                icon.height: 0.45 * height
                background:Rectangle{color:"transparent"}
                onClicked: {
                    deleteDialog.recipeIndex = index
                    deleteDialog.open()
                }
            }
        }
    }

    Component{
        id: emptyDelegate
        Button {
            icon.source: if(pressed){ "../icons/add_turqoise_clicked.png" } else if(hovered){ "../icons/add_turqoise_hover.png" } else { "../icons/add_turqoise.png" }
            icon.color: "transparent"
            icon.height: 0.75 * height
            icon.width : 0.75 * height
            background:Rectangle{color:"transparent"}
            height: recipeListView.rowHeight
            width: recipeListView.width
            onReleased: {
                CppListView.newButtonClicked();
            }
        }
    }

    ListView{
        id: recipeListView
        anchors.fill: parent
        model: recipeList
        delegate: listBaseDelegate
        cacheBuffer: height * 2 // TODO revisit this when you fit image to Rectangle
        property int rowHeight: 0.15 * parent.height
    }

    Connections{
        target: CppListView
        onListSet:{
            recipeList.clear()
            for(var index in list){
                recipeList.append({element: list[index]})
            }
            recipeList.append({element: undefined})
        }
    }

    StackView.onActivating: {
        returnButton = Qt.createQmlObject(
        'import QtQuick.Controls 2.3;import QtQuick 2.11;
        Button{id:sample;width:parent.height; height:parent.height; z:99; anchors.left: parent.left
            icon.color: "transparent"
            icon.source: if(pressed){"../icons/return_clicked.png"} else if(hovered){"../icons/return_hover.png"} else {"../icons/return.png"}
            icon.width: 60
            icon.height: 60
background:Rectangle{color:"transparent"}}',
        mainHeader,'firstObject1')
        returnButton.clicked.connect(buttonClicked)
        CppListView.activating()
    }

    StackView.onDeactivating: {
        sideBar.state =""
        returnButton.destroy();
    }

    function buttonClicked()
    {
        CppListView.returnButtonClicked();
    }
}
