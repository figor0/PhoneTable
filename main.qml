import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Телефонный справочник")
    onClosing: {
        entries_manager.save()
    }
    Item{
        id: header
        height: parent.height*0.1
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        HeadControls{
            id: header_controls
            height: parent.height*0.5
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
        }
        AppendForm{
            id: new_entry
            visible: false
            anchors{
                top: header_controls.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
        }
    }
    GridView{
        id: field_names
        height: parent.height*0.05
        anchors{
            top: header.bottom
            left: parent.left
            right: parent.right
        }
        model: ListModel{
            ListElement{name: "Имя"}
            ListElement{name: "Фамилия"}
            ListElement{name: "Отчество"}
            ListElement{name: "Телефон"}
        }
        cellHeight: height
        cellWidth: width*0.20
        delegate: Rectangle{
            implicitHeight: field_names.height
            implicitWidth: field_names.width*0.20
            border.color: "black"
            border.width: 1
            Text{
                anchors.fill: parent
                text: model.name
            }
        }
    }
    TableView{
        id: table_view
        model: entries
        anchors{
            left: parent.left
            right: parent.right
            top: field_names.bottom
            bottom: parent.bottom
        }
        property bool editable: true
        delegate: EntryDelegate{
            implicitHeight: 20
            implicitWidth: table_view.width
        }
    }
}
