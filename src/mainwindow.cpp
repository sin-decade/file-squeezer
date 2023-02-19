
// Qt
#include <QApplication>
#include <QAction>
#include <QSaveFile>
#include <QFileDialog>
#include <QTextStream>
#include <QByteArray>
#include <QBoxLayout>
// KF
#include <KTextEdit>
#include <KLocalizedString>
#include <KActionCollection>
#include <KStandardAction>
#include <KMessageBox>
#include <KIO/Job>
// own
#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent) {
    textArea = new KTextEdit();
    digitTextArea = new KTextEdit();

    auto* mainWidget = new QWidget;
    auto* texts = new QHBoxLayout(mainWidget);
    texts->addWidget(textArea);
    texts->addWidget(digitTextArea);

    setCentralWidget(mainWidget);

    setupActions();
}

void MainWindow::setupActions() {
    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());
    KStandardAction::open(this, &MainWindow::openFile, actionCollection());
    KStandardAction::save(this, &MainWindow::saveFile, actionCollection());
    KStandardAction::saveAs(this, &MainWindow::saveFileAs, actionCollection());
    KStandardAction::openNew(this, &MainWindow::newFile, actionCollection());

    setupGUI(Default, "yafilesqueezerui.rc");
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
        digitTextArea->setPlainText(txt);
    }
}

