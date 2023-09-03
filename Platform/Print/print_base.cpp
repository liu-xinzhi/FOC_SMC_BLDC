#include "print_base.h"
#include <cstdio>

void Print::println(float temp) {
    printf("%f\r\n", temp);
}

void Print::println(char* temp) {
    printf("%s\r\n", temp);
}

void Print::println(float temp,int accuracy) {
    switch (accuracy) {
        case 1:
            printf("%.1f\r\n", temp);
            break;
        case 2:
            printf("%.2f\r\n", temp);
            break;
        case 3:
            printf("%.3f\r\n", temp);
            break;
        case 4:
            printf("%.4f\r\n", temp);
            break;
        default:
            printf("%.2f\r\n", temp);
            break;
    }
}

void Print::println() {

}

void Print::print(char* temp) {
    printf("%s", temp);
}

void Print::print(char temp) {
    printf("%c", temp);
}

void Print::print(float temp,int accuracy)
{
    switch (accuracy) {
        case 1:
            printf("%.1f\r\n", temp);
            break;
        case 2:
            printf("%.2f\r\n", temp);
            break;
        case 3:
            printf("%.3f\r\n", temp);
            break;
        case 4:
            printf("%.4f\r\n", temp);
            break;
        default:
            printf("%.2f\r\n", temp);
            break;
    }
}

void Print::print(std::string str,uint8_t num) {
    char temp[num];
    temp[num]={0};
    strcpy(temp,str.c_str());
    printf("%s",temp);
}
