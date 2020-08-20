import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: new_entry
    visible: false
    anchors{
        top: header_controls.bottom
        left: parent.left
        right: parent.right
        bottom: parent.bottom
    }
    function flush(){
        new_first_name_input.text = ""
        new_last_name_input.text = ""
        new_father_name_input.text = ""
        new_phone_input.text = ""
        table_view.editable = true
        new_entry.visible = false
    }
    function prepareForWrite(){
        table_view.editable = false
    }
    function deny_append(){
        flush()
    }
    function accept_append(model_manager){
        model_manager.appendRow( new_first_name_input.text,
                    new_last_name_input.text,
                    new_father_name_input.text,
                    new_phone_input.text
        )
        flush()
    }
    Rectangle{
        id: new_first_name
        border.width: 1
        border.color: "black"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id: new_first_name_input
            anchors.fill: parent
            readOnly: false
        }
    }
    Rectangle{
        id: new_last_name
        border.width: 1
        border.color: "black"
        anchors.left: new_first_name.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id: new_last_name_input
            anchors.fill: parent
            readOnly: false
        }
    }
    Rectangle{
        id: new_father_name
        border.width: 1
        border.color: "black"
        anchors.left: new_last_name.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id : new_father_name_input
            anchors.fill: parent
            readOnly: false
        }
    }
    Rectangle{
        id: new_phone
        border.width: 1
        border.color: "black"
        anchors.left: new_father_name.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id: new_phone_input
            anchors.fill: parent
            readOnly: false
        }
    }
    Button{
        id: new_accept_button
        text: "Принять"
        width: parent.width*0.1
        anchors{
            left: new_phone.right
            top: parent.top
            bottom: parent.bottom
        }
        onClicked: {
            if (entries_manager.entryValidate(
                new_first_name_input.text.toString(),
                new_last_name_input.text.toString(),
                new_father_name_input.text.toString(),
                new_phone_input.text.toString()))
            {
                new_entry.accept_append(entries_manager)
            } else {
                new_entry.deny_append()
            }
        }
    }
    Button{
        id: new_deny_button
        text: "Отменить"
        width: parent.width*0.1
        anchors{
            left: new_accept_button.right
            top: parent.top
            bottom: parent.bottom
        }
        onClicked: {
            new_entry.deny_append()
        }
    }
}
