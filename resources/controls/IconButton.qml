import QtQuick.Controls 2.3;
import QtQuick 2.11;

Button{
    width:parent.height
    height:parent.height
    anchors.left: parent.left
    z:99;
    icon.color: "transparent"
    icon.source: if(pressed){"../icons/return_clicked.png"} else if(hovered){"../icons/return_hover.png"} else {"../icons/return.png"}
    icon.width: 60
    icon.height: 60
background:Rectangle{color:"transparent"}}
