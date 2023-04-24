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

#ifndef YA_FSQUEEZER_DIGITALTAB_HPP
#define YA_FSQUEEZER_DIGITALTAB_HPP

// own
#include "texttab.hpp"

class DigitalTab : public TextTab {
Q_OBJECT
public:
    explicit DigitalTab(QWidget *parent = nullptr);

    static QString castToNS(qint64 value, int ns, bool isCapital = true);

public slots:

    void setSymbolLength(int value);

    void setNumeralSystem(int value);

public Q_SLOTS:

    void setDigitText(const QString &text);

private:
    QVector<qint64> digitalization;
    int numeralSystem = 10;
    int symbolLength = 8;
    bool isCapital = true;
};


#endif //YA_FSQUEEZER_DIGITALTAB_HPP
