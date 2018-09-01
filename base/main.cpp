#include "main.h"
#include "menu.h"
core::process  process("csgo.exe");
constexpr int o_localplayer         = 0xC6086C;
constexpr int o_health			 = 0xFC;
uintptr_t      clientdll;
void csgo()
{
	if (!process.open_process())
	{
		printf("process not found\n");
		system("pause");
		return;
	}
	clientdll = process.get_module("client_panorama.dll");
	auto localplayer = process.read<uintptr_t >(clientdll + o_localplayer);
	auto health = process.read<uintptr_t >(localplayer + o_health);

	if (health)
		printf("\n health %i", health);

	system("pause");
}
void main()
{
	auto running{ true };
	
	const ConsoleMenu menu{ "------\n",
		"invalid\n", ">>",
		{
			{ "read health", [&running] {  csgo(); } },
			{ "exit", [&running] { running = false; } }
		} };
	while (running) {
		std::system("cls");
		printf("hi admin", std::getenv("USERNAME"));
		menu();
	}


}