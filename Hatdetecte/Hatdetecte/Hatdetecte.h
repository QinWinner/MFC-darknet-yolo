
// Hatdetecte.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHatdetecteApp: 
// �йش����ʵ�֣������ Hatdetecte.cpp
//

class CHatdetecteApp : public CWinApp
{
public:
	CHatdetecteApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHatdetecteApp theApp;