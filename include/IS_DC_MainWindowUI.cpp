/****************************************************************************
** Form implementation generated from reading ui file 'IS_DC_MainWindowUI.ui'
**
** Created: Mon Jul 29 15:55:34 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "IS_DC_MainWindowUI.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qtabwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
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
    setPaletteBackgroundColor( QColor( 195, 195, 195 ) );
    QPalette pal;
    QColorGroup cg;
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 221, 223, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, white );
    cg.setColor( QColorGroup::Dark, QColor( 85, 85, 85) );
    cg.setColor( QColorGroup::Mid, QColor( 199, 199, 199) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 195, 195, 195) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 103, 141, 178) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 238) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 82, 24, 139) );
    pal.setActive( cg );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 221, 223, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, white );
    cg.setColor( QColorGroup::Dark, QColor( 85, 85, 85) );
    cg.setColor( QColorGroup::Mid, QColor( 199, 199, 199) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 195, 195, 195) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 103, 141, 178) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 238) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 82, 24, 139) );
    pal.setInactive( cg );
    cg.setColor( QColorGroup::Foreground, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Button, QColor( 221, 223, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, white );
    cg.setColor( QColorGroup::Dark, QColor( 85, 85, 85) );
    cg.setColor( QColorGroup::Mid, QColor( 199, 199, 199) );
    cg.setColor( QColorGroup::Text, QColor( 199, 199, 199) );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 195, 195, 195) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 86, 117, 148) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 238) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 82, 24, 139) );
    pal.setDisabled( cg );
    setPalette( pal );
    IScale_DynClampUILayout = new QVBoxLayout( this, 11, 6, "IScale_DynClampUILayout"); 

    protocolButtonGroup = new QButtonGroup( this, "protocolButtonGroup" );
    protocolButtonGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, protocolButtonGroup->sizePolicy().hasHeightForWidth() ) );
    protocolButtonGroup->setPaletteBackgroundColor( QColor( 221, 223, 228 ) );
    QFont protocolButtonGroup_font(  protocolButtonGroup->font() );
    protocolButtonGroup_font.setBold( TRUE );
    protocolButtonGroup->setFont( protocolButtonGroup_font ); 
    protocolButtonGroup->setAlignment( int( QButtonGroup::AlignCenter ) );
    protocolButtonGroup->setColumnLayout(0, Qt::Vertical );
    protocolButtonGroup->layout()->setSpacing( 6 );
    protocolButtonGroup->layout()->setMargin( 11 );
    protocolButtonGroupLayout = new QGridLayout( protocolButtonGroup->layout() );
    protocolButtonGroupLayout->setAlignment( Qt::AlignTop );
    spacer1b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolButtonGroupLayout->addItem( spacer1b, 0, 4 );
    spacer2b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolButtonGroupLayout->addItem( spacer2b, 1, 4 );

    staticPacingButton = new QPushButton( protocolButtonGroup, "staticPacingButton" );
    staticPacingButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, staticPacingButton->sizePolicy().hasHeightForWidth() ) );
    staticPacingButton->setMaximumSize( QSize( 250, 32767 ) );
    staticPacingButton->setPaletteBackgroundColor( QColor( 116, 144, 191 ) );
    staticPacingButton->setFocusPolicy( QPushButton::NoFocus );
    staticPacingButton->setToggleButton( TRUE );

    protocolButtonGroupLayout->addWidget( staticPacingButton, 0, 3 );

    resetButton = new QPushButton( protocolButtonGroup, "resetButton" );
    resetButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, resetButton->sizePolicy().hasHeightForWidth() ) );
    resetButton->setMaximumSize( QSize( 250, 32767 ) );
    resetButton->setPaletteBackgroundColor( QColor( 116, 144, 191 ) );
    resetButton->setFocusPolicy( QPushButton::NoFocus );
    resetButton->setToggleButton( FALSE );

    protocolButtonGroupLayout->addWidget( resetButton, 1, 3 );
    spacer3b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolButtonGroupLayout->addItem( spacer3b, 0, 2 );
    spacer4b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolButtonGroupLayout->addItem( spacer4b, 1, 2 );

    startProtocolButton = new QPushButton( protocolButtonGroup, "startProtocolButton" );
    startProtocolButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, startProtocolButton->sizePolicy().hasHeightForWidth() ) );
    startProtocolButton->setMaximumSize( QSize( 250, 32767 ) );
    startProtocolButton->setPaletteBackgroundColor( QColor( 116, 144, 191 ) );
    startProtocolButton->setFocusPolicy( QPushButton::NoFocus );
    startProtocolButton->setToggleButton( TRUE );

    protocolButtonGroupLayout->addWidget( startProtocolButton, 1, 1 );

    thresholdButton = new QPushButton( protocolButtonGroup, "thresholdButton" );
    thresholdButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, thresholdButton->sizePolicy().hasHeightForWidth() ) );
    thresholdButton->setMaximumSize( QSize( 250, 32767 ) );
    thresholdButton->setPaletteBackgroundColor( QColor( 116, 144, 191 ) );
    thresholdButton->setFocusPolicy( QPushButton::NoFocus );
    thresholdButton->setToggleButton( TRUE );

    protocolButtonGroupLayout->addWidget( thresholdButton, 0, 1 );
    spacer5b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolButtonGroupLayout->addItem( spacer5b, 1, 0 );
    spacer6b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolButtonGroupLayout->addItem( spacer6b, 0, 0 );
    IScale_DynClampUILayout->addWidget( protocolButtonGroup );

    tabBox = new QTabWidget( this, "tabBox" );
    tabBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)1, 0, 0, tabBox->sizePolicy().hasHeightForWidth() ) );
    tabBox->setPaletteBackgroundColor( QColor( 221, 223, 228 ) );
    QFont tabBox_font(  tabBox->font() );
    tabBox_font.setBold( TRUE );
    tabBox->setFont( tabBox_font ); 
    tabBox->setFocusPolicy( QTabWidget::NoFocus );
    tabBox->setTabPosition( QTabWidget::Top );
    tabBox->setTabShape( QTabWidget::Rounded );

    TabPage = new QWidget( tabBox, "TabPage" );
    TabPageLayout = new QVBoxLayout( TabPage, 11, 0, "TabPageLayout"); 

    timeLayout = new QHBoxLayout( 0, 0, 6, "timeLayout"); 

    timeLabel = new QLabel( TabPage, "timeLabel" );
    timeLabel->setMinimumSize( QSize( 100, 0 ) );
    timeLabel->setMaximumSize( QSize( 100, 32767 ) );
    QFont timeLabel_font(  timeLabel->font() );
    timeLabel->setFont( timeLabel_font ); 
    timeLabel->setAlignment( int( QLabel::AlignCenter ) );
    timeLayout->addWidget( timeLabel );

    timeEdit = new QLineEdit( TabPage, "timeEdit" );
    timeEdit->setMinimumSize( QSize( 0, 0 ) );
    timeEdit->setMaximumSize( QSize( 75, 32767 ) );
    timeEdit->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
    QFont timeEdit_font(  timeEdit->font() );
    timeEdit->setFont( timeEdit_font ); 
    timeEdit->setAlignment( int( QLineEdit::AlignHCenter ) );
    timeEdit->setReadOnly( TRUE );
    timeLayout->addWidget( timeEdit );
    TabPageLayout->addLayout( timeLayout );

    beatNumLayout = new QHBoxLayout( 0, 0, 6, "beatNumLayout"); 

    beatNumLabel = new QLabel( TabPage, "beatNumLabel" );
    beatNumLabel->setMinimumSize( QSize( 100, 0 ) );
    beatNumLabel->setMaximumSize( QSize( 100, 32767 ) );
    QFont beatNumLabel_font(  beatNumLabel->font() );
    beatNumLabel->setFont( beatNumLabel_font ); 
    beatNumLabel->setAlignment( int( QLabel::AlignCenter ) );
    beatNumLayout->addWidget( beatNumLabel );

    beatNumEdit = new QLineEdit( TabPage, "beatNumEdit" );
    beatNumEdit->setMinimumSize( QSize( 0, 0 ) );
    beatNumEdit->setMaximumSize( QSize( 75, 32767 ) );
    beatNumEdit->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
    QFont beatNumEdit_font(  beatNumEdit->font() );
    beatNumEdit->setFont( beatNumEdit_font ); 
    beatNumEdit->setAlignment( int( QLineEdit::AlignHCenter ) );
    beatNumEdit->setReadOnly( TRUE );
    beatNumLayout->addWidget( beatNumEdit );
    TabPageLayout->addLayout( beatNumLayout );

    voltageLayout = new QHBoxLayout( 0, 0, 6, "voltageLayout"); 

    voltageLabel = new QLabel( TabPage, "voltageLabel" );
    voltageLabel->setMinimumSize( QSize( 100, 0 ) );
    voltageLabel->setMaximumSize( QSize( 100, 32767 ) );
    QFont voltageLabel_font(  voltageLabel->font() );
    voltageLabel->setFont( voltageLabel_font ); 
    voltageLabel->setAlignment( int( QLabel::AlignCenter ) );
    voltageLayout->addWidget( voltageLabel );

    voltageEdit = new QLineEdit( TabPage, "voltageEdit" );
    voltageEdit->setMinimumSize( QSize( 0, 0 ) );
    voltageEdit->setMaximumSize( QSize( 75, 32767 ) );
    voltageEdit->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
    QFont voltageEdit_font(  voltageEdit->font() );
    voltageEdit->setFont( voltageEdit_font ); 
    voltageEdit->setAlignment( int( QLineEdit::AlignHCenter ) );
    voltageEdit->setReadOnly( TRUE );
    voltageLayout->addWidget( voltageEdit );
    TabPageLayout->addLayout( voltageLayout );

    APDLayout = new QHBoxLayout( 0, 0, 6, "APDLayout"); 

    APDLabel = new QLabel( TabPage, "APDLabel" );
    APDLabel->setMinimumSize( QSize( 100, 0 ) );
    APDLabel->setMaximumSize( QSize( 100, 32767 ) );
    QFont APDLabel_font(  APDLabel->font() );
    APDLabel->setFont( APDLabel_font ); 
    APDLabel->setAlignment( int( QLabel::AlignCenter ) );
    APDLayout->addWidget( APDLabel );

    APDEdit = new QLineEdit( TabPage, "APDEdit" );
    APDEdit->setMinimumSize( QSize( 0, 0 ) );
    APDEdit->setMaximumSize( QSize( 75, 32767 ) );
    APDEdit->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
    QFont APDEdit_font(  APDEdit->font() );
    APDEdit->setFont( APDEdit_font ); 
    APDEdit->setAlignment( int( QLineEdit::AlignHCenter ) );
    APDEdit->setReadOnly( TRUE );
    APDLayout->addWidget( APDEdit );
    TabPageLayout->addLayout( APDLayout );
    tabBox->insertTab( TabPage, QString::fromLatin1("") );

    TabPage_2 = new QWidget( tabBox, "TabPage_2" );
    TabPageLayout_2 = new QVBoxLayout( TabPage_2, 11, 6, "TabPageLayout_2"); 

    BCLLayout = new QHBoxLayout( 0, 0, 6, "BCLLayout"); 

    BCLLabel = new QLabel( TabPage_2, "BCLLabel" );
    BCLLabel->setMinimumSize( QSize( 120, 0 ) );
    BCLLabel->setMaximumSize( QSize( 120, 32767 ) );
    QFont BCLLabel_font(  BCLLabel->font() );
    BCLLabel->setFont( BCLLabel_font ); 
    BCLLabel->setAlignment( int( QLabel::AlignCenter ) );
    BCLLayout->addWidget( BCLLabel );

    BCLEdit = new QLineEdit( TabPage_2, "BCLEdit" );
    BCLEdit->setMinimumSize( QSize( 0, 0 ) );
    BCLEdit->setMaximumSize( QSize( 50, 32767 ) );
    QFont BCLEdit_font(  BCLEdit->font() );
    BCLEdit->setFont( BCLEdit_font ); 
    BCLEdit->setAlignment( int( QLineEdit::AlignHCenter ) );
    BCLLayout->addWidget( BCLEdit );
    TabPageLayout_2->addLayout( BCLLayout );

    stimMagLayout = new QHBoxLayout( 0, 0, 6, "stimMagLayout"); 

    stimMagLabel = new QLabel( TabPage_2, "stimMagLabel" );
    stimMagLabel->setMinimumSize( QSize( 120, 0 ) );
    stimMagLabel->setMaximumSize( QSize( 120, 32767 ) );
    QFont stimMagLabel_font(  stimMagLabel->font() );
    stimMagLabel->setFont( stimMagLabel_font ); 
    stimMagLabel->setAlignment( int( QLabel::AlignCenter ) );
    stimMagLayout->addWidget( stimMagLabel );

    stimMagEdit = new QLineEdit( TabPage_2, "stimMagEdit" );
    stimMagEdit->setMinimumSize( QSize( 0, 0 ) );
    stimMagEdit->setMaximumSize( QSize( 50, 32767 ) );
    QFont stimMagEdit_font(  stimMagEdit->font() );
    stimMagEdit->setFont( stimMagEdit_font ); 
    stimMagEdit->setAlignment( int( QLineEdit::AlignHCenter ) );
    stimMagLayout->addWidget( stimMagEdit );
    TabPageLayout_2->addLayout( stimMagLayout );

    stimLengthLayout = new QHBoxLayout( 0, 0, 6, "stimLengthLayout"); 

    stimLengthLabel = new QLabel( TabPage_2, "stimLengthLabel" );
    stimLengthLabel->setMinimumSize( QSize( 120, 0 ) );
    stimLengthLabel->setMaximumSize( QSize( 120, 32767 ) );
    QFont stimLengthLabel_font(  stimLengthLabel->font() );
    stimLengthLabel->setFont( stimLengthLabel_font ); 
    stimLengthLabel->setAlignment( int( QLabel::AlignCenter ) );
    stimLengthLayout->addWidget( stimLengthLabel );

    stimLengthEdit = new QLineEdit( TabPage_2, "stimLengthEdit" );
    stimLengthEdit->setMinimumSize( QSize( 0, 0 ) );
    stimLengthEdit->setMaximumSize( QSize( 50, 32767 ) );
    QFont stimLengthEdit_font(  stimLengthEdit->font() );
    stimLengthEdit->setFont( stimLengthEdit_font ); 
    stimLengthEdit->setAlignment( int( QLineEdit::AlignHCenter ) );
    stimLengthLayout->addWidget( stimLengthEdit );
    TabPageLayout_2->addLayout( stimLengthLayout );

    CmEditLayout = new QHBoxLayout( 0, 0, 6, "CmEditLayout"); 

    CmLabel = new QLabel( TabPage_2, "CmLabel" );
    CmLabel->setMinimumSize( QSize( 120, 0 ) );
    CmLabel->setMaximumSize( QSize( 120, 32767 ) );
    QFont CmLabel_font(  CmLabel->font() );
    CmLabel->setFont( CmLabel_font ); 
    CmLabel->setAlignment( int( QLabel::AlignCenter ) );
    CmEditLayout->addWidget( CmLabel );

    CmEdit = new QLineEdit( TabPage_2, "CmEdit" );
    CmEdit->setMinimumSize( QSize( 0, 0 ) );
    CmEdit->setMaximumSize( QSize( 50, 32767 ) );
    QFont CmEdit_font(  CmEdit->font() );
    CmEdit->setFont( CmEdit_font ); 
    CmEdit->setAlignment( int( QLineEdit::AlignHCenter ) );
    CmEditLayout->addWidget( CmEdit );
    TabPageLayout_2->addLayout( CmEditLayout );

    LJPEditLayout = new QHBoxLayout( 0, 0, 6, "LJPEditLayout"); 

    LJPLabel = new QLabel( TabPage_2, "LJPLabel" );
    LJPLabel->setMinimumSize( QSize( 120, 0 ) );
    LJPLabel->setMaximumSize( QSize( 120, 32767 ) );
    QFont LJPLabel_font(  LJPLabel->font() );
    LJPLabel->setFont( LJPLabel_font ); 
    LJPLabel->setAlignment( int( QLabel::AlignCenter ) );
    LJPEditLayout->addWidget( LJPLabel );

    LJPEdit = new QLineEdit( TabPage_2, "LJPEdit" );
    LJPEdit->setMinimumSize( QSize( 0, 0 ) );
    LJPEdit->setMaximumSize( QSize( 50, 32767 ) );
    QFont LJPEdit_font(  LJPEdit->font() );
    LJPEdit->setFont( LJPEdit_font ); 
    LJPEdit->setAlignment( int( QLineEdit::AlignHCenter ) );
    LJPEditLayout->addWidget( LJPEdit );
    TabPageLayout_2->addLayout( LJPEditLayout );
    tabBox->insertTab( TabPage_2, QString::fromLatin1("") );

    tab = new QWidget( tabBox, "tab" );
    tabLayout = new QVBoxLayout( tab, 11, 0, "tabLayout"); 

    numTrialLayout = new QHBoxLayout( 0, 0, 6, "numTrialLayout"); 

    numTrialLabel = new QLabel( tab, "numTrialLabel" );
    numTrialLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, numTrialLabel->sizePolicy().hasHeightForWidth() ) );
    numTrialLabel->setMinimumSize( QSize( 130, 0 ) );
    numTrialLabel->setMaximumSize( QSize( 130, 32767 ) );
    QFont numTrialLabel_font(  numTrialLabel->font() );
    numTrialLabel->setFont( numTrialLabel_font ); 
    numTrialLabel->setAlignment( int( QLabel::AlignCenter ) );
    numTrialLayout->addWidget( numTrialLabel );

    numTrialEdit = new QLineEdit( tab, "numTrialEdit" );
    numTrialEdit->setMinimumSize( QSize( 50, 0 ) );
    numTrialEdit->setMaximumSize( QSize( 50, 32767 ) );
    numTrialLayout->addWidget( numTrialEdit );
    tabLayout->addLayout( numTrialLayout );

    intervalTimeLayout = new QHBoxLayout( 0, 0, 6, "intervalTimeLayout"); 

    intervalTimeLabel = new QLabel( tab, "intervalTimeLabel" );
    intervalTimeLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, intervalTimeLabel->sizePolicy().hasHeightForWidth() ) );
    intervalTimeLabel->setMinimumSize( QSize( 130, 0 ) );
    intervalTimeLabel->setMaximumSize( QSize( 130, 32767 ) );
    intervalTimeLabel->setAlignment( int( QLabel::AlignCenter ) );
    intervalTimeLayout->addWidget( intervalTimeLabel );

    intervalTimeEdit = new QLineEdit( tab, "intervalTimeEdit" );
    intervalTimeEdit->setMinimumSize( QSize( 50, 0 ) );
    intervalTimeEdit->setMaximumSize( QSize( 50, 32767 ) );
    intervalTimeLayout->addWidget( intervalTimeEdit );
    tabLayout->addLayout( intervalTimeLayout );

    recordDataLayout = new QHBoxLayout( 0, 0, 6, "recordDataLayout"); 
    spacer1a = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    recordDataLayout->addItem( spacer1a );

    recordDataCheckBox = new QCheckBox( tab, "recordDataCheckBox" );
    QFont recordDataCheckBox_font(  recordDataCheckBox->font() );
    recordDataCheckBox->setFont( recordDataCheckBox_font ); 
    recordDataCheckBox->setTristate( FALSE );
    recordDataLayout->addWidget( recordDataCheckBox );
    spacer2a = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    recordDataLayout->addItem( spacer2a );
    tabLayout->addLayout( recordDataLayout );

    modelGroup = new QGroupBox( tab, "modelGroup" );
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
    tabLayout->addWidget( modelGroup );
    tabBox->insertTab( tab, QString::fromLatin1("") );

    TabPage_3 = new QWidget( tabBox, "TabPage_3" );
    TabPageLayout_3 = new QVBoxLayout( TabPage_3, 11, 6, "TabPageLayout_3"); 

    pEditLayout1 = new QGridLayout( 0, 1, 1, 0, 6, "pEditLayout1"); 

    deleteStepButton = new QPushButton( TabPage_3, "deleteStepButton" );
    deleteStepButton->setMinimumSize( QSize( 120, 0 ) );
    deleteStepButton->setMaximumSize( QSize( 120, 32767 ) );
    QFont deleteStepButton_font(  deleteStepButton->font() );
    deleteStepButton->setFont( deleteStepButton_font ); 

    pEditLayout1->addWidget( deleteStepButton, 1, 0 );

    loadProtocolButton = new QPushButton( TabPage_3, "loadProtocolButton" );
    loadProtocolButton->setMinimumSize( QSize( 120, 0 ) );
    loadProtocolButton->setMaximumSize( QSize( 120, 32767 ) );
    QFont loadProtocolButton_font(  loadProtocolButton->font() );
    loadProtocolButton->setFont( loadProtocolButton_font ); 

    pEditLayout1->addWidget( loadProtocolButton, 1, 1 );

    saveProtocolButton = new QPushButton( TabPage_3, "saveProtocolButton" );
    saveProtocolButton->setMinimumSize( QSize( 120, 0 ) );
    saveProtocolButton->setMaximumSize( QSize( 120, 32767 ) );
    QFont saveProtocolButton_font(  saveProtocolButton->font() );
    saveProtocolButton->setFont( saveProtocolButton_font ); 

    pEditLayout1->addWidget( saveProtocolButton, 0, 1 );

    addStepButton = new QPushButton( TabPage_3, "addStepButton" );
    addStepButton->setMinimumSize( QSize( 120, 0 ) );
    addStepButton->setMaximumSize( QSize( 120, 32767 ) );
    QFont addStepButton_font(  addStepButton->font() );
    addStepButton->setFont( addStepButton_font ); 

    pEditLayout1->addWidget( addStepButton, 0, 0 );
    TabPageLayout_3->addLayout( pEditLayout1 );

    pEditLayout2 = new QHBoxLayout( 0, 0, 6, "pEditLayout2"); 
    spacer1 = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    pEditLayout2->addItem( spacer1 );

    clearProtocolButton = new QPushButton( TabPage_3, "clearProtocolButton" );
    clearProtocolButton->setMinimumSize( QSize( 120, 0 ) );
    clearProtocolButton->setMaximumSize( QSize( 120, 32767 ) );
    QFont clearProtocolButton_font(  clearProtocolButton->font() );
    clearProtocolButton->setFont( clearProtocolButton_font ); 
    pEditLayout2->addWidget( clearProtocolButton );
    spacer2 = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    pEditLayout2->addItem( spacer2 );
    TabPageLayout_3->addLayout( pEditLayout2 );
    tabBox->insertTab( TabPage_3, QString::fromLatin1("") );

    tab_2 = new QWidget( tabBox, "tab_2" );
    tabLayout_2 = new QVBoxLayout( tab_2, 11, 0, "tabLayout_2"); 

    APDRepolLayout = new QHBoxLayout( 0, 0, 6, "APDRepolLayout"); 

    APDRepolLabel = new QLabel( tab_2, "APDRepolLabel" );
    APDRepolLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, APDRepolLabel->sizePolicy().hasHeightForWidth() ) );
    APDRepolLabel->setMinimumSize( QSize( 150, 0 ) );
    APDRepolLabel->setMaximumSize( QSize( 150, 32767 ) );
    QFont APDRepolLabel_font(  APDRepolLabel->font() );
    APDRepolLabel->setFont( APDRepolLabel_font ); 
    APDRepolLabel->setAlignment( int( QLabel::AlignCenter ) );
    APDRepolLayout->addWidget( APDRepolLabel );

    APDRepolEdit = new QLineEdit( tab_2, "APDRepolEdit" );
    APDRepolEdit->setMinimumSize( QSize( 50, 0 ) );
    APDRepolEdit->setMaximumSize( QSize( 50, 32767 ) );
    QFont APDRepolEdit_font(  APDRepolEdit->font() );
    APDRepolEdit->setFont( APDRepolEdit_font ); 
    APDRepolLayout->addWidget( APDRepolEdit );
    tabLayout_2->addLayout( APDRepolLayout );

    minAPDLayout = new QHBoxLayout( 0, 0, 6, "minAPDLayout"); 

    minAPDLabel = new QLabel( tab_2, "minAPDLabel" );
    minAPDLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, minAPDLabel->sizePolicy().hasHeightForWidth() ) );
    minAPDLabel->setMinimumSize( QSize( 150, 0 ) );
    minAPDLabel->setMaximumSize( QSize( 150, 32767 ) );
    QFont minAPDLabel_font(  minAPDLabel->font() );
    minAPDLabel->setFont( minAPDLabel_font ); 
    minAPDLabel->setAlignment( int( QLabel::AlignCenter ) );
    minAPDLayout->addWidget( minAPDLabel );

    minAPDEdit = new QLineEdit( tab_2, "minAPDEdit" );
    minAPDEdit->setMinimumSize( QSize( 50, 0 ) );
    minAPDEdit->setMaximumSize( QSize( 50, 32767 ) );
    QFont minAPDEdit_font(  minAPDEdit->font() );
    minAPDEdit->setFont( minAPDEdit_font ); 
    minAPDLayout->addWidget( minAPDEdit );
    tabLayout_2->addLayout( minAPDLayout );

    APDRepolLayout_2 = new QHBoxLayout( 0, 0, 6, "APDRepolLayout_2"); 

    stimWindowLabel = new QLabel( tab_2, "stimWindowLabel" );
    stimWindowLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, stimWindowLabel->sizePolicy().hasHeightForWidth() ) );
    stimWindowLabel->setMinimumSize( QSize( 150, 0 ) );
    stimWindowLabel->setMaximumSize( QSize( 150, 32767 ) );
    QFont stimWindowLabel_font(  stimWindowLabel->font() );
    stimWindowLabel->setFont( stimWindowLabel_font ); 
    stimWindowLabel->setAlignment( int( QLabel::AlignCenter ) );
    APDRepolLayout_2->addWidget( stimWindowLabel );

    stimWindowEdit = new QLineEdit( tab_2, "stimWindowEdit" );
    stimWindowEdit->setMinimumSize( QSize( 50, 0 ) );
    stimWindowEdit->setMaximumSize( QSize( 50, 32767 ) );
    QFont stimWindowEdit_font(  stimWindowEdit->font() );
    stimWindowEdit->setFont( stimWindowEdit_font ); 
    APDRepolLayout_2->addWidget( stimWindowEdit );
    tabLayout_2->addLayout( APDRepolLayout_2 );
    tabBox->insertTab( tab_2, QString::fromLatin1("") );
    IScale_DynClampUILayout->addWidget( tabBox );

    protocolEditorListBox = new QListBox( this, "protocolEditorListBox" );
    protocolEditorListBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, protocolEditorListBox->sizePolicy().hasHeightForWidth() ) );
    protocolEditorListBox->setMinimumSize( QSize( 150, 0 ) );
    protocolEditorListBox->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 221, 223, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 238, 239, 241) );
    cg.setColor( QColorGroup::Dark, QColor( 110, 111, 114) );
    cg.setColor( QColorGroup::Mid, QColor( 147, 149, 152) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 221, 223, 228) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 0, 0, 128) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, black );
    cg.setColor( QColorGroup::LinkVisited, black );
    pal.setActive( cg );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 221, 223, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 254, 254, 255) );
    cg.setColor( QColorGroup::Dark, QColor( 110, 111, 114) );
    cg.setColor( QColorGroup::Mid, QColor( 147, 149, 152) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 221, 223, 228) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 0, 0, 128) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 238) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 82, 24, 139) );
    pal.setInactive( cg );
    cg.setColor( QColorGroup::Foreground, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Button, QColor( 221, 223, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 254, 254, 255) );
    cg.setColor( QColorGroup::Dark, QColor( 110, 111, 114) );
    cg.setColor( QColorGroup::Mid, QColor( 147, 149, 152) );
    cg.setColor( QColorGroup::Text, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 221, 223, 228) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 0, 0, 128) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 238) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 82, 24, 139) );
    pal.setDisabled( cg );
    protocolEditorListBox->setPalette( pal );
    QFont protocolEditorListBox_font(  protocolEditorListBox->font() );
    protocolEditorListBox->setFont( protocolEditorListBox_font ); 
    protocolEditorListBox->setVScrollBarMode( QListBox::AlwaysOn );
    protocolEditorListBox->setHScrollBarMode( QListBox::Auto );
    IScale_DynClampUILayout->addWidget( protocolEditorListBox );
    languageChange();
    resize( QSize(296, 371).expandedTo(minimumSizeHint()) );
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
    protocolButtonGroup->setTitle( QString::null );
    staticPacingButton->setText( tr( "Pace" ) );
    resetButton->setText( tr( "Reset" ) );
    startProtocolButton->setText( tr( "Protocol" ) );
    thresholdButton->setText( tr( "Threshold" ) );
    timeLabel->setText( tr( "Time (ms)" ) );
    beatNumLabel->setText( tr( "Beat Number" ) );
    voltageLabel->setText( tr( "Voltage (mV)" ) );
    APDLabel->setText( tr( "APD (ms)" ) );
    tabBox->changeTab( TabPage, tr( "States" ) );
    BCLLabel->setText( tr( "BCL (ms)" ) );
    stimMagLabel->setText( tr( "Stim Mag (nA)" ) );
    stimLengthLabel->setText( tr( "Stim Length (ms)" ) );
    CmLabel->setText( tr( "Cm (pF)" ) );
    LJPLabel->setText( tr( "LJP (mV)" ) );
    tabBox->changeTab( TabPage_2, tr( "Stim" ) );
    numTrialLabel->setText( tr( "Number of Trials" ) );
    intervalTimeLabel->setText( tr( "Interval Time (ms)" ) );
    recordDataCheckBox->setText( tr( "Record Data" ) );
    modelGroup->setTitle( tr( "Dynamic Clamp Model" ) );
    tabBox->changeTab( tab, tr( "Protocol" ) );
    deleteStepButton->setText( tr( "Delete Step" ) );
    loadProtocolButton->setText( tr( "Load Protocol" ) );
    saveProtocolButton->setText( tr( "Save Protocol" ) );
    addStepButton->setText( tr( "Add Step" ) );
    clearProtocolButton->setText( tr( "Clear Protocol" ) );
    tabBox->changeTab( TabPage_3, tr( "P. Edit" ) );
    APDRepolLabel->setText( tr( "APD Repolarization %" ) );
    minAPDLabel->setText( tr( "Minimum APD (ms)" ) );
    stimWindowLabel->setText( tr( "Stim Window (ms)" ) );
    tabBox->changeTab( tab_2, tr( "APD" ) );
}

