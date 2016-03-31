#pragma once
#include "BaseWnd.h"

namespace AceBear
{
    class CSpy;

    class CSpyWnd : public CBaseWnd
    {
    public:
        CSpyWnd();
        virtual ~CSpyWnd();

        void SetSpy(CSpy *pSpy) { m_pSpy = pSpy; }
    protected:
            LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
            virtual void OnPaint(HWND hwnd);
    private:
        CSpy *m_pSpy;
    };

}