#pragma once
#include "Memory.h"
#include <string>
#include <vector>
#include <cstdint>

namespace Cypher {
    namespace Scanner {
        class PatternScanner {
        private:
            Memory::MemEngine* memEngine;

        public:
            // Khởi tạo Scanner, liên kết trực tiếp với Core Engine
            PatternScanner(Memory::MemEngine* engine);
            ~PatternScanner();

            // Thuật toán phân tích cú pháp chuỗi byte dạng IDA (ví dụ: "48 8B 05 ? ? ? ?")
            // và tìm kiếm trong vùng nhớ của module mục tiêu
            uintptr_t FindPattern(const std::wstring& moduleName, const std::string& pattern);
        };
    }
}
