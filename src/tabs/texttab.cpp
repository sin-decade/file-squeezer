/*
 *   The GNU General Public License v3.0
 *
 *   Copyright (C) 2023 Yaroslav Riabtsev <yaroslav.riabtsev@rwth-aachen.de>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
*/

// Qt
#include <QDebug>
// own
#include "texttab.hpp"

TextTab::TextTab(QWidget *parent) : KTextEdit(parent) {

}

void TextTab::setHighlightingStyle(int index) {
    QTextDocument *document = this->document();

    if (index == 0) {
        document->setPlainText(body);
    } else if (index == 1) {
        document->setMarkdown(body);
    } else if (index == 2) {
        document->setHtml(body);
    }

    currentType = index;
}

void TextTab::setText(const QString &text) {
    body = text;
    setHighlightingStyle(currentType);
}
