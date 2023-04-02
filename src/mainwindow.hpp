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

#ifndef YA_FSQUEEZER_MAINWINDOW_HPP
#define YA_FSQUEEZER_MAINWINDOW_HPP

// KF
#include <KXmlGuiWindow>

class TextTab;

class DigitalTab;

class KJob;

class QSplitter;

class QTabWidget;

class MainWindow : public KXmlGuiWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private Q_SLOTS:

    void newFile();

    void openFile();

    void saveFile();

    void saveFileAs();

    void downloadFinished(KJob *job);


private:
    void setupActions();

    void saveFileToDisk(const QString &outputFileName);

    TextTab *textArea;
    DigitalTab *digitTextArea;
    QString fileName;

};


#endif //YA_FSQUEEZER_MAINWINDOW_HPP
