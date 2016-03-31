#pragma once

namespace AceBear
{
 
    class CSpy
    {
    public:
        CSpy();
        virtual ~CSpy();

        DWORD GetProcessId() { return m_dwProcessId; }
        DWORD GetThreadId() { return m_dwThreadId; }
        void Switch(DWORD dwProcessId, DWORD dwThreadId);
    private:
        DWORD m_dwProcessId;
        DWORD m_dwThreadId;
    };

}