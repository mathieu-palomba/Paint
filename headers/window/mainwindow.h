#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include "myPainter.h"
#include "defines.h"
#include "string.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MyPainter;
class QSpinBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const string QUIT_SHORTCUT;
    static const string ABOUT_SHORTCUT;
    static const int MAX_SIZE;

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow* ui;

    QMenu* _fileMenu;
    QMenu* _styleMenu;
    QMenu* _shapeMenu;
    QMenu* _colorMenu;
    QMenu* _penStyleMenu;
    QMenu* _helpMenu;
    QMenu* _aboutMenu;

    QAction* _newAction;
    QAction* _openAction;
    QAction* _saveAction;
    QAction* _quitAction;
    QActionGroup* _shapeActionGroup;
    QAction* _drawLineAction;
    QAction* _drawRectangleAction;
    QAction* _drawCircleAction;
    QAction* _drawPolygonAction;
    QAction* _drawTextAction;
    QAction* _rubberAction;
    QAction* _chooseShapeColorAction;
    QAction* _chooseFillColorAction;
    QActionGroup* _penStyleActionGroup;
    QAction* _solidLineAction;
    QAction* _dashLineAction;
    QAction* _dotLineAction;
    QAction* _dashDotLineAction;
    QAction* _dashDotDotLineAction;
    QAction* _aboutAction;

    QSpinBox* _sizeWidget;

    QToolBar* _toolBar;

    MyPainter* _myPainter;

    void _initScreen();
    void _createMenus();
    void _createToolbars();
    void _createDockWidget();
    void _createActions();
    void _connectActions();
    void _connectSignals();

    void closeEvent(QCloseEvent* event);
    bool askUser(QString title, QString question);

public slots:
    void newAction();
    void openAction();
    void saveAction();
    void exitAction(QCloseEvent *event = NULL);
    void drawShapeAction(QAction* action);
    void chooseColorAction(QAction *action);
    void changePenStyleAction(QAction *action);
    void aboutAction();
    void showContextMenu(const QPoint& pos);
};

#endif // MAINWINDOW_H
