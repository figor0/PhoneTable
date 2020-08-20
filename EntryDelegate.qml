import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: entry
    property string first_name
    property string last_name
    property string father_name
    property string phone
    function saveCondition()
    {
        entry.first_name = first_name_input.text
        entry.last_name = last_name_input.text
        entry.father_name = father_name_input.text
        entry.phone = phone_input.text
    }
    function refreshCondition(model)
    {
        first_name_input.text = model.first_name.toString()
        last_name_input.text = model.last_name.toString()
        father_name_input.text = model.father_name.toString()
        phone_input.text = model.phone.toString()
        entry.first_name = ""
        entry.last_name = ""
        entry.father_name = ""
        entry.phone = ""
    }
    function prepareForEdit()
    {
        header_controls.filter_input.readOnly = true
        saveCondition()
        first_name_input.readOnly = false
        last_name_input.readOnly = false
        father_name_input.readOnly = false
        phone_input.readOnly = false
        accept_button.visible = true
        header_controls.filter_input.readOnly = true
        header_controls.appednable = false
    }
    function prepareForRead()
    {
        first_name_input.readOnly = true
        last_name_input.readOnly = true
        father_name_input.readOnly = true
        phone_input.readOnly = true
        accept_button.visible = false
        header_controls.filter_input.readOnly = false
        header_controls.appednable = true
    }
    function acceptChanging(model)
    {
        model.first_name = entry.first_name
        model.last_name = entry.last_name
        model.father_name = entry.father_name
        model.phone = entry.phone
        prepareForRead()
    }
    function denyChanging(model)
    {
        refreshCondition(model)
        prepareForRead()
    }
    Rectangle{
        id: first_name
        border.width: 1
        border.color: "black"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id: first_name_input
            anchors.fill: parent
            text: model.first_name
            readOnly: true
        }
    }
    Rectangle{
        id: last_name
        border.width: 1
        border.color: "black"
        anchors.left: first_name.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id: last_name_input
            anchors.fill: parent
            text: model.last_name
            readOnly: true
        }
    }
    Rectangle{
        id: father_name
        border.width: 1
        border.color: "black"
        anchors.left: last_name.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id :father_name_input
            anchors.fill: parent
            text: model.father_name
            readOnly: true
        }
    }
    Rectangle{
        id: phone
        border.width: 1
        border.color: "black"
        anchors.left: father_name.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id: phone_input
            anchors.fill: parent
            text: model.phone
            readOnly: true
        }
    }
    Button{
        id: accept_button
        visible: false
        text: "Принять"
        width: parent.width*0.2
        anchors{
            left: phone.right
            top: parent.top
            bottom: parent.bottom
        }
        onClicked: {
            table_view.editable = true
            saveCondition()
            if (entries_manager.entryValidate(
                        entry.first_name,
                        entry.last_name,
                        entry.father_name,
                        entry.phone))
            {
                acceptChanging(model)
                entries_manager.filtration(header_controls.filter_input.text)
            } else {
                entry.first_name = ""
                entry.last_name = ""
                entry.father_name = ""
                entry.phone = ""
            }
        }
    }
    MouseArea{
        id: click_area
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        visible: table_view.editable
        onClicked:
        {
            if ( mouse.button === Qt.RightButton)
            contextMenu.popup();
        }
        Menu{
            id: contextMenu
            width: parent.width*0.25
            MenuItem {
                text: "Изменить"
                height: implicitHeight
                onTriggered: {
                    if (table_view.editable === true){
                        prepareForEdit();
                        table_view.editable = false;
                    }
                }
            }
            MenuItem {
                text: "Удалить"
                height: implicitHeight
                onTriggered: {
                    entries_manager.removeRow(index)
                }
            }
        }
    }
}

