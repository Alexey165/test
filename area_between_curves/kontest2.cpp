// kontest2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<fstream>
#include<string>
#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>


struct Func_num
{
    double a;
    double b;
    double c;
    Func_num(double&a, double&b, double&c):a{a},b{b},c{c}{}
};

int main()
{   
    std::ios::sync_with_stdio(false);
    std::ifstream FP{"Text.txt"};
    int n{}, m{};                                 
    std::string line;     
    std::getline(FP,line,' ');
    n = std::stoi(line);
    std::getline(FP, line, '\n');
    m = std::stoi(line);
    
    std::vector<double> li;          
    std::vector<Func_num> vec_F_a_b_c; 
    for (int i{}; i < n + 1; ++i)
    {    
        if(i==n)
            std::getline(FP, line, '\n');
        else
            std::getline(FP, line,' ');     
        li.push_back(std::stod(line));
    }
    for (int i{}; i < n; ++i)
    {
        double a{}, b{}, c{};
        std::getline(FP, line, ' ');
        a = std::stod(line);
        std::getline(FP, line, ' ');
        b = std::stod(line); 
        std::getline(FP, line, '\n');
        c = std::stod(line);
        vec_F_a_b_c.emplace_back(a, b, c);       
    }   
    std::vector<double> mi;                   
    std::vector<Func_num> vec_G_a_b_c;        
    for (int i{}; i < m + 1; ++i)
    {
        if (i == n)
            std::getline(FP, line, '\n');
        else
            std::getline(FP, line, ' ');
        mi.push_back(std::stod(line));
    }
    
    for (int i{}; i < m; ++i)
    {
        double a{}, b{}, c{};
        std::getline(FP, line, ' ');
        a = std::stod(line);
        std::getline(FP, line, ' ');
        b = std::stod(line);
        std::getline(FP, line, '\n');
        c = std::stod(line);
        vec_G_a_b_c.emplace_back(a, b, c);
        std::getline(FP, line, '\n');
    }
    double result{};
    if (n > m)
    n = m;
    for (int i{}; i < n; ++i)
    {
        int D{};
        double x1{}, x2{};
        D = pow((vec_F_a_b_c[i].b - vec_G_a_b_c[i].b), 2) - 4 * ((vec_F_a_b_c[i].a) - (vec_G_a_b_c[i].a)) * ((vec_F_a_b_c[i].c) - (vec_G_a_b_c[i].c));
        if (D > 0)
        {
            x1 = (-((vec_F_a_b_c[i].b) - (vec_G_a_b_c[i].b)) - sqrt(D)) / (2 * ((vec_F_a_b_c[i].a) - (vec_G_a_b_c[i].a)));
            x2 = (-((vec_F_a_b_c[i].b) - (vec_G_a_b_c[i].b)) + sqrt(D)) / (2 * ((vec_F_a_b_c[i].a) - (vec_G_a_b_c[i].a)));
            if (
                (x1 == li[i] && x2 == li[i + 1]) ||
                ((x1<li[i] || x1>li[i + 1]) && (x2<li[i] || x2>li[i + 1])) ||
                ((x1 == li[i] || x1 == li[i + 1]) && (x2<li[i] || x2>li[i + 1])) ||
                ((x2 == li[i] || x2 == li[i + 1]) && (x1<li[i] || x1>li[i + 1])))
            {
                double result_f{}, result_g{};
                result_f = (vec_F_a_b_c[i].a) * ((pow(li[i + 1], 3) - pow(li[i], 3)) / 3) + (vec_F_a_b_c[i].b) * ((pow(li[i + 1], 2) - pow(li[i], 2)) / 2) + (vec_F_a_b_c[i].c * (li[i + 1] - li[i]));
                result_g = (vec_G_a_b_c[i].a) * ((pow(li[i + 1], 3) - pow(li[i], 3)) / 3) + (vec_G_a_b_c[i].b) * ((pow(li[i + 1], 2) - pow(li[i], 2)) / 2) + (vec_G_a_b_c[i].c * (li[i + 1] - li[i]));
                result += abs(result_f - result_g);
            }
            else if ((li[i] < x1 && x1 < li[i + 1]) && (li[i] < x2 && x2 < li[i + 1]))
            {
                double result_f{}, result_g{};
                result_f = (vec_F_a_b_c[i].a) * ((pow(x1, 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(x1, 2.0) - pow(li[i], 2.0)) / 2.0) + (vec_F_a_b_c[i].c * (x1 - li[i]));
                result_g = (vec_G_a_b_c[i].a) * ((pow(x1, 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(x1, 2.0) - pow(li[i], 2.0)) / 2.0) + (vec_G_a_b_c[i].c * (x1 - li[i]));
                result += abs(result_f - result_g);
                result_f = (vec_F_a_b_c[i].a) * ((pow(x2, 3.0) - pow(x1, 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(x2, 2.0) - pow(x1, 2.0)) / 2.0) + (vec_F_a_b_c[i].c * (x2 - x1));
                result_g = (vec_G_a_b_c[i].a) * ((pow(x2, 3.0) - pow(x1, 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(x2, 2.0) - pow(x1, 2.0)) / 2.0) + (vec_G_a_b_c[i].c * (x2 - x1));
                result += abs(result_f - result_g);               
                result_f = (vec_F_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(x2, 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(x2, 2.0)) / 2.0) + ((vec_F_a_b_c[i].c) * (li[i + 1] - x2));
                result_g = (vec_G_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(x2, 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(x2, 2.0)) / 2.0) + (vec_G_a_b_c[i].c * (li[i + 1] - x2));
                result += abs(result_f - result_g);
                
            }
            else if ((li[i] < x1 && x1 < li[i + 1]) && (x2 > li[i + 1] || x2 < li[i]))
            {
                double result_f{}, result_g{};
                result_f = (vec_F_a_b_c[i].a) * ((pow(x1, 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(x1, 2.0) - pow(li[i], 2.0)) / 2.0) + ((vec_F_a_b_c[i].c) * (x1 - li[i]));
                result_g = (vec_G_a_b_c[i].a) * ((pow(x1, 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(x1, 2.0) - pow(li[i], 2.0)) / 2.0) + (vec_G_a_b_c[i].c * (x1 - li[i]));
                result += abs(result_f - result_g);              
                result_f = (vec_F_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(x1, 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(x1, 2)) / 2.0) + (vec_F_a_b_c[i].c * (li[i + 1] - x1));
                result_g = (vec_G_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(x1, 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(x1, 2)) / 2.0) + (vec_G_a_b_c[i].c * (li[i + 1] - x1));
                result += abs(result_f - result_g);
            }
            else if ((x1<li[i] || x1>li[i + 1]) && (li[i] < x2 && x2 < li[i + 1]))
            {
                double result_f{}, result_g{};
                result_f = (vec_F_a_b_c[i].a) * ((pow(x2, 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(x2, 2.0) - pow(li[i], 2.0)) / 2.0) + (vec_F_a_b_c[i].c * (x2 - li[i]));
                result_g = (vec_G_a_b_c[i].a) * ((pow(x2, 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(x2, 2.0) - pow(li[i], 2.0)) / 2.0) + (vec_G_a_b_c[i].c * (x2 - li[i]));
                result += abs(result_f - result_g);
                result_f = (vec_F_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(x2, 2.0)) / 2.0) + (vec_F_a_b_c[i].c * (li[i + 1] - x2));
                result_g = (vec_G_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(x2, 2.0)) / 2.0) + (vec_G_a_b_c[i].c * (li[i + 1] - x2));
                result += abs(result_f - result_g);
            }
        }
        else if (D == 0)
        {
            x1 = -((vec_F_a_b_c[i].b) - (vec_G_a_b_c[i].b)) / 2 * ((vec_F_a_b_c[i].a) - (vec_G_a_b_c[i].a));
            if ((x1 == li[i] || x1 == li[i + 1]) || (x1 < li[i] || x1 > li[i + 1]))
            {
                double result_f{}, result_g{};
                result_f = (vec_F_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(li[i], 2.0)) / 2.0) + (vec_F_a_b_c[i].c * (li[i + 1] - li[i]));
                result_g = (vec_G_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(li[i], 2.0)) / 2.0) + (vec_G_a_b_c[i].c * (li[i + 1] - li[i]));
                result += abs(result_f - result_g);
            }
            else if (li[i] < x1 && x1 < li[i + 1])
            {
                double result_f{}, result_g{};
                result_f = (vec_F_a_b_c[i].a) * ((pow(x1, 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(x1, 2.0) - pow(li[i], 2.0)) / 2.0) + (vec_F_a_b_c[i].c * (x1 - li[i]));
                result_g = (vec_G_a_b_c[i].a) * ((pow(x1, 3.0) - pow(li[i], 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(x1, 2.0) - pow(li[i], 2.0)) / 2.0) + (vec_G_a_b_c[i].c * (x1 - li[i]));
                result += abs(result_f - result_g);
                result_f = (vec_F_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(x1, 3.0)) / 3.0) + (vec_F_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(x1, 2.0)) / 2.0) + (vec_F_a_b_c[i].c * (li[i + 1] - x1));
                result_g = (vec_G_a_b_c[i].a) * ((pow(li[i + 1], 3.0) - pow(x1, 3.0)) / 3.0) + (vec_G_a_b_c[i].b) * ((pow(li[i + 1], 2.0) - pow(x1, 2.0)) / 2.0) + (vec_G_a_b_c[i].c * (li[i + 1] - x1));
                result += abs(result_f - result_g);
            }
        }
    }
    std::cout << std::setprecision(10) << std::fixed;
    std::cout << result << "\n";
    FP.close();
    return 0;   
}
