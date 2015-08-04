#include "IS_DC_AddStepDialogUI.h"

#include <QtWidgets>

/*
 *  Constructs a AddStepDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
AddStepDialog::AddStepDialog( QWidget* parent /*, const char* name, bool modal, WFlags fl*/ ) : QDialog( parent /*, name, modal, fl*/ ) {

	 QWidget::setAttribute(Qt::WA_DeleteOnClose);

    setWindowTitle( "Add Step to Protocol" );
//    AddStepDialogLayout = new QVBoxLayout( this );
    AddStepDialogLayout = new QGridLayout(this);

    stepComboBox = new QComboBox( this );
    stepComboBox->clear();
    stepComboBox->insertItem( 0, tr( "Static Pacing" ) );
    stepComboBox->insertItem( 1, tr( "Current Scaling" ) );
    stepComboBox->insertItem( 2, tr( "Wait" ) );
    stepComboBox->insertItem( 3, tr( "Model: Start" ) );
    stepComboBox->insertItem( 4, tr( "Model: Stop" ) );
    stepComboBox->insertItem( 5, tr( "Model: Reset" ) );
    stepComboBox->insertItem( 6, tr( "Model: Change" ) );
//    AddStepDialogLayout->addWidget( stepComboBox );
    AddStepDialogLayout->addWidget( stepComboBox, 0, 0, 1, 2 );

//    layout1 = new QHBoxLayout; 
    BCLLabel = new QLabel( "Basic Cycle Length (ms)", this );
//    BCLLabel->setAlignment( Qt::AlignCenter );
    AddStepDialogLayout->addWidget( BCLLabel, 1, 0);
//    layout1->addWidget( BCLLabel );
//    layout1->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    BCLEdit = new QLineEdit( "", this );
	 BCLEdit->setValidator( new QDoubleValidator(0, 1000, 2, BCLEdit) );
    AddStepDialogLayout->addWidget( BCLEdit, 1, 1);
//    layout1->addWidget( BCLEdit );
//    AddStepDialogLayout->addLayout( layout1 );

//    layout2 = new QHBoxLayout;
    numBeatsLabel = new QLabel( "Number of Beats", this );
//    numBeatsLabel->setAlignment( Qt::AlignCenter );
    AddStepDialogLayout->addWidget( numBeatsLabel, 2, 0);
//    layout2->addWidget( numBeatsLabel );
    numBeatsEdit = new QLineEdit( "", this );
	 numBeatsEdit->setValidator( new QIntValidator(0, 10000, numBeatsEdit) );
    AddStepDialogLayout->addWidget( numBeatsEdit, 2, 1);
//    layout2->addWidget( numBeatsEdit );
//    AddStepDialogLayout->addLayout( layout2 );

//    layout3 = new QHBoxLayout; 
    currentToScaleLabel = new QLabel( "Current to Scale", this );
//    currentToScaleLabel->setAlignment( Qt::AlignCenter );
//    layout3->addWidget( currentToScaleLabel );
    AddStepDialogLayout->addWidget( currentToScaleLabel, 3, 0);
    currentToScaleEdit = new QLineEdit( "", this );
	 QRegExp currentToScaleRegExp("(INa|IKr|ICaL|IK1|IKs|ICaT|INaK|INCX)");
	 currentToScaleEdit->setValidator( new QRegExpValidator(currentToScaleRegExp, currentToScaleEdit) );
    currentToScaleEdit->setToolTip( tr( "Choices: INa, IKr, IKs, ICaL, IK1, ICaT, INaK, or INCX" ) );
    AddStepDialogLayout->addWidget( currentToScaleEdit, 3, 1);
//    layout3->addWidget( currentToScaleEdit );
//    AddStepDialogLayout->addLayout( layout3 );

//    layout4 = new QHBoxLayout;  
    scalingPercentageLabel = new QLabel( "Scaling Percentage", this );
//    scalingPercentageLabel->setAlignment( Qt::AlignCenter );
    AddStepDialogLayout->addWidget( scalingPercentageLabel, 4, 0);
//    layout4->addWidget( scalingPercentageLabel );
    scalingPercentageEdit = new QLineEdit( "", this );
	 scalingPercentageEdit->setValidator( new QDoubleValidator(-1000, 1000, 2, scalingPercentageEdit) );
    AddStepDialogLayout->addWidget( scalingPercentageEdit, 4, 1);
//    layout4->addWidget( scalingPercentageEdit );
//    AddStepDialogLayout->addLayout( layout4 );

//    layout5 = new QHBoxLayout;  
    waitTimeLabel = new QLabel( "Wait Time (ms)", this );
//    waitTimeLabel->setAlignment( Qt::AlignCenter );
    AddStepDialogLayout->addWidget( waitTimeLabel, 5, 0);
//    layout5->addWidget( waitTimeLabel );
    waitTimeEdit = new QLineEdit( "", this );
	 waitTimeEdit->setValidator( new QDoubleValidator(0, 10000, 2, waitTimeEdit) );
    AddStepDialogLayout->addWidget( waitTimeEdit, 5, 1);
//    layout5->addWidget( waitTimeEdit );
//    AddStepDialogLayout->addLayout( layout5 );

//    layout6 = new QHBoxLayout; 
    modelLabel = new QLabel( "Model", this );
//    modelLabel->setAlignment( Qt::AlignCenter );
    AddStepDialogLayout->addWidget( modelLabel, 6, 0);
//    layout6->addWidget( modelLabel );
    modelComboBox = new QComboBox( this );
    modelComboBox->clear();
    modelComboBox->insertItem( 0, tr( "Livzhitz Rudy 2009" ) );
    modelComboBox->insertItem( 1, tr( "Faber Rudy 2000" ) );
    AddStepDialogLayout->addWidget( modelComboBox, 6, 1);
//    layout6->addWidget( modelComboBox );
//    AddStepDialogLayout->addLayout( layout6 );

    buttonGroup = new QButtonGroup( this );
//    buttonGroupLayout = new QHBoxLayout( buttonGroup );
//    buttonGroupLayout->setAlignment( Qt::AlignTop );
	 buttonGroupBox = new QGroupBox( this );
    buttonGroupBoxLayout = new QHBoxLayout( buttonGroupBox );
    buttonGroupBoxLayout->setAlignment( Qt::AlignTop );

    addStepButton = new QPushButton( "Add Step", buttonGroupBox );
//    addStepButton = new QPushButton( "addStepButton", buttonGroup );
    buttonGroupBoxLayout->addWidget( addStepButton );
	 buttonGroup->addButton(addStepButton);
//    buttonGroupLayout->addWidget( addStepButton );

    exitButton = new QPushButton( "Exit", buttonGroupBox );
    buttonGroupBoxLayout->addWidget( exitButton );
	 buttonGroup->addButton(exitButton);
//    AddStepDialogLayout->addWidget( buttonGroupBox );
    AddStepDialogLayout->addWidget( buttonGroupBox, 7, 0, 1, 2 );
//    exitButton = new QPushButton( "exitButton", buttonGroup );
//    buttonGroupLayout->addWidget( exitButton );
//    AddStepDialogLayout->addWidget( buttonGroup );
}

/*
 *  Destroys the object and frees any allocated resources
 */
AddStepDialog::~AddStepDialog() { } // no need to delete child widgets, Qt does it all for us
