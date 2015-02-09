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
AddStepDialog::AddStepDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "AddStepDialog" );
    setPaletteBackgroundColor( QColor( 221, 223, 228 ) );
    AddStepDialogLayout = new QVBoxLayout( this, 11, 6, "AddStepDialogLayout"); 

    stepComboBox = new QComboBox( FALSE, this, "stepComboBox" );
    QFont stepComboBox_font(  stepComboBox->font() );
    stepComboBox_font.setBold( TRUE );
    stepComboBox->setFont( stepComboBox_font ); 
    AddStepDialogLayout->addWidget( stepComboBox );

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 

    BCLLabel = new QLabel( this, "BCLLabel" );
    BCLLabel->setMinimumSize( QSize( 175, 0 ) );
    BCLLabel->setMaximumSize( QSize( 175, 32767 ) );
    QFont BCLLabel_font(  BCLLabel->font() );
    BCLLabel_font.setBold( TRUE );
    BCLLabel->setFont( BCLLabel_font ); 
    BCLLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout1->addWidget( BCLLabel );

    BCLEdit = new QLineEdit( this, "BCLEdit" );
    BCLEdit->setMinimumSize( QSize( 75, 0 ) );
    BCLEdit->setMaximumSize( QSize( 75, 32767 ) );
    layout1->addWidget( BCLEdit );
    AddStepDialogLayout->addLayout( layout1 );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    numBeatsLabel = new QLabel( this, "numBeatsLabel" );
    numBeatsLabel->setMinimumSize( QSize( 175, 0 ) );
    numBeatsLabel->setMaximumSize( QSize( 175, 32767 ) );
    QFont numBeatsLabel_font(  numBeatsLabel->font() );
    numBeatsLabel_font.setBold( TRUE );
    numBeatsLabel->setFont( numBeatsLabel_font ); 
    numBeatsLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout2->addWidget( numBeatsLabel );

    numBeatsEdit = new QLineEdit( this, "numBeatsEdit" );
    numBeatsEdit->setMinimumSize( QSize( 75, 0 ) );
    numBeatsEdit->setMaximumSize( QSize( 75, 32767 ) );
    layout2->addWidget( numBeatsEdit );
    AddStepDialogLayout->addLayout( layout2 );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    currentToScaleLabel = new QLabel( this, "currentToScaleLabel" );
    currentToScaleLabel->setMinimumSize( QSize( 175, 0 ) );
    currentToScaleLabel->setMaximumSize( QSize( 175, 32767 ) );
    QFont currentToScaleLabel_font(  currentToScaleLabel->font() );
    currentToScaleLabel_font.setBold( TRUE );
    currentToScaleLabel->setFont( currentToScaleLabel_font ); 
    currentToScaleLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout3->addWidget( currentToScaleLabel );

    currentToScaleEdit = new QLineEdit( this, "currentToScaleEdit" );
    currentToScaleEdit->setMinimumSize( QSize( 75, 0 ) );
    currentToScaleEdit->setMaximumSize( QSize( 75, 32767 ) );
    layout3->addWidget( currentToScaleEdit );
    AddStepDialogLayout->addLayout( layout3 );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    scalingPercentageLabel = new QLabel( this, "scalingPercentageLabel" );
    scalingPercentageLabel->setMinimumSize( QSize( 175, 0 ) );
    scalingPercentageLabel->setMaximumSize( QSize( 175, 32767 ) );
    QFont scalingPercentageLabel_font(  scalingPercentageLabel->font() );
    scalingPercentageLabel_font.setBold( TRUE );
    scalingPercentageLabel->setFont( scalingPercentageLabel_font ); 
    scalingPercentageLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout4->addWidget( scalingPercentageLabel );

    scalingPercentageEdit = new QLineEdit( this, "scalingPercentageEdit" );
    scalingPercentageEdit->setMinimumSize( QSize( 75, 0 ) );
    scalingPercentageEdit->setMaximumSize( QSize( 75, 32767 ) );
    layout4->addWidget( scalingPercentageEdit );
    AddStepDialogLayout->addLayout( layout4 );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    waitTimeLabel = new QLabel( this, "waitTimeLabel" );
    waitTimeLabel->setMinimumSize( QSize( 175, 0 ) );
    waitTimeLabel->setMaximumSize( QSize( 175, 32767 ) );
    QFont waitTimeLabel_font(  waitTimeLabel->font() );
    waitTimeLabel_font.setBold( TRUE );
    waitTimeLabel->setFont( waitTimeLabel_font ); 
    waitTimeLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout5->addWidget( waitTimeLabel );

    waitTimeEdit = new QLineEdit( this, "waitTimeEdit" );
    waitTimeEdit->setMinimumSize( QSize( 75, 0 ) );
    waitTimeEdit->setMaximumSize( QSize( 75, 32767 ) );
    layout5->addWidget( waitTimeEdit );
    AddStepDialogLayout->addLayout( layout5 );

    layout6 = new QHBoxLayout( 0, 0, 6, "layout6"); 

    modelLabel = new QLabel( this, "modelLabel" );
    modelLabel->setMinimumSize( QSize( 65, 0 ) );
    modelLabel->setMaximumSize( QSize( 65, 32767 ) );
    QFont modelLabel_font(  modelLabel->font() );
    modelLabel_font.setBold( TRUE );
    modelLabel->setFont( modelLabel_font ); 
    modelLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout6->addWidget( modelLabel );

    modelComboBox = new QComboBox( FALSE, this, "modelComboBox" );
    layout6->addWidget( modelComboBox );
    AddStepDialogLayout->addLayout( layout6 );

    buttonGroup = new QButtonGroup( this, "buttonGroup" );
    buttonGroup->setPaletteBackgroundColor( QColor( 221, 223, 228 ) );
    buttonGroup->setColumnLayout(0, Qt::Vertical );
    buttonGroup->layout()->setSpacing( 6 );
    buttonGroup->layout()->setMargin( 11 );
    buttonGroupLayout = new QHBoxLayout( buttonGroup->layout() );
    buttonGroupLayout->setAlignment( Qt::AlignTop );

    addStepButton = new QPushButton( buttonGroup, "addStepButton" );
    addStepButton->setPaletteBackgroundColor( QColor( 116, 144, 191 ) );
    QFont addStepButton_font(  addStepButton->font() );
    addStepButton_font.setBold( TRUE );
    addStepButton->setFont( addStepButton_font ); 
    buttonGroupLayout->addWidget( addStepButton );

    exitButton = new QPushButton( buttonGroup, "exitButton" );
    exitButton->setPaletteBackgroundColor( QColor( 116, 144, 191 ) );
    QFont exitButton_font(  exitButton->font() );
    exitButton_font.setBold( TRUE );
    exitButton->setFont( exitButton_font ); 
    buttonGroupLayout->addWidget( exitButton );
    AddStepDialogLayout->addWidget( buttonGroup );
    languageChange();
    resize( QSize(297, 279).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
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

