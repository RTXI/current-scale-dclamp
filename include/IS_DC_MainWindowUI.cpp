#include "IS_DC_MainWindowUI.h"

#include <QtWidgets>

/*
 *  Constructs a IScale_DynClampUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
IScale_DynClampUI::IScale_DynClampUI( QWidget* parent ) : QWidget( parent ) {

	 QWidget::setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle( tr( "Current Scaling Dynamic Clamp" ) );
	 
    IScale_DynClampUILayout = new QVBoxLayout( this );
//    IScale_DynClampUILayout = new QVBoxLayout( parent );
	 setLayout(IScale_DynClampUILayout);

//    protocolButtonGroup = new QButtonGroup( parent );
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

    protocolGroup = new QWidget;
//    protocolGroup = new QGroupBox;
//    protocolGroup->setAlignment( Qt::AlignCenter );
    protocolGroupLayout = new QGridLayout( protocolGroup );
	 protocolGroup->setLayout(protocolGroupLayout);
    protocolGroupLayout->setAlignment( Qt::AlignTop );

    staticPacingButton = new QPushButton( "Pace", protocolGroup );
//	 protocolButtonGroup->addButton(staticPacingButton);
    staticPacingButton->setCheckable( true );
    protocolGroupLayout->addWidget( staticPacingButton, 0, 3 );

    resetButton = new QPushButton( "Reset", protocolGroup );
//	 protocolButtonGroup->addButton(resetButton);
    resetButton->setCheckable( false );
    protocolGroupLayout->addWidget( resetButton, 1, 3 );

    startProtocolButton = new QPushButton( "Protocol", protocolGroup );
//	 protocolButtonGroup->addButton(startProtocolButton);
    startProtocolButton->setCheckable( true );
    protocolGroupLayout->addWidget( startProtocolButton, 1, 1 );

    thresholdButton = new QPushButton( "Threshold", protocolGroup );
//	 protocolButtonGroup->addButton(thresholdButton);
    thresholdButton->setCheckable( true );
    protocolGroupLayout->addWidget( thresholdButton, 0, 1 );
    
	 IScale_DynClampUILayout->addWidget( protocolGroup );

//    tabBox = new QTabWidget( parent );
    tabBox = new QTabWidget( this );
//    tabBox->setFocusPolicy( QTabWidget::NoFocus );
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

//    protocolEditorListBox = new QListWidget( parent );
    protocolEditorListBox = new QListWidget( this );
    protocolEditorListBox->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    protocolEditorListBox->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    IScale_DynClampUILayout->addWidget( protocolEditorListBox );
}

/*
 *  Destroys the object and frees any allocated resources
 */
IScale_DynClampUI::~IScale_DynClampUI() { } // no need to delete child widgets, Qt does it all for us
