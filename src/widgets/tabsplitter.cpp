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
#include <QTabBar>
#include <QMenu>
#include <QDebug>
// own
#include "tabsplitter.hpp"


TabSplitter::TabSplitter(Qt::Orientation orientation, QWidget *parent) : QSplitter(orientation, parent) {

}

void TabSplitter::addTabWidget(bool back) {
    auto newTabWidget = new QTabWidget;

    connect(newTabWidget->tabBar(), &QTabBar::tabBarDoubleClicked,
            this, [=](int index) { showMenu(newTabWidget, index); });

    if (back) {
        addWidget(newTabWidget);
    } else {
        insertWidget(0, newTabWidget);
    }
}

void TabSplitter::addTab(QWidget *widget, const QString &name) {
    m_tabs.append({widget, name});
    if (count() == 0) {
        addTabWidget(true);
    }
    qobject_cast<QTabWidget *>(this->widget(0))->addTab(widget, name);
}

void TabSplitter::removeTabWidget(int index) {
    auto widget = qobject_cast<QTabWidget *>(this->widget(index));
    if (widget != nullptr && widget->count() == 0) {
        widget->setParent(nullptr);
    }
}

void TabSplitter::moveTab(int tabIndex, int tabWidgetIndex, int direction) {
    if (tabWidgetIndex + direction >= count()) {
        addTabWidget();
    } else if (tabWidgetIndex + direction < 0) {
        addTabWidget(false);
        tabWidgetIndex++;
    }
    qobject_cast<QTabWidget *>(this->widget(tabWidgetIndex + direction))->
            addTab(m_tabs[tabIndex].first, m_tabs[tabIndex].second);
    removeTabWidget(tabWidgetIndex);
}

void TabSplitter::showMenu(QTabWidget *widget, int index) {
    QMenu menu(this);
    int tabIndex = 0;
    for (; tabIndex < m_tabs.count() && m_tabs[tabIndex].first != widget->widget(index); tabIndex++);
    menu.addAction("Move Left", [=]() {
        moveTab(tabIndex, this->indexOf(widget), -1);
    });
    menu.addAction("Move Right", [=]() {
        moveTab(tabIndex, this->indexOf(widget), 1);
    });
    menu.exec(QCursor::pos());
}

