#include "stdafx.h"
#include "ToolWnd.h"

namespace AceBear
{
    CToolWnd::CToolWnd()
    {
        StringCchPrintf(m_wszClsName, sizeof(m_wszClsName) / sizeof(wchar_t), L"%S", typeid(this).name());
    }


    CToolWnd::~CToolWnd()
    {
    }
}