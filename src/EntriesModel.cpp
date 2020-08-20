#include <EntriesModel.h>

EntriesModel::EntriesModel( EntriesModel::Entries_ptr entries_ptr,
							QObject *parent): QAbstractTableModel(parent),
	m_entries_ptr(entries_ptr)
{}

int EntriesModel::rowCount(const QModelIndex &parent) const
{
	int result = 0;
	if (m_entries_ref_ptr != nullptr){
		result = m_entries_ref_ptr->size();
	} else{
		result = m_entries_ptr->size();
	}
	return result;
}

int EntriesModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

QVariant EntriesModel::data(const QModelIndex &index, int role) const
{
	QVariant result;
	switch (role) {
	case Roles::FirstName:
		if (m_entries_ref_ptr == nullptr){
			result.setValue(m_entries_ptr->at(index.row()).first_name);
		} else {
			result.setValue(m_entries_ref_ptr->at(index.row()).first_name);
		}
		break;
	case Roles::LastName:
		if (m_entries_ref_ptr == nullptr){
			result.setValue(m_entries_ptr->at(index.row()).last_name);
		} else{
			result.setValue(m_entries_ref_ptr->at(index.row()).last_name);
		}
		break;
	case Roles::FatherName:
		if (m_entries_ref_ptr == nullptr){
			result.setValue(m_entries_ptr->at(index.row()).father_name);
		} else{
			result.setValue(m_entries_ref_ptr->at(index.row()).father_name);
		}
		break;
	case Roles::Phone:
		if (m_entries_ref_ptr == nullptr){
			result.setValue(m_entries_ptr->at(index.row()).phone);
		} else{
			result.setValue(m_entries_ref_ptr->at(index.row()).phone);
		}
		break;
	}
	return result;
}

bool EntriesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	bool result = true;
	qDebug() << "W index = " << index.row();
	switch (role) {
	case Roles::FirstName:
		if (m_entries_ref_ptr == nullptr){
			m_entries_ptr->operator[](index.row()).first_name = value.toString();
			qDebug() << "W first_name " <<m_entries_ptr->at(index.row()).first_name;
		} else {
			m_entries_ref_ptr->operator[](index.row()).first_name = value.toString();
		}
		break;
	case Roles::LastName:
		if (m_entries_ref_ptr == nullptr){
			m_entries_ptr->operator[](index.row()).last_name = value.toString();
			qDebug() << "W last_name "<<m_entries_ptr->at(index.row()).last_name;
		} else{
			m_entries_ref_ptr->operator[](index.row()).last_name = value.toString();
		}
		break;
	case Roles::FatherName:
		if (m_entries_ref_ptr == nullptr){
			m_entries_ptr->operator[](index.row()).father_name = value.toString();
			qDebug() << "W father_name "<<m_entries_ptr->at(index.row()).father_name;
		} else{
			m_entries_ref_ptr->operator[](index.row()).father_name = value.toString();
		}
		break;
	case Roles::Phone:
		if (m_entries_ref_ptr == nullptr){
			m_entries_ptr->operator[](index.row()).phone = value.toString();
			qDebug() << "W phone " <<m_entries_ptr->at(index.row()).phone;
		} else{
			m_entries_ref_ptr->operator[](index.row()).phone = value.toString();
		}
		break;
	default:
		result = false;
	}
	dataChanged(createIndex(0,0), createIndex(rowCount() - 1, 0));
	return result;
}

void EntriesModel::removeRow(const int index){
	beginRemoveRows(QModelIndex(), index, 1);
	if (m_entries_ref_ptr != nullptr){
		m_entries_ref_ptr->erase(index);
	} else{
		m_entries_ptr->erase(index);
	}
	endRemoveRows();
}

void EntriesModel::appendRow(const Entry &entry)
{
	beginInsertRows(QModelIndex(), rowCount() - 1, 1);
	if (m_entries_ref_ptr != nullptr){
		m_entries_ref_ptr->push_back(entry);
	} else {
		m_entries_ptr->push_back(entry);
	}
	endInsertRows();
}

QHash<int, QByteArray> EntriesModel::roleNames() const
{
	return {
		{FirstName, "first_name"},
		{LastName, "last_name"},
		{FatherName, "father_name"},
		{Phone, "phone"}
	};
}

void EntriesModel::filtration(const QString &filter){
	beginRemoveRows(QModelIndex(), 0, rowCount());
	endRemoveRows();
	m_entries_ref_ptr.reset();
	if (filter != ""){
		m_entries_ref_ptr = std::make_shared<EntriesRef>(m_entries_ptr.get(), filter);
	}
}
