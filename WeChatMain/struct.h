#pragma once
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