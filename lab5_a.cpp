#include <Windows.h>

class WindowHandler {
public:
    virtual LRESULT HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};

class CreateHandler : public WindowHandler {
public:
    LRESULT HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override {
        // Обработка сообщения WM_CREATE
        return 0;
    }
};

class PaintHandler : public WindowHandler {
public:
    LRESULT HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override {
        // Обработка сообщения WM_PAINT
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Нарисуйте что-то на окне

        EndPaint(hWnd, &ps);
        return 0;
    }
};

class CloseHandler : public WindowHandler {
public:
    LRESULT HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override {
        // Обработка сообщения WM_CLOSE
        DestroyWindow(hWnd);
        return 0;
    }
};

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    WindowHandler* handler = reinterpret_cast<WindowHandler*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    if (handler) {
        return handler->HandleMessage(hWnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Регистрация класса окна
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"ClassName";
    RegisterClass(&wc);

    // Создание окна
    HWND hWnd = CreateWindow(
        L"ClassName",            // Имя класса окна
        L"Window Title",         // Заголовок окна
        WS_OVERLAPPEDWINDOW,     // Стиль окна
        CW_USEDEFAULT,           // Позиция X окна
        CW_USEDEFAULT,           // Позиция Y окна
        CW_USEDEFAULT,           // Ширина окна
        CW_USEDEFAULT,           // Высота окна
        nullptr,                 // Дескриптор родительского окна
        nullptr,                 // Дескриптор меню окна
        hInstance,               // Дескриптор экземпляра приложения
        nullptr                  // Дополнительные данные окна
    );

    CreateHandler createHandler;
    PaintHandler paintHandler;
    CloseHandler closeHandler;

    SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&createHandler));

    // Отображение окна
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Основной цикл сообщений
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}