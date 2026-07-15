#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

namespace Cypher {
    namespace Memory {
        class MemEngine {
        private:
            DWORD processId;
            HANDLE hProcess;

        public:
            // Khởi tạo và Hủy
            MemEngine();
            ~MemEngine();

            // Gắn kết vào tiến trình
            bool Attach(const std::wstring& processName);
            void Detach();

            // Đọc bộ nhớ (Sử dụng Template để tối ưu hóa type-casting)
            template <typename T>
            T Read(uintptr_t address) {
                T buffer;
                ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), nullptr);
                return buffer;
            }

            // Ghi bộ nhớ
            template <typename T>
            bool Write(uintptr_t address, const T& value) {
                return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), nullptr);
            }
        };
    }
}
