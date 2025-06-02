#include "../../include/all_headers.h"
#include <cstdlib>

// функция для очистки экрана
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // Предполагаем Unix-подобную систему (Linux, macOS)
    system("clear");
#endif
}
