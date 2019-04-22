import QtQuick 2.11
import QtQuick.Controls 2.4

ListView{
    signal rightButtonClicked(string value)
    property var items: []
    property bool edit: false
    property string rightButton: ""
    property int separatorHeight: 0
    id: listArea
    clip: true

    ListModel{ id: itemListModel }
    model: itemListModel
    delegate: baseDelegate

    Component {
        id: baseDelegate
        Loader {
            property var itemText: itemModel
            property var m: model
            asynchronous: true
            sourceComponent: {
                if(itemModel) {
                    return itemDelegate
                }
                return ingredientsEmptyDelegate
            }
        }
    }

    Component{
        id: itemDelegate
        Rectangle {
            height: listArea.height * 0.1
            width: listArea.width
            TextField {
                anchors.fill: parent
                text: itemText
                readOnly: !edit;
                font.pointSize: 10
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                background: Rectangle {}
                onTextChanged: {
                    items[m.index] = text
                    itemsChanged()
                }
                Button{
                    visible: edit
                    width: parent.height
                    height: parent.height
                    anchors.right: parent.right
                    anchors.top: parent.top
                    icon.source: pressed ? "../icons/delete_turqoise_hover.png" : "../icons/delete_turqoise.png"
                    opacity: hovered ? 1.0 : 0.1
                    icon.color: "transparent"
                    icon.width: 0.75 * width
                    icon.height: 0.75 * height
                    background:Rectangle{color:"transparent"}
                    onClicked: {
                        deleteItem(m.index);
                    }
                }
                Button{
                    property string imageSuffix: pressed ? "_clicked" : ""
                    visible: !edit && rightButton != ""
                    width: parent.height
                    height: parent.height
                    anchors.right: parent.right
                    anchors.top: parent.top
                    icon.source: rightButton != "" ? "../icons/" + rightButton + imageSuffix + ".png" : ""
                    opacity: hovered ? 1.0 : 0.1
                    icon.color: "transparent"
                    icon.width: 0.75 * width
                    icon.height: 0.75 * height
                    background:Rectangle{color:"transparent"}
                    onClicked: {
                        rightButtonClicked(itemText)
                    }
                }
                Rectangle {
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width * 0.75
                    height: separatorHeight
                    color: "black"
                }
            }
        }
    }

    Component{
        id: ingredientsEmptyDelegate
        Button {
            height: listArea.height * 0.1
            width: listArea.width
            icon.source: if(pressed){ "../icons/add_turqoise_clicked.png" } else if(hovered){ "../icons/add_turqoise_hover.png" } else { "../icons/add_turqoise.png" }
            icon.color: "transparent"
            background:Rectangle{color:"transparent"}
            onReleased: {
                addItem();
            }
        }
    }

    onEditChanged: {
        switch(edit){
        case true: enableEditing(); break;
        case false: disableEditing(); break;
        }
    }

    function enableEditing(){
        itemListModel.append({itemModel : ""})
    }

    function disableEditing(){
        if(itemListModel.count > 0 && itemListModel.get(itemListModel.count - 1).itemModel === ""){
            itemListModel.remove(itemListModel.count - 1);
        }
    }

    function setItemList(list){
        items = []
        itemListModel.clear()
        for(var index in list){
            items.push(list[index])
            itemListModel.append({itemModel : list[index]})
        }
        itemsChanged()
    }

    function addItem()
    {
        items.push("New Item");
        itemsChanged()
        itemListModel.insert(itemListModel.count - 1, {itemModel: "New Item"})
    }

    function deleteItem(index)
    {
        items.splice(index, 1)
        itemsChanged()
        itemListModel.remove(index)
    }
}
