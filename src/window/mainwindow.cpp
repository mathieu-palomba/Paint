#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLabel>
#include <QFileDialog>
#include <QSpinBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

const int MainWindow::WINDOW_WIDTH = 800;
const int MainWindow::WINDOW_HEIGHT = 800;
const string MainWindow::QUIT_SHORTCUT = "ctrl+q";
const string MainWindow::ABOUT_SHORTCUT = "ctrl+a";
const int MainWindow::MAX_SIZE = 10;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _initScreen();
    _createActions();
    _createMenus();
    _createToolbars();
    _createDockWidget();
    _connectActions();
    _connectSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_initScreen()
{

    // Set the window size
    this->resize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));

    // Create central widget and vertical layout
    QWidget* wid = new QWidget();
    QVBoxLayout* mainLayout= new QVBoxLayout();

    // Create a new painter
    _myPainter = new MyPainter(this);
    _myPainter->setContextMenuPolicy(Qt::CustomContextMenu);

    // Add painter into vertical layout
    mainLayout->addWidget(_myPainter);

    // Add layout into the central widget
    wid->setLayout(mainLayout);

    // Set central widget into the MainWindow
    this->setCentralWidget(wid);                                        // To fill out the window with the painter
    this->setWindowIcon(QIcon(PAINT_ICON_NAME_IN_QRC));                 // To set the window icon in the title bar
}

void MainWindow::_createMenus()
{
    // Add menu into the menu bar
    QMenuBar* menubar = menuBar();

    // Add File menu into the menu bar
    _fileMenu = menubar->addMenu(tr("&File"));

    // Add Style menu into the menu bar
    _styleMenu = menubar->addMenu(tr("&Style"));

    // Add Shape sub menu menu into the Style menu
    _shapeMenu = _styleMenu->addMenu(QIcon(":/change_shape_icon"), tr("&Shapes"));

    // Add Pen style sub menu menu into the Style menu
    _penStyleMenu = _styleMenu->addMenu(QIcon(":/pen_style_icon"), tr("&Pen style"));

    // Add separator into the Style menu
    _styleMenu->addSeparator();

    // Add Color sub menu into the Style menu
    _colorMenu = _styleMenu->addMenu(QIcon(":/change_color_icon"), tr("&Color"));

    // Add Help menu into the menu bar
    _helpMenu = menubar->addMenu(tr("&Help"));
}

void MainWindow::_createToolbars()
{
    ui->ToolBar->addAction(_newAction);
    ui->ToolBar->addAction(_openAction);
    ui->ToolBar->addAction(_saveAction);
    ui->ToolBar->addSeparator();
    ui->ToolBar->addAction(_quitAction);
}

void MainWindow::_createDockWidget()
{
    _toolBar = addToolBar(tr("&Tools toolbar"));

    _toolBar->addWidget(new QLabel(tr("<b>Shapes</b>")));
    _toolBar->addSeparator();
    _toolBar->addAction(_drawFreeHandAction);
    _toolBar->addAction(_drawLineAction);
    _toolBar->addAction(_drawRectangleAction);
    _toolBar->addAction(_drawCircleAction);
    _toolBar->addAction(_drawPolygonAction);
    _toolBar->addAction(_drawTextAction);
    _toolBar->addAction(_rubberAction);

    _toolBar->addWidget(new QLabel(tr("<b>Line styles</b>")));
    _toolBar->addSeparator();
    _toolBar->addAction(_solidLineAction);
    _toolBar->addAction(_dotLineAction);
    _toolBar->addAction(_dashLineAction);
    _toolBar->addAction(_dashDotLineAction);
    _toolBar->addAction(_dashDotDotLineAction);

    _toolBar->addWidget(new QLabel(tr("<b>Colors</b>")));
    _toolBar->addSeparator();
    _toolBar->addAction(_chooseShapeColorAction);
    _toolBar->addAction(_chooseFillColorAction);

    _toolBar->addWidget(new QLabel(tr("<b>Size</b>")));
    _toolBar->addSeparator();
    _sizeWidget = new QSpinBox();
    _sizeWidget->setMinimum(1);
    _sizeWidget->setMaximum(MAX_SIZE);
    _toolBar->addWidget(_sizeWidget);

    //_toolBar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );      // To display icon with title

     this->addToolBar(Qt::LeftToolBarArea, _toolBar);
}

void MainWindow::_createActions()
{
    // Style menu --> Shape sub menu
    QString drawFreeHandAction;
    drawFreeHandAction.append("&");
    drawFreeHandAction.append(FREE_HAND);

    QString drawLineAction;
    drawLineAction.append("&");
    drawLineAction.append(LINE_SHAPE);

    QString drawRectangleAction;
    drawRectangleAction.append("&");
    drawRectangleAction.append(RECTANGLE_SHAPE);

    QString drawCircleAction;
    drawCircleAction.append("&");
    drawCircleAction.append(CIRCLE_SHAPE);

    QString drawPolygonAction;
    drawPolygonAction.append("&");
    drawPolygonAction.append(POLYGON_SHAPE);

    QString drawTextAction;
    drawTextAction.append("&");
    drawTextAction.append(TEXT_SHAPE);

    QString rubberAction;
    rubberAction.append("&");
    rubberAction.append(RUBBER_SHAPE);

    // Style menu --> Color sub menu
    QString chooseShapeColorAction;
    chooseShapeColorAction.append("&");
    chooseShapeColorAction.append(CHOOSE_SHAPE_COLOR_MENU_NAME);

    QString chooseFillColorAction;
    chooseFillColorAction.append("&");
    chooseFillColorAction.append(CHOOSE_FILL_COLOR_MENU_NAME);

    // Style menu --> Pen style sub menu
    QString solidLineAction;
    solidLineAction.append("&");
    solidLineAction.append(SOLID_LINE_PEN_STYLE);

    QString dashLineAction;
    dashLineAction.append("&");
    dashLineAction.append(DASH_LINE_PEN_STYLE);

    QString dotLineAction;
    dotLineAction.append("&");
    dotLineAction.append(DOT_LINE_PEN_STYLE);

    QString dashDotLineAction;
    dashDotLineAction.append("&");
    dashDotLineAction.append(DASH_DOT_LINE_PEN_STYLE);

    QString dashDotDotLineAction;
    dashDotDotLineAction.append("&");
    dashDotDotLineAction.append(DASH_DOT_DOT_LINE_PEN_STYLE);

    // Create action for File menu
    _newAction = new QAction(QIcon(":/new_icon"), tr("&New"), this);
    _newAction->setShortcut(QKeySequence(QKeySequence::New));

    _openAction = new QAction(QIcon(":/open_icon"), tr("&Open"), this);
    _openAction->setShortcut(QKeySequence(QKeySequence::Open));

    _saveAction = new QAction(QIcon(":/save_icon"), tr("&Save"), this);
    _saveAction->setShortcut(QKeySequence(QKeySequence::Save));                  // Define the SAVE_SHORTCUT as shortcut for the "Save QAction"

    _quitAction = new QAction(QIcon(":/exit_icon"), tr("&Quit"), this);
    _quitAction->setShortcut(QKeySequence(QKeySequence(QUIT_SHORTCUT.c_str())));                  // Define the EXIT_SHORTCUT as shortcut for the "Exit QAction"

    // Create action for File menu --> Shape sub menu
    _drawFreeHandAction = new QAction(QIcon(":/free_hand_icon"), drawFreeHandAction, this);
    _drawFreeHandAction->setData(FREE_HAND);                                 // setData to identify what QAction generating an event
    _drawFreeHandAction->setCheckable(true);

    _drawLineAction = new QAction(QIcon(":/line_icon"), drawLineAction, this);
    _drawLineAction->setData(LINE_SHAPE);                                   // setData to identify what QAction generating an event
    _drawLineAction->setCheckable(true);

    _drawRectangleAction = new QAction(QIcon(":/rectangle_icon"), drawRectangleAction, this);
    _drawRectangleAction->setData(RECTANGLE_SHAPE);                         // setData to identify what QAction generating an event
    _drawRectangleAction->setCheckable(true);

    _drawCircleAction = new QAction(QIcon(":/circle_icon"), drawCircleAction, this);
    _drawCircleAction->setData(CIRCLE_SHAPE);                               // setData to identify what QAction generating an event
    _drawCircleAction->setCheckable(true);

    _drawPolygonAction = new QAction(QIcon(":/polygon_icon"), drawPolygonAction, this);
    _drawPolygonAction->setData(POLYGON_SHAPE);                             // setData to identify what QAction generating an event
    _drawPolygonAction->setCheckable(true);

    _drawTextAction = new QAction(QIcon(":/text_icon"), drawTextAction, this);
    _drawTextAction->setData(TEXT_SHAPE);                                   // setData to identify what QAction generating an event
    _drawTextAction->setCheckable(true);

    _rubberAction = new QAction(QIcon(":/rubber_icon"), rubberAction, this);
    _rubberAction->setData(RUBBER_SHAPE);
    _rubberAction->setCheckable(true);

    // Create action for File menu --> Color sub menu
    _chooseShapeColorAction = new QAction(QIcon(":/pen_color_icon"), chooseShapeColorAction, this);
    _chooseShapeColorAction->setData(CHOOSE_SHAPE_COLOR_MENU_NAME);                 // setData to identify what QAction generating an event

    _chooseFillColorAction = new QAction(QIcon(":/fill_out_color_icon"), chooseFillColorAction, this);
    _chooseFillColorAction->setData(CHOOSE_FILL_COLOR_MENU_NAME);                  // setData to identify what QAction generating an event

    // Create action for File menu --> Pen style sub menu
    _solidLineAction = new QAction(QIcon(":/solid_line_icon"), solidLineAction, this);
    _solidLineAction->setData(SOLID_LINE_PEN_STYLE);                 // setData to identify what QAction generating an event
    _solidLineAction->setCheckable(true);

    _dashLineAction = new QAction(QIcon(":/dash_line_icon"), dashLineAction, this);
    _dashLineAction->setData(DASH_LINE_PEN_STYLE);                 // setData to identify what QAction generating an event
    _dashLineAction->setCheckable(true);

    _dotLineAction = new QAction(QIcon(":/dot_line_icon"), dotLineAction, this);
    _dotLineAction->setData(DOT_LINE_PEN_STYLE);                 // setData to identify what QAction generating an event
    _dotLineAction->setCheckable(true);

    _dashDotLineAction = new QAction(QIcon(":/dash_dot_line_icon"), dashDotLineAction, this);
    _dashDotLineAction->setData(DASH_DOT_LINE_PEN_STYLE);                 // setData to identify what QAction generating an event
    _dashDotLineAction->setCheckable(true);

    _dashDotDotLineAction = new QAction(QIcon(":/dash_dot_dot_line_icon"), dashDotDotLineAction, this);
    _dashDotDotLineAction->setData(DASH_DOT_DOT_LINE_PEN_STYLE);                 // setData to identify what QAction generating an event
    _dashDotDotLineAction->setCheckable(true);

    // Create action for Help menu
    _aboutAction = new QAction(QIcon(":/about"), tr("&About"), this);
    _aboutAction->setShortcut(QKeySequence(ABOUT_SHORTCUT.c_str()));                // Define the ABOUT_SHORTCUT as shortcut for the "About QAction"


    // Create action group for radiobox into the Style menu --> Shape sub menu
    _shapeActionGroup = new QActionGroup(this);
    _shapeActionGroup->addAction(_drawFreeHandAction);
    _shapeActionGroup->addAction(_drawLineAction);
    _shapeActionGroup->addAction(_drawRectangleAction);
    _shapeActionGroup->addAction(_drawCircleAction);
    _shapeActionGroup->addAction(_drawPolygonAction);
    _shapeActionGroup->addAction(_drawTextAction);
    _shapeActionGroup->addAction(_rubberAction);
    _drawFreeHandAction->setChecked(true);

    // Create action group for radiobox into the Style menu --> Pen style sub menu
    _penStyleActionGroup = new QActionGroup(this);
    _penStyleActionGroup->addAction(_solidLineAction);
    _penStyleActionGroup->addAction(_dashLineAction);
    _penStyleActionGroup->addAction(_dotLineAction);
    _penStyleActionGroup->addAction(_dashDotLineAction);
    _penStyleActionGroup->addAction(_dashDotDotLineAction);
    _solidLineAction->setChecked(true);

}

void MainWindow::_connectActions()
{
    // Connect File actions with her menu
    _fileMenu->addAction(_newAction);
    _fileMenu->addAction(_openAction);
    _fileMenu->addAction(_saveAction);
    _fileMenu->addSeparator();
    _fileMenu->addAction(_quitAction);

    // Connect Shape actions with her menu
    _shapeMenu->addAction(_drawFreeHandAction);
    _shapeMenu->addAction(_drawLineAction);
    _shapeMenu->addAction(_drawRectangleAction);
    _shapeMenu->addAction(_drawCircleAction);
    _shapeMenu->addAction(_drawPolygonAction);
    _shapeMenu->addAction(_drawTextAction);
    _shapeMenu->addAction(_rubberAction);

    // Connect Pen style actions with her menu
    _penStyleMenu->addAction(_solidLineAction);
    _penStyleMenu->addAction(_dashLineAction);
    _penStyleMenu->addAction(_dotLineAction);
    _penStyleMenu->addAction(_dashDotLineAction);
    _penStyleMenu->addAction(_dashDotDotLineAction);

    // Connect Color actions with her menu
    _colorMenu->addAction(_chooseShapeColorAction);
    _colorMenu->addAction(_chooseFillColorAction);

    // Connect About actions with her menu
    _helpMenu->addAction(_aboutAction);
}

void MainWindow::_connectSignals()
{
    // Link signals in relation with File menu with slots
    connect(_newAction, SIGNAL(triggered()), this, SLOT(newAction()));
    connect(_openAction, SIGNAL(triggered()), this, SLOT(openAction()));
    connect(_saveAction, SIGNAL(triggered()), this, SLOT(saveAction()));
    connect(_quitAction, SIGNAL(triggered()), this, SLOT(exitAction()));

    // Link signals in relation with Style menu with slots
    connect(_shapeMenu, SIGNAL(triggered(QAction*)), this, SLOT(drawShapeAction(QAction*)));
    connect(_colorMenu, SIGNAL(triggered(QAction*)), this, SLOT(chooseColorAction(QAction*)));
    connect(_penStyleMenu, SIGNAL(triggered(QAction*)), this, SLOT(changePenStyleAction(QAction*)));

    // Link signals in relation with Help menu with slots
    connect(_aboutAction, SIGNAL(triggered()), this, SLOT(aboutAction()));

    // Link signal to change the shape size
    connect(_sizeWidget, SIGNAL(valueChanged(int)), _myPainter, SLOT(sizeChange(int)));

    // To allow right clic on the painter
    connect(_myPainter, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
}

void MainWindow::drawShapeAction(QAction* action)
{
    QString shapeToDraw = action->data().toString();

    _myPainter->shapeToDrawChange(shapeToDraw);
}

void MainWindow::chooseColorAction(QAction* action)
{
   QColorDialog* colorChooser = new QColorDialog();
   colorChooser->setWindowIcon(QIcon(":/change_color_icon"));
   QColor color = QColorDialog::getColor(Qt::white, colorChooser, CHOOSE_COLOR_DIALOG_NAME, QColorDialog::DontUseNativeDialog);

   if(color.isValid())
   {
        QString submenuGenerateEvent = action->data().toString();
        //QString textColorName = color.name();
        //QMessageBox::information(this, "Text Color", "You selected " + textColorName);

        _myPainter->colorToApplyChange(submenuGenerateEvent, color);
   }
}

void MainWindow::changePenStyleAction(QAction *action)
{
    QString newPenStyle = action->data().toString();

    _myPainter->penStyleChange(newPenStyle);
}

void MainWindow::newAction()
{
    bool response = askUser(tr("New drawing"), tr("Are you sure to create a new drawing?"));

    if (response){
        qDebug("Yes was clicked");
        _myPainter->eraseScreen();
    }
    else{
        qDebug("Cancel was clicked");
    }
}

void MainWindow::openAction()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"), QDir::currentPath(), tr("PNG (*.png);;JPEG (*.jpg);;BMP (*.bmp)") );

    if(!filename.isEmpty())
    {
        QStringList filesName = filename.split(".");

        _myPainter->eraseScreen();
        _myPainter->getBuffer().load(filename, filesName.at(1).toStdString().c_str());
    }
}

void MainWindow::saveAction()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save as"), QDir::currentPath(), tr("PNG (*.png);;JPEG (*.jpg);;BMP (*.bmp)") );

    if(!filename.isEmpty())
    {
        QStringList filesName = filename.split(".");
        _myPainter->getBuffer().save(filename, filesName.at(1).toStdString().c_str());
        qDebug("%s", filename.toStdString().c_str());
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    exitAction(event);
}

void MainWindow::exitAction(QCloseEvent* event)
{
    bool response = askUser(tr("Paint"), tr("Do you really want to exit?"));

    if (response){
        qDebug("Yes was clicked");
        QApplication::quit();
    }
    else{
        qDebug("Cancel was clicked");
        if( event)
        {
            event->ignore();
        }
    }
}

bool MainWindow::askUser(QString title, QString question)
{
    int response = QMessageBox::question(this, title, question, QMessageBox::Yes|QMessageBox::No);

    if (response == QMessageBox::Yes){
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::aboutAction()
{
    QMessageBox msg(QMessageBox::Information, tr("Informations sur projet Paint"), tr("<strong>Projet Paint</strong><br><i>Année 2013-2014</i><br /><br><br />Développé par Kévin GEORGES et Mathieu PALOMBA<br><br />"), QMessageBox::Ok);
    QPixmap image = QPixmap(":/enib_logo");     // Permet de charger le logo qui sera dans la QMessageBox
    //image = image.scaled(QSize(200,100));     // Permet de redimenssioner le logo enib pour faire rentrer le texte sur une ligne
    msg.setIconPixmap(image);
    msg.setWindowIcon(QIcon(":/about_icon"));
    msg.exec();
}

void MainWindow::showContextMenu(const QPoint& pos)
{
    // To place the menu
    QPoint globalPos = _myPainter->mapToGlobal(pos);

    QMenu myRightMenu;
    myRightMenu.addMenu(_shapeMenu);
    myRightMenu.addMenu(_penStyleMenu);
    myRightMenu.addSeparator();
    myRightMenu.addMenu(_colorMenu);

    // To execute the menu
    myRightMenu.exec(globalPos);
}
