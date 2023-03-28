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
#include <QBoxLayout>
// own
#include "basetab.hpp"

BaseTab::BaseTab(QWidget *parent) : QWidget(parent) {
    auto *boxLayout = new QVBoxLayout(this);
    mainArea = new QWidget;
    settings = new QWidget;
    boxLayout->addWidget(mainArea);
    boxLayout->addWidget(settings);
}

void BaseTab::setMainArea(QWidget *area) {
    mainArea = area;
}
