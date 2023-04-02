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
#include <QApplication>
#include <QSaveFile>
#include <QFileDialog>
#include <QTextStream>
#include <QByteArray>
#include <QBoxLayout>
#include <QDebug>
#include <QTabBar>
#include <QMenu>
// KF
#include <KLocalizedString>
#include <KActionCollection>
#include <KStandardAction>
#include <KMessageBox>
#include <KIO/Job>
// own
#include "mainwindow.hpp"
#include "tabs/texttab.hpp"
#include "tabs/digitaltab.hpp"
#include "src/tabs/settingstab.hpp"
#include "src/widgets/tabsplitter.hpp"


MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent) {
    textArea = new TextTab();
    digitTextArea = new DigitalTab();
    auto settingsTab = new SettingsTab();

    auto splitter = new TabSplitter(Qt::Horizontal);
    splitter->addTab(textArea, "Text Tab");
    splitter->addTab(digitTextArea, "Digital Tab");
    splitter->addTab(settingsTab, "Settings Tab");


    setCentralWidget(splitter);

    setupActions();
}

void MainWindow::setupActions() {
    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());
    KStandardAction::open(this, &MainWindow::openFile, actionCollection());
    KStandardAction::save(this, &MainWindow::saveFile, actionCollection());
    KStandardAction::saveAs(this, &MainWindow::saveFileAs, actionCollection());
    KStandardAction::openNew(this, &MainWindow::newFile, actionCollection());

    setupGUI(Default, "ya-fsqueezerui.rc");
}

void MainWindow::newFile() {
    fileName.clear();
    textArea->clear();
    digitTextArea->clear();
}

void MainWindow::saveFileToDisk(const QString &outputFileName) {
    if (!outputFileName.isNull()) {
        QSaveFile file(outputFileName);
        file.open(QIODevice::WriteOnly);

        QByteArray outputByteArray;
        outputByteArray.append(textArea->toPlainText().toUtf8());

        file.write(outputByteArray);
        file.commit();

        fileName = outputFileName;
    }
}

void MainWindow::saveFileAs() {
    saveFileToDisk(QFileDialog::getSaveFileName(this, i18n("Save File As")));
}

void MainWindow::saveFile() {
    if (!fileName.isEmpty()) {
        saveFileToDisk(fileName);
    } else {
        saveFileAs();
    }
}

void MainWindow::openFile() {
    const QUrl fileNameFromDialog = QFileDialog::getOpenFileUrl(this, i18n("Open File"));

    if (!fileNameFromDialog.isEmpty()) {
        KIO::Job *job = KIO::storedGet(fileNameFromDialog);
        fileName = fileNameFromDialog.toLocalFile();

        connect(job, &KJob::result, this, &MainWindow::downloadFinished);

        job->exec();
    }
}

void MainWindow::downloadFinished(KJob *job) {
    if (job->error()) {
        KMessageBox::error(this, job->errorString());
        fileName.clear();
        return;
    }

    const KIO::StoredTransferJob *storedJob = qobject_cast<KIO::StoredTransferJob *>(job);

    if (storedJob) {
        auto txt = QTextStream(storedJob->data(), QIODevice::ReadOnly).readAll();
        textArea->setPlainText(txt);
        digitTextArea->setDigitText(txt);
    }
}

