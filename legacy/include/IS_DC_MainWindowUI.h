/****************************************************************************
** Form interface generated from reading ui file 'IS_DC_MainWindowUI.ui'
**
** Created: Wed Mar 7 20:56:21 2012
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ISCALE_DYNCLAMPUI_H
#define ISCALE_DYNCLAMPUI_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QPushButton;
class QGroupBox;
class QLabel;
class DefaultGUILineEdit;
class QCheckBox;
class QComboBox;
class QListBox;
class QListBoxItem;

class IScale_DynClampUI : public QWidget
{
    Q_OBJECT

public:
    IScale_DynClampUI( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~IScale_DynClampUI();

    QButtonGroup* systemButtonGroup;
    QPushButton* pauseButton;
    QPushButton* modifyButton;
    QPushButton* resetButton;
    QPushButton* unloadButton;
    QGroupBox* stateGroupBox;
    QLabel* timeLabel;
    DefaultGUILineEdit* timeEdit;
    QLabel* beatNumLabel;
    DefaultGUILineEdit* beatNumEdit;
    QLabel* voltageLabel;
    DefaultGUILineEdit* voltageEdit;
    QLabel* APDLabel;
    DefaultGUILineEdit* APDEdit;
    QButtonGroup* protocolButtonGroup;
    QPushButton* thresholdButton;
    QPushButton* staticPacingButton;
    QPushButton* startProtocolButton;
    QButtonGroup* APDParamGroup;
    QLabel* APDRepolLabel;
    DefaultGUILineEdit* APDRepolEdit;
    QLabel* minAPDLabel;
    DefaultGUILineEdit* minAPDEdit;
    QButtonGroup* protocolParamGroup;
    QLabel* numTrialLabel;
    DefaultGUILineEdit* numTrialEdit;
    QLabel* intervalTimeLabel;
    DefaultGUILineEdit* intervalTimeEdit;
    QCheckBox* recordDataCheckBox;
    QGroupBox* stimParamGroup;
    QLabel* BCLLabel;
    DefaultGUILineEdit* BCLEdit;
    QLabel* stimMagLabel;
    DefaultGUILineEdit* stimMagEdit;
    QLabel* stimLengthLabel;
    DefaultGUILineEdit* stimLengthEdit;
    QLabel* CmLabel;
    DefaultGUILineEdit* CmEdit;
    QGroupBox* modelGroup;
    QComboBox* modelComboBox;
    QButtonGroup* protocolEditorButtonGroup;
    QPushButton* addStepButton;
    QPushButton* deleteStepButton;
    QPushButton* saveProtocolButton;
    QPushButton* loadProtocolButton;
    QPushButton* clearProtocolButton;
    QListBox* protocolEditorListBox;

protected:
    QVBoxLayout* IScale_DynClampUILayout;
    QHBoxLayout* systemButtonGroupLayout;
    QGridLayout* stateGroupBoxLayout;
    QSpacerItem* spacer5;
    QSpacerItem* spacer4;
    QHBoxLayout* timeLayout;
    QHBoxLayout* beatNumLayout;
    QHBoxLayout* voltageLayout;
    QHBoxLayout* APDLayout;
    QHBoxLayout* protocolButtonGroupLayout;
    QHBoxLayout* layout26;
    QSpacerItem* spacer3;
    QVBoxLayout* layoutA2;
    QVBoxLayout* APDParamGroupLayout;
    QHBoxLayout* APDRepolLayout;
    QHBoxLayout* minAPDLayout;
    QVBoxLayout* protocolParamGroupLayout;
    QHBoxLayout* numTrialLayout;
    QHBoxLayout* intervalTimeLayout;
    QVBoxLayout* layoutA3;
    QVBoxLayout* stimParamGroupLayout;
    QHBoxLayout* BCLLayout;
    QHBoxLayout* stimMagLayout;
    QHBoxLayout* stimLengthLayout;
    QHBoxLayout* CmEditLayout;
    QVBoxLayout* modelGroupLayout;
    QHBoxLayout* layoutB;
    QVBoxLayout* protocolEditorButtonGroupLayout;

protected slots:
    virtual void languageChange();

};

#endif // ISCALE_DYNCLAMPUI_H
