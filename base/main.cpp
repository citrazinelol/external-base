#include "main.h"
core::process  process("csgo.exe");
//constexpr int o_localplayer         = 0xC6086C;
//constexpr int o_health			 = 0xFC;
uintptr_t      clientdll;

void main()
{   
	if (!process.open_process())
	{
		printf("process not found\n");
		system("pause");
		return;
	}

	clientdll			= process.get_module("client_panorama.dll");
	auto o_localplayer  = process.read<uintptr_t >(clientdll + 0xC6086C);
	auto health			= process.read<uintptr_t >(o_localplayer + 0xFC);

	if (health )
		printf("\n health %i", health);

	system("pause");

}