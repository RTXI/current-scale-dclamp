#include "IS_DC_MainWindowUI.h"

#include <QtGui>
#include <iostream>

/*
 *  Constructs a IScale_DynClampUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
IScale_DynClampUI::IScale_DynClampUI( QWidget* parent /*, const char* name, WFlags fl*/ ) : QWidget( parent /*, name, fl */) {

std::cout<<"IScale_DynClampUI constructor called"<<std::endl;
	 QWidget::setAttribute(Qt::WA_DeleteOnClose);

//    setWindowTitle( "IScale_DynClampUI" );
    IScale_DynClampUILayout = new QVBoxLayout( this ); /*, 11, 6, "IScale_DynClampUILayout"); */
	 setLayout(IScale_DynClampUILayout);

    protocolButtonGroup = new QButtonGroup( this );
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
//    protocolGroup->setColumnLayout(0, Qt::Vertical );
//    protocolGroup->layout()->setSpacing( 6 );
//    protocolGroup->layout()->setMargin( 11 );
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

    tabBox = new QTabWidget( this /*, "tabBox"*/ );
//    tabBox->setFocusPolicy( QTabWidget::NoFocus );
    tabBox->setTabPosition( QTabWidget::North );
    tabBox->setTabShape( QTabWidget::Rounded );

    TabPage = new QWidget( tabBox );
    TabPageLayout = new QVBoxLayout( TabPage );
	 TabPage->setLayout(TabPageLayout);

    timeLayout = new QHBoxLayout; 

    timeLabel = new QLabel( "timeLabel", TabPage );
    timeLabel->setAlignment( Qt::AlignCenter );
    timeLayout->addWidget( timeLabel );

    timeEdit = new QLineEdit( "timeEdit", TabPage );
    timeEdit->setAlignment( Qt::AlignHCenter );
    timeEdit->setReadOnly( TRUE );
    timeLayout->addWidget( timeEdit );
    TabPageLayout->addLayout( timeLayout );

    beatNumLayout = new QHBoxLayout; /*( 0, 0, 6, "beatNumLayout"); */

    beatNumLabel = new QLabel( "beatNumLabel", TabPage );
    beatNumLabel->setAlignment( Qt::AlignCenter );
    beatNumLayout->addWidget( beatNumLabel );

    beatNumEdit = new QLineEdit( "beatNumEdit", TabPage );
    beatNumEdit->setAlignment( Qt::AlignHCenter );
    beatNumEdit->setReadOnly( TRUE );
    beatNumLayout->addWidget( beatNumEdit );
    TabPageLayout->addLayout( beatNumLayout );

    voltageLayout = new QHBoxLayout; /*( 0, 0, 6, "voltageLayout"); */

    voltageLabel = new QLabel( "voltageLabel", TabPage );
    voltageLabel->setAlignment( Qt::AlignCenter );
    voltageLayout->addWidget( voltageLabel );

    voltageEdit = new QLineEdit( "voltageEdit", TabPage );
    voltageEdit->setAlignment( Qt::AlignHCenter );
    voltageEdit->setReadOnly( TRUE );
    voltageLayout->addWidget( voltageEdit );
    TabPageLayout->addLayout( voltageLayout );

    APDLayout = new QHBoxLayout; /*( 0, 0, 6, "APDLayout"); */

    APDLabel = new QLabel( "APDLabel", TabPage );
    APDLabel->setAlignment( Qt::AlignCenter );
    APDLayout->addWidget( APDLabel );

    APDEdit = new QLineEdit( "APDEdit", TabPage );
    APDEdit->setAlignment( Qt::AlignHCenter );
    APDEdit->setReadOnly( TRUE );
    APDLayout->addWidget( APDEdit );
    TabPageLayout->addLayout( APDLayout );
    tabBox->addTab( TabPage, QString::fromLatin1("") );
//    tabBox->insertTab( TabPage, QString::fromLatin1("") );

    TabPage_2 = new QWidget( tabBox );
    TabPageLayout_2 = new QVBoxLayout( TabPage_2 );
	 TabPage_2->setLayout(TabPageLayout_2);

    BCLLayout = new QHBoxLayout; /*( 0, 0, 6, "BCLLayout"); */

    BCLLabel = new QLabel(  "BCLLabel", TabPage_2 );
    BCLLabel->setAlignment( Qt::AlignCenter );
    BCLLayout->addWidget( BCLLabel );

    BCLEdit = new QLineEdit( "BCLEdit", TabPage_2 );
    BCLEdit->setAlignment( Qt::AlignHCenter );
    BCLLayout->addWidget( BCLEdit );
    TabPageLayout_2->addLayout( BCLLayout );

    stimMagLayout = new QHBoxLayout; /*( 0, 0, 6, "stimMagLayout"); */

    stimMagLabel = new QLabel( "stimMagLabel", TabPage_2 );
    stimMagLabel->setAlignment( Qt::AlignCenter );
    stimMagLayout->addWidget( stimMagLabel );

    stimMagEdit = new QLineEdit( "stimMagEdit", TabPage_2 );
    stimMagEdit->setAlignment( Qt::AlignHCenter );
    stimMagLayout->addWidget( stimMagEdit );
    TabPageLayout_2->addLayout( stimMagLayout );

    stimLengthLayout = new QHBoxLayout; /*( 0, 0, 6, "stimLengthLayout"); */

    stimLengthLabel = new QLabel( "stimLengthLabel", TabPage_2 );
    stimLengthLabel->setAlignment( Qt::AlignCenter );
    stimLengthLayout->addWidget( stimLengthLabel );

    stimLengthEdit = new QLineEdit( "stimLengthEdit", TabPage_2 );
    stimLengthEdit->setAlignment( Qt::AlignHCenter );
    stimLengthLayout->addWidget( stimLengthEdit );
    TabPageLayout_2->addLayout( stimLengthLayout );

    CmEditLayout = new QHBoxLayout; /*( 0, 0, 6, "CmEditLayout"); */

    CmLabel = new QLabel( "CmLabel", TabPage_2 );
    CmLabel->setAlignment( Qt::AlignCenter );
    CmEditLayout->addWidget( CmLabel );

    CmEdit = new QLineEdit( "CmEdit", TabPage_2 );
    CmEdit->setAlignment( Qt::AlignHCenter );
    CmEditLayout->addWidget( CmEdit );
    TabPageLayout_2->addLayout( CmEditLayout );

    LJPEditLayout = new QHBoxLayout;

    LJPLabel = new QLabel( "LJPLabel", TabPage_2 );
    LJPLabel->setAlignment( Qt::AlignCenter );
    LJPEditLayout->addWidget( LJPLabel );

    LJPEdit = new QLineEdit( "LJPEdit", TabPage_2 );
    LJPEdit->setAlignment( Qt::AlignHCenter );
    LJPEditLayout->addWidget( LJPEdit );
    TabPageLayout_2->addLayout( LJPEditLayout );
    tabBox->addTab( TabPage_2, QString::fromLatin1("") );

    tab = new QWidget( tabBox /*, "tab"*/ );
    tabLayout = new QVBoxLayout( tab );
	 tab->setLayout(tabLayout);

    numTrialLayout = new QHBoxLayout; /*( 0, 0, 6, "numTrialLayout"); */

    numTrialLabel = new QLabel( "numTrialLabel", tab );
    numTrialLabel->setAlignment( Qt::AlignCenter );
    numTrialLayout->addWidget( numTrialLabel );

    numTrialEdit = new QLineEdit( "numTrialEdit", tab );
    numTrialLayout->addWidget( numTrialEdit );
    tabLayout->addLayout( numTrialLayout );

    intervalTimeLayout = new QHBoxLayout; /*( 0, 0, 6, "intervalTimeLayout"); */

    intervalTimeLabel = new QLabel( "intervalTimeLabel", tab );
    intervalTimeLabel->setAlignment( Qt::AlignCenter );
    intervalTimeLayout->addWidget( intervalTimeLabel );

    intervalTimeEdit = new QLineEdit( "intervalTimeEdit", tab );
    intervalTimeLayout->addWidget( intervalTimeEdit );
    tabLayout->addLayout( intervalTimeLayout );

    recordDataLayout = new QHBoxLayout; /*( 0, 0, 6, "recordDataLayout"); */
    spacer1a = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    recordDataLayout->addItem( spacer1a );

    recordDataCheckBox = new QCheckBox( "recordDataCheckBox", tab );
    recordDataCheckBox->setTristate( FALSE );
    recordDataLayout->addWidget( recordDataCheckBox );
    spacer2a = new QSpacerItem( 0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    recordDataLayout->addItem( spacer2a );
    tabLayout->addLayout( recordDataLayout );

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
    tabLayout->addWidget( modelGroup );
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
    tabLayout_2 = new QVBoxLayout( tab_2 );
	 tab_2->setLayout(tabLayout_2);

    APDRepolLayout = new QHBoxLayout; /*( 0, 0, 6, "APDRepolLayout"); */

    APDRepolLabel = new QLabel( "APDRepolLabel", tab_2 );
    APDRepolLabel->setAlignment( Qt::AlignCenter );
    APDRepolLayout->addWidget( APDRepolLabel );

    APDRepolEdit = new QLineEdit( "APDRepolEdit", tab_2 );
    APDRepolLayout->addWidget( APDRepolEdit );
    tabLayout_2->addLayout( APDRepolLayout );

    minAPDLayout = new QHBoxLayout; /*( 0, 0, 6, "minAPDLayout"); */

    minAPDLabel = new QLabel( "minAPDLabel", tab_2 );
    minAPDLabel->setAlignment( Qt::AlignCenter );
    minAPDLayout->addWidget( minAPDLabel );

    minAPDEdit = new QLineEdit( "minAPDEdit", tab_2 );
    minAPDLayout->addWidget( minAPDEdit );
    tabLayout_2->addLayout( minAPDLayout );

    APDRepolLayout_2 = new QHBoxLayout; /*( 0, 0, 6, "APDRepolLayout_2"); */

    stimWindowLabel = new QLabel( "stimWindowLabel", tab_2 );
    stimWindowLabel->setAlignment( Qt::AlignCenter );
    APDRepolLayout_2->addWidget( stimWindowLabel );

    stimWindowEdit = new QLineEdit( "stimWindowEdit", tab_2 );
    APDRepolLayout_2->addWidget( stimWindowEdit );
    tabLayout_2->addLayout( APDRepolLayout_2 );
    tabBox->addTab( tab_2, QString::fromLatin1("") );
    IScale_DynClampUILayout->addWidget( tabBox );

    protocolEditorListBox = new QListWidget( this );
//    protocolEditorListBox->setVScrollBarMode( QListWidget::AlwaysOn );
//    protocolEditorListBox->setHScrollBarMode( QListWidget::Auto );
    IScale_DynClampUILayout->addWidget( protocolEditorListBox );
    languageChange();
//    resize( QSize(296, 371).expandedTo(minimumSizeHint()) );
std::cout<<"IScale_DynClampUI constructor returned"<<std::endl;
}

/*
 *  Destroys the object and frees any allocated resources
 */
IScale_DynClampUI::~IScale_DynClampUI() {
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void IScale_DynClampUI::languageChange() {


    setWindowTitle( tr( "Current Scaling Dynamic Clamp" ) );
//    protocolButtonGroup->setTitle( QString::null );
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
    APDRepolLabel->setText( tr( "APD Repolarization %" ) );
    minAPDLabel->setText( tr( "Minimum APD (ms)" ) );
    stimWindowLabel->setText( tr( "Stim Window (ms)" ) );
    tabBox->setTabText( tabBox->indexOf(tab_2), tr( "APD" ) );
}
