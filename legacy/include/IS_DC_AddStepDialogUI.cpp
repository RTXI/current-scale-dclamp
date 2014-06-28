/****************************************************************************
** Form implementation generated from reading ui file 'IS_DC_AddStepDialogUI.ui'
**
** Created: Wed Mar 7 20:56:21 2012
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "IS_DC_AddStepDialogUI.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

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

    buttonGroup = new QButtonGroup( this, "buttonGroup" );
    buttonGroup->setColumnLayout(0, Qt::Vertical );
    buttonGroup->layout()->setSpacing( 6 );
    buttonGroup->layout()->setMargin( 11 );
    buttonGroupLayout = new QHBoxLayout( buttonGroup->layout() );
    buttonGroupLayout->setAlignment( Qt::AlignTop );

    addStepButton = new QPushButton( buttonGroup, "addStepButton" );
    QFont addStepButton_font(  addStepButton->font() );
    addStepButton_font.setBold( TRUE );
    addStepButton->setFont( addStepButton_font ); 
    buttonGroupLayout->addWidget( addStepButton );

    exitButton = new QPushButton( buttonGroup, "exitButton" );
    QFont exitButton_font(  exitButton->font() );
    exitButton_font.setBold( TRUE );
    exitButton->setFont( exitButton_font ); 
    buttonGroupLayout->addWidget( exitButton );
    AddStepDialogLayout->addWidget( buttonGroup );
    languageChange();
    resize( QSize(280, 249).expandedTo(minimumSizeHint()) );
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
    BCLLabel->setText( tr( "Basic Cycle Length (ms)" ) );
    numBeatsLabel->setText( tr( "Number of Beats" ) );
    currentToScaleLabel->setText( tr( "Current to Scale" ) );
    scalingPercentageLabel->setText( tr( "Scaling Percentage" ) );
    waitTimeLabel->setText( tr( "Wait Time (ms)" ) );
    buttonGroup->setTitle( QString::null );
    addStepButton->setText( tr( "Add Step" ) );
    exitButton->setText( tr( "Exit" ) );
}

