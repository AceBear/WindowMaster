#include "stdafx.h"
#include "resource.h"
#include "Spy.h"
#include "MasterWnd.h"

namespace AceBear
{
    CSpy::CSpy()
        :m_dwProcessId(0), m_dwThreadId(0)
    {

    }


    CSpy::~CSpy()
    {
    }

    void CSpy::Switch(DWORD dwProcessId, DWORD dwThreadId)
    {
        m_dwProcessId = dwProcessId;
        m_dwThreadId = dwThreadId;

        CMasterWnd::GetMainWnd()->PostMessage(UM_SWITCHSPY, dwProcessId, dwThreadId);
    }
}