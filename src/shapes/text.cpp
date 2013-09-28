#include <QInputDialog>
#include "shapes/text.h"

Text::Text(QPen& pen, QBrush& brush) :
    Shape(pen, brush)
{
}

Text::~Text()
{
}

void Text::draw(QPixmap& pixmap)
{
    QPainter painter(&pixmap);

    // Apply brush to the painter which draw shape
    painter.setBrush(_brush);

    // Apply pen to the painter which draw shape
    painter.setPen(_pen);

    // We draw the correct shape
    if( !_textToDisplay.isEmpty() )
    {
        painter.drawText(_startPoint, _textToDisplay);
    }
}

void Text::mousePressEvent(QMouseEvent* event)
{
    // We get the mouse position
    _startPoint = event->pos();

    // We ask to the user the text to write
    bool ok;
    QString text = QInputDialog::getText(NULL, tr("Text"), tr("Text"), QLineEdit::Normal, tr("Enter you're text here"), &ok);

    // If the user enter text
    if (ok && !text.isEmpty()){
        _textToDisplay.clear();
        _textToDisplay.append(text);
    }

    // We signal the shape it's drawed
    _drawed = true;
    emit drawed();
}

