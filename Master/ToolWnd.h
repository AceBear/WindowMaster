#pragma once
#include "BaseWnd.h"

namespace AceBear {
    class CSpy;

    class CToolWnd : public CBaseWnd
    {
    public:
        CToolWnd();
        virtual ~CToolWnd();

        void SetSpy(CSpy *pSpy) { m_pSpy = pSpy; }
    protected:
        LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        virtual void OnPaint(HWND hwnd);
        virtual void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
        virtual void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
        virtual void OnSize(HWND hwnd, UINT state, int cx, int cy);
        virtual void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
    private:
        POINT m_pointScreen;
        RECT m_rcTarget;
        CSpy *m_pSpy;
    };

}