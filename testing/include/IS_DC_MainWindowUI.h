/****************************************************************************
** Form interface generated from reading ui file 'IS_DC_MainWindowUI.ui'
**
** Created: Mon Jul 29 15:55:34 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ISCALE_DYNCLAMPUI_H
#define ISCALE_DYNCLAMPUI_H

#include <QtGui>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QPushButton;
class QTabWidget;
class QLabel;
class QLineEdit;
class QCheckBox;
class QGroupBox;
class QComboBox;
//class QListBox;
//class QListBoxItem;

class IScale_DynClampUI : public QWidget
{
    Q_OBJECT

public:
    IScale_DynClampUI( QWidget* parent = 0 /*, const char* name = 0, WFlags fl = 0 */);
    ~IScale_DynClampUI();

    QButtonGroup* protocolButtonGroup;
	 QGroupBox* protocolGroup;
    QPushButton* staticPacingButton;
    QPushButton* resetButton;
    QPushButton* startProtocolButton;
    QPushButton* thresholdButton;
    QTabWidget* tabBox;
    QWidget* TabPage;
    QLabel* timeLabel;
    QLineEdit* timeEdit;
    QLabel* beatNumLabel;
    QLineEdit* beatNumEdit;
    QLabel* voltageLabel;
    QLineEdit* voltageEdit;
    QLabel* APDLabel;
    QLineEdit* APDEdit;
    QWidget* TabPage_2;
    QLabel* BCLLabel;
    QLineEdit* BCLEdit;
    QLabel* stimMagLabel;
    QLineEdit* stimMagEdit;
    QLabel* stimLengthLabel;
    QLineEdit* stimLengthEdit;
    QLabel* CmLabel;
    QLineEdit* CmEdit;
    QLabel* LJPLabel;
    QLineEdit* LJPEdit;
    QWidget* tab;
    QLabel* numTrialLabel;
    QLineEdit* numTrialEdit;
    QLabel* intervalTimeLabel;
    QLineEdit* intervalTimeEdit;
    QCheckBox* recordDataCheckBox;
    QGroupBox* modelGroup;
    QComboBox* modelComboBox;
    QWidget* TabPage_3;
    QPushButton* deleteStepButton;
    QPushButton* loadProtocolButton;
    QPushButton* saveProtocolButton;
    QPushButton* addStepButton;
    QPushButton* clearProtocolButton;
    QWidget* tab_2;
    QLabel* APDRepolLabel;
    QLineEdit* APDRepolEdit;
    QLabel* minAPDLabel;
    QLineEdit* minAPDEdit;
    QLabel* stimWindowLabel;
    QLineEdit* stimWindowEdit;
    QListWidget* protocolEditorListBox;

protected:
    QVBoxLayout* IScale_DynClampUILayout;
    QGridLayout* protocolButtonGroupLayout;
    QGridLayout* protocolGroupLayout;
    QSpacerItem* spacer1b;
    QSpacerItem* spacer2b;
    QSpacerItem* spacer3b;
    QSpacerItem* spacer4b;
    QSpacerItem* spacer5b;
    QSpacerItem* spacer6b;
    QVBoxLayout* TabPageLayout;
    QHBoxLayout* timeLayout;
    QHBoxLayout* beatNumLayout;
    QHBoxLayout* voltageLayout;
    QHBoxLayout* APDLayout;
    QVBoxLayout* TabPageLayout_2;
    QHBoxLayout* BCLLayout;
    QHBoxLayout* stimMagLayout;
    QHBoxLayout* stimLengthLayout;
    QHBoxLayout* CmEditLayout;
    QHBoxLayout* LJPEditLayout;
    QVBoxLayout* tabLayout;
    QHBoxLayout* numTrialLayout;
    QHBoxLayout* intervalTimeLayout;
    QHBoxLayout* recordDataLayout;
    QSpacerItem* spacer1a;
    QSpacerItem* spacer2a;
    QVBoxLayout* modelGroupLayout;
    QVBoxLayout* TabPageLayout_3;
    QGridLayout* pEditLayout1;
    QHBoxLayout* pEditLayout2;
    QSpacerItem* spacer1;
    QSpacerItem* spacer2;
    QVBoxLayout* tabLayout_2;
    QHBoxLayout* APDRepolLayout;
    QHBoxLayout* minAPDLayout;
    QHBoxLayout* APDRepolLayout_2;

protected slots:
    virtual void languageChange();

};

#endif // ISCALE_DYNCLAMPUI_H
