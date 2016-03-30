#pragma once
#include "BaseWnd.h"

namespace AceBear {

    class CToolWnd : public CBaseWnd
    {
    public:
        CToolWnd();
        virtual ~CToolWnd();

        void ReSize(int width, int height);
    protected:
        LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        virtual void OnPaint(HWND hwnd);
    };

}