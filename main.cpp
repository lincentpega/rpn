#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


#include <iostream>
#include <vector>

using namespace std;

int pow(int a, int b) { // функция возведения в степень для целых чисел
    int res = 1;
    for (int i = 0; i < b; ++i) {
        res = res * a;
    }
    return res;
}

void shift(vector<int> &n, int s) { // ф-ия побитового сдвига вправо, т.е. в сторону самого малозначащего индекса вектора
    for (int j = 0; j < s; ++j) {
        for (int i = 0; i < n.size() - 1; ++i) {
            n[i] = n[i + 1];
        }
    }
}

class Num {
public:
    vector<int> bin; // двоичная запись числа хранится в структуре данных "вектор", которая, в отличие от массива,
    // обладает автоматической очисткой памяти

    int nBit;        // количество бит в числе

    Num(const Num &n) = default;  // стандартный конструктор копирования, что значит, что аналогичным полям при
    // инициализации копированиям присваиваются значения соответствующих полей этого объекта

    Num(int number, int bitness){ // конструктор создаёт новый объект типа Num
        nBit = bitness;
        bin.resize(nBit); // изменение размера вектора под новый размер
        setbin(number);        // вызов функции заполнения бинарного вектора
    }

    Num(std::vector<int> &arr) {  // конструктор, который создаёт объект по двоичному представлению, хранящемуся в векторе
        nBit = arr.size();
        bin.resize(nBit);
        setbin(arr);        // функция setbin, как и все эти конструкторы перегружена, что значит, что может быть
        // вызвана с аргументами разных типов, даже если имеет одно и то же имя
    }

    void setbin(int n) { // setbin для числа
        if (n < 0) {
            n = -n - 1;
            for (int i = 0; i < nBit; ++i) {
                if (n % 2) {
                    bin[i] = 0;
                } else {
                    bin[i] = 1;
                }
                n /= 2;
            }
        } else {
            for (int i = 0; i < nBit; ++i) {
                bin[i] = n % 2;
                n /= 2;
            }
        }
    }

    void setbin(vector<int> dump) { // setbin для вектора
        for (int i = 0; i < dump.size(); ++i) {
            bin[i] = dump[i];
        }
    }

    int desyat() { // вывод числа, хранящегося в двоичном виде в десятичном
        int result = 0;
        Num temp{bin}; // временная копия, чтобы получить дополнение отрицательного числа

        if (temp.bin[temp.bin.size() - 1] == 1) { // если число отрицательное
            cout << "-";
            temp = vtoroyedop(temp); // второе дополнение инвертирует число
        }


        for (int i = 0; i < this->nBit; ++i) { // обычный перевод числа в десятичное
            result += temp.bin[i] * pow(2, i);
        }
        return result;
    }

    Num dopolnyeniye(Num &n) {              // первое дополнение числа
        vector<int> result_vect(n.nBit); // создается вектор изначального размера
        for (int i = 0; i < n.nBit; ++i) {
            if (n.bin[i] == 0)
                result_vect[i] = 1;         // просто инвертируются биты числа
            else
                result_vect[i] = 0;
        }
        Num result{result_vect};         // а это uniform инициализация, просто соответствующие поля заполняются
        return result;
    }

    Num vtoroyedop(Num &n) {                // к первому дополнению прибавляется единица
        Num dop = dopolnyeniye(n);
        Num one{1, n.nBit};
        Num result{dop.sum(one)};
        return result;
    }

    Num sum(const Num &n2) {
        int new_bitness = (nBit > n2.nBit ? nBit : n2.nBit); // это тернарный оператор если условие вып.,: то значение,? иначе
        std::vector<int> n1{bin};
        std::vector<int> num2{n2.bin};

        if (nBit > n2.nBit) {
            if (n2.bin.back() == 1)
                num2.resize(new_bitness, 1);
            else
                num2.resize(new_bitness, 0);
        } else {
            if (bin.back() == 1)
                n1.resize(new_bitness, 1);
            else
                n1.resize(new_bitness, 0);
        }

        num2.push_back(num2.back());  // добавление контрольного бита
        n1.push_back(n1.back());  // добавление контрольного бита

        std::vector<int> result;
        result.resize(new_bitness + 1);

        int carry = 0;
        for (int i = 0; i < result.size(); ++i) {
            int sum_of_digits = n1.at(i) + num2.at(i); // обычное сложение в столбик
            if (sum_of_digits + carry == 0) {
                result[i] = 0;
                carry = 0;
            } else if (sum_of_digits + carry == 1) {
                result[i] = 1;
                carry = 0;
            } else if (sum_of_digits + carry == 2) {
                result[i] = 0;
                carry = 1;
            } else if (sum_of_digits + carry == 3) {
                result[i] = 1;
                carry = 1;
            }
        }
        if (result.at(result.size() - 1) != result.at(result.size() - 2)) {
            exit(2);
        }

        result.pop_back(); // добавление элемента в конец вектора

        Num new_number{result};

        return new_number;
    }

    vector<int> sum(const Num &n1, const Num &n2, bool ignore_overflow) { // перегруженная ф-ия суммы, возвращает вектор,
        // есть возможность игнорировать переполнение
        int new_bitness = (n1.nBit > n2.nBit ? n1.nBit : n2.nBit);
        vector<int> number1{n1.bin};
        vector<int> number2{n2.bin};

        if (n1.nBit > n2.nBit) {
            if (n2.bin.back() == 1)
                number2.resize(new_bitness, 1);
            else
                number2.resize(new_bitness, 0);
        } else {
            if (n1.bin.back() == 1)
                number1.resize(new_bitness, 1);
            else
                number1.resize(new_bitness, 0);
        }

        number2.push_back(number2[number2.size() - 1]);  // добавление контрольного бита
        number1.push_back(number1[number1.size() - 1]);  // добавление контрольного бита

        vector<int> result;
        result.resize(new_bitness + 1);

        int carry = 0;
        for (int i = 0; i < result.size(); ++i) {
            int sum_of_digits = number1[i] + number2[i];
            if (sum_of_digits + carry == 0) {
                result[i] = 0;
                carry = 0;
            } else if (sum_of_digits + carry == 1) {
                result[i] = 1;
                carry = 0;
            } else if (sum_of_digits + carry == 2) {
                result[i] = 0;
                carry = 1;
            } else if (sum_of_digits + carry == 3) {
                result[i] = 1;
                carry = 1;
            }
        }
        if (result[result.size() - 1] != result[result.size() - 2] && !ignore_overflow) {
            exit(2); // если переполнение, то есть контольный бит не соотв. последнему, то выход из программы с ошибкой
        }

        result.pop_back(); // удаляется контрольный бит

        Num new_number{result};

        return new_number.bin;
    }

    Num sub(Num &n2) { // вычитание - просто складывается число и второе дополнение второго числа
        Num vt_dop = Num::vtoroyedop(n2);
        Num result = this->sum(vt_dop);

        return result;
    }

    Num mult(Num &r) { // алгоритм Бафа - есть в википедии - релизовано прям оттуда
        int x = nBit;
        int y = r.nBit;
        std::vector<int> A;
        std::vector<int> S;
        std::vector<int> P;

        for (int i = 0; i < y + 1; ++i)
            A.push_back(0);
        for (int &i: bin)
            A.push_back(i);

        Num twos_compl_m = Num::vtoroyedop(*this);

        for (int i = 0; i < y + 1; ++i)
            S.push_back(0);
        for (int &i: twos_compl_m.bin)
            S.push_back(i);

        P.push_back(0);
        for (int &i: r.bin)
            P.push_back(i);
        for (int i = 0; i < x; ++i) {
            P.push_back(0);
        }

        for (int i = 0; i < y; ++i) {
            Num tP{P};
            Num tA{A};
            Num tS{S};
            if (P[0] == 1 && P[1] == 0) {
                P = sum(tP, tA, true);
            }
            if (P[0] == 0 && P[1] == 1) {
                P = sum(tP, tS, true);
            }
            shift(P, 1);
        }

        P.erase(P.begin()); // передаётся иттератор на первый элемент вектора
        return Num{P};
    }

    void print() { // обычный вывод двоичного числа
        for (int i = nBit - 1; i >= 0; --i) {
            cout << bin[i];
        }
    }
};


const int bitness = 16;

bool isNumber(const std::string str) {
    return std::all_of(str.begin(), str.end(), [](char i){ return std::isdigit(i) != 0; });
}

void split(std::string &str, char del, std::vector<std::string>& vect) {
    std::string temp;

    for (char i : str) {
        if(i != del) {
            temp += i;
        }
        else {
            vect.push_back(temp);
            temp = "";
        }
    }

    vect.push_back(temp);
}

int processing(std::vector<std::string> &expr) {
    Stack stack;

    for (auto &i: expr) {
        if (isNumber(i))
            stack.push(Num(std::stoi(i), bitness));
        else if (i == "+" || i == "-" || i == "*" || i == "/") {
            Num n1 = stack.pop();
            Num n2 = stack.pop();

            if ((char) i[0] == '+') {
                Num result(n1.sum(n2));
                stack.push(result);
            } else if ((char) i[0] == '-') {
                Num result(n1.sub(n2));
                stack.push(result);
            } else if ((char) i[0] == '*') {
                Num result(n1.mult(n2));
                stack.push(result);
            }
        }
    }
    if (stack.size() > 1){
        std::cerr << "Incorrect expression" << std::endl;
        exit(1);
    }
    return stack.pop().desyat();
}


int main() {
    std::string input;
    char delimiter;

    std::cout << "Enter expr: " << std::endl;
    std::getline(std::cin, input);

    std::vector<std::string> expression;
    split(input, ' ', expression);

    int result = processing(expression);
    Num bin_res{result, bitness};
    std::cout << result << std::endl;
    bin_res.print();
}
