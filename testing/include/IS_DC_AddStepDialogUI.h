/****************************************************************************
** Form interface generated from reading ui file 'IS_DC_AddStepDialogUI.ui'
**
** Created: Mon Jul 29 15:55:34 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ADDSTEPDIALOG_H
#define ADDSTEPDIALOG_H

#include <QtGui>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QComboBox;
class QLabel;
class QLineEdit;
class QButtonGroup;
class QPushButton;

class AddStepDialog : public QDialog
{
    Q_OBJECT

public:
    AddStepDialog( QWidget* parent = 0 /*, const char* name = 0, bool modal = FALSE, WFlags fl = 0*/ );
    ~AddStepDialog();

    QComboBox* stepComboBox;
    QLabel* BCLLabel;
    QLineEdit* BCLEdit;
    QLabel* numBeatsLabel;
    QLineEdit* numBeatsEdit;
    QLabel* currentToScaleLabel;
    QLineEdit* currentToScaleEdit;
    QLabel* scalingPercentageLabel;
    QLineEdit* scalingPercentageEdit;
    QLabel* waitTimeLabel;
    QLineEdit* waitTimeEdit;
    QLabel* modelLabel;
    QComboBox* modelComboBox;
    QButtonGroup* buttonGroup;
    QPushButton* addStepButton;
    QPushButton* exitButton;

protected:
    QVBoxLayout* AddStepDialogLayout;
    QHBoxLayout* layout1;
    QHBoxLayout* layout2;
    QHBoxLayout* layout3;
    QHBoxLayout* layout4;
    QHBoxLayout* layout5;
    QHBoxLayout* layout6;
    QHBoxLayout* buttonGroupLayout;

protected slots:
    virtual void languageChange();

};

#endif // ADDSTEPDIALOG_H
