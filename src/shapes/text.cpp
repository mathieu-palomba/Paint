#include "text.h"
#include "defines.h"
#include <QInputDialog>

Text::Text(QPen& pen, QBrush& brush) :
    Shape(pen, brush)
{
}

Text::~Text()
{
}

void Text::draw(QPixmap& pixmap)
{
        qDebug() << " BLOP " << _textToDisplay;
    QPainter painter(&pixmap);
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We draw the correct shape
    qDebug() << " BLOP " << _textToDisplay;
    if( !_textToDisplay.isEmpty() )
    {
        painter.drawText(_startPoint, _textToDisplay);
    }
}

void Text::mousePressEvent(QMouseEvent* event)
{
    _startPoint = event->pos();

    bool ok;
    QString text = QInputDialog::getText(NULL, TEXT_SHAPE_DIALOG_TITLE, TEXT_SHAPE_LABEL_NAME, QLineEdit::Normal, TEXT_SHAPE_FIELD_DIALOG, &ok);

    if (ok && !text.isEmpty()){
        qDebug("TEXTE changed");
        _textToDisplay.clear();
        _textToDisplay.append(text);
    }

    _drawed = true;
    emit drawed();
}

