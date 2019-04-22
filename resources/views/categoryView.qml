import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.1
import CustomComponents 1.0
import QtGraphicalEffects 1.12
import "../controls"

Item {
    property var searchObject
    property QmlRecipeFilter recipeFilter: QmlRecipeFilter{}
    id: categoryView
    signal buttonPressed(string category)

    ListModel{ id: categoryList }

    Button{
        text: "All recipes"
        id: allButton
        z: 2
        anchors.left: categoryView.left
        anchors.right: categoryView.right
        anchors.top: categoryView.top
        height: stackView.height * 0.1
        font.pointSize: 30
        onClicked: {
            recipeFilter.category = "" // TODO is it ok to leave it like this
            CategoryView.handleClickedButton(recipeFilter)
        }
        contentItem: Text {
            text: allButton.text
            font: allButton.font
            opacity: enabled ? 1.0 : 0.3
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        background: Rectangle {
            clip: true
            Image{
                id:test
                source: "../all-recipes.jpg"
                width: parent.width
                y: -500
            }
        }
    }

    Component {
        id: categoryDelegate
        Button {
            text: category.name;
            font.pointSize: 30
            width: getWidth(index, categoryList.count)
            height: getHeight(categoryList.count)
            onClicked: {
                recipeFilter.category = text
                CategoryView.handleClickedButton(recipeFilter)
            }
            contentItem: Text {
                text: parent.text
                font: parent.font
                opacity: enabled ? 1.0 : 0.3
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            background: Rectangle {
                clip: true
                Image{
                    source: category.imagePath
                    width: parent.width
                    y: -550
                }
            }
            Rectangle{
                height: 1
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                color: "black"
            }
        }
    }

    GridView{
        id: categoryGrid
        anchors.left: categoryView.left
        anchors.right: categoryView.right
        anchors.bottom: categoryView.bottom
        anchors.top: allButton.bottom

        model: categoryList
        delegate: categoryDelegate
    }

    MessageDialog {
        id: errorDialog
        standardButtons: StandardButton.Ok
        onAccepted: {
            close()
        }
    }

    Connections{
        target: CategoryView
        onCategoriesSet:{
            categoryList.clear()
            formatGridViewCells(categories.length)
            for(var index in categories){
                categoryList.append({category: categories[index]})
            }
        }
        onMessageSet:{
            errorDialog.title = "Nothing found"
            errorDialog.text = message
            errorDialog.open()
        }
    }

    Connections{
        target: shoppingListButton
        onClicked:{
            sideBar.state = ""
            CategoryView.handleShoppingListClicked()
        }
    }

    StackView.onActivating: {
        searchObject = Qt.createQmlObject(
        'import QtQuick 2.11;
        import "../controls"
        RecipeSearch{
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: width
            maxWidth: 300
            Rectangle {
                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "black"
            }
        }',
        sideBar.container)
        searchObject.filter.connect(filterClicked)
        searchObject.filterRandom.connect(filterRandomClicked)
        CategoryView.activating()
    }

    function filterClicked(filter)
    {
        sideBar.state = ""
        CategoryView.handleClickedButton(filter)
    }

    function filterRandomClicked(filter)
    {
        sideBar.state = ""
        CategoryView.handleRandomClicked(filter)
    }

    StackView.onDeactivating: {
        searchObject.destroy();
    }

    function getWidth(index, numCategories){
        if((index === (numCategories - 1) && (numCategories % 2) === 1) || numCategories <= 5){
            return categoryView.width
        }
        return categoryView.width / 2
    }

    function getHeight(numCategories){
        var heightModifier = 1 / numCategories;
        var minModifier = 0.18
        if(numCategories > 5){
            heightModifier = 1 / Math.ceil(numCategories / 2)
        }
        var cellHeight = (stackView.height - allButton.height) * heightModifier
        if(cellHeight < (minModifier * stackView.height)){
            cellHeight = (minModifier * stackView.height)
        }
        return cellHeight
    }

    function formatGridViewCells(numCategories){
        var widthModifier = 1;
        var heightModifier = 1;
        if(numCategories > 5){
            widthModifier = 2
            heightModifier = 1 / Math.ceil(numCategories / 2)
        }
        else{
            heightModifier = 1 / numCategories
        }
        categoryGrid.cellWidth = categoryView.width / widthModifier
        categoryGrid.cellHeight = (stackView.height - allButton.height) * heightModifier
        if(categoryGrid.cellHeight < (0.18 * stackView.height)){
            categoryGrid.cellHeight = (0.18 * stackView.height)
        }
    }
}
