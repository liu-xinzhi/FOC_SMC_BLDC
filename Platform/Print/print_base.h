#ifndef FOC_SMC_BLDC_PRINT_BASE_H
#define FOC_SMC_BLDC_PRINT_BASE_H

#include <cstdint>
#include <cstring>
#include <string>

#define F (char*)

class Print
{
public:

    void println(float temp);
    void println(char * temp);
    void println(float temp,int accuracy);
    void println();
    void print(char * temp);
    void print(char temp);
    void print(float temp, int accuracy);
    void print(std::string str,uint8_t num);
private:

};

#endif //FOC_SMC_BLDC_PRINT_BASE_H
