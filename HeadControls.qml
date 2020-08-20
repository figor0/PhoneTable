import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: header_controls
    property alias filter_input: filter_input
    property bool appednable: true
    Button{
        id: add_button
        text: "Добавить запись"
        width: parent.width*0.5
        height: parent.height
        anchors{
            top: parent.top
            left: parent.left
        }
        onClicked: {
            if (header_controls.appednable === true){
                new_entry.visible = true
                new_entry.prepareForWrite()
            }
        }
    }
    Rectangle{
        width: parent.width*0.5
        height: parent.height
        anchors{
            top: parent.top
            left: add_button.right
        }
        border.color: "black"
        border.width: 1
        color: "yellow"
        Text{
            text: "Поиск по фамилии"
            visible: filter_input.focus === false
            anchors.fill: parent
            anchors.leftMargin: 8
        }
        TextInput{
            id: filter_input
            anchors.fill: parent
            anchors.leftMargin: 8
            onLengthChanged: {
                print("length changed")
                entries_manager.filtration(text);
            }
        }
    }
}
