/****************************************************************************
** Form implementation generated from reading ui file 'IS_DC_AddStepDialogUI.ui'
**
** Created: Mon Jul 29 15:55:34 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

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

    setWindowTitle( "AddStepDialog" );
    AddStepDialogLayout = new QVBoxLayout( this, 11, 6, "AddStepDialogLayout"); 

    stepComboBox = new QComboBox( FALSE, this, "stepComboBox" );
    AddStepDialogLayout->addWidget( stepComboBox );

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 

    BCLLabel = new QLabel( this, "BCLLabel" );
    BCLLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout1->addWidget( BCLLabel );

    BCLEdit = new QLineEdit( this, "BCLEdit" );
    layout1->addWidget( BCLEdit );
    AddStepDialogLayout->addLayout( layout1 );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    numBeatsLabel = new QLabel( this, "numBeatsLabel" );
    numBeatsLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout2->addWidget( numBeatsLabel );

    numBeatsEdit = new QLineEdit( this, "numBeatsEdit" );
    layout2->addWidget( numBeatsEdit );
    AddStepDialogLayout->addLayout( layout2 );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    currentToScaleLabel = new QLabel( this, "currentToScaleLabel" );
    currentToScaleLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout3->addWidget( currentToScaleLabel );

    currentToScaleEdit = new QLineEdit( this, "currentToScaleEdit" );
    layout3->addWidget( currentToScaleEdit );
    AddStepDialogLayout->addLayout( layout3 );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    scalingPercentageLabel = new QLabel( this, "scalingPercentageLabel" );
    scalingPercentageLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout4->addWidget( scalingPercentageLabel );

    scalingPercentageEdit = new QLineEdit( this, "scalingPercentageEdit" );
    layout4->addWidget( scalingPercentageEdit );
    AddStepDialogLayout->addLayout( layout4 );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    waitTimeLabel = new QLabel( this, "waitTimeLabel" );
    waitTimeLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout5->addWidget( waitTimeLabel );

    waitTimeEdit = new QLineEdit( this, "waitTimeEdit" );
    layout5->addWidget( waitTimeEdit );
    AddStepDialogLayout->addLayout( layout5 );

    layout6 = new QHBoxLayout( 0, 0, 6, "layout6"); 

    modelLabel = new QLabel( this, "modelLabel" );
    modelLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout6->addWidget( modelLabel );

    modelComboBox = new QComboBox( FALSE, this, "modelComboBox" );
    layout6->addWidget( modelComboBox );
    AddStepDialogLayout->addLayout( layout6 );

    buttonGroup = new QButtonGroup( this, "buttonGroup" );
    buttonGroupLayout = new QHBoxLayout( buttonGroup->layout() );
    buttonGroupLayout->setAlignment( Qt::AlignTop );

    addStepButton = new QPushButton( buttonGroup, "addStepButton" );
    buttonGroupLayout->addWidget( addStepButton );

    exitButton = new QPushButton( buttonGroup, "exitButton" );
    buttonGroupLayout->addWidget( exitButton );
    AddStepDialogLayout->addWidget( buttonGroup );
    languageChange();
}

/*
 *  Destroys the object and frees any allocated resources
 */
AddStepDialog::~AddStepDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void AddStepDialog::languageChange()
{
    setCaption( tr( "Add Step to Protocol" ) );
    stepComboBox->clear();
    stepComboBox->insertItem( tr( "Static Pacing" ) );
    stepComboBox->insertItem( tr( "Current Scaling" ) );
    stepComboBox->insertItem( tr( "Wait" ) );
    stepComboBox->insertItem( tr( "Model: Start" ) );
    stepComboBox->insertItem( tr( "Model: Stop" ) );
    stepComboBox->insertItem( tr( "Model: Reset" ) );
    stepComboBox->insertItem( tr( "Model: Change" ) );
    BCLLabel->setText( tr( "Basic Cycle Length (ms)" ) );
    numBeatsLabel->setText( tr( "Number of Beats" ) );
    currentToScaleLabel->setText( tr( "Current to Scale" ) );
    QToolTip::add( currentToScaleEdit, tr( "INa IKr IKs ICaL IK1 ICaT INaK INCX" ) );
    scalingPercentageLabel->setText( tr( "Scaling Percentage" ) );
    waitTimeLabel->setText( tr( "Wait Time (ms)" ) );
    modelLabel->setText( tr( "Model" ) );
    modelComboBox->clear();
    modelComboBox->insertItem( tr( "Livzhitz Rudy 2009" ) );
    modelComboBox->insertItem( tr( "Faber Rudy 2000" ) );
    buttonGroup->setTitle( QString::null );
    addStepButton->setText( tr( "Add Step" ) );
    exitButton->setText( tr( "Exit" ) );
}

