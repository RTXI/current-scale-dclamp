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

#include "IS_DC_AddStepDialogUI.h"

#include <QtGlobal>
#if QT_VERSION >= 0x050000
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

/*
 *  Constructs a AddStepDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
AddStepDialog::AddStepDialog( QWidget* parent /*, const char* name, bool modal, WFlags fl*/ ) : QDialog( parent /*, name, modal, fl*/ ) {

	setWindowTitle( "Add Step to Protocol" );
	AddStepDialogLayout = new QGridLayout(this);

	stepComboBox = new QComboBox( this );
	stepComboBox->clear();
	stepComboBox->insertItem( 0, tr( "Static Pacing" ) );
	stepComboBox->insertItem( 1, tr( "Current Scaling" ) );
	stepComboBox->insertItem( 2, tr( "Diastolic Interval" ) );
	stepComboBox->insertItem( 3, tr( "DI + Scaling" ) );
	stepComboBox->insertItem( 4, tr( "Wait" ) );
	stepComboBox->insertItem( 5, tr( "Model: Start" ) );
	stepComboBox->insertItem( 6, tr( "Model: Stop" ) );
	stepComboBox->insertItem( 7, tr( "Model: Reset" ) );
	stepComboBox->insertItem( 8, tr( "Model: Change" ) );
	AddStepDialogLayout->addWidget( stepComboBox, 0, 0, 1, 2 );

	BCLLabel = new QLabel( "Basic Cycle Length (ms)", this );
	AddStepDialogLayout->addWidget( BCLLabel, 1, 0);
	BCLEdit = new QLineEdit( "", this );
	BCLEdit->setValidator( new QDoubleValidator(0, 1000, 10, BCLEdit) );
	AddStepDialogLayout->addWidget( BCLEdit, 1, 1);

	numBeatsLabel = new QLabel( "Number of Beats", this );
	AddStepDialogLayout->addWidget( numBeatsLabel, 2, 0);
	numBeatsEdit = new QLineEdit( "", this );
	numBeatsEdit->setValidator( new QIntValidator(0, 10000, numBeatsEdit) );
	AddStepDialogLayout->addWidget( numBeatsEdit, 2, 1);
	
	DILabel = new QLabel( "Diastolic Interval (ms)", this );
	AddStepDialogLayout->addWidget( DILabel, 3, 0);
	DIEdit = new QLineEdit( "", this );
	DIEdit->setValidator( new QDoubleValidator(0, 1000, 10, DIEdit) );
	AddStepDialogLayout->addWidget( DIEdit, 3, 1);

	currentToScaleLabel = new QLabel( "Current to Scale", this );
	AddStepDialogLayout->addWidget( currentToScaleLabel, 4, 0);
	currentToScaleEdit = new QLineEdit( "", this );
	QRegExp currentToScaleRegExp("(INa|IKr|ICaL|IK1|IKs|ICaT|INaK|INCX|IpCA)");
	currentToScaleEdit->setValidator( new QRegExpValidator(currentToScaleRegExp, currentToScaleEdit) );
	currentToScaleEdit->setToolTip( tr( "Choices: INa, IKr, IKs, ICaL, IK1, ICaT, INaK, or INCX" ) );
	AddStepDialogLayout->addWidget( currentToScaleEdit, 4, 1);

	scalingPercentageLabel = new QLabel( "Scaling Percentage", this );
	AddStepDialogLayout->addWidget( scalingPercentageLabel, 5, 0);
	scalingPercentageEdit = new QLineEdit( "", this );
	scalingPercentageEdit->setValidator( new QDoubleValidator(-1000, 1000, 2, scalingPercentageEdit) );
	AddStepDialogLayout->addWidget( scalingPercentageEdit, 5, 1);

	waitTimeLabel = new QLabel( "Wait Time (ms)", this );
	AddStepDialogLayout->addWidget( waitTimeLabel, 6, 0);
	waitTimeEdit = new QLineEdit( "", this );
	waitTimeEdit->setValidator( new QDoubleValidator(0, 10000, 2, waitTimeEdit) );
	AddStepDialogLayout->addWidget( waitTimeEdit, 6, 1);

	modelLabel = new QLabel( "Model", this );
	AddStepDialogLayout->addWidget( modelLabel, 7, 0);
	modelComboBox = new QComboBox( this );
	modelComboBox->clear();
	modelComboBox->insertItem( 0, tr( "Livzhitz Rudy 2009" ) );
	modelComboBox->insertItem( 1, tr( "Faber Rudy 2000" ) );
	AddStepDialogLayout->addWidget( modelComboBox, 7, 1);

	buttonGroup = new QButtonGroup( this );
	buttonGroupBox = new QGroupBox( this );
	buttonGroupBoxLayout = new QHBoxLayout( buttonGroupBox );
	buttonGroupBoxLayout->setAlignment( Qt::AlignTop );

	addStepButton = new QPushButton( "Add Step", buttonGroupBox );
	buttonGroupBoxLayout->addWidget( addStepButton );
	buttonGroup->addButton(addStepButton);

	exitButton = new QPushButton( "Exit", buttonGroupBox );
	buttonGroupBoxLayout->addWidget( exitButton );
	buttonGroup->addButton(exitButton);
	AddStepDialogLayout->addWidget( buttonGroupBox, 8, 0, 1, 2 );
}

/*
 *  Destroys the object and frees any allocated resources
 */
AddStepDialog::~AddStepDialog() { } // no need to delete child widgets, Qt does it all for us
