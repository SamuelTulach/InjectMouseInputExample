#include <Windows.h>
#include <iostream>

enum InjectedInputMouseOptions
{
    Absolute = 32768,
    HWheel = 4096,
    LeftDown = 2,
    LeftUp = 4,
    MiddleDown = 32,
    MiddleUp = 64,
    Move = 1,
    MoveNoCoalesce = 8192,
    None = 0,
    RightDown = 8,
    RightUp = 16,
    VirtualDesk = 16384,
    Wheel = 2048,
    XDown = 128,
    XUp = 256
};

typedef struct _InjectedInputMouseInfo
{
    int DeltaX;
    int DeltaY;
    unsigned int MouseData;
    InjectedInputMouseOptions MouseOptions;
    unsigned int TimeOffsetInMilliseconds;
    void* ExtraInfo;
} InjectedInputMouseInfo;

typedef bool (WINAPI* InjectMouseInput_t)(InjectedInputMouseInfo* inputs, int count);

int main()
{
    const HMODULE user32 = LoadLibraryA("user32.dll");
    if (!user32)
    {
        printf("user32.dll failed to load!\n");
        return -1;
    }

    InjectMouseInput_t InjectMouseInput = reinterpret_cast<InjectMouseInput_t>(GetProcAddress(user32, "InjectMouseInput"));
    if (!InjectMouseInput)
    {
        printf("InjectMouseInput not found!\n");
        return -1;
    }

    for (int i = 0; i < 10000; i++)
    {
        InjectedInputMouseInfo info = { 0 };
        info.DeltaX = 5;
        info.DeltaY = 5;
        InjectMouseInput(&info, 1);
        Sleep(1);
    }

    

    return 0;
}
