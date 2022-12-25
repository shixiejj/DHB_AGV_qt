#undef UNICODE
#include "showunitywindowsinqt.h"
#include "winuser.h"
#include <QHBoxLayout>
#include <QTabWidget>
#include <QWidget>

ShowUnityWindowsInQt::ShowUnityWindowsInQt(QObject* parent)
    : QObject{parent}
{
    process = new QProcess(this);

    connect(process, &QProcess::started, this, &ShowUnityWindowsInQt::unityProgramStarted);
}

ShowUnityWindowsInQt::~ShowUnityWindowsInQt()
{
    process->kill();
}

void ShowUnityWindowsInQt::startUnityProgram(const QString& unityExePath)
{
    process->setProgram(unityExePath);
    process->start(QIODevice::Truncate);
    qDebug() << "PID: " << process->processId();
}

void ShowUnityWindowsInQt::setWindowParent(HWND parentWidgetHandle, const QString& sonWindowTitleName)
{
    HWND hfigure = FindWindow(NULL, sonWindowTitleName.toStdString().c_str());

    qDebug() << hfigure;

    if (NULL != ::SetParent(hfigure, parentWidgetHandle))
    {
        //通过该函数设置窗口大小以适配qt内界面
        SetWindowPos(hfigure,HWND_TOP,0,0,1270,890,SWP_SHOWWINDOW);
        qDebug() << "Success";
    }
    else
        qDebug() << "Fail";
}

