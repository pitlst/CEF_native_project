#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"
#include "source/simple_app.h"
#include "source/simple_handler.h"

#include <iostream>
#include "windows.h"

// 重载的windows应用入口，应微软的要求
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    // 避免编译器关于未引用参数的警告
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // 将命令行参数提供给CEF
    CefMainArgs main_args(hInstance);

    // CEF应用程序有多个共享的子进程（渲染、GPU等）相同可执行文件。 该函数检查命令行，如果是
    // 一个子进程，执行适当的逻辑。
    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0)
    {
        return exit_code;
    }
    // 使用该方法解析对应的命令行参数
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());
    // 指定CEF全局设置
    CefSettings settings;
    settings.no_sandbox = true;

    CefRefPtr<SimpleApp> app(new SimpleApp);

    // 初始化CEF
    CefInitialize(main_args, settings, app.get(), nullptr);
    // 运行 CEF 消息循环。 这将阻塞直到 CefQuitMessageLoop() 被调用
    CefRunMessageLoop();
    // 关闭CEF
    CefShutdown();

    return 0;
}