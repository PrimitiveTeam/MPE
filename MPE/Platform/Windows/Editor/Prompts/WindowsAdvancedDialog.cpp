#include "WindowsAdvancedDialog.h"

#include "MPE/Editor/Prompts/AdvancedDialog.h"
#include "MPE/MPEPCH.h"
#include "MPE/MPEPLAT.h"

namespace MPE
{
INT_PTR CALLBACK WindowsAdvancedDialog::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowsAdvancedDialog* pDialog = nullptr;
    if (message == WM_INITDIALOG)
    {
        pDialog = reinterpret_cast<WindowsAdvancedDialog*>(lParam);
        SetWindowLongPtr(hDlg, GWLP_USERDATA, lParam);
    }
    else
    {
        pDialog = reinterpret_cast<WindowsAdvancedDialog*>(GetWindowLongPtr(hDlg, GWLP_USERDATA));
    }

    switch (message)
    {
        case WM_COMMAND:
            if (pDialog)
            {
                int wmId = LOWORD(wParam);
                for (const auto& option : pDialog->m_Options)
                {
                    if (wmId == option.first)
                    {
                        EndDialog(hDlg, wmId);
                        return (INT_PTR) TRUE;
                    }
                }
            }
            break;
        case WM_CLOSE:
            EndDialog(hDlg, -1);
            return (INT_PTR) TRUE;
    }
    return (INT_PTR) FALSE;
}

AdvancedDialog::DialogResponse WindowsAdvancedDialog::show()
{
    // Register the window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = TEXT("CustomDialog");
    RegisterClass(&wc);

    // Calculate the size needed for the dialog
    int buttonWidth = 100;
    int buttonHeight = 30;
    int padding = 10;
    int width = (buttonWidth + padding) * m_Options.size() + padding;
    int height = 150;

    // Create the dialog window
    HWND hDlg = CreateWindowEx(0, TEXT("CustomDialog"), m_Title.c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                               NULL, NULL, GetModuleHandle(NULL), this);

    // Add static text
    HWND hText = CreateWindow(TEXT("STATIC"), m_Message.c_str(), WS_VISIBLE | WS_CHILD, padding, padding, width - 2 * padding, 20, hDlg, NULL,
                              GetModuleHandle(NULL), NULL);

    // Add buttons for each option
    for (size_t i = 0; i < m_Options.size(); ++i)
    {
        CreateWindow(TEXT("BUTTON"), m_Options[i].second.c_str(), WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, padding + i * (buttonWidth + padding), 50,
                     buttonWidth, buttonHeight, hDlg, (HMENU) (m_Options[i].first), GetModuleHandle(NULL), NULL);
    }

    // Show the dialog and wait for a response
    ShowWindow(hDlg, SW_SHOW);
    UpdateWindow(hDlg);

    MSG msg;
    int result = -1;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (msg.message == WM_COMMAND && msg.hwnd == hDlg)
        {
            result = LOWORD(msg.wParam);
            DestroyWindow(hDlg);
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return result;
}
}