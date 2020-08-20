#include <ModelManager.h>
#include <QQmlContext>

ModelManager::ModelManager(const QString &db_path, QObject *parent): QObject(parent),
	m_db_path(db_path)
{}

bool ModelManager::load()
{
	bool result = true;
	m_model_ptr.reset();
	m_entries_ptr.reset();
	m_entries_ptr = std::make_shared<Entries>(m_db_manager.load(m_db_path));
	m_model_ptr = std::make_shared<EntriesModel>(m_entries_ptr);
	return result;
}

bool ModelManager::save()
{
	return m_db_manager.save(m_db_path, m_entries_ptr->entries());
}

void ModelManager::filtration(const QString &filter)
{
	m_model_ptr->filtration(filter);
}

void ModelManager::removeRow(const int index){
	m_model_ptr->removeRow(index);
}

void ModelManager::appendRow(const QString &first_name, const QString &last_name, const QString &father_name, const QString &phone)
{
	Entry new_entry = {
		first_name,
		last_name,
		father_name,
		phone
	};
	m_model_ptr->appendRow(new_entry);
}

bool ModelManager::entryValidate(const QString &first_name,
								 const QString &last_name,
								 const QString &father_name,
								 const QString &phone)
{
	bool right = nameValidator(first_name) &&
				nameValidator(last_name) &&
				nameValidator(father_name) &&
				phoneValidator(phone);
	return right;
}

void ModelManager::registration(QQmlContext* context_ptr,
								const QString &model_name,
								const QString &model_manager_name)
{
	context_ptr->setContextProperty(model_name, m_model_ptr.get());
	context_ptr->setContextProperty(model_manager_name, this);
}

