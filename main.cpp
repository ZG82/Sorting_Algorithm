#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

// 冒泡排序
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 选择排序
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// 插入排序
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 快速排序的分区函数
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// 快速排序
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 归并排序的合并函数
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// 归并排序
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 从文件读取数据
std::vector<int> readDataFromFile(const char* filename) {
    std::vector<int> data;
    std::ifstream inFile(filename);
    int num;
    while (inFile >> num) {
        data.push_back(num);
    }
    inFile.close();
    return data;
}
static int count = 0;
// 将排序后的数据写回文件
void writeDataToFile(const char* filename, const std::vector<int>& arr) {
    std::ofstream outFile(filename);
    for (int num : arr) {
        count++;
        outFile << num <<" ";
        if (count >= 50){
            outFile << std::endl;
            count = 0;
        }
    }
    outFile.close();
}

int main() {
    const char* filename = "C:\\Users\\ZGLNC\\Desktop\\data.txt";
    std::vector<int> data = readDataFromFile(filename);

    std::cout << "请选择排序算法：" << std::endl;
    std::cout << "1. 冒泡排序" << std::endl;
    std::cout << "2. 选择排序" << std::endl;
    std::cout << "3. 插入排序" << std::endl;
    std::cout << "4. 快速排序" << std::endl;
    std::cout << "5. 归并排序" << std::endl;

    int choice;
    std::cin >> choice;
    
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "running..."<<std::endl;
    switch (choice) {
    case 1:
        bubbleSort(data);
        break;
    case 2:
        selectionSort(data);
        break;
    case 3:
        insertionSort(data);
        break;
    case 4:
        quickSort(data, 0, data.size() - 1);
        break;
    case 5:
        mergeSort(data, 0, data.size() - 1);
        break;
    default:
        std::cout << "无效的选择，请输入 1 - 5 之间的数字。" << std::endl;
        return 1;
    }
    std::cout << "finish";
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    const char* filename1 = "date.txt";
    writeDataToFile(filename1, data);

    std::cout << "排序完成，耗时: " << duration.count() << " 毫秒。" << std::endl;

    return 0;
}
