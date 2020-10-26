
#include<fstream>
#include<string>
#include <iostream>


int main()
{
   
    std::ios::sync_with_stdio(false);

    std::ifstream File{ "file_to_decrypt.txt" };
    int n{}, m{}, type{};
    std::string input_data;

    std::getline(File, input_data, ' ');
    n = std::stoi(input_data);
    std::getline(File, input_data, ' ');
    m = std::stoi(input_data);
    std::getline(File, input_data, '\n');
    type = std::stoi(input_data);

    int* input_numbers = new int[n];
    int* coding_numbers = new int[m];
    int** references_to_coding_numbers = new int* [m + 1];

    for (int i{}; i < n; ++i)       // заполнение массива символами шифруемого текста
    {
        if (i == n - 1)            
            std::getline(File, input_data, '\n');
        else
            std::getline(File, input_data, ' ');
        input_numbers[i] = std::stoi(input_data);
    }
    for (int i{}; i < m; ++i)       // заполнение массива кодировки и массива ссылок  
    {
        coding_numbers[i] = i + 1;
        references_to_coding_numbers[i + 1] = &coding_numbers[i];
    } 

    if (type == 1)                  // шифрование
    {
        for (int i{}; i < n; ++i)
        {
            int  num{coding_numbers[input_numbers[i] - 1] };                                    // зашифрованное число
            std::cout <<num << " ";
            //------------------------------------------------------------------------------------ начало алгоритма шифровки
            references_to_coding_numbers[0] = references_to_coding_numbers[num];
            for (int j{ num - 1 }; j != 0; j = j - 1)
            {
                *references_to_coding_numbers[j] = *references_to_coding_numbers[j] + 1;        // увелечение числа позиции на 1
                references_to_coding_numbers[j + 1] = references_to_coding_numbers[j];          // смещение ссылок на 1 позицию вперед
            }
            references_to_coding_numbers[1] = references_to_coding_numbers[0];
            *references_to_coding_numbers[1] = 1;
            //------------------------------------------------------------------------------------ конец алгоритма шифровки
        }
    }
    else                            // расшифровка
    {
         for (int i{}; i < n; ++i)
         {
             references_to_coding_numbers[0] = references_to_coding_numbers[input_numbers[i]];
             std::cout << *references_to_coding_numbers[input_numbers[i]]<<" ";                 // вывод расшифрованного числа
              //---------------------------------------------------------------------------------- начало алгоритма расшифровки
             for (int j{ input_numbers[i] -1}; j != 0; --j)
                 references_to_coding_numbers[j + 1] = references_to_coding_numbers[j];
             references_to_coding_numbers[1] = references_to_coding_numbers[0];
             //----------------------------------------------------------------------------------- конец алгоритма расшифровки
         }     
    }
    File.close();
    return 0;
}