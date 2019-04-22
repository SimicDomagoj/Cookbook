import QtQuick 2.11
import QtQuick.Controls 2.4
import CustomComponents 1.0
import QtQuick.Dialogs 1.1
import "../controls"

Item {

    property QmlRecipeViewModel recipeModel: QmlRecipeViewModel{
        ingredients: ingredientList.items
    }
    property var returnButton
    property var saveButton
    property var deleteButton
    property var editButton
    property var cancelButton
    property bool edit: false

    Image {
        property string oldPath: ""
        id: recipeImage
        source: getImageSource()
        clip: true
        anchors.left: parent.left
        anchors.top: parent.top
        width: 0.4 * parent.height
        height: 0.4 * parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.leftMargin: 0.01 * parent.width
        anchors.topMargin: 0.01 * parent.height
        onStatusChanged: {
            if (recipeImage.status === Image.Error && oldPath !== recipeModel.imagePath ) {
                recipeModel.imagePath = oldPath
                oldPath = ""
                recipeImage.source = getImageSource()
            }
        }
        Button{
            id: imageSelectButton
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: parent.height
            visible: edit
            icon.source: hovered ? "../icons/search.png" : ""
            icon.color: "transparent"
            icon.width: width
            icon.height: height
            background: Rectangle{
                color: "black"
                opacity: if(imageSelectButton.pressed){ 0.4 }
                         else if(imageSelectButton.hovered) { 0.3 }
                         else { 0.0 }
            }
            onClicked: imageFileDialog.open()
        }
    }

    TextField{
        id: recipeName
        readOnly: !edit;
        text: recipeModel.name
        placeholderText: "Recipe name"
        anchors.left: recipeImage.right
        anchors.right: recipeStarred.left
        anchors.top: parent.top
        height: 0.1 * parent.height
        anchors.leftMargin: 0.01 * parent.width
        anchors.rightMargin: 0.01 * parent.width
        font.pointSize: 24
        verticalAlignment: Text.AlignVCenter
        background: Rectangle {}
        onTextChanged: {
            recipeModel.name = text
        }
    }    

    Button{
        id: recipeStarred
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 0.01 * parent.width
        width: height
        height: recipeName.height
        enabled: edit
        icon.source: if(recipeModel.starred) {"../icons/star.png"}
                     else if(edit && hovered){"../icons/star_hover.png"}
                     else {"../icons/star_empty.png"}
        icon.color: "transparent"
        icon.width: 0.75 * width
        icon.height: 0.75 * height
        opacity: recipeModel.starred || (edit && hovered) ? 1.0 : 0.3
        background:Rectangle{color:"transparent"}
        onClicked: {
            recipeModel.starred = !recipeModel.starred
        }
    }

    Rectangle {
        id: nameSeparator
        anchors.top: recipeName.bottom
        anchors.left: recipeImage.right
        anchors.right: parent.right
        anchors.leftMargin: 0.0075 * parent.width
        anchors.rightMargin: 0.0075 * parent.width
        height: 1
        color: 'orange'
    }

    TextArea{
        text: recipeModel.description
        placeholderText: "Recipe description"
        readOnly: !edit;
        font.pointSize: 20
        topPadding: 10
        anchors.left: recipeImage.right
        anchors.top: nameSeparator.bottom
        anchors.right: parent.right
        anchors.bottom: descriptionSeparator.top
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignLeft
        anchors.leftMargin: 0.01 * parent.width
        anchors.rightMargin: 0.01 * parent.width
        onTextChanged: {
            recipeModel.description = text
        }
    }

    Rectangle {
        id: descriptionSeparator
        anchors.bottom: recipeInfoRect.top
        anchors.left: recipeImage.right
        anchors.right: parent.right
        anchors.leftMargin: 0.0075 * parent.width
        anchors.rightMargin: 0.0075 * parent.width
        height: 1
        color: 'orange'
    }

    Rectangle{
        id: recipeInfoRect
        anchors.bottom: recipeImage.bottom
        anchors.left: recipeImage.right
        anchors.right: parent.right
        height: 0.5 * recipeName.height
        anchors.leftMargin: 0.01 * parent.width
        anchors.rightMargin: 0.01 * parent.width
        Rectangle{
            id: servingsArea
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            width: 0.25 * parent.width

            TextField{
                id: servingsValue
                readOnly: !edit;
                text: recipeModel.servings
                font.pointSize: 10
                anchors.right: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                verticalAlignment: Text.AlignVCenter
                background: Rectangle{}
                onTextChanged: {
                    recipeModel.servings = text
                }
            }

            Text{
                id: servingsText
                text: recipeModel.servings == 1 ? "serving" : "servings"
                font.pointSize: 10
                anchors.left: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                verticalAlignment: Text.AlignVCenter
            }

        }

        Rectangle{
            id: difficultyArea
            anchors.left: servingsArea.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            width: 0.5 * parent.width

            Rectangle{
                id: difficultyValue
                anchors.right: recipeDifficulty.left
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                width: parent.height

                MouseArea{
                    anchors.fill: parent
                    onPositionChanged: {
                        setDifficulty(mouse)
                    }
                    onReleased: {
                        setDifficulty(mouse)
                    }

                    function setDifficulty(mouse){
                        if(edit){
                            var ratio = mouse.x / difficultyValue.width
                            recipeModel.difficulty = ratioToDifficulty(ratio)
                        }
                    }

                    function ratioToDifficulty(ratio){
                        var difficulty = Math.ceil((ratio) * 4)
                        difficulty = difficulty <= 1 ? 1 : difficulty
                        difficulty = difficulty >= 4 ? 4 : difficulty
                        return difficulty
                    }
                }

                Rectangle{
                    id: difficulty1
                    color: recipeModel.difficulty >= 1 ? "green" : "transparent"
                    radius: 4
                    border.width: 1
                    height: parent.height * 0.5
                    width: parent.width * 0.2
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.15
                }

                Rectangle{
                    id: difficulty2
                    color: recipeModel.difficulty >= 2 ? "yellow" : "transparent"
                    radius: 4
                    border.width: 1
                    height: parent.height * 0.57
                    width: parent.width * 0.2
                    anchors.left: difficulty1.right
                    anchors.leftMargin: parent.width * 0.05
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.15
                }

                Rectangle{
                    id: difficulty3
                    color: recipeModel.difficulty >= 3 ? "orange" : "transparent"
                    radius: 4
                    border.width: 1
                    height: parent.height * 0.64
                    width: parent.width * 0.2
                    anchors.left: difficulty2.right
                    anchors.leftMargin: parent.width * 0.05
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.15
                }

                Rectangle{
                    id: difficulty4
                    color: recipeModel.difficulty == 4 ? "red" : "transparent"
                    radius: 4
                    border.width: 1
                    height: parent.height * 0.71
                    width: parent.width * 0.2
                    anchors.left: difficulty3.right
                    anchors.leftMargin: parent.width * 0.05
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.15
                }
            }

            Text{
                id: recipeDifficulty
                text: getDifficultyText(recipeModel.difficulty)
                font.pointSize: 10
                x: parent.width * 0.4
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                leftPadding: 10
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle{
            id: timeArea
            anchors.left: difficultyArea.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.right: parent.right
            Image{
                source: "../icons/clock.png"
                anchors.right: timeValue.left
                y: parent.y + 0.175 * parent.height
                width: 0.65 * parent.height
                height: 0.65 * parent.height
            }

            TextField{
                id: timeValue
                readOnly: !edit;
                text: recipeModel.time
                font.pointSize: 10
                anchors.right: timeUnits.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.height
                verticalAlignment: Text.AlignVCenter
                background: Rectangle {}
                onTextChanged: {
                    recipeModel.time = text
                }
            }

            Text{
                id: timeUnits
                text: "min"
                font.pointSize: 10
                anchors.left: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                verticalAlignment: Text.AlignVCenter
            }
        }
    }


    Rectangle{
        id: ingredientsRect
        anchors.left: recipeImage.left
        anchors.top: recipeImage.bottom
        anchors.bottom: parent.bottom
        anchors.right: recipeImage.right
        anchors.topMargin: 0.01 * parent.height
        anchors.bottomMargin: 0.01 * parent.height

        Text{
            id: ingredientsText
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            height: 0.1 * parent.height
            text: "Ingredients"
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter
            leftPadding: 0.3 * width
            z: 2
        }

        ItemList{
            id:ingredientList
            anchors.left: parent.left
            anchors.top: ingredientsText.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            edit: parent.parent.edit
            rightButton: "shopping_list"
            onRightButtonClicked: {
                RecipeView.addToShoppingList(value)
            }
        }
    }

    Rectangle {
        id: stepsRect
        anchors.right: parent.right
        anchors.left: recipeName.left
        anchors.top: recipeImage.bottom
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0.01 * parent.width
        anchors.topMargin: 0.01 * parent.height
        anchors.bottomMargin: 0.01 * parent.height

        Text{
            id: stepsText
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            height: 0.1 * parent.height
            text: "Method"
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter
            leftPadding: 0.1 * width
        }

        ItemList{
            id: stepList
            anchors.left: parent.left
            anchors.top: stepsText.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            edit: parent.parent.edit
            z: stepsText - 1
        }
    }

    Connections{
        target: RecipeView
        onRecipeSet: {
            recipeModel = recipe
            ingredientList.setItemList(recipe.ingredients)
            stepList.setItemList(recipe.steps)
        }
        onEditingEnabled: {
            if(!edit)
            {
                enableEdit()
            }
        }
        onEditingDisabled: {
            if(edit)
            {
                disableEdit()
            }
        }
        onErrorMessageSet: {
            errorDialog.text = message
            errorDialog.open()
        }
    }

    StackView.onActivating:{
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
        editButton.clicked.connect(RecipeView.editButtonClicked)

        deleteButton = Qt.createQmlObject(
        'import QtQuick.Controls 2.3;import QtQuick 2.11;
        Button{id:gaf;width: parent.width; height:width; z:99; anchors.top: editButton.bottom; anchors.left: parent.left
            icon.color: "transparent"
            icon.source: if(pressed){"../icons/delete_turqoise_clicked.png"} else if(hovered){"../icons/delete_turqoise_hover.png"} else {"../icons/delete_turqoise.png"}
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
        deleteButton.clicked.connect(messageDialog.open)

        RecipeView.activating()
    }

    MessageDialog {
        id: messageDialog
        title: "Delete"
        text: "Are you sure you want to delete this recipe?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            RecipeView.deleteButtonClicked(recipeModel);
        }
    }

    MessageDialog {
        id: errorDialog
        title: "Error"
        standardButtons: StandardButton.Close
        onRejected: {
            close()
        }
    }

    FileDialog {
        id: imageFileDialog
        title: "Please choose an image"
        selectMultiple: false
        onAccepted: {
            changeImageFile(imageFileDialog.fileUrl)
            close()
        }
        onRejected: {
            close()
        }
    }

    StackView.onDeactivating: {
        if(saveButton){
            saveButton.destroy();
        }
        if(deleteButton){
            deleteButton.destroy();
        }
        if(cancelButton){
            cancelButton.destroy();
        }
        if(returnButton){
            returnButton.destroy();
        }
        if(editButton){
            editButton.destroy();
        }
        sideBar.state =""
    }

    function getDifficultyText(difficulty)
    {
        switch(difficulty){
        case 1: return "Super easy"
        case 2: return "Not too difficult"
        case 3: return "Challenging"
        case 4: return "Showing off"
        }
        return "Something went wrong"
    }

    function enableEdit()
    {
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

    function disableEdit()
    {
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

    function buttonClicked()
    {
        RecipeView.returnButtonClicked();
    }

    function cancelClicked()
    {
        RecipeView.cancelButtonClicked();
    }

    function saveButtonClicked()
    {
        recipeModel.ingredients = ingredientList.items // TODO can this be better
        recipeModel.steps = stepList.items // TODO can this be better
        RecipeView.saveButtonClicked(recipeModel);
    }

    function getImageSource()
    {
        return recipeModel.imagePath !== "" ? recipeModel.imagePath : "../placeholder.png"
    }

    function changeImageFile(imageUrl)
    {
        recipeImage.oldPath = recipeModel.imagePath
        recipeModel.imagePath = imageUrl
        recipeImage.source = getImageSource()
    }
}
