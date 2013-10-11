#ifndef _ARCADEMODESETUP_H_
#define _ARCADEMODESETUP_H_

#include <QStringList>

#include "ui_arcademodesetup.h"
#include "gamelist.h"

class ArcadeModeSetup : public QDialog, public Ui::ArcadeModeSetup
{
	Q_OBJECT

       	public:
		ArcadeModeSetup(QWidget *parent = 0);
		~ArcadeModeSetup();

		bool isWritableFile(QString);
		static bool lessThan(const GamelistItem *, const GamelistItem *);

		static QStringList keySequenceMapBases;
		static QStringList joyFunctionMapBases;

	public slots:
		void scanCustomKeySequence(QTreeWidgetItem *, int);
		void scanCustomJoyFunction(QTreeWidgetItem *, int);
		void loadKeySequenceMaps();
		void loadJoyFunctionMaps();
		void saveKeySequenceMaps();
		void saveJoyFunctionMaps();
		void checkKeySequenceMaps();
		void checkJoyFunctionMaps();
		void adjustIconSizes();
		void saveSettings();
		void updateCategoryFilter();
		void saveCategoryFilter();
		void on_checkBoxUseFilteredList_toggled(bool);
		void on_checkBoxFavoriteSetsOnly_toggled(bool);
		void on_checkBoxTaggedSetsOnly_toggled(bool);
		void on_pushButtonExport_clicked();
		void on_toolButtonBrowseExecutableFile_clicked();
		void on_toolButtonBrowseWorkingDirectory_clicked();
		void on_toolButtonBrowseConfigurationPath_clicked();
		void on_toolButtonBrowseFilteredListFile_clicked();
		void on_lineEditFilteredListFile_textChanged(QString);
		void on_toolButtonSelectAll_clicked();
		void on_toolButtonDeselectAll_clicked();
};

#endif
