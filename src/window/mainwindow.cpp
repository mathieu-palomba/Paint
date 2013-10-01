#include <QVBoxLayout>
#include <QColorDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLabel>
#include <QFileDialog>
#include <QSpinBox>
#include <QScrollArea>
#include "ui_mainwindow.h"
#include "window/mainwindow.h"

const int MainWindow::WINDOW_WIDTH = 900;
const int MainWindow::WINDOW_HEIGHT = 900;
const string MainWindow::SAVE_AS_SHORTCUT = "ctrl+shift+s";
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

    // Create central widget, vertical layout and scroll area
    QWidget* wid = new QWidget();
    QVBoxLayout* mainLayout= new QVBoxLayout();
    QScrollArea* scrollArea = new QScrollArea();

    // Create a new painter
    _myPainter = new MyPainter(this);
    _myPainter->setContextMenuPolicy(Qt::CustomContextMenu);

    // We add the painter object into the scroll area
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(_myPainter);

    // Add painter into vertical layout
    mainLayout->addWidget(scrollArea);

    // Add layout into the central widget
    wid->setLayout(mainLayout);

    // Set central widget into the MainWindow
    this->setCentralWidget(wid);                                // To fill out the window with the painter
    this->setWindowIcon(QIcon(":/paint_icon"));                 // To set the window icon in the title bar
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

    // Add Brush style sub menu menu into the Style menu
    _brushStyleMenu = _styleMenu->addMenu(QIcon(":/brush_icon"), tr("&Brush style"));

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
    _shapesToolBar = addToolBar(tr("&Shape toolbar"));

    _shapesToolBar->addWidget(new QLabel(tr("<b>Shapes</b>")));
    _shapesToolBar->addSeparator();
    _shapesToolBar->addAction(_drawFreeHandAction);
    _shapesToolBar->addAction(_drawLineAction);
    _shapesToolBar->addAction(_drawRectangleAction);
    _shapesToolBar->addAction(_drawCircleAction);
    _shapesToolBar->addAction(_drawPolygonAction);
    _shapesToolBar->addAction(_drawTextAction);
    _shapesToolBar->addAction(_rubberAction);

    _penToolBar = addToolBar(tr("&Pen toolbar"));
    _penToolBar->addWidget(new QLabel(tr("<b>Line styles</b>")));
    _penToolBar->addSeparator();
    _penToolBar->addAction(_solidLineAction);
    _penToolBar->addAction(_dotLineAction);
    _penToolBar->addAction(_dashLineAction);
    _penToolBar->addAction(_dashDotLineAction);
    _penToolBar->addAction(_dashDotDotLineAction);
    _penToolBar->addAction(_chooseShapeColorAction);

    _brushToolBar = addToolBar(tr("&Brush toolbar"));
    _brushToolBar->addWidget(new QLabel(tr("<b>Brush styles</b>")));
    _brushToolBar->addSeparator();
    _brushToolBar->addAction(_solidPatternAction);
    _brushToolBar->addAction(_horizontalPatternAction);
    _brushToolBar->addAction(_verticalPatternAction);
    _brushToolBar->addAction(_chooseFillColorAction);

    _otherToolBar = addToolBar(tr("&Others toolbar"));
    _otherToolBar->addWidget(new QLabel(tr("<b>Size</b>")));
    _otherToolBar->addSeparator();
    _sizeWidget = new QSpinBox();
    _sizeWidget->setMinimum(1);
    _sizeWidget->setMaximum(MAX_SIZE);
    _otherToolBar->addWidget(_sizeWidget);

    //_toolBar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );      // To display icon with title

    this->addToolBar(Qt::LeftToolBarArea, _shapesToolBar);
    this->addToolBar(Qt::LeftToolBarArea, _penToolBar);
    this->addToolBar(Qt::LeftToolBarArea, _brushToolBar);
    this->addToolBar(Qt::LeftToolBarArea, _otherToolBar);
}

void MainWindow::_createActions()
{
    // Create action for File menu
    _newAction = new QAction(QIcon(":/new_icon"), tr("&New"), this);
    _newAction->setShortcut(QKeySequence(QKeySequence::New));

    _openAction = new QAction(QIcon(":/open_icon"), tr("&Open"), this);
    _openAction->setShortcut(QKeySequence(QKeySequence::Open));

    _saveAction = new QAction(QIcon(":/save_icon"), tr("&Save"), this);
    _saveAction->setShortcut(QKeySequence(QKeySequence::Save));              // Define the SAVE_AS_SHORTCUT as shortcut for the "Save QAction"

    _saveAsAction = new QAction(QIcon(":/save_icon"), tr("&Save as"), this);
    _saveAsAction->setShortcut(QKeySequence(SAVE_AS_SHORTCUT.c_str()));      // Define the SAVE_AS_SHORTCUT as shortcut for the "Save As QAction"

    _quitAction = new QAction(QIcon(":/exit_icon"), tr("&Quit"), this);
    _quitAction->setShortcut(QKeySequence(QUIT_SHORTCUT.c_str()));           // Define the EXIT_SHORTCUT as shortcut for the "Exit QAction"


    // Create action for Style menu --> Shape sub menu
    _drawFreeHandAction = new QAction(QIcon(":/free_hand_icon"), tr("&Free hand"), this);
    _drawFreeHandAction->setData(ShapeFactory::freeHand);                           // setData to identify what QAction generating an event
    _drawFreeHandAction->setCheckable(true);

    _drawLineAction = new QAction(QIcon(":/line_icon"), tr("&Line"), this);
    _drawLineAction->setData(ShapeFactory::line);                                   // setData to identify what QAction generating an event
    _drawLineAction->setCheckable(true);

    _drawRectangleAction = new QAction(QIcon(":/rectangle_icon"), tr("&Rectangle"), this);
    _drawRectangleAction->setData(ShapeFactory::rectangle);                         // setData to identify what QAction generating an event
    _drawRectangleAction->setCheckable(true);

    _drawCircleAction = new QAction(QIcon(":/circle_icon"), tr("&Circle"), this);
    _drawCircleAction->setData(ShapeFactory::circle);                               // setData to identify what QAction generating an event
    _drawCircleAction->setCheckable(true);

    _drawPolygonAction = new QAction(QIcon(":/polygon_icon"), tr("&Polygon"), this);
    _drawPolygonAction->setData(ShapeFactory::polygon);                             // setData to identify what QAction generating an event
    _drawPolygonAction->setCheckable(true);

    _drawTextAction = new QAction(QIcon(":/text_icon"), tr("&Text"), this);
    _drawTextAction->setData(ShapeFactory::text);                                   // setData to identify what QAction generating an event
    _drawTextAction->setCheckable(true);

    _rubberAction = new QAction(QIcon(":/rubber_icon"), tr("&Rubber"), this);
    _rubberAction->setData(ShapeFactory::rubber);
    _rubberAction->setCheckable(true);


    // Create action for Style menu --> Color sub menu
    _chooseShapeColorAction = new QAction(QIcon(":/pen_color_icon"), tr("&Changed shape color"), this);
    _chooseShapeColorAction->setData(tr("Changed shape color"));            // setData to identify what QAction generating an event

    _chooseFillColorAction = new QAction(QIcon(":/fill_out_color_icon"), tr("&Changed fill Color"), this);
    _chooseFillColorAction->setData(tr("Changed fill Color"));              // setData to identify what QAction generating an event


    // Create action for Style menu --> Pen style sub menu
    _solidLineAction = new QAction(QIcon(":/solid_line_icon"), tr("&Solid line"), this);
    _solidLineAction->setData(Qt::SolidLine);                            // setData to identify what QAction generating an event
    _solidLineAction->setCheckable(true);

    _dashLineAction = new QAction(QIcon(":/dash_line_icon"), tr("&Dash line"), this);
    _dashLineAction->setData(Qt::DashLine);                              // setData to identify what QAction generating an event
    _dashLineAction->setCheckable(true);

    _dotLineAction = new QAction(QIcon(":/dot_line_icon"), tr("&Dot line"), this);
    _dotLineAction->setData(Qt::DotLine);                                // setData to identify what QAction generating an event
    _dotLineAction->setCheckable(true);

    _dashDotLineAction = new QAction(QIcon(":/dash_dot_line_icon"), tr("&Dash dot line"), this);
    _dashDotLineAction->setData(Qt::DashDotLine);                       // setData to identify what QAction generating an event
    _dashDotLineAction->setCheckable(true);

    _dashDotDotLineAction = new QAction(QIcon(":/dash_dot_dot_line_icon"), tr("&Dash dot dot line"), this);
    _dashDotDotLineAction->setData(Qt::DashDotDotLine);                // setData to identify what QAction generating an event
    _dashDotDotLineAction->setCheckable(true);

    // Create action for Style menu --> Brush style sub menu
    _solidPatternAction = new QAction(QIcon(":/solid_pattern_icon"), tr("&Solid pattern"), this);
    _solidPatternAction->setData(Qt::SolidPattern);                            // setData to identify what QAction generating an event
    _solidPatternAction->setCheckable(true);

    _horizontalPatternAction = new QAction(QIcon(":/horizontal_pattern_icon"), tr("&Horizontal pattern"), this);
    _horizontalPatternAction->setData(Qt::HorPattern);                            // setData to identify what QAction generating an event
    _horizontalPatternAction->setCheckable(true);

    _verticalPatternAction = new QAction(QIcon(":/vertical_pattern_icon"), tr("&Vertical pattern"), this);
    _verticalPatternAction->setData(Qt::VerPattern);                            // setData to identify what QAction generating an event
    _verticalPatternAction->setCheckable(true);

    _crossPatternAction = new QAction(QIcon(":/cross_pattern_icon"), tr("&Cross pattern"), this);
    _crossPatternAction->setData(Qt::CrossPattern);                            // setData to identify what QAction generating an event
    _crossPatternAction->setCheckable(true);

    _bDiagPatternAction = new QAction(QIcon(":/b_diag_pattern_icon"), tr("&B Diagonal pattern"), this);
    _bDiagPatternAction->setData(Qt::BDiagPattern);                            // setData to identify what QAction generating an event
    _bDiagPatternAction->setCheckable(true);

    _fDiagPatternAction = new QAction(QIcon(":/f_diag_pattern_icon"), tr("&F Diagonal pattern"), this);
    _fDiagPatternAction->setData(Qt::FDiagPattern);                            // setData to identify what QAction generating an event
    _fDiagPatternAction->setCheckable(true);

    _diagCrossPatternAction = new QAction(QIcon(":/diag_cross_pattern_icon"), tr("&Diagonal cross pattern"), this);
    _diagCrossPatternAction->setData(Qt::DiagCrossPattern);                            // setData to identify what QAction generating an event
    _diagCrossPatternAction->setCheckable(true);

    // Create action for Help menu
    _aboutAction = new QAction(QIcon(":/about"), tr("&About"), this);
    _aboutAction->setShortcut(QKeySequence(ABOUT_SHORTCUT.c_str()));                // Define the ABOUT_SHORTCUT as shortcut for the "About QAction"

    _aboutQtAction = new QAction(QIcon(":/about_Qt_icon"), tr("About &Qt"), this);

    _helpAction = new QAction(QIcon(":/documentation_icon"), tr("&Help"), this);

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

    // Create action group for radiobox into the Style menu --> Brush style sub menu
    _brushStyleActionGroup = new QActionGroup(this);
    _brushStyleActionGroup->addAction(_solidPatternAction);
    _brushStyleActionGroup->addAction(_horizontalPatternAction);
    _brushStyleActionGroup->addAction(_verticalPatternAction);
    _brushStyleActionGroup->addAction(_crossPatternAction);
    _brushStyleActionGroup->addAction(_bDiagPatternAction);
    _brushStyleActionGroup->addAction(_fDiagPatternAction);
    _brushStyleActionGroup->addAction(_diagCrossPatternAction);
    _solidPatternAction->setChecked(true);

    // Create action for context menu
    _eraseAction = new QAction(QIcon(":/erase_icon"), tr("&Erase"), this);
}

void MainWindow::_connectActions()
{
    // Connect File actions with her menu
    _fileMenu->addAction(_newAction);
    _fileMenu->addAction(_openAction);
    _fileMenu->addAction(_saveAction);
    _fileMenu->addAction(_saveAsAction);
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

    // Connect Brush style actions with her menu
    _brushStyleMenu->addAction(_solidPatternAction);
    _brushStyleMenu->addAction(_horizontalPatternAction);
    _brushStyleMenu->addAction(_verticalPatternAction);
    _brushStyleMenu->addAction(_crossPatternAction);
    _brushStyleMenu->addAction(_bDiagPatternAction);
    _brushStyleMenu->addAction(_fDiagPatternAction);
    _brushStyleMenu->addAction(_diagCrossPatternAction);

    // Connect Color actions with her menu
    _colorMenu->addAction(_chooseShapeColorAction);
    _colorMenu->addAction(_chooseFillColorAction);

    // Connect About actions with her menu
    _helpMenu->addAction(_aboutAction);
    _helpMenu->addAction(_aboutQtAction);
    _helpMenu->addAction(_helpAction);
}

void MainWindow::_connectSignals()
{
    // Link signals in relation with File menu with slots
    connect(_newAction, SIGNAL(triggered()), this, SLOT(newAction()));
    connect(_openAction, SIGNAL(triggered()), this, SLOT(openAction()));
    connect(_saveAction, SIGNAL(triggered()), this, SLOT(saveAction()));
    connect(_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsAction()));
    connect(_quitAction, SIGNAL(triggered()), this, SLOT(exitAction()));

    // Link signals in relation with Style menu with slots
    connect(_shapeMenu, SIGNAL(triggered(QAction*)), this, SLOT(drawShapeAction(QAction*)));
    connect(_colorMenu, SIGNAL(triggered(QAction*)), this, SLOT(chooseColorAction(QAction*)));
    connect(_penStyleMenu, SIGNAL(triggered(QAction*)), this, SLOT(changePenStyleAction(QAction*)));
    connect(_brushStyleMenu, SIGNAL(triggered(QAction*)), this, SLOT(changeBrushStyleAction(QAction*)));

    // Link signals in relation with Help menu with slots
    connect(_aboutAction, SIGNAL(triggered()), this, SLOT(aboutAction()));
    connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQtAction()));
    connect(_helpAction, SIGNAL(triggered()), this, SLOT(helpAction()));

    // Link signal to change the shape size
    connect(_sizeWidget, SIGNAL(valueChanged(int)), _myPainter, SLOT(sizeChange(int)));

    // To allow right clic on the painter
    connect(_myPainter, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect(_eraseAction, SIGNAL(triggered()), _myPainter, SLOT(eraseScreen()));
}

void MainWindow::drawShapeAction(QAction* action)
{
    int shapeToDraw = action->data().toInt();

    _myPainter->shapeToDrawChange((ShapeFactory::Shape_enum)shapeToDraw);
}

void MainWindow::chooseColorAction(QAction* action)
{
   QColorDialog* colorChooser = new QColorDialog();

   colorChooser->setWindowIcon(QIcon(":/change_color_icon"));

   QColor color = QColorDialog::getColor(Qt::white, colorChooser, tr("Choose a new color"), QColorDialog::DontUseNativeDialog);

   if(color.isValid())
   {
        QString submenuGenerateEvent = action->data().toString();

        _myPainter->colorToApplyChange(submenuGenerateEvent, color);
   }
}

void MainWindow::changePenStyleAction(QAction* action)
{
    int newPenStyle = action->data().toInt();

    _myPainter->penStyleChange((Qt::PenStyle)newPenStyle);
}

void MainWindow::changeBrushStyleAction(QAction* action)
{
    int newBrushStyle = action->data().toInt();

    _myPainter->brushStyleChange((Qt::BrushStyle)newBrushStyle);
}

void MainWindow::newAction()
{
    bool response = askUser(tr("New drawing"), tr("Are you sure to create a new drawing?"));

    if (response){
        _myPainter->eraseScreen(true);
        _filePath.clear();
    }
}

void MainWindow::openAction()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"), QDir::currentPath(), tr("PNG (*.png);;JPEG (*.jpg);;BMP (*.bmp)") );

    if(!filename.isEmpty())
    {
        if(askUser(tr("Paint"), tr("Do you really want to erase you're drawing?")))
        {
            QStringList filesName = filename.split(".");

            _myPainter->eraseScreen(true);
            _myPainter->getBuffer().load(filename, filesName.at(1).toStdString().c_str());

            // We save the current path
            _filePath = filename;
        }
    }
}

void MainWindow::saveAction()
{
    // If the file isn't save, we call the save as method
    if(_filePath.isEmpty())
    {
        saveAsAction();
    }

    // We save the picture
    else
    {
        QStringList filesName = _filePath.split(".");
        _myPainter->getBuffer().save(_filePath, filesName.at(1).toStdString().c_str());
    }
}

void MainWindow::saveAsAction()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save as"), QDir::currentPath(), tr("PNG (*.png);;JPEG (*.jpg);;BMP (*.bmp)") );

    if(!filename.isEmpty())
    {
        QStringList filesName = filename.split(".");
        _myPainter->getBuffer().save(filename, filesName.at(1).toStdString().c_str());

        // We save the current path
        _filePath = filename;
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
        QApplication::quit();
    }
    else{
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
    QMessageBox msg(QMessageBox::Information, tr("Informations about Paint project"), tr("<strong>Paint projet</strong><br><i>Years 2013-2014</i><br /><br />Developped by Kévin GEORGES and Mathieu PALOMBA<br /><br />CC-BY-NC-ND"), QMessageBox::Ok);
    QPixmap image = QPixmap(":/enib_logo");     // Permet de charger le logo qui sera dans la QMessageBox
    //image = image.scaled(QSize(200, 100));     // Permet de redimenssioner le logo enib pour faire rentrer le texte sur une ligne
    msg.setIconPixmap(image);
    msg.setWindowIcon(QIcon(":/about_icon"));
    msg.exec();
}

void MainWindow::aboutQtAction()
{
    QMessageBox::aboutQt(NULL);
}

void MainWindow::helpAction()
{
    QMessageBox msg(QMessageBox::Information, tr("Documentation about Paint projet"), tr("<strong>Documentation</strong><br /><br /> - If you want to draw a Polygon, you have to click on the pixmap, move you're mouse in the next point that you want, and after, release you're mouse button. To end you're draw, you have to click on the start point, that it's represent by a circle around the first point.<br /><br />Have fun with you're favorite Paint."), QMessageBox::Ok);
    QPixmap image = QPixmap(":/documentation_icon");     // Permet de charger le logo qui sera dans la QMessageBox
    image = image.scaled(QSize(64, 64));     // Permet de redimenssioner l'image
    msg.setIconPixmap(image);
    msg.setWindowIcon(QIcon(":/documentation_icon"));
    msg.exec();
}

void MainWindow::showContextMenu(const QPoint& pos)
{
    // To place the menu
    QPoint globalPos = _myPainter->mapToGlobal(pos);

    QMenu myRightMenu;
    myRightMenu.addMenu(_shapeMenu);
    myRightMenu.addMenu(_penStyleMenu);
    myRightMenu.addMenu(_brushStyleMenu);
    myRightMenu.addSeparator();
    myRightMenu.addMenu(_colorMenu);
    myRightMenu.addSeparator();
    myRightMenu.addAction(_eraseAction);

    // To execute the menu
    myRightMenu.exec(globalPos);
}
