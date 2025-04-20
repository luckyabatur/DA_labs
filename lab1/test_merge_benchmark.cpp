#include <iostream>
#include <cstring>
#include <chrono>


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


void merge(unsigned long long arr[], int resultArray[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    unsigned long long* leftArr = new unsigned long long[n1];
    unsigned long long* rightArr = new unsigned long long [n2];
    unsigned int* resLeft = new unsigned int[n1];
    unsigned int* resRight = new unsigned int[n2];

    for (i = 0; i < n1; i++){
        leftArr[i] = arr[left + i];
        resLeft[i] = resultArray[left + i];
    }
    for (j = 0; j < n2; j++){
        rightArr[j] = arr[mid + 1 + j];
        resRight[j] = resultArray[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            resultArray[k] = resLeft[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            resultArray[k] = resRight[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        resultArray[k] = resLeft[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        resultArray[k] = resRight[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
    delete[] resLeft;
    delete[] resRight;
}

void mergeSort(unsigned long long arr[], int resultArray[], int left, int right) {
    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, resultArray, left, mid);
        mergeSort(arr, resultArray, mid + 1, right);

        merge(arr, resultArray, left, mid, right);
    }
}


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


//void CountingSort(unsigned long long* array, int* resultArray,
//                  const int &arraySize,
//                  const int &numbersCount = NUMBERS_COUNT)
//{
//    unsigned int maskArray[arraySize];
//    for (int i = 0; i < arraySize; i++){
//        maskArray[i] = array[i] & MASK;
//    }
//    int copyResultArray[arraySize];
//    unsigned long long copyArray[arraySize];
//    unsigned int dopArray[numbersCount];
//    for (int i = 0; i < numbersCount; i++) {
//        dopArray[i] = 0;
//    }
//    for (int i = 0; i < arraySize; i++) {
//        ++dopArray[maskArray[i]];
//    }
//    for (int i = 1; i < numbersCount; i++) {
//        dopArray[i] = dopArray[i] + dopArray[i - 1];
//    }
//    for (int i = arraySize - 1; i >= 0; i--) {
//        copyResultArray[dopArray[maskArray[i]] - 1] = resultArray[i];
//        copyArray[dopArray[maskArray[i]] - 1] = array[i];
//        --dopArray[maskArray[i]];
//    }
//    for (int i = 0; i < arraySize; i++) {
//        resultArray[i] = copyResultArray[i];
//        array[i] = copyArray[i];
//    }
//}


//void RadixSort(unsigned long long* array, int* resultArray,
//               const int &arraySize){
//    for (int i = 0; i < sizeof(unsigned long long); i++){
//        CountingSort(array, resultArray, arraySize);
//        for (int j = 0; j < arraySize; j++){
//            array[j] = array[j] >> BITS_COUNT;
//        }
//    }
//}


int main(){


//    FILE* fd = fopen("./output.txt", "r");
    FILE* fd = fopen("./big.txt", "r");

    TVector<TPhoneNumber> baseArray;
    TPhoneNumber element;
    char buffer[BUFFER_SIZE];
    char bufferValue[VALUE_LENGTH];
    while (fgets(buffer, sizeof(buffer), fd)) {
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
    unsigned long long* dopArray = new unsigned long long[length];
    int* resultArray = new int[length];

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < length; i++){
        dopArray[i] = baseArray[i].phone;
        resultArray[i] = i;
    }
    mergeSort(dopArray, resultArray, 0, length - 1);
    for (int i = 0; i < length; i++){
        dopArray[i] = baseArray[resultArray[i]].city;
    }
    mergeSort(dopArray, resultArray, 0, length - 1);
    for (int i = 0; i < length; i++){
        dopArray[i] = baseArray[resultArray[i]].country;
    }
    mergeSort(dopArray, resultArray, 0, length - 1);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

//    for (int i = 0; i < length; i++){
//        printf("%s\t%s\n", baseArray[resultArray[i]].outputString, baseArray[resultArray[i]].value.GetData());
//    }

    std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;

    delete[] dopArray;
    delete[] resultArray;


    return 0;
}