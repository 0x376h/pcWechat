#pragma once
//�û�������Ϣ�ṹ��
struct Information
{
	wchar_t wxid[0x100]			= L"NULL";	//΢��ID
	wchar_t account[0x100]		= L"NULL";	//�Զ����˺�
	wchar_t nickname[0x200]		= L"NULL";	//�ǳ�
	wchar_t device[0x100]		= L"NULL";	//��½�豸
	wchar_t phone[0x100]		= L"NULL";	//���ֻ���
	wchar_t email[0x200]		= L"NULL";	//������
	wchar_t sex[0x8]			= L"NULL";	//�Ա�
	wchar_t nation[0x100]		= L"NULL";	//����
	wchar_t province[0x100]		= L"NULL";	//ʡ��
	wchar_t city[0x100]			= L"NULL";	//����
	wchar_t signName[0x1000]	= L"NULL";	//ǩ��
	wchar_t header[0x1000]		= L"NULL";	//ͷ��
};

//�û���Ϣ�ṹ��
struct recieveMsgStruct
{
	int type;
	int isSelf;
	wchar_t* fromWxid;
	wchar_t* senderWxid;
	wchar_t* unkonwStr;
	wchar_t* content;
};

//�����б�ṹ��
struct friendStruct
{
	wchar_t wxid[0x100] = L"NULL";
	wchar_t account[0x200] = L"NULL";
	wchar_t nickname[0x200] = L"NULL";
	wchar_t head[0x1000] = L"NULL";
	wchar_t v1[0x200] = L"NULL";
	wchar_t reMark[0x200] = L"NULL";
};

//���ݿ����ṹ��
struct DbHandle
{
	int handler;
	char path[0x1000];
};

typedef int (*sqlite3_callback)(void*, int, char**, char**);
typedef int(WINAPI* Sqlite3_exec)(
	DWORD,
	const char*,
	sqlite3_callback,
	void*,
	char**
	);