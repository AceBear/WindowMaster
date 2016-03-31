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
        void UpdateScrollInfo();
    protected:
        LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        virtual void OnPaint(HWND hwnd);
        virtual void OnSize(HWND hwnd, UINT state, int cx, int cy);
        virtual BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
        virtual void OnDestroy(HWND hwnd);
        virtual void OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
        virtual void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
    private:
        CSpy *m_pSpy;
        HFONT m_fontSimSun;
        HBRUSH m_brSelected;
        static const int c_yGap = 4;
        int m_yBase = 0;
    };

}