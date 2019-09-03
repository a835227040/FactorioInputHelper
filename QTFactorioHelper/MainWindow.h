#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QCloseEvent>
#include <Windows.h>
#include "qstack.h"
LRESULT CALLBACK LowLevelKeyboardProc(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	//主窗口构造函数
	MainWindow(QWidget *parent = Q_NULLPTR);
private:
	//重载的基类CloseEvent函数用于防止窗口被关闭
	void CloseEvent(QCloseEvent* event);
public:
	//静态函数、隐藏窗口。请注意，主窗口是唯一的。
	static void Hide();
	//静态函数、显示窗口。请注意，主窗口是唯一的。
	static void Show(bool isTag = false);
	//静态函数、判断窗口是否在【显示】。请注意，主窗口是唯一的。
	static bool IsShow();
	//只要进程在运行，用户按下回车键后会调起这个函数
	static void keyEnterPressEvent();
	//只要进程在运行，用户按下上方向键后会调起这个函数
	static void keyUpPerssEvent();
	//只要进程在运行，用户按下下方向键后会调起这个函数
	static void keyDownPerssEvent();
	//粘贴指令，在聊天窗下粘贴后自动模拟回车键按下事件
	static void Paste();
public:
	//公开的静态实例变量
	static MainWindow* instance;
private:
	Ui::MainWindowClass ui;
	HWND hWnd;
	HWND factorioHwnd;
	bool isTag;
#ifdef _WIN32
private:
	void setWindowsHookEx();
	DWORD GetProcessIDByName(const WCHAR* pName);
	QStack<QString> historyString;
	QStack<QString> backString;
#endif
};
