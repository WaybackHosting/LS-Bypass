#include <iostream>
#include "memcury.h"
bool Hook() {
	return false;
}

void Main() {
	Memcury::VEHHook::Init();
	void* Func = Memcury::Scanner::FindStringRef(L"Reason for Showing/Hiding LoadingScreen is unknown!").ScanFor({ 48, 89 }, false).GetAs<void*>();
	Memcury::VEHHook::AddHook(Func, Hook);

	while (true)
	{
		if (GetAsyncKeyState(VK_F9) & 0x1) {
			std::cout << "Force Drop Loading Screen: " << ((Memcury::VEHHook::ToggleHook(Func)) ? "True" : "False");
			Sleep(1000);
		}
		Sleep(1000 / 30);
	}
}

bool DllMain(void* pModule, int call_reason, void* pReserved)
{
	if (call_reason == 1) {
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Main), pModule, 0, nullptr);
	}

	return true;
}