import QtQuick 2.11
import QtQuick.Controls 2.3
import CustomComponents 1.0

Search {
    property QmlRecipeFilter recipeFilter: QmlRecipeFilter
    {
        name: searchValue;
        minServings: servingsSlider.first.value
        maxServings: servingsSlider.second.value
        minTime: timeSlider.first.value
        maxTime: timeSlider.second.value
        category: categoryField.text
        ingredient: ingredientField.text
        starred: starredField.checked
    }
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    height: parent.width
    maxWidth: 300
    searchDelegate: doFilter
    searchRandomDelegate: doFilterRandom
    signal filter(QmlRecipeFilter filter)
    signal filterRandom(QmlRecipeFilter filter)

    content: [
        Rectangle{
            id: servingsSliderArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 100
            Text {
                text: "Servings:"
                font.pointSize: 11
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                height: 0.3 * parent.height
            }
            Text {
                text: servingsSlider.first.value
                font.pointSize: 10
                anchors.bottom: servingsSlider.top
                anchors.left: parent.left
                anchors.leftMargin: 10
                verticalAlignment: Text.AlignVCenter
                height: 0.2 * parent.height
            }
            Text {
                text: servingsSlider.second.value
                font.pointSize: 10
                anchors.bottom: servingsSlider.top
                anchors.right: parent.right
                anchors.rightMargin: 10
                verticalAlignment: Text.AlignVCenter
                height: 0.2 * parent.height
            }
            RangeSlider{
                id: servingsSlider
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 0.5 * parent.height
                from: 0
                to: 100
                first.value: 0
                second.value: 100
                stepSize: 1
                snapMode: RangeSlider.SnapAlways
                Rectangle {
                    anchors.top: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 1
                    color: "black"
                }
            }
        },
        Rectangle{
            id: timeSliderArea
            anchors.top: servingsSliderArea.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 1
            height: 100
            Text {
                text: "Time:"
                font.pointSize: 11
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                height: 0.3 * parent.height
            }
            Text {
                text: timeSlider.first.value
                font.pointSize: 10
                anchors.bottom: timeSlider.top
                anchors.left: parent.left
                anchors.leftMargin: 10
                verticalAlignment: Text.AlignVCenter
                height: 0.2 * parent.height
            }
            Text {
                text: timeSlider.second.value
                font.pointSize: 10
                anchors.bottom: timeSlider.top
                anchors.right: parent.right
                anchors.rightMargin: 10
                verticalAlignment: Text.AlignVCenter
                height: 0.2 * parent.height
            }
            RangeSlider{
                id: timeSlider
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 0.5 * parent.height
                from: 0
                to: 100
                first.value: 0
                second.value: 100
                stepSize: 1
                snapMode: RangeSlider.SnapAlways
                Rectangle {
                    anchors.top: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 1
                    color: "black"
                }
            }
        },
        TextField{
            id: categoryField
            placeholderText: "Category"
            font.pointSize: 11
            anchors.top: timeSliderArea.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 1
            height: 60
            background: Rectangle {}
            Rectangle {
                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "black"
            }
        },
        TextField{
            id: ingredientField
            placeholderText: "Ingredient"
            font.pointSize: 11
            anchors.top: categoryField.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 1
            height: 60
            background: Rectangle {}
            Rectangle {
                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "black"
            }
        },
        CheckBox{
            id: starredField
            anchors.top: ingredientField.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 60
            text: "Starred"
            font.pointSize: 11
            spacing: 10
            checked: false
            Rectangle {
                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "black"
            }
        }

    ]

    function doFilter(){
        filter(recipeFilter)
    }

    function doFilterRandom(){
        filterRandom(recipeFilter)
    }
}
