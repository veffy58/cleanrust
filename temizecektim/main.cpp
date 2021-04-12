#include <Windows.h>
#include <iostream>
#include "driver.h"
#include <string>
#include "offsets.h"
#include <iostream>
#include <string>
#include <sstream>
#include "xor.hpp"
#include "thread.h"

HANDLE memory_read = NULL, memory_write = NULL, memory_esp_write = NULL;
bool skid = true;
int main() {
	if (skid == true)
	{
		if (driver::open_memory_handles())
			std::cout << "[-] Shared memory handles opened successfully" << std::endl;
		else
		{
			std::cout << "[!] Shared memory handles failed to open" << std::endl;
			std::cin.get();
			return 0;
		}

		driver::get_process_id("RustClient.exe"); // RustClient.exe

		game_assembly = (uintptr_t)driver::get_module_base_address("GameAssembly.dll");
		unity_player = (uintptr_t)driver::get_module_base_address("UnityPlayer.dll");
		if (!game_assembly || !unity_player)
		{
			std::cout << "	[+] game assembly: " << std::hex << game_assembly << std::endl;
			std::cout << "	[+] unity player: " << std::hex << unity_player << std::endl;

			std::cout << "[!] failed to aquire base address..." << std::endl;
			std::cin.get();
			return 0;
		}

		std::cout << "[+] aquired base address and PID" << std::endl;
		std::cout << "	[+] game assembly: " << std::hex << game_assembly << std::endl;
		std::cout << "	[+] unity player: " << std::hex << unity_player << std::endl;

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread::features, 0, 0, 0);

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (true)
		{
			if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
				continue;
			}

		}


		std::cin.get();
		return 1;
	}
}

