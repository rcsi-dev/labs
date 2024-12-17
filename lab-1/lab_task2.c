#include <stdio.h>
#include <string.h>

struct microcontroller {
    char name[50];
    char core_name[16];
    int flash_memory;  // KB
    int ram;           // KB
    float clock_speed; // MHz
};

void print_microcontroller(struct microcontroller mc) {
    printf("Name of the MC: %s\n", mc.name);
    printf("Name of the core: %s\n", mc.core_name);
    printf("Amount of flash memory: %d KB\n", mc.flash_memory);
    printf("Amount of RAM: %d KB\n", mc.ram);
    printf("MC clock speed: %.1f MHz\n", mc.clock_speed);
}

int main() {
    struct microcontroller stm32f407 = {
        "STM32F407VG",
        "Cortex-M4F",
        1024,
        192,
        168.0
    };

    printf("Original data:\n");
    print_microcontroller(stm32f407);
    printf("\n");

    stm32f407.flash_memory = stm32f407.flash_memory * 2;
    stm32f407.ram = stm32f407.ram * 2;
    stm32f407.clock_speed = stm32f407.clock_speed * 2;

    printf("Modified data (3 last specs multiplied by 2):\n");
    print_microcontroller(stm32f407);

    return 0;
}