/****************************************************************************
** Form implementation generated from reading ui file 'IS_DC_MainWindowUI.ui'
**
** Created: Wed Mar 7 20:56:21 2012
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "IS_DC_MainWindowUI.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <default_gui_model.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlistbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a IScale_DynClampUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
IScale_DynClampUI::IScale_DynClampUI( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "IScale_DynClampUI" );
    setBaseSize( QSize( 0, 0 ) );
    IScale_DynClampUILayout = new QVBoxLayout( this, 4, 6, "IScale_DynClampUILayout"); 

    systemButtonGroup = new QButtonGroup( this, "systemButtonGroup" );
    systemButtonGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, systemButtonGroup->sizePolicy().hasHeightForWidth() ) );
    systemButtonGroup->setMinimumSize( QSize( 0, 0 ) );
    QFont systemButtonGroup_font(  systemButtonGroup->font() );
    systemButtonGroup_font.setBold( TRUE );
    systemButtonGroup->setFont( systemButtonGroup_font ); 
    systemButtonGroup->setFrameShape( QButtonGroup::NoFrame );
    systemButtonGroup->setColumnLayout(0, Qt::Vertical );
    systemButtonGroup->layout()->setSpacing( 6 );
    systemButtonGroup->layout()->setMargin( 11 );
    systemButtonGroupLayout = new QHBoxLayout( systemButtonGroup->layout() );
    systemButtonGroupLayout->setAlignment( Qt::AlignTop );

    pauseButton = new QPushButton( systemButtonGroup, "pauseButton" );
    pauseButton->setToggleButton( TRUE );
    systemButtonGroupLayout->addWidget( pauseButton );

    modifyButton = new QPushButton( systemButtonGroup, "modifyButton" );
    modifyButton->setToggleButton( FALSE );
    systemButtonGroupLayout->addWidget( modifyButton );

    resetButton = new QPushButton( systemButtonGroup, "resetButton" );
    resetButton->setToggleButton( FALSE );
    systemButtonGroupLayout->addWidget( resetButton );

    unloadButton = new QPushButton( systemButtonGroup, "unloadButton" );
    unloadButton->setToggleButton( FALSE );
    systemButtonGroupLayout->addWidget( unloadButton );
    IScale_DynClampUILayout->addWidget( systemButtonGroup );

    stateGroupBox = new QGroupBox( this, "stateGroupBox" );
    stateGroupBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, stateGroupBox->sizePolicy().hasHeightForWidth() ) );
    QFont stateGroupBox_font(  stateGroupBox->font() );
    stateGroupBox_font.setBold( TRUE );
    stateGroupBox->setFont( stateGroupBox_font ); 
    stateGroupBox->setAlignment( int( QGroupBox::AlignCenter ) );
    stateGroupBox->setColumnLayout(0, Qt::Vertical );
    stateGroupBox->layout()->setSpacing( 6 );
    stateGroupBox->layout()->setMargin( 11 );
    stateGroupBoxLayout = new QGridLayout( stateGroupBox->layout() );
    stateGroupBoxLayout->setAlignment( Qt::AlignTop );

    timeLayout = new QHBoxLayout( 0, 0, 6, "timeLayout"); 

    timeLabel = new QLabel( stateGroupBox, "timeLabel" );
    timeLabel->setMinimumSize( QSize( 100, 0 ) );
    timeLabel->setMaximumSize( QSize( 100, 32767 ) );
    timeLabel->setAlignment( int( QLabel::AlignCenter ) );
    timeLayout->addWidget( timeLabel );

    timeEdit = new DefaultGUILineEdit( stateGroupBox );
    timeEdit->setMinimumSize( QSize( 0, 0 ) );
    timeEdit->setMaximumSize( QSize( 75, 32767 ) );
    timeEdit->setReadOnly( TRUE );
    timeLayout->addWidget( timeEdit );

    stateGroupBoxLayout->addLayout( timeLayout, 0, 0 );

    beatNumLayout = new QHBoxLayout( 0, 0, 6, "beatNumLayout"); 

    beatNumLabel = new QLabel( stateGroupBox, "beatNumLabel" );
    beatNumLabel->setMinimumSize( QSize( 100, 0 ) );
    beatNumLabel->setMaximumSize( QSize( 100, 32767 ) );
    beatNumLabel->setAlignment( int( QLabel::AlignCenter ) );
    beatNumLayout->addWidget( beatNumLabel );

    beatNumEdit = new DefaultGUILineEdit( stateGroupBox );
    beatNumEdit->setMinimumSize( QSize( 0, 0 ) );
    beatNumEdit->setMaximumSize( QSize( 75, 32767 ) );
    beatNumEdit->setReadOnly( TRUE );
    beatNumLayout->addWidget( beatNumEdit );

    stateGroupBoxLayout->addLayout( beatNumLayout, 1, 0 );

    voltageLayout = new QHBoxLayout( 0, 0, 6, "voltageLayout"); 

    voltageLabel = new QLabel( stateGroupBox, "voltageLabel" );
    voltageLabel->setMinimumSize( QSize( 100, 0 ) );
    voltageLabel->setMaximumSize( QSize( 100, 32767 ) );
    voltageLabel->setAlignment( int( QLabel::AlignCenter ) );
    voltageLayout->addWidget( voltageLabel );

    voltageEdit = new DefaultGUILineEdit( stateGroupBox );
    voltageEdit->setMinimumSize( QSize( 0, 0 ) );
    voltageEdit->setMaximumSize( QSize( 75, 32767 ) );
    voltageEdit->setReadOnly( TRUE );
    voltageLayout->addWidget( voltageEdit );

    stateGroupBoxLayout->addLayout( voltageLayout, 0, 2 );

    APDLayout = new QHBoxLayout( 0, 0, 6, "APDLayout"); 

    APDLabel = new QLabel( stateGroupBox, "APDLabel" );
    APDLabel->setMinimumSize( QSize( 100, 0 ) );
    APDLabel->setMaximumSize( QSize( 100, 32767 ) );
    APDLabel->setAlignment( int( QLabel::AlignCenter ) );
    APDLayout->addWidget( APDLabel );

    APDEdit = new DefaultGUILineEdit( stateGroupBox );
    APDEdit->setMinimumSize( QSize( 0, 0 ) );
    APDEdit->setMaximumSize( QSize( 75, 32767 ) );
    APDEdit->setReadOnly( TRUE );
    APDLayout->addWidget( APDEdit );

    stateGroupBoxLayout->addLayout( APDLayout, 1, 2 );
    spacer5 = new QSpacerItem( 1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    stateGroupBoxLayout->addItem( spacer5, 1, 1 );
    spacer4 = new QSpacerItem( 1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    stateGroupBoxLayout->addItem( spacer4, 0, 1 );
    IScale_DynClampUILayout->addWidget( stateGroupBox );

    protocolButtonGroup = new QButtonGroup( this, "protocolButtonGroup" );
    protocolButtonGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, protocolButtonGroup->sizePolicy().hasHeightForWidth() ) );
    QFont protocolButtonGroup_font(  protocolButtonGroup->font() );
    protocolButtonGroup_font.setBold( TRUE );
    protocolButtonGroup->setFont( protocolButtonGroup_font ); 
    protocolButtonGroup->setAlignment( int( QButtonGroup::AlignCenter ) );
    protocolButtonGroup->setColumnLayout(0, Qt::Vertical );
    protocolButtonGroup->layout()->setSpacing( 6 );
    protocolButtonGroup->layout()->setMargin( 11 );
    protocolButtonGroupLayout = new QHBoxLayout( protocolButtonGroup->layout() );
    protocolButtonGroupLayout->setAlignment( Qt::AlignTop );

    thresholdButton = new QPushButton( protocolButtonGroup, "thresholdButton" );
    thresholdButton->setToggleButton( TRUE );
    protocolButtonGroupLayout->addWidget( thresholdButton );

    staticPacingButton = new QPushButton( protocolButtonGroup, "staticPacingButton" );
    staticPacingButton->setToggleButton( TRUE );
    protocolButtonGroupLayout->addWidget( staticPacingButton );

    startProtocolButton = new QPushButton( protocolButtonGroup, "startProtocolButton" );
    startProtocolButton->setToggleButton( TRUE );
    protocolButtonGroupLayout->addWidget( startProtocolButton );
    IScale_DynClampUILayout->addWidget( protocolButtonGroup );

    layout26 = new QHBoxLayout( 0, 0, 6, "layout26"); 

    layoutA2 = new QVBoxLayout( 0, 0, 6, "layoutA2"); 

    APDParamGroup = new QButtonGroup( this, "APDParamGroup" );
    APDParamGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, APDParamGroup->sizePolicy().hasHeightForWidth() ) );
    QFont APDParamGroup_font(  APDParamGroup->font() );
    APDParamGroup->setFont( APDParamGroup_font ); 
    APDParamGroup->setAlignment( int( QButtonGroup::AlignCenter ) );
    APDParamGroup->setColumnLayout(0, Qt::Vertical );
    APDParamGroup->layout()->setSpacing( 6 );
    APDParamGroup->layout()->setMargin( 11 );
    APDParamGroupLayout = new QVBoxLayout( APDParamGroup->layout() );
    APDParamGroupLayout->setAlignment( Qt::AlignTop );

    APDRepolLayout = new QHBoxLayout( 0, 0, 6, "APDRepolLayout"); 

    APDRepolLabel = new QLabel( APDParamGroup, "APDRepolLabel" );
    APDRepolLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, APDRepolLabel->sizePolicy().hasHeightForWidth() ) );
    APDRepolLabel->setMinimumSize( QSize( 130, 0 ) );
    APDRepolLabel->setMaximumSize( QSize( 130, 32767 ) );
    APDRepolLabel->setAlignment( int( QLabel::AlignCenter ) );
    APDRepolLayout->addWidget( APDRepolLabel );

    APDRepolEdit = new DefaultGUILineEdit( APDParamGroup );
    APDRepolEdit->setMinimumSize( QSize( 50, 0 ) );
    APDRepolEdit->setMaximumSize( QSize( 50, 32767 ) );
    APDRepolLayout->addWidget( APDRepolEdit );
    APDParamGroupLayout->addLayout( APDRepolLayout );

    minAPDLayout = new QHBoxLayout( 0, 0, 6, "minAPDLayout"); 

    minAPDLabel = new QLabel( APDParamGroup, "minAPDLabel" );
    minAPDLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, minAPDLabel->sizePolicy().hasHeightForWidth() ) );
    minAPDLabel->setMinimumSize( QSize( 130, 0 ) );
    minAPDLabel->setMaximumSize( QSize( 130, 32767 ) );
    minAPDLabel->setAlignment( int( QLabel::AlignCenter ) );
    minAPDLayout->addWidget( minAPDLabel );

    minAPDEdit = new DefaultGUILineEdit( APDParamGroup );
    minAPDEdit->setMinimumSize( QSize( 50, 0 ) );
    minAPDEdit->setMaximumSize( QSize( 50, 32767 ) );
    minAPDLayout->addWidget( minAPDEdit );
    APDParamGroupLayout->addLayout( minAPDLayout );
    layoutA2->addWidget( APDParamGroup );

    protocolParamGroup = new QButtonGroup( this, "protocolParamGroup" );
    protocolParamGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, protocolParamGroup->sizePolicy().hasHeightForWidth() ) );
    QFont protocolParamGroup_font(  protocolParamGroup->font() );
    protocolParamGroup->setFont( protocolParamGroup_font ); 
    protocolParamGroup->setAlignment( int( QButtonGroup::AlignCenter ) );
    protocolParamGroup->setColumnLayout(0, Qt::Vertical );
    protocolParamGroup->layout()->setSpacing( 6 );
    protocolParamGroup->layout()->setMargin( 11 );
    protocolParamGroupLayout = new QVBoxLayout( protocolParamGroup->layout() );
    protocolParamGroupLayout->setAlignment( Qt::AlignTop );

    numTrialLayout = new QHBoxLayout( 0, 0, 6, "numTrialLayout"); 

    numTrialLabel = new QLabel( protocolParamGroup, "numTrialLabel" );
    numTrialLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, numTrialLabel->sizePolicy().hasHeightForWidth() ) );
    numTrialLabel->setMinimumSize( QSize( 130, 0 ) );
    numTrialLabel->setMaximumSize( QSize( 130, 32767 ) );
    QFont numTrialLabel_font(  numTrialLabel->font() );
    numTrialLabel->setFont( numTrialLabel_font ); 
    numTrialLabel->setAlignment( int( QLabel::AlignCenter ) );
    numTrialLayout->addWidget( numTrialLabel );

    numTrialEdit = new DefaultGUILineEdit( protocolParamGroup );
    numTrialEdit->setMinimumSize( QSize( 50, 0 ) );
    numTrialEdit->setMaximumSize( QSize( 50, 32767 ) );
    numTrialLayout->addWidget( numTrialEdit );
    protocolParamGroupLayout->addLayout( numTrialLayout );

    intervalTimeLayout = new QHBoxLayout( 0, 0, 6, "intervalTimeLayout"); 

    intervalTimeLabel = new QLabel( protocolParamGroup, "intervalTimeLabel" );
    intervalTimeLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, intervalTimeLabel->sizePolicy().hasHeightForWidth() ) );
    intervalTimeLabel->setMinimumSize( QSize( 130, 0 ) );
    intervalTimeLabel->setMaximumSize( QSize( 130, 32767 ) );
    intervalTimeLabel->setAlignment( int( QLabel::AlignCenter ) );
    intervalTimeLayout->addWidget( intervalTimeLabel );

    intervalTimeEdit = new DefaultGUILineEdit( protocolParamGroup );
    intervalTimeEdit->setMinimumSize( QSize( 50, 0 ) );
    intervalTimeEdit->setMaximumSize( QSize( 50, 32767 ) );
    intervalTimeLayout->addWidget( intervalTimeEdit );
    protocolParamGroupLayout->addLayout( intervalTimeLayout );

    recordDataCheckBox = new QCheckBox( protocolParamGroup, "recordDataCheckBox" );
    QFont recordDataCheckBox_font(  recordDataCheckBox->font() );
    recordDataCheckBox_font.setBold( TRUE );
    recordDataCheckBox->setFont( recordDataCheckBox_font ); 
    recordDataCheckBox->setTristate( FALSE );
    protocolParamGroupLayout->addWidget( recordDataCheckBox );
    layoutA2->addWidget( protocolParamGroup );
    layout26->addLayout( layoutA2 );
    spacer3 = new QSpacerItem( 1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout26->addItem( spacer3 );

    layoutA3 = new QVBoxLayout( 0, 0, 6, "layoutA3"); 

    stimParamGroup = new QGroupBox( this, "stimParamGroup" );
    stimParamGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, stimParamGroup->sizePolicy().hasHeightForWidth() ) );
    QFont stimParamGroup_font(  stimParamGroup->font() );
    stimParamGroup->setFont( stimParamGroup_font ); 
    stimParamGroup->setAlignment( int( QGroupBox::AlignCenter ) );
    stimParamGroup->setColumnLayout(0, Qt::Vertical );
    stimParamGroup->layout()->setSpacing( 6 );
    stimParamGroup->layout()->setMargin( 11 );
    stimParamGroupLayout = new QVBoxLayout( stimParamGroup->layout() );
    stimParamGroupLayout->setAlignment( Qt::AlignTop );

    BCLLayout = new QHBoxLayout( 0, 0, 6, "BCLLayout"); 

    BCLLabel = new QLabel( stimParamGroup, "BCLLabel" );
    BCLLabel->setMinimumSize( QSize( 110, 0 ) );
    BCLLabel->setMaximumSize( QSize( 110, 32767 ) );
    BCLLabel->setAlignment( int( QLabel::AlignCenter ) );
    BCLLayout->addWidget( BCLLabel );

    BCLEdit = new DefaultGUILineEdit( stimParamGroup );
    BCLEdit->setMinimumSize( QSize( 50, 0 ) );
    BCLEdit->setMaximumSize( QSize( 50, 32767 ) );
    BCLLayout->addWidget( BCLEdit );
    stimParamGroupLayout->addLayout( BCLLayout );

    stimMagLayout = new QHBoxLayout( 0, 0, 6, "stimMagLayout"); 

    stimMagLabel = new QLabel( stimParamGroup, "stimMagLabel" );
    stimMagLabel->setMinimumSize( QSize( 110, 0 ) );
    stimMagLabel->setMaximumSize( QSize( 110, 32767 ) );
    stimMagLabel->setAlignment( int( QLabel::AlignCenter ) );
    stimMagLayout->addWidget( stimMagLabel );

    stimMagEdit = new DefaultGUILineEdit( stimParamGroup );
    stimMagEdit->setMinimumSize( QSize( 50, 0 ) );
    stimMagEdit->setMaximumSize( QSize( 50, 32767 ) );
    stimMagLayout->addWidget( stimMagEdit );
    stimParamGroupLayout->addLayout( stimMagLayout );

    stimLengthLayout = new QHBoxLayout( 0, 0, 6, "stimLengthLayout"); 

    stimLengthLabel = new QLabel( stimParamGroup, "stimLengthLabel" );
    stimLengthLabel->setMinimumSize( QSize( 110, 0 ) );
    stimLengthLabel->setMaximumSize( QSize( 110, 32767 ) );
    stimLengthLabel->setAlignment( int( QLabel::AlignCenter ) );
    stimLengthLayout->addWidget( stimLengthLabel );

    stimLengthEdit = new DefaultGUILineEdit( stimParamGroup );
    stimLengthEdit->setMinimumSize( QSize( 50, 0 ) );
    stimLengthEdit->setMaximumSize( QSize( 50, 32767 ) );
    stimLengthLayout->addWidget( stimLengthEdit );
    stimParamGroupLayout->addLayout( stimLengthLayout );

    CmEditLayout = new QHBoxLayout( 0, 0, 6, "CmEditLayout"); 

    CmLabel = new QLabel( stimParamGroup, "CmLabel" );
    CmLabel->setMinimumSize( QSize( 110, 0 ) );
    CmLabel->setMaximumSize( QSize( 110, 32767 ) );
    CmLabel->setAlignment( int( QLabel::AlignCenter ) );
    CmEditLayout->addWidget( CmLabel );

    CmEdit = new DefaultGUILineEdit( stimParamGroup );
    CmEdit->setMinimumSize( QSize( 50, 0 ) );
    CmEdit->setMaximumSize( QSize( 50, 32767 ) );
    CmEditLayout->addWidget( CmEdit );
    stimParamGroupLayout->addLayout( CmEditLayout );
    layoutA3->addWidget( stimParamGroup );

    modelGroup = new QGroupBox( this, "modelGroup" );
    modelGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, modelGroup->sizePolicy().hasHeightForWidth() ) );
    QFont modelGroup_font(  modelGroup->font() );
    modelGroup->setFont( modelGroup_font ); 
    modelGroup->setAlignment( int( QGroupBox::AlignCenter ) );
    modelGroup->setColumnLayout(0, Qt::Vertical );
    modelGroup->layout()->setSpacing( 6 );
    modelGroup->layout()->setMargin( 11 );
    modelGroupLayout = new QVBoxLayout( modelGroup->layout() );
    modelGroupLayout->setAlignment( Qt::AlignTop );

    modelComboBox = new QComboBox( FALSE, modelGroup, "modelComboBox" );
    modelGroupLayout->addWidget( modelComboBox );
    layoutA3->addWidget( modelGroup );
    layout26->addLayout( layoutA3 );
    IScale_DynClampUILayout->addLayout( layout26 );

    layoutB = new QHBoxLayout( 0, 0, 6, "layoutB"); 

    protocolEditorButtonGroup = new QButtonGroup( this, "protocolEditorButtonGroup" );
    QFont protocolEditorButtonGroup_font(  protocolEditorButtonGroup->font() );
    protocolEditorButtonGroup_font.setBold( TRUE );
    protocolEditorButtonGroup->setFont( protocolEditorButtonGroup_font ); 
    protocolEditorButtonGroup->setAlignment( int( QButtonGroup::AlignCenter ) );
    protocolEditorButtonGroup->setColumnLayout(0, Qt::Vertical );
    protocolEditorButtonGroup->layout()->setSpacing( 6 );
    protocolEditorButtonGroup->layout()->setMargin( 11 );
    protocolEditorButtonGroupLayout = new QVBoxLayout( protocolEditorButtonGroup->layout() );
    protocolEditorButtonGroupLayout->setAlignment( Qt::AlignTop );

    addStepButton = new QPushButton( protocolEditorButtonGroup, "addStepButton" );
    protocolEditorButtonGroupLayout->addWidget( addStepButton );

    deleteStepButton = new QPushButton( protocolEditorButtonGroup, "deleteStepButton" );
    protocolEditorButtonGroupLayout->addWidget( deleteStepButton );

    saveProtocolButton = new QPushButton( protocolEditorButtonGroup, "saveProtocolButton" );
    protocolEditorButtonGroupLayout->addWidget( saveProtocolButton );

    loadProtocolButton = new QPushButton( protocolEditorButtonGroup, "loadProtocolButton" );
    protocolEditorButtonGroupLayout->addWidget( loadProtocolButton );

    clearProtocolButton = new QPushButton( protocolEditorButtonGroup, "clearProtocolButton" );
    protocolEditorButtonGroupLayout->addWidget( clearProtocolButton );
    layoutB->addWidget( protocolEditorButtonGroup );

    protocolEditorListBox = new QListBox( this, "protocolEditorListBox" );
    protocolEditorListBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, protocolEditorListBox->sizePolicy().hasHeightForWidth() ) );
    protocolEditorListBox->setMinimumSize( QSize( 250, 0 ) );
    QFont protocolEditorListBox_font(  protocolEditorListBox->font() );
    protocolEditorListBox->setFont( protocolEditorListBox_font ); 
    protocolEditorListBox->setVScrollBarMode( QListBox::AlwaysOn );
    protocolEditorListBox->setHScrollBarMode( QListBox::Auto );
    layoutB->addWidget( protocolEditorListBox );
    IScale_DynClampUILayout->addLayout( layoutB );
    languageChange();
    resize( QSize(427, 615).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
IScale_DynClampUI::~IScale_DynClampUI()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void IScale_DynClampUI::languageChange()
{
    setCaption( tr( "Current Scaling Dynamic Clamp" ) );
    systemButtonGroup->setTitle( QString::null );
    pauseButton->setText( tr( "Pause" ) );
    modifyButton->setText( tr( "Modify" ) );
    resetButton->setText( tr( "Reset" ) );
    unloadButton->setText( tr( "Unload" ) );
    stateGroupBox->setTitle( tr( "States" ) );
    timeLabel->setText( tr( "Time (ms)" ) );
    beatNumLabel->setText( tr( "Beat Number" ) );
    voltageLabel->setText( tr( "Voltage (mV)" ) );
    APDLabel->setText( tr( "APD (ms)" ) );
    protocolButtonGroup->setTitle( tr( "Protocol Control" ) );
    thresholdButton->setText( tr( "Threshold" ) );
    staticPacingButton->setText( tr( "Static Pacing" ) );
    startProtocolButton->setText( tr( "Start Protocol" ) );
    APDParamGroup->setTitle( tr( "APD Parameters" ) );
    APDRepolLabel->setText( tr( "APD Repolarization %" ) );
    minAPDLabel->setText( tr( "Minimum APD (ms)" ) );
    protocolParamGroup->setTitle( tr( "Protocol Parameters" ) );
    numTrialLabel->setText( tr( "Number of Trials" ) );
    intervalTimeLabel->setText( tr( "Interval Time (ms)" ) );
    recordDataCheckBox->setText( tr( "Record Data" ) );
    stimParamGroup->setTitle( tr( "Stimulation Parameters" ) );
    BCLLabel->setText( tr( "BCL (ms)" ) );
    stimMagLabel->setText( tr( "Stim Mag (nA)" ) );
    stimLengthLabel->setText( tr( "Stim Length (ms)" ) );
    CmLabel->setText( tr( "Cm (pF)" ) );
    modelGroup->setTitle( tr( "Dynamic Clamp Model" ) );
    protocolEditorButtonGroup->setTitle( tr( "Protocol Editor" ) );
    addStepButton->setText( tr( "Add Step" ) );
    deleteStepButton->setText( tr( "Delete Step" ) );
    saveProtocolButton->setText( tr( "Save Protocol" ) );
    loadProtocolButton->setText( tr( "Load Protocol" ) );
    clearProtocolButton->setText( tr( "Clear Protocol" ) );
}

