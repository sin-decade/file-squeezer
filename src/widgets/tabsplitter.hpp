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


#ifndef FILE_SQUEEZER_TABSPLITTER_HPP
#define FILE_SQUEEZER_TABSPLITTER_HPP

// Qt
#include <QSplitter>
#include <QTabWidget>

class TabSplitter : public QSplitter {
Q_OBJECT

public:

    explicit TabSplitter(Qt::Orientation orientation = Qt::Horizontal, QWidget *parent = nullptr);

    void addTab(QWidget *widget, const QString &name);


public Q_SLOTS:

    void showMenu(QTabWidget *widget, int index);

private:
    QList<QPair<QWidget *, QString>> m_tabs;

    void addTabWidget(bool back = true);

    void removeTabWidget(int index);

    void moveTab(int tabIndex, int tabWidgetIndex, int direction = 1);

};


#endif //FILE_SQUEEZER_TABSPLITTER_HPP
