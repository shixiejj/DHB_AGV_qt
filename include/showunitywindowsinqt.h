#ifndef SHOWUNITYWINDOWSINQT_H
#define SHOWUNITYWINDOWSINQT_H

#include <QObject>
#include <QProcess>
#include <Windows.h>
#include <winuser.h>
#include <QDebug>

class ShowUnityWindowsInQt: public QObject
{
    Q_OBJECT
public:
    explicit ShowUnityWindowsInQt(QObject* parent = nullptr);

    ~ShowUnityWindowsInQt();

    void startUnityProgram(const QString& unityExePath);

    void setWindowParent(HWND parentWidgetHandle, const QString& sonWindowTitleName);

signals:
    void unityProgramStarted();

private:
    QProcess* process;

};

#endif // SHOWUNITYWINDOWSINQT_H
