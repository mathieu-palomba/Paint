#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <string.h>
#include "myPainter.h"


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
    static const string SAVE_AS_SHORTCUT;
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
    QMenu* _brushStyleMenu;
    QMenu* _helpMenu;
    QMenu* _aboutMenu;

    QAction* _newAction;
    QAction* _openAction;
    QAction* _saveAction;
    QAction* _saveAsAction;
    QAction* _quitAction;

    QAction* _eraseAction;

    QActionGroup* _shapeActionGroup;
    QAction* _drawFreeHandAction;
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

    QActionGroup* _brushStyleActionGroup;
    QAction* _solidPatternAction;
    QAction* _horizontalPatternAction;
    QAction* _verticalPatternAction;
    QAction* _crossPatternAction;
    QAction* _bDiagPatternAction;
    QAction* _fDiagPatternAction;
    QAction* _diagCrossPatternAction;

    QAction* _aboutAction;
    QAction* _aboutQtAction;
    QAction* _helpAction;

    QSpinBox* _sizeWidget;

    QToolBar* _toolBar;

    MyPainter* _myPainter;

    QString _filePath;

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
    void saveAsAction();
    void exitAction(QCloseEvent *event = NULL);
    void drawShapeAction(QAction* action);
    void chooseColorAction(QAction *action);
    void changePenStyleAction(QAction *action);
    void changeBrushStyleAction(QAction *action);
    void aboutAction();
    void aboutQtAction();
    void helpAction();
    void showContextMenu(const QPoint& pos);
};

#endif // MAINWINDOW_H
