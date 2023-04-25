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
#include <QPropertyAnimation>
#include <QToolButton>
#include <QFrame>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QGridLayout>
// own
#include "spoiler.hpp"

Spoiler::Spoiler(QWidget *parent) : QWidget(parent) {
    toggleButton = new QToolButton;
    contentArea = new QScrollArea;
    auto *mainLayout = new QVBoxLayout;

    toggleButton->setStyleSheet("QToolButton {border: none;}");
    toggleButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toggleButton->setArrowType(Qt::ArrowType::RightArrow);
    toggleButton->setCheckable(true);
    toggleButton->setChecked(false);

    setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
    contentArea->hide();

    mainLayout->addWidget(toggleButton);
    mainLayout->addWidget(contentArea);
    setLayout(mainLayout);

    connect(toggleButton, &QToolButton::toggled, this, &Spoiler::toggle);
}

void Spoiler::toggle(bool expanded) {
    toggleButton->setArrowType(expanded ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
    contentArea->setHidden(!expanded);
}

void Spoiler::setContentLayout(QLayout *contentLayout) {
    delete contentArea->layout();

    contentArea->setLayout(contentLayout);
    contentArea->setMaximumHeight(contentLayout->minimumSize().height());
}

void Spoiler::setTitle(const QString &title) {
    toggleButton->setText(title);
}
