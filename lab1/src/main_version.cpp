#include <iostream>
#include <cstring>


const int VALUE_LENGTH = 2049;
const int NUMBERS_COUNT = 256;
const int BITS_COUNT = 8;
const int BUFFER_SIZE = 2085;
const int PHONE_SIZE = 20;
const unsigned long long MASK = 255;


template <typename T>
class TVector{
    int capacity{1};
    int size{};
    T *data{nullptr};

public:
    TVector() = default;

    TVector& operator=(TVector&& right) noexcept
    {
        if (this == &right) return *this;
        delete[] data;
        capacity = right.capacity;
        size = right.size;
        data = right.data;
        right.data = nullptr;

        return *this;
    }

    void Resize(){
        T* newData = new T[capacity *= 2];
        for (int i = 0; i < size; i++)
            newData[i] = std::move(data[i]);
        delete [] data;
        data = newData;
    }

    void SetData(T* array, int arraySize){
        delete [] data;
        size = capacity = arraySize;
        data = new T[arraySize];
        for (int i = 0; i < arraySize; i++){
            data[i] = array[i];
        }
    }

    void PushBack(T& element){
        if (size == capacity || size == 0){
            Resize();
        }

        data[size] = std::move(element);
        size++;
    }

    int GetSize(){
        return size;
    }

    T* GetData(){
        return data;
    }

    T& operator[](int index){
        return data[index];
    }

    ~TVector(){
        delete[] data;
    }
};


struct TPhoneNumber{
    unsigned int country;
    unsigned int city;
    unsigned long long phone;
    char outputString[PHONE_SIZE];
    TVector<char> value;

    TPhoneNumber& operator=(TPhoneNumber&& right) noexcept
    {
        if (this == &right) return *this;
        country = right.country;
        city = right.city;
        phone = right.phone;
        for (int i = 0; i < PHONE_SIZE; i++){
            outputString[i] = right.outputString[i];
        }
        value = std::move(right.value);

        return *this;
    }
};


void CountingSort(unsigned long long* array, int* resultArray,
                  const int &arraySize,
                  const int &numbersCount = NUMBERS_COUNT)
{
    unsigned char maskArray[arraySize];
    for (int i = 0; i < arraySize; i++){
        maskArray[i] = array[i] & MASK;
    }
    int copyResultArray[arraySize];
    unsigned long long copyArray[arraySize];
    unsigned int dopArray[numbersCount];
    for (int i = 0; i < numbersCount; i++) {
        dopArray[i] = 0;
    }
    for (int i = 0; i < arraySize; i++) {
        ++dopArray[maskArray[i]];
    }
    for (int i = 1; i < numbersCount; i++) {
        dopArray[i] = dopArray[i] + dopArray[i - 1];
    }
    for (int i = arraySize - 1; i >= 0; i--) {
        copyResultArray[dopArray[maskArray[i]] - 1] = resultArray[i];
        copyArray[dopArray[maskArray[i]] - 1] = array[i];
        --dopArray[maskArray[i]];
    }
    for (int i = 0; i < arraySize; i++) {
        resultArray[i] = copyResultArray[i];
        array[i] = copyArray[i];
    }
}


void RadixSort(unsigned long long* array, int* resultArray,
               const int &arraySize){
    for (int i = 0; i < sizeof(unsigned long long); i++){
        CountingSort(array, resultArray, arraySize);
        for (int j = 0; j < arraySize; j++){
            array[j] = array[j] >> BITS_COUNT;
        }
    }
}


int main(){
    TVector<TPhoneNumber> baseArray;
    TPhoneNumber element;
    char buffer[BUFFER_SIZE];
    char bufferValue[VALUE_LENGTH];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (sscanf(buffer, "+%u-%u-%llu %2048s",
                   &element.country,
                   &element.city,
                   &element.phone,
                   bufferValue) == 4)
        {
            element.value.SetData(bufferValue, strlen(bufferValue) + 1);
            int pos = strchr(buffer, '\t') - buffer;
            buffer[pos] = 0;
            strcpy(element.outputString, buffer);
            baseArray.PushBack(element);
        }
    }
    int length = baseArray.GetSize();
    unsigned long long dopArray[length];
    int resultArray[length];

    for (int i = 0; i < length; i++){
        dopArray[i] = baseArray[i].phone;
        resultArray[i] = i;
    }
    RadixSort(dopArray, resultArray, length);
    for (int i = 0; i < length; i++){
        dopArray[i] = baseArray[resultArray[i]].city;
    }
    RadixSort(dopArray, resultArray, length);
    for (int i = 0; i < length; i++){
        dopArray[i] = baseArray[resultArray[i]].country;
    }
    RadixSort(dopArray, resultArray, length);


    for (int i = 0; i < length; i++){
        printf("%s\t%s\n", baseArray[resultArray[i]].outputString, baseArray[resultArray[i]].value.GetData());
    }

    return 0;
}