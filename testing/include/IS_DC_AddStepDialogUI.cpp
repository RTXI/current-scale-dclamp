#include "IS_DC_AddStepDialogUI.h"

#include <QtGui>

/*
 *  Constructs a AddStepDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
AddStepDialog::AddStepDialog( QWidget* parent /*, const char* name, bool modal, WFlags fl*/ ) : QDialog( parent /*, name, modal, fl*/ ) {

	 QWidget::setAttribute(Qt::WA_DeleteOnClose);

//    setWindowTitle( "AddStepDialog" );
    AddStepDialogLayout = new QVBoxLayout( this );/*, 11, 6, "AddStepDialogLayout"); */

    stepComboBox = new QComboBox( this);
    AddStepDialogLayout->addWidget( stepComboBox );

    layout1 = new QHBoxLayout; 

    BCLLabel = new QLabel( "BCLLabel", this );
    BCLLabel->setAlignment( Qt::AlignCenter );
    layout1->addWidget( BCLLabel );

    BCLEdit = new QLineEdit( "BCLEdit", this );
    layout1->addWidget( BCLEdit );
    AddStepDialogLayout->addLayout( layout1 );

    layout2 = new QHBoxLayout; //( 0, 0, 6, "layout2"); 

    numBeatsLabel = new QLabel( "numBeatsLabel", this );
    numBeatsLabel->setAlignment( Qt::AlignCenter );
    layout2->addWidget( numBeatsLabel );

    numBeatsEdit = new QLineEdit( "numBeatsEdit", this );
    layout2->addWidget( numBeatsEdit );
    AddStepDialogLayout->addLayout( layout2 );

    layout3 = new QHBoxLayout; //( 0, 0, 6, "layout3"); 

    currentToScaleLabel = new QLabel( "currentToScaleLabel", this );
    currentToScaleLabel->setAlignment( Qt::AlignCenter );
    layout3->addWidget( currentToScaleLabel );

    currentToScaleEdit = new QLineEdit( "currentToScaleEdit", this );
    layout3->addWidget( currentToScaleEdit );
    AddStepDialogLayout->addLayout( layout3 );

    layout4 = new QHBoxLayout; //( 0, 0, 6, "layout4"); 

    scalingPercentageLabel = new QLabel( "scalingPercentageLabel", this );
    scalingPercentageLabel->setAlignment( Qt::AlignCenter );
    layout4->addWidget( scalingPercentageLabel );

    scalingPercentageEdit = new QLineEdit( "scalingPercentageEdit", this );
    layout4->addWidget( scalingPercentageEdit );
    AddStepDialogLayout->addLayout( layout4 );

    layout5 = new QHBoxLayout; //( 0, 0, 6, "layout5"); 

    waitTimeLabel = new QLabel( "waitTimeLabel", this );
    waitTimeLabel->setAlignment( Qt::AlignCenter );
    layout5->addWidget( waitTimeLabel );

    waitTimeEdit = new QLineEdit( "waitTimeEdit", this );
    layout5->addWidget( waitTimeEdit );
    AddStepDialogLayout->addLayout( layout5 );

    layout6 = new QHBoxLayout; //( 0, 0, 6, "layout6"); 

    modelLabel = new QLabel( "modelLabel", this );
    modelLabel->setAlignment( Qt::AlignCenter );
    layout6->addWidget( modelLabel );

    modelComboBox = new QComboBox( this );//( FALSE, this, "modelComboBox" );
    layout6->addWidget( modelComboBox );
    AddStepDialogLayout->addLayout( layout6 );

    buttonGroup = new QButtonGroup( this );
//    buttonGroupLayout = new QHBoxLayout( buttonGroup );
//    buttonGroupLayout->setAlignment( Qt::AlignTop );
	 buttonGroupBox = new QGroupBox( this );
    buttonGroupBoxLayout = new QHBoxLayout( buttonGroupBox );
    buttonGroupBoxLayout->setAlignment( Qt::AlignTop );

    addStepButton = new QPushButton( "addStepButton", buttonGroupBox );
//    addStepButton = new QPushButton( "addStepButton", buttonGroup );
    buttonGroupBoxLayout->addWidget( addStepButton );
	 buttonGroup->addButton(addStepButton);
//    buttonGroupLayout->addWidget( addStepButton );

    exitButton = new QPushButton( "exitButton", buttonGroupBox );
    buttonGroupBoxLayout->addWidget( exitButton );
	 buttonGroup->addButton(exitButton);
    AddStepDialogLayout->addWidget( buttonGroupBox );
//    exitButton = new QPushButton( "exitButton", buttonGroup );
//    buttonGroupLayout->addWidget( exitButton );
//    AddStepDialogLayout->addWidget( buttonGroup );
    languageChange();
}

/*
 *  Destroys the object and frees any allocated resources
 */
AddStepDialog::~AddStepDialog() {
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void AddStepDialog::languageChange() {

    setWindowTitle( tr( "Add Step to Protocol" ) );
    stepComboBox->clear();
    stepComboBox->insertItem( 0, tr( "Static Pacing" ) );
    stepComboBox->insertItem( 1, tr( "Current Scaling" ) );
    stepComboBox->insertItem( 2, tr( "Wait" ) );
    stepComboBox->insertItem( 3, tr( "Model: Start" ) );
    stepComboBox->insertItem( 4, tr( "Model: Stop" ) );
    stepComboBox->insertItem( 5, tr( "Model: Reset" ) );
    stepComboBox->insertItem( 6, tr( "Model: Change" ) );
    BCLLabel->setText( tr( "Basic Cycle Length (ms)" ) );
    numBeatsLabel->setText( tr( "Number of Beats" ) );
    currentToScaleLabel->setText( tr( "Current to Scale" ) );
    currentToScaleEdit->setToolTip( tr( "INa IKr IKs ICaL IK1 ICaT INaK INCX" ) );
    scalingPercentageLabel->setText( tr( "Scaling Percentage" ) );
    waitTimeLabel->setText( tr( "Wait Time (ms)" ) );
    modelLabel->setText( tr( "Model" ) );
    modelComboBox->clear();
    modelComboBox->insertItem( 0, tr( "Livzhitz Rudy 2009" ) );
    modelComboBox->insertItem( 1, tr( "Faber Rudy 2000" ) );
//    buttonGroup->setTitle( QString::null );
    addStepButton->setText( tr( "Add Step" ) );
    exitButton->setText( tr( "Exit" ) );
}
