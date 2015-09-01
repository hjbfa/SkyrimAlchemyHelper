#ifndef CONFIGPANE_H
#define CONFIGPANE_H

#include <QWidget>

class QCheckBox;
class QLineEdit;
class QPushButton;
class QTimer;

class ConfigPane : public QWidget
{
	Q_OBJECT

public:
	ConfigPane(QWidget* parent = 0, bool firstLaunch = false);

	bool testConfig(); // Returns false if there is a problem with the current configuration
	void saveConfig(); 

public slots:
	void editDataPath();
	void editPluginsPath();
	void editSavesPath();
	void editModOrganizerPath();
	void useModOrganizerChanged(int);
	void parseMods();
	void defaultConfig();
	void updateLists();

signals:
	void startModsParse();
	void endModsParse();

protected:
	void loadConfig();
	bool prepareParsing();

	bool m_firstLaunch;
	QLineEdit *m_dataFolderEdit,
		*m_pluginsListPathEdit, 
		*m_savesFolderEdit, 
		*m_modOrganizerPathEdit;
	QCheckBox *m_useModOrganizerCheckBox;
	QPushButton *m_modOrganizerPathButton;
	QTimer *m_timer;
};

#endif // CONFIGPANE_H