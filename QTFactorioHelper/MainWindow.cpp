#include "MainWindow.h"
#include <QCloseEvent>
#include "qevent.h"
#include "qclipboard.h"
#include "qdebug.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#include <tlhelp32.h>
#include <qstack.h>
#include <list>
HHOOK g_hHook;
// 全局函数
LRESULT CALLBACK LowLevelKeyboardProc(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	auto lpKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
	auto keyStruct = *lpKeyStruct;
	if ((VK_OEM_3 == keyStruct.vkCode) && WM_KEYUP == wParam) {
		if (!MainWindow::IsShow()) MainWindow::Show();
		return 1;
	}
	else if ((VK_F1 == keyStruct.vkCode) && WM_KEYUP == wParam) {
		if (!MainWindow::IsShow()) MainWindow::Show(true);
		return 1;
	}
	else if (VK_RETURN == keyStruct.vkCode && WM_KEYUP == wParam && MainWindow::IsShow()) {
		MainWindow::keyEnterPressEvent();
		return 1;
	}
	else if (VK_UP == keyStruct.vkCode && WM_KEYUP == wParam && MainWindow::IsShow()) {
		MainWindow::keyUpPerssEvent();
	}
	else if (VK_DOWN == keyStruct.vkCode && WM_KEYUP == wParam && MainWindow::IsShow()) {
		MainWindow::keyDownPerssEvent();
	}
	return 0;
}
char* trans(const wchar_t* wch, int type = CP_ACP) {
	int len = WideCharToMultiByte(type, 0, wch, -1, nullptr, 0, nullptr, nullptr);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(type, 0, wch, -1, str, len, nullptr, nullptr);
	return str;
}

MainWindow* MainWindow::instance = NULL;
#endif
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	instance = this;
	ui.setupUi(this);

	//top most
	this->setWindowFlag(Qt::WindowStaysOnTopHint);

	//setwindowshook
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, NULL);
	if (nullptr == g_hHook) qDebug("hook设置失败,错误码:&d", GetLastError());

	this->setGeometry(60, 950, 800, 27);

	hWnd = (HWND)winId();
	DWORD factorioID = GetProcessIDByName(L"factorio.exe");
	factorioHwnd = (HWND)OpenProcess(PROCESS_ALL_ACCESS, FALSE, factorioID);
}

DWORD MainWindow::GetProcessIDByName(const WCHAR* pName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	std::list<LPCWCHAR> l;
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe)) {
		if (wcscmp(pe.szExeFile, pName) == 0) {
			
			CloseHandle(hSnapshot);
			return pe.th32ProcessID;
		}

		qDebug(trans(pe.szExeFile));
	}
	CloseHandle(hSnapshot);
	return 0;
}

void MainWindow::CloseEvent(QCloseEvent * event)
{
	event->ignore();
	MainWindow::Hide();
}

void MainWindow::Hide()
{
	if (nullptr != instance) {
		instance->hide();

		SetWindowPos(instance->factorioHwnd, HWND_TOPMOST,0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
	}
}

void MainWindow::Show(bool isTag)
{
	if (nullptr != instance) {
		instance->isTag = isTag;
		instance->show();
		instance->ui.textEdit->setText(NULL);
		SetWindowPos(instance->hWnd, HWND_TOPMOST, 60, 950,0,0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
}

bool MainWindow::IsShow()
{
	if (nullptr != instance)
		return !(instance->isHidden());
	return false;

}

#ifdef _WIN32
void MainWindow::keyEnterPressEvent()
{
	auto text = MainWindow::instance->ui.textEdit->text();
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(text);
	Hide();
	Paste();
	if (text.length() != 0) {
		instance->historyString.push(text);
		instance->backString.clear();
	}
}
void MainWindow::keyUpPerssEvent()
{
	if (!instance->historyString.empty()) {
		if (1 <= instance->historyString.count()) {
			auto historyText = instance->historyString.pop();
			//历史记录pop以后，将pop出的元素放入back里
			MainWindow::instance->backString.push(historyText);

			MainWindow::instance->ui.textEdit->setText(historyText);
		}
		else {
			//如果历史记录仅剩一个，则不pop，而是直接取栈顶元素，然后设置text
			auto historyText = instance->historyString.top();
			MainWindow::instance->ui.textEdit->setText(historyText);
		}
	}
}
void MainWindow::keyDownPerssEvent()
{
	if (!instance->backString.empty()) {
		if (1 <= instance->backString.count()) {
			auto backText = instance->backString.pop();
			//回退pop以后，将pop出的元素放入history里
			MainWindow::instance->historyString.push(backText);

			MainWindow::instance->ui.textEdit->setText(backText);
		}
		else {
			//如果历史记录仅剩一个，则不pop，而是直接取栈顶元素，然后设置text
			auto backText = instance->backString.top();
			MainWindow::instance->ui.textEdit->setText(backText);
		}
	}
}
void MainWindow::Paste()
{
	keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0u), 0, 0);
	keybd_event('V', MapVirtualKey('V', 0u), 0, 0);
	keybd_event('V', MapVirtualKey('V', 0u), KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0u), KEYEVENTF_KEYUP, 0);
	if (!instance->isTag) {
		//如果不是标记/车站等，自动按下enter
		keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0u), 0, 0);
		keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0u), KEYEVENTF_KEYUP, 0);
	}
	else {
		//如果是标记/车站等，不自动按下enter,并且把flag置非
		instance->isTag = false;
	}
}
void MainWindow::setWindowsHookEx()
{
}
#endif
