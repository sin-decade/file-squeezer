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

#ifndef FILE_SQUEEZER_TEXTTAB_HPP
#define FILE_SQUEEZER_TEXTTAB_HPP

// KF
#include <KTextEdit>

class TextTab : public KTextEdit {
Q_OBJECT
public:
    explicit TextTab(QWidget *parent = nullptr);

public slots:

    void setHighlightingStyle(int index);
public Q_SLOTS:

    void setText(const QString &text);

private:
    int currentType = 0;
    QString body;
};


#endif //FILE_SQUEEZER_TEXTTAB_HPP
