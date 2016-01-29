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

	setWindowTitle( "Add Step to Protocol" );
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
	AddStepDialogLayout->addWidget( stepComboBox, 0, 0, 1, 2 );

	BCLLabel = new QLabel( "Basic Cycle Length (ms)", this );
	AddStepDialogLayout->addWidget( BCLLabel, 1, 0);
	BCLEdit = new QLineEdit( "", this );
//	QDoubleValidator* BCLValidator = new QDoubleValidator(0.00, 1000.00, 2, BCLEdit);
	BCLEdit->setValidator( new QDoubleValidator(0, 1000, 10, BCLEdit) );
//	BCLValidator->setNotation(QDoubleValidator::StandardNotation);
//	BCLEdit->setValidator( BCLValidator );
	AddStepDialogLayout->addWidget( BCLEdit, 1, 1);

	numBeatsLabel = new QLabel( "Number of Beats", this );
	AddStepDialogLayout->addWidget( numBeatsLabel, 2, 0);
	numBeatsEdit = new QLineEdit( "", this );
	numBeatsEdit->setValidator( new QIntValidator(0, 10000, numBeatsEdit) );
	AddStepDialogLayout->addWidget( numBeatsEdit, 2, 1);

	currentToScaleLabel = new QLabel( "Current to Scale", this );
	AddStepDialogLayout->addWidget( currentToScaleLabel, 3, 0);
	currentToScaleEdit = new QLineEdit( "", this );
	QRegExp currentToScaleRegExp("(INa|IKr|ICaL|IK1|IKs|ICaT|INaK|INCX|IpCA)");
	currentToScaleEdit->setValidator( new QRegExpValidator(currentToScaleRegExp, currentToScaleEdit) );
	currentToScaleEdit->setToolTip( tr( "Choices: INa, IKr, IKs, ICaL, IK1, ICaT, INaK, or INCX" ) );
	AddStepDialogLayout->addWidget( currentToScaleEdit, 3, 1);

	scalingPercentageLabel = new QLabel( "Scaling Percentage", this );
	AddStepDialogLayout->addWidget( scalingPercentageLabel, 4, 0);
	scalingPercentageEdit = new QLineEdit( "", this );
	scalingPercentageEdit->setValidator( new QDoubleValidator(-1000, 1000, 2, scalingPercentageEdit) );
	AddStepDialogLayout->addWidget( scalingPercentageEdit, 4, 1);

	waitTimeLabel = new QLabel( "Wait Time (ms)", this );
	AddStepDialogLayout->addWidget( waitTimeLabel, 5, 0);
	waitTimeEdit = new QLineEdit( "", this );
	waitTimeEdit->setValidator( new QDoubleValidator(0, 10000, 2, waitTimeEdit) );
	AddStepDialogLayout->addWidget( waitTimeEdit, 5, 1);

	modelLabel = new QLabel( "Model", this );
	AddStepDialogLayout->addWidget( modelLabel, 6, 0);
	modelComboBox = new QComboBox( this );
	modelComboBox->clear();
	modelComboBox->insertItem( 0, tr( "Livzhitz Rudy 2009" ) );
	modelComboBox->insertItem( 1, tr( "Faber Rudy 2000" ) );
	AddStepDialogLayout->addWidget( modelComboBox, 6, 1);

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
	AddStepDialogLayout->addWidget( buttonGroupBox, 7, 0, 1, 2 );
}

/*
 *  Destroys the object and frees any allocated resources
 */
AddStepDialog::~AddStepDialog() { } // no need to delete child widgets, Qt does it all for us
