import QtQuick 2.11
import QtQuick.Controls 2.4
import "../controls"

Item {
    property bool edit: false
    property var returnButton
    property var saveButton
    property var editButton
    property var cancelButton

    Rectangle{
        id: ingredientsRect
        anchors.fill: parent
        anchors.topMargin: 0.01 * parent.height
        anchors.bottomMargin: 0.01 * parent.height

        Text{
            id: ingredientsText
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            height: 0.1 * parent.height
            text: "Shopping List"
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            z: 2
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 0.9
                height: 1
                color: "black"
            }
        }

        ItemList{
            id: ingredientList
            anchors.left: parent.left
            anchors.top: ingredientsText.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            edit: parent.parent.edit
            separatorHeight: 1
        }
    }

    Connections{
        target: ShoppingListView
        onListSet:{
            ingredientList.setItemList(list)
        }
        onEditingEnabled: {
            if(!edit){
                enableEdit()
            }
        }
        onEditingDisabled: {
            if(edit){
                disableEdit()
            }
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
        mainHeader,'firstObject')
        returnButton.clicked.connect(buttonClicked)

        editButton = Qt.createQmlObject(
        'import QtQuick.Controls 2.3;import QtQuick 2.11;
        Button{id:gaf;width: parent.width; height:width; z:99; anchors.top: parent.top; anchors.left: parent.left
            icon.color: "transparent"
            icon.source: if(pressed){"../icons/edit_clicked.png"} else if(hovered){"../icons/edit_hover.png"} else {"../icons/edit.png"}
            icon.width: 0.5 * width
            icon.height: 0.5 *height
background:Rectangle{color:"transparent"}
            Rectangle {
                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "black"
            }}',
        sideBar.children[2],'thirdObject')
        editButton.clicked.connect(ShoppingListView.editButtonClicked)
        ShoppingListView.activating();
    }

    StackView.onDeactivating: {
        if(saveButton)  { saveButton.destroy(); }
        if(cancelButton){ cancelButton.destroy(); }
        if(returnButton){ returnButton.destroy(); }
        if(editButton)  { editButton.destroy(); }
        sideBar.state =""
    }

    function enableEdit(){
        edit = true
        returnButton.destroy();
        cancelButton = Qt.createQmlObject(
        'import QtQuick.Controls 2.3;import QtQuick 2.11;
        Button{id:sample;width:40; height:40; z:99; anchors.left: parent.left
            icon.color: "transparent"
            icon.source: if(pressed){"../icons/close_clicked.png"} else if(hovered){"../icons/close_hover.png"} else {"../icons/close-black-white-fill.png"}
            icon.width: 60
            icon.height: 60
            background:Rectangle{color:"transparent"}
        }',
        mainHeader.children[0],'firstObject')
        cancelButton.clicked.connect(cancelClicked)

        saveButton = Qt.createQmlObject(
        'import QtQuick.Controls 2.3;import QtQuick 2.11;
        Button{id:save;width:40; height:40; z:99; anchors.left: cancelButton.right
            icon.color: "transparent"
            icon.source: if(pressed){"../icons/save_clicked.png"} else if(hovered){"../icons/save_hover.png"} else {"../icons/save.png"}
            icon.width: 60
            icon.height: 60
background:Rectangle{color:"transparent"}}',
        mainHeader.children[0],'secondObject')
        saveButton.clicked.connect(saveButtonClicked)
    }

    function disableEdit(){
        edit = false
        saveButton.destroy()
        cancelButton.destroy()
        returnButton = Qt.createQmlObject(
        'import QtQuick.Controls 2.3;import QtQuick 2.11;
        Button{id:sample;width:parent.height; height:parent.height; z:99; anchors.left: parent.left
            icon.color: "transparent"
            icon.source: if(pressed){"../icons/return_clicked.png"} else if(hovered){"../icons/return_hover.png"} else {"../icons/return.png"}
            icon.width: 60
            icon.height: 60
background:Rectangle{color:"transparent"}}',
        mainHeader.children[0],'firstObject')
        returnButton.clicked.connect(buttonClicked)
    }

    function buttonClicked(){
        ShoppingListView.handleRetrunClicked();
    }

    function cancelClicked(){
        ShoppingListView.cancelButtonClicked();
    }

    function saveButtonClicked(){
        ShoppingListView.saveButtonClicked(ingredientList.items);
    }
}
