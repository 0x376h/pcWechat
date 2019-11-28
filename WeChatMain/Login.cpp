#include <Windows.h>
#include "common.h"
#include "offset.h"
#include "resource.h"

/**
 * ����QQ��50728123
 * ����Ⱥ��810420984
 * ����΢�ţ�codeByDog
 * ��ȡ΢�ŵ�¼״̬
 * @param  
 * @return int
 */
int isLogin()
{
	return (int) * (int*)(getWeChatWinAddr() + ISLOGIN);
}

/**
 * ����QQ��50728123
 * ����Ⱥ��810420984
 * ����΢�ţ�codeByDog
 * �̳߳�����ȡ��¼״̬
 * @param  HWND hwnd
 * @return void
 */
void getLoginStatus(HWND hwnd)
{
	if (getWeChatWinAddr() != 0)
	{
		SetDlgItemText(hwnd, LOGIN_STATUS, isLogin() == 0 ? L"δ��¼" : L"�ѵ�¼");
	}
	Sleep(500);
	HANDLE lThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)getLoginStatus, hwnd, NULL, 0);
	if (lThread != 0) {
		CloseHandle(lThread);
	}
}