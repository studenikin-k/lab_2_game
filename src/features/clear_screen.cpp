#include "clear_screen.h"
#include <cstdlib>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // Предполагаем Unix-подобную систему (Linux, macOS)
    system("clear");
#endif
}
