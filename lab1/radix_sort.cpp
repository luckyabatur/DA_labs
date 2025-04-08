#include <stdio.h>


const int VALUE_LENGTH = 2049;
const int BASE_SIZE = 70; //бред
const int DIGITS_COUNT = 10;
const int COUNTY_FIELD_SIZE = 3;
const int CITY_FIELD_SIZE = 5;
const int PHONE_FIELD_SIZE = 10;
const int BITS_COUNT = 8;
const unsigned int MASK = 255;

enum class FieldType {COUNTRY, CITY, PHONE};


struct PhoneNumber{
    unsigned int country;
    unsigned int city;
    unsigned int phone;
    char value[VALUE_LENGTH];
};

void CountingSort(unsigned int* array, PhoneNumber* baseArray,
                  const int arraySize = BASE_SIZE,
                  const int digitsCount = DIGITS_COUNT){
    int dopArray[BASE_SIZE] {};

}




void RadixSort(unsigned int* array, PhoneNumber* baseArray,
               int arraySize = BASE_SIZE){
    for (int i = 0; i < sizeof(int)/BITS_COUNT; i++){
        unsigned int countingArray[BASE_SIZE];
        for (int j = 0; j < BASE_SIZE; j++){
            countingArray[j] = array[j] & MASK;
            countingArray[j] << BITS_COUNT;
        }
        CountingSort(countingArray, baseArray);
    }
}

void MainRadixSort(PhoneNumber* array, FieldType field){
    int dopArray[DIGITS_COUNT];
    switch (field){



    }

}



int main(){





    return 0;
}
