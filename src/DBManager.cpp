#include <DBManager.h>

QString EntryType2Str(EntryType type){
	static std::map<EntryType, QString> type_mapping{
		{EntryType::FirstName, "first_name"},
		{EntryType::LastName, "last_name"},
		{EntryType::FatherName, "father_name"},
		{EntryType::Phone, "phone"}
	};
	return type_mapping[type];
}

DBManager::DBManager():
	m_db(QSqlDatabase::addDatabase("QSQLITE"))
{}

std::vector<Entry> DBManager::load(const QString &db_path)
{
	std::vector<Entry> result;
	m_db.setDatabaseName(db_path);
	if (m_db.open() == false){
		qDebug() << "Error db open";
	} else{
		QSqlQuery query;
		if (query.exec("select * from Entries;")){
			QSqlRecord record = query.record();
			while(query.next() == true){
				result.push_back(readEntry(query, record));
			}
		}
	}
	m_db.close();
	return result;
}

size_t DBManager::save(const QString &db_path, const std::vector<Entry> &entries)
{
	QString read_request_template("Select from Entries WHERE phone == %1");
	QString insert_request_template("Insert into Entries (first_name, last_name,"
									"father_name, phone) "
									"values('%1','%2', '%3', '%4')");
	QSqlQuery query;
	QSqlRecord record;
	QString command;
	size_t saved_size = 0;
	m_db.setDatabaseName(db_path);
	if (m_db.open() == false){
		return 0;
		qDebug() << "Error db open";
	}
	if (m_db.tables().size() == 0){
		QString create_command =
				"create table %1 ("
				"first_name VARCHAR(20) NOT NULL, "
				"last_name VARCHAR(20) NOT NULL, "
				"father_name VARCHAR(20), "
				"phone VARCHAR(12) NOT NULL UNIQUE"
				");";
		if ( !query.exec(create_command.arg(m_table_name))){
			qDebug() << "Can't create table " << m_table_name;
		}
	}
	for (const auto& item: entries){
		command = insert_request_template
				.arg(item.first_name)
				.arg(item.last_name)
				.arg(item.father_name)
				.arg(item.phone);
		if (!query.exec(command)) {
			qDebug() << "Fail input";
		} else{
			saved_size++;
		}
	}
	m_db.close();
	return saved_size;
}

Entry readEntry(const QSqlQuery &query, const QSqlRecord &record){
	Entry result;
	result.first_name = query.value(record.indexOf
									(
										EntryType2Str(EntryType::FirstName)
										)).toString();
	result.last_name = query.value(
				record.indexOf
				(
					EntryType2Str(EntryType::LastName)
					)).toString();
	result.father_name = query.value( record.indexOf
									  (
										  EntryType2Str(EntryType::FatherName)
										  )).toString();
	result.phone= query.value(
				record.indexOf
				(
					EntryType2Str(EntryType::Phone)
					)).toString();
	return result;
}
