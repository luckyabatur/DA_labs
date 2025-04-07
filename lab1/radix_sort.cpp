#include <stdio.h>


const int VALUE_LENGTH = 2049;
const int BASE_SIZE = 70;
const int DIGITS_COUNT = 10;
const int COUNTY_FIELD_SIZE = 3;
const int CITY_FIELD_SIZE = 5;
const int PHONE_FIELD_SIZE = 10;

enum class FieldType {COUNTRY, CITY, PHONE};

void CountingSort(unsigned int* mainArray, int digitsCount = DIGITS_COUNT){




})


void RadixSort(unsigned int* array, int arraySize = BASE_SIZE){



}

void MainRadixSort(PhoneNumber* array, FieldType field){
    int dopArray[DIGITS_COUNT];
    switch (field){



    }

}

struct PhoneNumber{
    unsigned int country;
    unsigned int city;
    unsigned int phone;
    char value[VALUE_LENGTH];
};

int main(){





    return 0;
}
