#pragma once
#include"includes.h"


namespace core
{
	class memory
	{
		
	public:
		
		
		uintptr_t find(const std::string& pat, uintptr_t start, size_t len) {
			std::vector< std::pair< uint8_t, bool > >	pattern{ };
			std::istringstream							stream{ pat };
			std::string									w{ };

			
			auto scan_start = reinterpret_cast<uint8_t*>(start);
			auto scan_end = scan_start + len;

			
			do {
				// anti-cb
				if (w.empty())
					continue;

				
				if (w[0] == '?')
					pattern.push_back({ 0, true });
				else
					pattern.push_back({ uint8_t(std::strtoul(w.c_str(), 0, 16)), false });
			} while (std::getline(stream, w, ' '));

			
			auto result = std::search(scan_start, scan_end, pattern.begin(), pattern.end(),
				[&](const uint8_t b, const std::pair< uint8_t, bool > p) {
				
				return b == p.first || p.second;
			}
			);

			
			if (result == scan_end)
				return { };

			return { reinterpret_cast<uintptr_t>(result) };
		}
		 uintptr_t find(uintptr_t mod, const std::string& pat, size_t len = 0) {
			if (!mod)
				return 0;

			if (!len)
				len = sizeof(mod);

			return find(pat, mod, len);
		}
		template < typename t > void write(uintptr_t address, const t& value, HANDLE base) {
			WriteProcessMemory(base, reinterpret_cast<LPVOID>(address), &value, sizeof(t), nullptr);
		}
		template < typename t > t read(uintptr_t address, HANDLE base) {t buffer{ };
		ReadProcessMemory(base, reinterpret_cast<LPVOID>(address), &buffer, sizeof(t), nullptr);
		return buffer;
		}

		int get_process_id(LPSTR process_name)
		{
			HANDLE h_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

			if (h_snapshot == INVALID_HANDLE_VALUE)
			{
				printf("[!] CreateToolhelp32Snapshot, GetLastError( ) = %d\n", GetLastError());
				return NULL;
			}

			PROCESSENTRY32 pe = { 0 };
			pe.dwSize = sizeof(PROCESSENTRY32);

			for (BOOL success = Process32First(h_snapshot, &pe); success == TRUE; success = Process32Next(h_snapshot, &pe))
			{
				if (strcmp(process_name, pe.szExeFile) == 0)
				{
					CloseHandle(h_snapshot);
					return pe.th32ProcessID;
				}
			}

			CloseHandle(h_snapshot);
			return NULL;
		}
		std::pair<HANDLE, int> setup_process(LPSTR process_name)
		{
			unsigned int pid = NULL;
			while (!pid)
				pid = get_process_id(process_name);
			printf("[+] process id 0x%X\n", pid);
			HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

			return std::pair<HANDLE, int>(h_process, pid);
		}
	};
}