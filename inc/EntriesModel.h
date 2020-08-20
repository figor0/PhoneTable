#pragma once
#include <QAbstractTableModel>
#include <QString>
#include <vector>
#include <Entries.h>
#include <EntriesRef.h>
#include <memory>
#include <DBManager.h>

class EntriesModel: public QAbstractTableModel
{
	Q_OBJECT
public:
	using Entries_ptr = std::shared_ptr<Entries>;
	using EntriesRef_ptr = std::shared_ptr<EntriesRef>;
	enum Roles{
		FirstName = Qt::UserRole + 1,
		LastName,
		FatherName,
		Phone
	};
	EntriesModel(Entries_ptr entries_ptr, QObject* parent = nullptr);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	void removeRow(const int index);
	void appendRow(const Entry& entry);
	QHash<int, QByteArray> roleNames() const;
	void filtration(const QString& filter);
private:
	Entries_ptr m_entries_ptr;
	EntriesRef_ptr m_entries_ref_ptr;
};
