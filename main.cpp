#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ModelManager.h>
#include <generate.h>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//	DBManager manager;
//	manager.save("./db", entriesGenerator(40));
	QGuiApplication app(argc, argv);
	ModelManager model_manager("./db");
	model_manager.load();
	QQmlApplicationEngine engine;
	model_manager.registration(engine.rootContext(), "entries", "entries_manager");
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
