#pragma once
#include "includes.h"
namespace core {
	class process {

		HANDLE		base_{ };
		int			id_{ };
		std::string	name_{ };

	public:
		process(std::string name) : name_(name) { };

		bool open_process() {
			PROCESSENTRY32	proc_entry;
			HANDLE t32_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			proc_entry.dwSize = sizeof(proc_entry);

			for (Process32First(t32_snapshot, &proc_entry); Process32Next(t32_snapshot, &proc_entry);)
			{
				if (!std::string(proc_entry.szExeFile).compare(name_)) {
					CloseHandle(t32_snapshot);
					id_ = proc_entry.th32ProcessID;
					base_ = OpenProcess(PROCESS_ALL_ACCESS, 0, id_);

					return true;
				}
			}

			return false;
		}

		uintptr_t get_module(std::string name) {

			MODULEENTRY32	mod_entry;
			if (!id_) return uintptr_t{ };

			HANDLE t32_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, id_);
			mod_entry.dwSize = sizeof(mod_entry);

			for (Module32First(t32_snapshot, &mod_entry); Module32Next(t32_snapshot, &mod_entry);)
			{
				if (!name.compare(mod_entry.szModule)) {
					CloseHandle(t32_snapshot);
					printf("module %s:\t0x%08x\n", mod_entry.szModule, mod_entry.modBaseAddr);
					return uintptr_t(mod_entry.modBaseAddr);
				}
			}

			return uintptr_t{ };
		}

		template < typename t > void write(uintptr_t address, const t& value) {
			WriteProcessMemory(base_, reinterpret_cast<LPVOID>(address), &value, sizeof(t), nullptr);
		}

		template < typename t > t read(uintptr_t address) {
			t buffer{ };
			ReadProcessMemory(base_, reinterpret_cast<LPVOID>(address), &buffer, sizeof(t), nullptr);
			return buffer;
		}


	};
}