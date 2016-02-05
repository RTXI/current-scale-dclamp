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

#include "IS_DC_MainWindowUI.h"

#include <QtGlobal>
#if QT_VERSION >= 0x050000
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

/*
 *  Constructs a IScale_DynClampUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
IScale_DynClampUI::IScale_DynClampUI( QWidget* parent ) : QWidget( parent ) {

//	QWidget::setAttribute(Qt::WA_DeleteOnClose);

	IScale_DynClampUILayout = new QVBoxLayout( this );
	setLayout(IScale_DynClampUILayout);

	protocolButtonGroup = new QButtonGroup( this );

	protocolGroup = new QWidget;
	protocolGroupLayout = new QGridLayout( protocolGroup );
	protocolGroup->setLayout(protocolGroupLayout);
	protocolGroupLayout->setAlignment( Qt::AlignTop );

	staticPacingButton = new QPushButton( "Pace", protocolGroup );
	staticPacingButton->setCheckable( true );
	protocolGroupLayout->addWidget( staticPacingButton, 0, 3 );

	resetButton = new QPushButton( "Reset", protocolGroup );
	resetButton->setCheckable( false );
	protocolGroupLayout->addWidget( resetButton, 1, 3 );

	startProtocolButton = new QPushButton( "Protocol", protocolGroup );
	startProtocolButton->setCheckable( true );
	protocolGroupLayout->addWidget( startProtocolButton, 1, 1 );

	thresholdButton = new QPushButton( "Threshold", protocolGroup );
	thresholdButton->setCheckable( true );
	protocolGroupLayout->addWidget( thresholdButton, 0, 1 );

	IScale_DynClampUILayout->addWidget( protocolGroup );

	tabBox = new QTabWidget( this );
	tabBox->setTabPosition( QTabWidget::North );
	tabBox->setTabShape( QTabWidget::Rounded );

	TabPage = new QWidget( tabBox );
	TabPageLayout = new QGridLayout( TabPage );
	TabPageLayout->setColumnStretch( 0, 1);
	TabPageLayout->setColumnStretch( 1, 0);
	TabPage->setLayout(TabPageLayout);

	timeLabel = new QLabel( "Time (ms)", TabPage );
	TabPageLayout->addWidget( timeLabel, 0, 0 );
	timeEdit = new QLineEdit( "", TabPage );
	timeEdit->setAlignment( Qt::AlignHCenter );
	timeEdit->setReadOnly( true );
	TabPageLayout->addWidget( timeEdit, 0, 1 );

	beatNumLabel = new QLabel( "Beat Number", TabPage );
	TabPageLayout->addWidget( beatNumLabel, 1, 0 );
	beatNumEdit = new QLineEdit( "", TabPage );
	beatNumEdit->setAlignment( Qt::AlignHCenter );
	beatNumEdit->setReadOnly( true );
	TabPageLayout->addWidget( beatNumEdit, 1, 1 );

	voltageLabel = new QLabel( "Voltage (mV)", TabPage );
	TabPageLayout->addWidget( voltageLabel, 2, 0 );
	voltageEdit = new QLineEdit( "", TabPage );
	voltageEdit->setAlignment( Qt::AlignHCenter );
	voltageEdit->setReadOnly( true );
	TabPageLayout->addWidget( voltageEdit, 2, 1 );

	APDLabel = new QLabel( "APD (ms)", TabPage );
	TabPageLayout->addWidget( APDLabel, 3, 0 );
	APDEdit = new QLineEdit( "", TabPage );
	APDEdit->setAlignment( Qt::AlignHCenter );
	APDEdit->setReadOnly( true );
	TabPageLayout->addWidget( APDEdit, 3, 1 );
	tabBox->addTab( TabPage, QString::fromLatin1("") );
	tabBox->setTabText( tabBox->indexOf(TabPage), "States" );

	TabPage_2 = new QWidget( tabBox );
	TabPageLayout_2 = new QGridLayout( TabPage_2 );
	TabPageLayout_2->setColumnStretch( 0, 1);
	TabPageLayout_2->setColumnStretch( 1, 0);
	TabPage_2->setLayout(TabPageLayout_2);

	BCLLabel = new QLabel(  "BCL (ms)", TabPage_2 );
	TabPageLayout_2->addWidget( BCLLabel, 0, 0 );
	BCLEdit = new QLineEdit( "", TabPage_2 );
	BCLEdit->setAlignment( Qt::AlignHCenter );
	TabPageLayout_2->addWidget( BCLEdit, 0, 1 );

	stimMagLabel = new QLabel( "Stim Mag (nA)", TabPage_2 );
	TabPageLayout_2->addWidget( stimMagLabel, 1, 0 );
	stimMagEdit = new QLineEdit( "", TabPage_2 );
	stimMagEdit->setAlignment( Qt::AlignHCenter );
	TabPageLayout_2->addWidget( stimMagEdit, 1, 1 );

	stimLengthLabel = new QLabel( "Stim Length (ms)", TabPage_2 );
	TabPageLayout_2->addWidget( stimLengthLabel, 2, 0 );
	stimLengthEdit = new QLineEdit( "", TabPage_2 );
	stimLengthEdit->setAlignment( Qt::AlignHCenter );
	TabPageLayout_2->addWidget( stimLengthEdit, 2, 1 );

	CmLabel = new QLabel( "Cm (pF)", TabPage_2 );
	TabPageLayout_2->addWidget( CmLabel, 3, 0 );
	CmEdit = new QLineEdit( "", TabPage_2 );
	CmEdit->setAlignment( Qt::AlignHCenter );
	TabPageLayout_2->addWidget( CmEdit, 3, 1 );

	LJPLabel = new QLabel( "LJP (mV)", TabPage_2 );
	TabPageLayout_2->addWidget( LJPLabel, 4, 0 );
	LJPEdit = new QLineEdit( "", TabPage_2 );
	LJPEdit->setAlignment( Qt::AlignHCenter );
	TabPageLayout_2->addWidget( LJPEdit, 4, 1 );
	tabBox->addTab( TabPage_2, QString::fromLatin1("") );
	tabBox->setTabText( tabBox->indexOf(TabPage_2), "Stim" );

	// Next tab
	tab = new QWidget( tabBox /*, "tab"*/ );
	tabLayout = new QGridLayout( tab );
	tabLayout->setColumnStretch( 0, 1);
	tabLayout->setColumnStretch( 1, 0);
	tab->setLayout(tabLayout);

	numTrialLabel = new QLabel( "Number of Trials", tab );
	tabLayout->addWidget( numTrialLabel, 0, 0 );
	numTrialEdit = new QLineEdit( "", tab );
	numTrialEdit->setAlignment( Qt::AlignHCenter );
	tabLayout->addWidget( numTrialEdit, 0, 1 );

	intervalTimeLabel = new QLabel( "Interval Time (ms)", tab );
	tabLayout->addWidget( intervalTimeLabel, 1, 0 );
	intervalTimeEdit = new QLineEdit( "", tab );
	intervalTimeEdit->setAlignment( Qt::AlignHCenter );
	tabLayout->addWidget( intervalTimeEdit, 1, 1 );

	recordDataLayout = new QHBoxLayout;
	spacer1a = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	recordDataLayout->addItem( spacer1a );

	recordDataCheckBox = new QCheckBox( "Record Data", tab );
	recordDataCheckBox->setTristate( false );
	recordDataLayout->addWidget( recordDataCheckBox );
	spacer2a = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	recordDataLayout->addItem( spacer2a );
	tabLayout->addLayout( recordDataLayout, 2, 0, 1, 2 );

	modelGroup = new QGroupBox( "Dynamic Clamp Model", tab );
	modelGroup->setAlignment( Qt::AlignCenter );
	modelGroupLayout = new QVBoxLayout( modelGroup );
	modelGroup->setLayout(modelGroupLayout);
	modelGroupLayout->setAlignment( Qt::AlignTop );

	modelComboBox = new QComboBox( modelGroup );
	modelGroupLayout->addWidget( modelComboBox );
	tabLayout->addWidget( modelGroup, 3, 0, 1, 2 );
	tabBox->addTab( tab, QString::fromLatin1("") );
	tabBox->setTabText( tabBox->indexOf(tab), "Protocol" );

	TabPage_3 = new QWidget( tabBox );
	TabPageLayout_3 = new QVBoxLayout( TabPage_3 );
	TabPage_3->setLayout(TabPageLayout_3);

	pEditLayout1 = new QGridLayout;
	deleteStepButton = new QPushButton( "Delete Step", TabPage_3 );
	pEditLayout1->addWidget( deleteStepButton, 1, 0 );
	loadProtocolButton = new QPushButton( "Load Protocol", TabPage_3 );
	pEditLayout1->addWidget( loadProtocolButton, 1, 1 );
	saveProtocolButton = new QPushButton( "Save Protocol", TabPage_3 );
	pEditLayout1->addWidget( saveProtocolButton, 0, 1 );
	addStepButton = new QPushButton( "Add Step", TabPage_3 );
	pEditLayout1->addWidget( addStepButton, 0, 0 );
	TabPageLayout_3->addLayout( pEditLayout1 );

	pEditLayout2 = new QHBoxLayout;
	spacer1 = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	pEditLayout2->addItem( spacer1 );
	clearProtocolButton = new QPushButton( "Clear Protocol", TabPage_3 );
	pEditLayout2->addWidget( clearProtocolButton );
	spacer2 = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	pEditLayout2->addItem( spacer2 );
	TabPageLayout_3->addLayout( pEditLayout2 );
	tabBox->addTab( TabPage_3, QString::fromLatin1("") );
	tabBox->setTabText( tabBox->indexOf(TabPage_3), "P. Editor" );

	tab_2 = new QWidget( tabBox );
	tabLayout_2 = new QGridLayout( tab_2 );
	tabLayout_2->setColumnStretch( 0, 1);
	tabLayout_2->setColumnStretch( 1, 0);
	tab_2->setLayout(tabLayout_2);

	APDRepolLabel = new QLabel( "APD Repol (%)", tab_2 );
	tabLayout_2->addWidget( APDRepolLabel, 0, 1, 1, 2);
	APDRepolEdit = new QLineEdit( "", tab_2 );
	APDRepolEdit->setAlignment( Qt::AlignCenter );
	tabLayout_2->addWidget( APDRepolEdit, 0, 3, 1, 1);

	minAPDLabel = new QLabel( "Min APD (ms)", tab_2 );
	tabLayout_2->addWidget( minAPDLabel, 1, 1, 1, 2);

	minAPDEdit = new QLineEdit( "", tab_2 );
	minAPDEdit->setAlignment( Qt::AlignCenter );
	tabLayout_2->addWidget( minAPDEdit, 1, 3, 1, 1);

	stimWindowLabel = new QLabel( "Stim Window (ms)", tab_2 );
	tabLayout_2->addWidget( stimWindowLabel, 2, 1, 1, 2);

	stimWindowEdit = new QLineEdit( "", tab_2 );
	stimWindowEdit->setAlignment( Qt::AlignCenter );
	tabLayout_2->addWidget( stimWindowEdit, 2, 3, 1, 1);

	tabBox->addTab( tab_2, QString::fromLatin1("") );
	tabBox->setTabText( tabBox->indexOf(tab_2), "APD" );
	IScale_DynClampUILayout->addWidget( tabBox );

	protocolEditorListBox = new QListWidget( this );
	protocolEditorListBox->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	protocolEditorListBox->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
	IScale_DynClampUILayout->addWidget( protocolEditorListBox );
}

/*
 *  Destroys the object and frees any allocated resources
 */
IScale_DynClampUI::~IScale_DynClampUI() { } // no need to delete child widgets, Qt does it all for us
