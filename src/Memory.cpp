#include "../include/Memory.h"

namespace Cypher {
    namespace Memory {
        
        // Khởi tạo các giá trị mặc định
        MemEngine::MemEngine() : processId(0), hProcess(nullptr) {}

        // Tự động đóng handle khi hủy object để tránh rò rỉ bộ nhớ (Memory Leak)
        MemEngine::~MemEngine() {
            Detach();
        }

        // Logic tìm kiếm và gắn kết (Attach) vào tiến trình mục tiêu
        bool MemEngine::Attach(const std::wstring& processName) {
            HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            if (hSnapshot == INVALID_HANDLE_VALUE) return false;

            PROCESSENTRY32W pe32;
            pe32.dwSize = sizeof(PROCESSENTRY32W);

            if (Process32FirstW(hSnapshot, &pe32)) {
                do {
                    if (processName == pe32.szExeFile) {
                        processId = pe32.th32ProcessID;
                        // Mở tiến trình với các quyền truy cập bộ nhớ ảo cơ bản
                        hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processId);
                        CloseHandle(hSnapshot);
                        return hProcess != nullptr;
                    }
                } while (Process32NextW(hSnapshot, &pe32));
            }

            CloseHandle(hSnapshot);
            return false;
        }

        // Ngắt kết nối và giải phóng tài nguyên
        void MemEngine::Detach() {
            if (hProcess) {
                CloseHandle(hProcess);
                hProcess = nullptr;
                processId = 0;
            }
        }
    }
}
