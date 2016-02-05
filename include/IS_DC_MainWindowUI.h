/*
 * Copyright (C) 2011 Weill Medical College of Cornell University
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef ISCALE_DYNCLAMPUI_H
#define ISCALE_DYNCLAMPUI_H

#include <QtGlobal>
#if QT_VERSION >= 0x050000
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

class IScale_DynClampUI : public QWidget {
	Q_OBJECT

	public:
		IScale_DynClampUI( QWidget* parent = 0 /*, const char* name = 0, WFlags fl = 0 */);
		~IScale_DynClampUI();

		QButtonGroup* protocolButtonGroup;
//		QGroupBox* protocolGroup;
		QWidget* protocolGroup;
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
		QGridLayout* TabPageLayout;
		QGridLayout* TabPageLayout_2;
		QGridLayout* tabLayout;
		QHBoxLayout* recordDataLayout;
		QSpacerItem* spacer1a;
		QSpacerItem* spacer2a;
		QVBoxLayout* modelGroupLayout;
		QVBoxLayout* TabPageLayout_3;
		QGridLayout* pEditLayout1;
		QHBoxLayout* pEditLayout2;
		QSpacerItem* spacer1;
		QSpacerItem* spacer2;
		QGridLayout* tabLayout_2;
};

#endif // ISCALE_DYNCLAMPUI_H
