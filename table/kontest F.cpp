// kontest F.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
int main()
{
    int m_row{}, m_col{}, row{}, col{}, q{};

    std::ifstream file{ "text.txt" };

    std::vector<std::string> table;
    std::vector<int> h;
    std::vector<int> w;

    file >> m_row >> m_col;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i{}; i < m_row; ++i)
    {
        std::string s;
        std::getline(file, s);
        table.push_back(s);
    }
    file >> row;
    for (int i{}; i < row; ++i)
    {
        int x{};
        file >> x;
        h.push_back(x);
    }
    file >> col;
    for (int i{}; i < col; ++i)
    {
        int x{};
        file >> x;
        w.push_back(x);
    }
    file >> q;

    std::string comand;
    const std::string merge{ "merge" };
    const std::string split{ "split" };

    int asci[256]{};
    for (int i{ 65 }, j{ 1 }; i < 91; ++i, ++j)
        asci[i] = j;

    while (q!=0)
    {
        file >> comand;
        --q;

        if (comand == merge)
        {
            std::string position_1, position_2;

            file >> position_1 >> position_2;           
            int Line_1{}, Line_2{}, column_1{}, column_2{};
            for (int i{}; i < position_1.size(); ++i)
            {
                if (64 < position_1.at(i) && position_1.at(i) < 91)
                {
                    column_1 = asci[position_1.at(i)] + i * 26;
                }
                else
                    Line_1 = std::stoi(&position_1.at(i));
            }
            for (int i{}; i < position_2.size(); ++i)
            {
                if (64 < position_2.at(i) && position_2.at(i) < 91)
                {
                    column_2 = asci[position_2.at(i)] + i * 26;
                }
                else
                    Line_2 = std::stoi(&position_2.at(i));
            }

            if (Line_1 > Line_2)
                std::swap(Line_1, Line_2);
            if (column_1 > column_2)
                std::swap(column_1, column_2);

            if (column_1 != column_2 && Line_1 == Line_2)
            {
                int w1{}, h1{}, num{};
                for (int i{}; i < column_1 - 1; ++i)
                    w1 += w.at(i)+1;
                for (int i{}; i< Line_1 - 1; ++i)
                    h1 += h.at(i) + 1;
               
                for (int i{column_1-1}; i < column_2; ++i)
                {
                    w1 += w.at(i)+1;
                    if (table.at(h1).at(w1) == '+' && table.at(h1 + 1).at(w1) == '|' && i+1!=column_2 )
                    {                             
                        ++num;
                        for (int j{0}; j < h.at(Line_1-1); ++j)
                            table.at(h1+1+ j).at(w1) = ' ';
                    }                                   
                }
                if (num == 0)
                {
                    std::cout << "Can not merge cell with itself" << std::endl;
                    continue;
                }
                else
                    std::cout << "Merged horizontally - aligned cells" << std::endl;
            }
            else if (column_1 == column_2 && Line_1 != Line_2)
            {
                int h1{};
                for (int i{}; i < Line_1 - 1; ++i)
                    h1 += h.at(i)+1;
                int w1{};
                for (int i{}; i < column_1 - 1; ++i)
                    w1 += w.at(i)+1;
                int num{};                
                for (int i{}; i < Line_2-Line_1; ++i)
                {
                    h1 = h.at(i) + 1;
                    for (int j{1}; j < w.at(column_1 - 1)+1; ++j)
                    {
                        if (table.at(h1).at(w1+j) == ' ')
                            break;
                        table.at(h1).at(w1+j) = ' ';
                        ++num;
                    }

                }
                if (num == 0)
                    std::cout << "Can not merge cell with itself" << std::endl;
                else
                    std::cout << "Merged vertically-aligned cells" << std::endl;
            }
            else
            {
                std::cout << "Can not merge unaligned cells" << std::endl;
                continue;
            }

            int w2{}, h2{};
            for (int i{}, j{}; i < m_row; ++i)
            {
                if (i == h2)
                {                    
                    if(i+1!=m_row)
                        h2 += h.at(j) + 1;
                    ++j;
                    
                    for (int z{}, k{}; z < table.at(i).size(); ++z)
                    {                       
                        std::cout << table.at(i).at(z);
                    }
                }
                else
                {
                    std::cout << table.at(i).at(0);
                    int set_w{};
                    for (int z{}; z < w.size(); ++z)
                    {
                        set_w = w2;
                        w2 += w.at(z) + 1;
                      if(z==0)
                        std::cout << std::setw(w2) << table.at(i).at(w2);
                      else
                      {
                          int x{ w2 - set_w };
                          std::cout << std::setw(x) << table.at(i).at(w2);
                      }
                    }
                }
                w2 = 0;
                std::cout << std::endl;
            }

        }
        else if (comand == split)
        {
            std::string pos;
            file >> pos;
            int strok{}, stolb{};
            for (int i{}; i < pos.size(); ++i)
            {
                if (64 < pos.at(i) && pos.at(i) < 91)
                {
                    stolb = asci[pos.at(i)] + i * 26;
                }
                else
                    strok = std::stoi(&pos.at(i));
            }
            int w1{ 0 }, num{};

            for (int i{}; i < stolb - 1; ++i)
                w1 += w.at(i)+1;
            if (table.at(strok * 2 - 1).at(w1) == '|' && table.at(strok * 2 - 1).at(w1 + w.at(stolb-1) == '|'))
            {
                std::cout << "Can not split elementary cell" << std::endl;
                continue;
            }
            else
            {
                int w1{};
                for (int i{}; i < w.size() - 1; ++i)
                {

                    w1 += w.at(i)+1;
                        table.at(strok * 2 - 1).at(w1) = '|';
                    ++num;
                }
            }
            ++num;
            std::cout << "Split onto " << num << " cells" << std::endl;
            int w2{}, h2{};

            for (int i{}, j{}; i < m_row; ++i)
            {
                if (i == h2)
                {
                    if (i + 1 != m_row)
                        h2 += h.at(j) + 1;
                    ++j;
                    for (int z{}; z < table.at(i).size(); ++z)
                        std::cout << table.at(i).at(z);
                }
                else
                {
                    std::cout << table.at(i).at(0);
                    int set_w{};
                    for (int z{}; z < w.size(); ++z)
                    {
                        set_w = w2;
                        w2 += w.at(z) + 1;
                        if (z == 0)
                            std::cout << std::setw(w2) << table.at(i).at(w2);
                        else
                        {
                            int x{ w2 - set_w };
                            std::cout << std::setw(x) << table.at(i).at(w2);
                        }
                    }
                }
                w2 = 0;
                std::cout << std::endl;
            }
        }

    } 
    file.close();
    return 0;
}

