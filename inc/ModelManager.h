#include <QObject>
#include <memory>
#include <EntriesModel.h>
#include <Entries.h>
#include <EntriesRef.h>
#include <Validate.h>

class QQmlContext;

class ModelManager: public QObject{
	Q_OBJECT
public:
	using EntriesModel_ptr = std::shared_ptr<EntriesModel>;
	using Entries_ptr = std::shared_ptr<Entries>;
	ModelManager(const QString& db_path,
				 QObject* parent = nullptr);
	Q_INVOKABLE bool load();
	Q_INVOKABLE bool save();
	Q_INVOKABLE void filtration(const QString& filter);
	Q_INVOKABLE void removeRow(const int index);
	Q_INVOKABLE void appendRow(const QString& first_name,
							   const QString& last_name,
							   const QString& father_name,
							   const QString& phone);
	Q_INVOKABLE bool entryValidate(const QString& first_name,
								   const QString& last_name,
								   const QString& father_name,
								   const QString& phone);
	void registration( QQmlContext* context_ptr,
						const QString& model_name,
						const QString& model_manager_name);
private:
	QString m_db_path;
	Entries_ptr m_entries_ptr;
	EntriesModel_ptr m_model_ptr;
	DBManager m_db_manager;
};
