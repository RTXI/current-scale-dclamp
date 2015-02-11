#include "IS_DC_MainWindowUI.h"

#include <QtGui>
#include <iostream>

/*
 *  Constructs a IScale_DynClampUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
IScale_DynClampUI::IScale_DynClampUI( QWidget* parent ) : QWidget( parent ) {

std::cout<<"IScale_DynClampUI constructor called"<<std::endl;
	 QWidget::setAttribute(Qt::WA_DeleteOnClose);
	 
    IScale_DynClampUILayout = new QVBoxLayout( parent );
	 setLayout(IScale_DynClampUILayout);

    protocolButtonGroup = new QButtonGroup( parent );
//    protocolButtonGroup->setAlignment( Qt::AlignCenter );
//    protocolButtonGroup->setColumnLayout(0, Qt::Vertical );
//    protocolButtonGroup->layout()->setSpacing( 6 );
//    protocolButtonGroup->layout()->setMargin( 11 );
//    protocolButtonGroupLayout = new QGridLayout( protocolButtonGroup->layout() );
//    protocolButtonGroupLayout->setAlignment( Qt::AlignTop );
//    spacer1b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
//    protocolButtonGroupLayout->addItem( spacer1b, 0, 4 );
//    spacer2b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
//    protocolButtonGroupLayout->addItem( spacer2b, 1, 4 );

    protocolGroup = new QGroupBox;
    protocolGroup->setAlignment( Qt::AlignCenter );
    protocolGroupLayout = new QGridLayout( protocolGroup );
	 protocolGroup->setLayout(protocolGroupLayout);
    protocolGroupLayout->setAlignment( Qt::AlignTop );
    spacer1b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolGroupLayout->addItem( spacer1b, 0, 4 );
    spacer2b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolGroupLayout->addItem( spacer2b, 1, 4 );

    staticPacingButton = new QPushButton( "staticPacingButton", protocolGroup );
	 protocolButtonGroup->addButton(staticPacingButton);
    staticPacingButton->setCheckable( TRUE );

    protocolGroupLayout->addWidget( staticPacingButton, 0, 3 );

    resetButton = new QPushButton( "resetButton", protocolGroup );
	 protocolButtonGroup->addButton(resetButton);
    resetButton->setCheckable( FALSE );

    protocolGroupLayout->addWidget( resetButton, 1, 3 );
    spacer3b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolGroupLayout->addItem( spacer3b, 0, 2 );
    spacer4b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolGroupLayout->addItem( spacer4b, 1, 2 );

    startProtocolButton = new QPushButton( "startProtocolButton", protocolGroup );
	 protocolButtonGroup->addButton(startProtocolButton);
    startProtocolButton->setCheckable( TRUE );

    protocolGroupLayout->addWidget( startProtocolButton, 1, 1 );

    thresholdButton = new QPushButton( "thresholdButton", protocolGroup );
	 protocolButtonGroup->addButton(thresholdButton);
    thresholdButton->setCheckable( TRUE );

    protocolGroupLayout->addWidget( thresholdButton, 0, 1 );
    spacer5b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolGroupLayout->addItem( spacer5b, 1, 0 );
    spacer6b = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    protocolGroupLayout->addItem( spacer6b, 0, 0 );
    IScale_DynClampUILayout->addWidget( protocolGroup );

    tabBox = new QTabWidget( parent );
//    tabBox->setFocusPolicy( QTabWidget::NoFocus );
    tabBox->setTabPosition( QTabWidget::North );
    tabBox->setTabShape( QTabWidget::Rounded );

    TabPage = new QWidget( tabBox );
    TabPageLayout = new QGridLayout( TabPage );
	 TabPage->setLayout(TabPageLayout);

    timeLabel = new QLabel( "timeLabel", TabPage );
    TabPageLayout->addWidget( timeLabel, 0, 0 );
    timeEdit = new QLineEdit( "timeEdit", TabPage );
    timeEdit->setAlignment( Qt::AlignHCenter );
    timeEdit->setReadOnly( TRUE );
    TabPageLayout->addWidget( timeEdit, 0, 1 );

    beatNumLabel = new QLabel( "beatNumLabel", TabPage );
    TabPageLayout->addWidget( beatNumLabel, 1, 0 );
    beatNumEdit = new QLineEdit( "beatNumEdit", TabPage );
    beatNumEdit->setAlignment( Qt::AlignHCenter );
    beatNumEdit->setReadOnly( TRUE );
    TabPageLayout->addWidget( beatNumEdit, 1, 1 );

    voltageLabel = new QLabel( "voltageLabel", TabPage );
    TabPageLayout->addWidget( voltageLabel, 2, 0 );
    voltageEdit = new QLineEdit( "voltageEdit", TabPage );
    voltageEdit->setAlignment( Qt::AlignHCenter );
    voltageEdit->setReadOnly( TRUE );
    TabPageLayout->addWidget( voltageEdit, 2, 1 );

    APDLabel = new QLabel( "APDLabel", TabPage );
    TabPageLayout->addWidget( APDLabel, 3, 0 );
    APDEdit = new QLineEdit( "APDEdit", TabPage );
    APDEdit->setAlignment( Qt::AlignHCenter );
    APDEdit->setReadOnly( TRUE );
    TabPageLayout->addWidget( APDEdit, 3, 1 );
    tabBox->addTab( TabPage, QString::fromLatin1("") );

    TabPage_2 = new QWidget( tabBox );
    TabPageLayout_2 = new QGridLayout( TabPage_2 );
	 TabPage_2->setLayout(TabPageLayout_2);

    BCLLabel = new QLabel(  "BCLLabel", TabPage_2 );
    TabPageLayout_2->addWidget( BCLLabel, 0, 0 );
    BCLEdit = new QLineEdit( "BCLEdit", TabPage_2 );
    BCLEdit->setAlignment( Qt::AlignHCenter );
    TabPageLayout_2->addWidget( BCLEdit, 0, 1 );

    stimMagLabel = new QLabel( "stimMagLabel", TabPage_2 );
    TabPageLayout_2->addWidget( stimMagLabel, 1, 0 );
    stimMagEdit = new QLineEdit( "stimMagEdit", TabPage_2 );
    stimMagEdit->setAlignment( Qt::AlignHCenter );
    TabPageLayout_2->addWidget( stimMagEdit, 1, 1 );

    stimLengthLabel = new QLabel( "stimLengthLabel", TabPage_2 );
    TabPageLayout_2->addWidget( stimLengthLabel, 2, 0 );
    stimLengthEdit = new QLineEdit( "stimLengthEdit", TabPage_2 );
    stimLengthEdit->setAlignment( Qt::AlignHCenter );
    TabPageLayout_2->addWidget( stimLengthEdit, 2, 1 );

    CmLabel = new QLabel( "CmLabel", TabPage_2 );
    TabPageLayout_2->addWidget( CmLabel, 3, 0 );
    CmEdit = new QLineEdit( "CmEdit", TabPage_2 );
    CmEdit->setAlignment( Qt::AlignHCenter );
    TabPageLayout_2->addWidget( CmEdit, 3, 1 );

    LJPLabel = new QLabel( "LJPLabel", TabPage_2 );
    TabPageLayout_2->addWidget( LJPLabel, 4, 0 );
    LJPEdit = new QLineEdit( "LJPEdit", TabPage_2 );
    LJPEdit->setAlignment( Qt::AlignHCenter );
    TabPageLayout_2->addWidget( LJPEdit, 4, 1 );
    tabBox->addTab( TabPage_2, QString::fromLatin1("") );

	 // Next tab
    tab = new QWidget( tabBox /*, "tab"*/ );
    tabLayout = new QGridLayout( tab );
	 tab->setLayout(tabLayout);

    numTrialLabel = new QLabel( "numTrialLabel", tab );
    tabLayout->addWidget( numTrialLabel, 0, 0 );
    numTrialEdit = new QLineEdit( "numTrialEdit", tab );
    numTrialEdit->setAlignment( Qt::AlignHCenter );
    tabLayout->addWidget( numTrialEdit, 0, 1 );

    intervalTimeLabel = new QLabel( "intervalTimeLabel", tab );
    tabLayout->addWidget( intervalTimeLabel, 1, 0 );
    intervalTimeEdit = new QLineEdit( "intervalTimeEdit", tab );
    intervalTimeEdit->setAlignment( Qt::AlignHCenter );
    tabLayout->addWidget( intervalTimeEdit, 1, 1 );

    recordDataLayout = new QHBoxLayout;
    spacer1a = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    recordDataLayout->addItem( spacer1a );

    recordDataCheckBox = new QCheckBox( "recordDataCheckBox", tab );
    recordDataCheckBox->setTristate( FALSE );
    recordDataLayout->addWidget( recordDataCheckBox );
    spacer2a = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    recordDataLayout->addItem( spacer2a );
    tabLayout->addLayout( recordDataLayout, 2, 0, 1, 2 );

    modelGroup = new QGroupBox( "modelGroup", tab );
    modelGroup->setAlignment( Qt::AlignCenter );
//    modelGroup->setColumnLayout( 0, Qt::Vertical );
//    modelGroup->layout()->setSpacing( 6 );
//    modelGroup->layout()->setMargin( 11 );
    modelGroupLayout = new QVBoxLayout( modelGroup );
	 modelGroup->setLayout(modelGroupLayout);
    modelGroupLayout->setAlignment( Qt::AlignTop );

    modelComboBox = new QComboBox( modelGroup );
    modelGroupLayout->addWidget( modelComboBox );
    tabLayout->addWidget( modelGroup, 3, 0, 1, 2 );
    tabBox->addTab( tab, QString::fromLatin1("") );

    TabPage_3 = new QWidget( tabBox );
    TabPageLayout_3 = new QVBoxLayout( TabPage_3 );
	 TabPage_3->setLayout(TabPageLayout_3);

    pEditLayout1 = new QGridLayout;
    deleteStepButton = new QPushButton( "deleteStepButton", TabPage_3 );
    pEditLayout1->addWidget( deleteStepButton, 1, 0 );
    loadProtocolButton = new QPushButton( "loadProtocolButton", TabPage_3 );
    pEditLayout1->addWidget( loadProtocolButton, 1, 1 );
    saveProtocolButton = new QPushButton( "saveProtocolButton", TabPage_3 );
    pEditLayout1->addWidget( saveProtocolButton, 0, 1 );
    addStepButton = new QPushButton( "addStepButton", TabPage_3 );
    pEditLayout1->addWidget( addStepButton, 0, 0 );
    TabPageLayout_3->addLayout( pEditLayout1 );

    pEditLayout2 = new QHBoxLayout;
    spacer1 = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    pEditLayout2->addItem( spacer1 );
    clearProtocolButton = new QPushButton( "clearProtocolButton", TabPage_3 );
    pEditLayout2->addWidget( clearProtocolButton );
    spacer2 = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    pEditLayout2->addItem( spacer2 );
    TabPageLayout_3->addLayout( pEditLayout2 );
    tabBox->addTab( TabPage_3, QString::fromLatin1("") );

    tab_2 = new QWidget( tabBox );
    tabLayout_2 = new QGridLayout( tab_2 );
	 tab_2->setLayout(tabLayout_2);

    APDRepolLabel = new QLabel( "APDRepolLabel", tab_2 );
    tabLayout_2->addWidget( APDRepolLabel, 0, 1, 1, 2);
    APDRepolEdit = new QLineEdit( "APDRepolEdit", tab_2 );
    APDRepolEdit->setAlignment( Qt::AlignCenter );
    tabLayout_2->addWidget( APDRepolEdit, 0, 3, 1, 1);

    minAPDLabel = new QLabel( "minAPDLabel", tab_2 );
    tabLayout_2->addWidget( minAPDLabel, 1, 1, 1, 2);

    minAPDEdit = new QLineEdit( "minAPDEdit", tab_2 );
    minAPDEdit->setAlignment( Qt::AlignCenter );
    tabLayout_2->addWidget( minAPDEdit, 1, 3, 1, 1);

    stimWindowLabel = new QLabel( "stimWindowLabel", tab_2 );
    tabLayout_2->addWidget( stimWindowLabel, 2, 1, 1, 2);

    stimWindowEdit = new QLineEdit( "stimWindowEdit", tab_2 );
    stimWindowEdit->setAlignment( Qt::AlignCenter );
    tabLayout_2->addWidget( stimWindowEdit, 2, 3, 1, 1);

    tabBox->addTab( tab_2, QString::fromLatin1("") );
    IScale_DynClampUILayout->addWidget( tabBox );

    protocolEditorListBox = new QListWidget( parent );
//    protocolEditorListBox->setVScrollBarMode( QListWidget::AlwaysOn );
//    protocolEditorListBox->setHScrollBarMode( QListWidget::Auto );
    IScale_DynClampUILayout->addWidget( protocolEditorListBox );
    languageChange();
std::cout<<"IScale_DynClampUI constructor returned"<<std::endl;
}

/*
 *  Destroys the object and frees any allocated resources
 */
IScale_DynClampUI::~IScale_DynClampUI() { } // no need to delete child widgets, Qt does it all for us

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void IScale_DynClampUI::languageChange() {

    setWindowTitle( tr( "Current Scaling Dynamic Clamp" ) );
    staticPacingButton->setText( tr( "Pace" ) );
    resetButton->setText( tr( "Reset" ) );
    startProtocolButton->setText( tr( "Protocol" ) );
    thresholdButton->setText( tr( "Threshold" ) );
    timeLabel->setText( tr( "Time (ms)" ) );
    beatNumLabel->setText( tr( "Beat Number" ) );
    voltageLabel->setText( tr( "Voltage (mV)" ) );
    APDLabel->setText( tr( "APD (ms)" ) );
    tabBox->setTabText( tabBox->indexOf(TabPage), tr( "States" ) );
    BCLLabel->setText( tr( "BCL (ms)" ) );
    stimMagLabel->setText( tr( "Stim Mag (nA)" ) );
    stimLengthLabel->setText( tr( "Stim Length (ms)" ) );
    CmLabel->setText( tr( "Cm (pF)" ) );
    LJPLabel->setText( tr( "LJP (mV)" ) );
    tabBox->setTabText( tabBox->indexOf(TabPage_2), tr( "Stim" ) );
    numTrialLabel->setText( tr( "Number of Trials" ) );
    intervalTimeLabel->setText( tr( "Interval Time (ms)" ) );
    recordDataCheckBox->setText( tr( "Record Data" ) );
    modelGroup->setTitle( tr( "Dynamic Clamp Model" ) );
    tabBox->setTabText( tabBox->indexOf(tab), tr( "Protocol" ) );
    deleteStepButton->setText( tr( "Delete Step" ) );
    loadProtocolButton->setText( tr( "Load Protocol" ) );
    saveProtocolButton->setText( tr( "Save Protocol" ) );
    addStepButton->setText( tr( "Add Step" ) );
    clearProtocolButton->setText( tr( "Clear Protocol" ) );
    tabBox->setTabText( tabBox->indexOf(TabPage_3), tr( "P. Edit" ) );
    APDRepolLabel->setText( tr( "APD Repol (%)" ) );
    minAPDLabel->setText( tr( "Min APD (ms)" ) );
    stimWindowLabel->setText( tr( "Stim Window (ms)" ) );
    tabBox->setTabText( tabBox->indexOf(tab_2), tr( "APD" ) );
}
