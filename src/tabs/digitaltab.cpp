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
#include "digitaltab.hpp"

DigitalTab::DigitalTab(QWidget *parent) : TextTab(parent) {

}

void DigitalTab::setDigitText(const QString &text) {
    QByteArray byteArray = text.toUtf8();
    bitVector.clear();
    bitVector.resize(byteArray.size() * 8);
    for (int i = 0; i < byteArray.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            bitVector.setBit(i * 8 + j, (byteArray[i] & (1 << j)));
        }
    }
    updateText();
}

void DigitalTab::updateText() {
    QString str;
    int startIndex = 0;
    while (startIndex < bitVector.size()) {
        int symbolCode = extractBitArraySymbol(startIndex);
        QString symbolStr = QString("%1").arg(symbolCode, fieldWidth * withLeadingZeros, numeralSystem, QChar('0'));
        if (isCapital) {
            str.append(symbolStr.toUpper());
        } else {
            str.append(symbolStr.toLower());
        }
        startIndex += symbolLength;
        if (withSeparator) {
            str.append("-");
        }
    }
    setPlainText(str);
}

void DigitalTab::setSymbolLength(int value) {
    symbolLength = value;
    fieldWidth = QString::number((1 << symbolLength) - 1, numeralSystem).length();
    updateText();
}

void DigitalTab::setNumeralSystem(int value) {
    numeralSystem = value;
    fieldWidth = QString::number((1 << symbolLength) - 1, numeralSystem).length();
    updateText();
}

void DigitalTab::setIsCapital(bool value) {
    isCapital = value;
    updateText();
}

void DigitalTab::setWithLeadingZero(bool value) {
    withLeadingZeros = value;
    updateText();
}

void DigitalTab::setWithSeparator(bool value) {
    withSeparator = value;
    updateText();
}

int DigitalTab::extractBitArraySymbol(int startIndex) {
    int symbolCode = 0;
    for (int i = startIndex; i < startIndex + symbolLength && i < bitVector.size(); i++) {
        if (bitVector.testBit(i)) {
            symbolCode |= (1 << (i - startIndex));
        }
    }
    return symbolCode;
}

