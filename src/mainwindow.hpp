
#ifndef YAFILESQUEEZER_MAINWINDOW_HPP
#define YAFILESQUEEZER_MAINWINDOW_HPP

// KF
#include <KXmlGuiWindow>

class KTextEdit;

class KJob;


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

    KTextEdit *textArea;
    KTextEdit *digitTextArea;
    QString fileName;
};



#endif //YAFILESQUEEZER_MAINWINDOW_HPP
