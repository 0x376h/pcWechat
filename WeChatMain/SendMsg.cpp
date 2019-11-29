#include <Windows.h>
#include <string>
#include "common.h"
#include "offset.h"
using namespace std;

/**
 * ����QQ��50728123
 * ����Ⱥ��810420984
 * ����΢�ţ�codeByDog
 * �����ı���Ϣ
 * @param wchar_t* wxid, string content
 * @return void
 */
void SendTextMsg(wchar_t* wxid, wchar_t* msg)
{
	struct wxMsg
	{
		wchar_t* pMsg;		//΢��ID
		int msgLen;			//ID����
		int buffLen;		//����������
		int fill1 = 0;
		int fill2 = 0;
	};
	//�õ�������Ϣ��call�ĵ�ַ
	DWORD dwSendCallAddr = getWeChatWinAddr() + SENDTEXTADDR;

	//��װ΢��ID/ȺID�Ľṹ��
	wxMsg id = { 0 };
	id.pMsg = wxid;
	id.msgLen = wcslen(wxid);
	id.buffLen = wcslen(wxid) * 2;

	//��Ϣ����
	wxMsg text = { 0 };
	text.pMsg = msg;
	text.msgLen = wcslen(msg);
	text.buffLen = wcslen(msg) * 2;

	//ȡ��΢��ID����Ϣ�ĵ�ַ
	char* pWxid = (char*)&id.pMsg;
	char* pWxmsg = (char*)&text.pMsg;

	char buff[0x81C] = { 0 };

	//����΢�ŷ�����Ϣcall
	__asm {
		mov edx, pWxid;
		push 0x1;
		push 0;
		mov ebx, pWxmsg;
		push ebx;
		lea ecx, buff;
		call dwSendCallAddr;
		add esp, 0xC;
	}
}

/**
 * ����QQ��50728123
 * ����Ⱥ��810420984
 * ����΢�ţ�codeByDog
 * ����ͼƬ�ļ�
 * @param wchar_t* wxid, string content
 * @return void
 */
void SendImageMsg(wchar_t* wxid, wchar_t* filepath)
{
	struct SendImageStruct
	{
		wchar_t* pWxid = nullptr;
		DWORD length = 0;
		DWORD maxLength = 0;
		DWORD fill1 = 0;
		DWORD fill2 = 0;
		wchar_t wxid[1024] = { 0 };
	};

	//��װ΢��ID�����ݽṹ
	SendImageStruct imagewxid;
	memcpy(imagewxid.wxid, wxid, wcslen(wxid) + 1);
	imagewxid.length = wcslen(wxid) + 1;
	imagewxid.maxLength = wcslen(wxid) * 2;
	imagewxid.pWxid = wxid;

	//��װ�ļ�·�������ݽṹ
	SendImageStruct imagefilepath;
	memcpy(imagefilepath.wxid, filepath, wcslen(filepath) + 1);
	imagefilepath.length = wcslen(filepath) + 1;
	imagefilepath.maxLength = MAX_PATH;
	imagefilepath.pWxid = filepath;

	char buff[0x45C] = { 0 };

	DWORD dwCall1 = getWeChatWinAddr() + SENDIMGADDR1;
	DWORD dwCall2 = getWeChatWinAddr() + SENDIMGADDR2;
	DWORD myEsp = 0;


	//΢�ŷ���ͼƬ������GidCreateBimapFileCM ֮��ͼƬһֱ��ռ�� �޷�ɾ�� patch������Ĵ���
	unsigned char oldcode[5] = { 0 };
	unsigned char fix[5] = { 0x31,0xC0,0x90,0x90,0x90 };
	DWORD dwPathcAddr = getWeChatWinAddr() + SENDIMGADDR3;
	//�޸Ĵ��������
	DWORD dwOldAttr = 0;
	VirtualProtect((LPVOID)dwPathcAddr, 5, PAGE_EXECUTE_READWRITE, &dwOldAttr);
	//�ȱ���ԭ��ָ��
	memcpy(oldcode, (LPVOID)dwPathcAddr, 5);
	//��Patch��
	memcpy((LPVOID)dwPathcAddr, fix, 5);
	__asm
	{
		//����esp
		mov myEsp, esp;

		lea ebx, imagefilepath;
		push ebx;
		lea eax, imagewxid;
		push eax;
		lea eax, buff;
		push eax;
		push 0;
		call dwCall1;
		add esp, 0x4;
		mov ecx, eax;
		call dwCall2;
		//�ָ���ջ
		mov eax, myEsp;
		mov esp, eax;
	}
	//������֮��ָ�
	memcpy((LPVOID)dwPathcAddr, oldcode, 5);
	//�ָ�����
	VirtualProtect((LPVOID)dwPathcAddr, 5, dwOldAttr, &dwOldAttr);
}

/**
 * ����QQ��50728123
 * ����Ⱥ��810420984
 * ����΢�ţ�codeByDog
 * ���͸����ļ�
 * @param wchar_t* wxid, string content
 * @return void
 */
void SendAttachMsg(wchar_t* wxid, wchar_t* filepath)
{
	//΢��ID�Ľṹ��
	struct Wxid
	{
		wchar_t* str;
		int strLen = 0;
		int maxLen = 0;
		char file[0x8] = { 0 };
	};

	//�ļ�·���Ľṹ��
	struct filePath
	{
		wchar_t* str;
		int strLen = 0;
		int maxLen = 0;
		char file[0x18] = { 0 };
	};

	//������Ҫ�ĵ�ַ
	DWORD dwCall1 = getWeChatWinAddr() + SENDATTACHADDR1;
	DWORD dwCall2 = getWeChatWinAddr() + SENDATTACHADDR2;
	DWORD dwCall3 = getWeChatWinAddr() + SENDATTACHADDR3;	//�������
	DWORD dwCall4 = getWeChatWinAddr() + SENDATTACHADDR4;	//������Ϣ
	DWORD dwParams = getWeChatWinAddr() + SENDATTACHPARAM;

	char buff[0x45C] = { 0 };

	//������Ҫ������
	Wxid wxidStruct = { 0 };
	wxidStruct.str = wxid;
	wxidStruct.strLen = wcslen(wxid);
	wxidStruct.maxLen = wcslen(wxid) * 2;

	filePath filePathStruct = { 0 };
	filePathStruct.str = filepath;
	filePathStruct.strLen = wcslen(filepath);
	filePathStruct.maxLen = wcslen(filepath) * 2;

	//ȡ����Ҫ�����ݵĵ�ַ
	char* pFilePath = (char*)&filePathStruct.str;
	char* pWxid = (char*)&wxidStruct.str;

	__asm {
		push dword ptr ss : [ebp - 0x5C] ;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		push dwParams;
		call dwCall1;
		sub esp, 0x14;
		mov ecx, esp;
		push pFilePath;
		call dwCall2;
		sub esp, 0x14;
		mov ecx, esp;
		push pWxid;
		call dwCall2;
		lea eax, buff;
		push eax;
		call dwCall3;
		mov ecx, eax;
		call dwCall4;
	}
}