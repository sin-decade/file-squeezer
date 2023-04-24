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
    digitalization.clear();
    for (auto &symbol: text) {
        digitalization.push_back(symbol.unicode());
    }
    setSymbolLength(symbolLength);
}

void DigitalTab::setNumeralSystem(int value) {
    QString digitalizedText = "";
    for (auto digit: digitalization) {
        digitalizedText.append(castToNS(digit, value, isCapital));
    }
    numeralSystem = value;
    setPlainText(digitalizedText);
}

void DigitalTab::setSymbolLength(int value) {
    // todo
    symbolLength = value;
    setNumeralSystem(numeralSystem);
}

QString DigitalTab::castToNS(qint64 value, int ns, bool isCapital) {
    QString code = "";
    while (value) {
        char c = value % ns;
        if (c < 10) {
            c += '0';
        } else if (isCapital) {
            c += 'A' - 10;
        } else {
            c += 'a' - 10;
        }
        code = c + code;
        value /= ns;
    }
    if (code.isEmpty()){
        code = "0";
    }
    return code + "-";
}
