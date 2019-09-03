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
	//�����ڹ��캯��
	MainWindow(QWidget *parent = Q_NULLPTR);
private:
	//���صĻ���CloseEvent�������ڷ�ֹ���ڱ��ر�
	void CloseEvent(QCloseEvent* event);
public:
	//��̬���������ش��ڡ���ע�⣬��������Ψһ�ġ�
	static void Hide();
	//��̬��������ʾ���ڡ���ע�⣬��������Ψһ�ġ�
	static void Show(bool isTag = false);
	//��̬�������жϴ����Ƿ��ڡ���ʾ������ע�⣬��������Ψһ�ġ�
	static bool IsShow();
	//ֻҪ���������У��û����»س����������������
	static void keyEnterPressEvent();
	//ֻҪ���������У��û������Ϸ�����������������
	static void keyUpPerssEvent();
	//ֻҪ���������У��û������·�����������������
	static void keyDownPerssEvent();
	//ճ��ָ������촰��ճ�����Զ�ģ��س��������¼�
	static void Paste();
public:
	//�����ľ�̬ʵ������
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
