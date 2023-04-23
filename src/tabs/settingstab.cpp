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
#include <QSlider>
#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
// own
#include "settingstab.hpp"
#include "src/widgets/spoiler.hpp"

SettingsTab::SettingsTab(QWidget *parent) : QWidget(parent) {
    auto *spoilerDT = new Spoiler;
    spoilerDT->setTitle("Digital Tab");
    auto *spoilerTT = new Spoiler;
    spoilerTT->setTitle("Text Tab");
    {
        auto *layout = new QVBoxLayout;

        auto *digitalLengthLabel = new QLabel("Length (in bits) of the symbol:");
        auto *digitalNumeralSystemLabel = new QLabel("Numeral System to display the symbol:");
        auto *digitalLengthSlider = new QSlider(Qt::Horizontal);
        auto *digitalNumeralSystemSlider = new QSlider(Qt::Horizontal);

        digitalLengthSlider->setMinimum(1);
        digitalLengthSlider->setMaximum(64);
        digitalLengthSlider->setValue(8);
//    connect(digitalLengthSlider, &QSlider::valueChanged, this, &SettingsTab::onDigitalLengthSliderValueChanged);

        digitalNumeralSystemSlider->setMinimum(2);
        digitalNumeralSystemSlider->setMaximum(16);
        digitalNumeralSystemSlider->setValue(10);
//    connect(digitalNumeralSystemSlider, &QSlider::valueChanged, this, &SettingsTab::onDigitalLengthSliderValueChanged);


        layout->addWidget(digitalLengthLabel);
        layout->addWidget(digitalLengthSlider);
        layout->addWidget(digitalNumeralSystemLabel);
        layout->addWidget(digitalNumeralSystemSlider);

        spoilerDT->setContentLayout(layout);
    }
    {
        auto *layout = new QVBoxLayout;
        auto *textSyntaxHighlightingLabel = new QLabel("Syntax Highlighting:");
        auto *textSyntaxHighlightingComboBox = new QComboBox;
        textSyntaxHighlightingComboBox->addItem("None");
        textSyntaxHighlightingComboBox->addItem("Markdown");
        textSyntaxHighlightingComboBox->addItem("HTML");
//        connect(textSyntaxHighlightingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SettingsTab::onTextSyntaxHighlightingComboBoxCurrentIndexChanged);

        layout->addWidget(textSyntaxHighlightingLabel);
        layout->addWidget(textSyntaxHighlightingComboBox);
        spoilerTT->setContentLayout(layout);
    }

    auto *layout = new QVBoxLayout;
    layout->addWidget(spoilerDT);
    layout->addWidget(spoilerTT);
    layout->addStretch();
    setLayout(layout);
}
