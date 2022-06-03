#include "binary_number.h"

#include <cmath>


int pow(int a, int b) {
    int result = 1;
    for (int i = 0; i < b; ++i) {
        result *= a;
    }
    return result;
}

void right_shift(std::vector<int> &number, int shift) {
    for (int j = 0; j < shift; ++j) {
        for (int i = 0; i < number.size() - 1; ++i)
            number[i] = number[i + 1];

        if (number.back() == 1)
            *(number.end()) = 1;
        else
            *(number.end()) = 0;
    }
}

void BinaryNumber::setDump(int number) {
    if (number < 0) {
        m_negative_flag = true;
        number = -number - 1;
        for (int i = 0; i < m_bitness; ++i) {
            if (number % 2) {
                m_bin_dump[i] = 0;
            } else {
                m_bin_dump[i] = 1;
            }
            number /= 2;
        }
    } else {
        m_negative_flag = false;
        for (int i = 0; i < m_bitness; ++i) {
            m_bin_dump[i] = number % 2;
            number /= 2;
        }
    }
}

void BinaryNumber::setDump(std::vector<int> dump) {
    if (dump.back() == 1)
        m_negative_flag = false;
    else
        m_negative_flag = true;
    for (int i = 0; i < dump.size(); ++i) {
        m_bin_dump[i] = dump[i];
    }
}

int BinaryNumber::getBite(int number) const {
    if (number > m_bitness) {
        if (m_negative_flag)
            return 1;
        else
            return 0;
    } else {
        return m_bin_dump[number];
    }
}

BinaryNumber BinaryNumber::ones_complement(const BinaryNumber &n) {
    std::vector<int> result_vect(n.m_bitness);
    for (int i = 0; i < n.m_bitness; ++i) {
        if (n.m_bin_dump[i] == 0)
            result_vect[i] = 1;
        else
            result_vect[i] = 0;
    }
    BinaryNumber result{result_vect};
    return result;
}

BinaryNumber BinaryNumber::twos_complement(const BinaryNumber &n) {
    BinaryNumber ones_compl = ones_complement(n);
    BinaryNumber result{ones_compl + 1};
    return result;
}

int BinaryNumber::to_decimal() const {
    int result = 0;
    BinaryNumber tmp_number1{m_bin_dump};

    if (!tmp_number1.m_negative_flag) { // if negative
        tmp_number1 = BinaryNumber::twos_complement(tmp_number1);
    }

    for (int i = 0; i < this->getBitness(); ++i) {
        result += tmp_number1.getBite(i) * pow(2, i);
    }
    if (!tmp_number1.m_negative_flag){
        result = -result;
    }
    return result;
}

std::ostream &operator<<(std::ostream &out, BinaryNumber &bin_number) {
    for (int i = bin_number.getBitness() - 1; i >= 0; --i) {
        out << bin_number.getBite(i);
    }

    return out;
}

BinaryNumber operator+(const BinaryNumber &n1, const BinaryNumber &n2) {
    int new_bitness = (n1.m_bitness > n2.m_bitness ? n1.m_bitness : n2.m_bitness);
    std::vector<int> number1{n1.m_bin_dump};
    std::vector<int> number2{n2.m_bin_dump};

    if (n1.m_bitness > n2.m_bitness) {
        if (n2.m_bin_dump.back() == 1)
            number2.resize(new_bitness, 1);
        else
            number2.resize(new_bitness, 0);
    } else {
        if (n1.m_bin_dump.back() == 1)
            number1.resize(new_bitness, 1);
        else
            number1.resize(new_bitness, 0);
    }

    number2.push_back(number2.back());  // добавление контрольного бита
    number1.push_back(number1.back());  // добавление контрольного бита

    std::vector<int> result;
    result.resize(new_bitness + 1);

    int carry = 0;
    for (int i = 0; i < result.size(); ++i) {
        int sum_of_digits = number1.at(i) + number2.at(i);
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
        std::cerr << "Overflow | Unavailable '+' operation: bitness is less then required";
        exit(3);
    }

    result.pop_back(); // removing the control bit

    BinaryNumber new_number{result};

    return new_number;
}

std::vector<int> sum(const BinaryNumber &n1, const BinaryNumber &n2, bool ignore_overflow) {
    int new_bitness = (n1.m_bitness > n2.m_bitness ? n1.m_bitness : n2.m_bitness);
    std::vector<int> number1{n1.m_bin_dump};
    std::vector<int> number2{n2.m_bin_dump};

    if (n1.m_bitness > n2.m_bitness) {
        if (n2.m_bin_dump.back() == 1)
            number2.resize(new_bitness, 1);
        else
            number2.resize(new_bitness, 0);
    } else {
        if (n1.m_bin_dump.back() == 1)
            number1.resize(new_bitness, 1);
        else
            number1.resize(new_bitness, 0);
    }

    number2.push_back(number2.back());  // добавление контрольного бита
    number1.push_back(number1.back());  // добавление контрольного бита

    std::vector<int> result;
    result.resize(new_bitness + 1);

    int carry = 0;
    for (int i = 0; i < result.size(); ++i) {
        int sum_of_digits = number1.at(i) + number2.at(i);
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
    if (result.at(result.size() - 1) != result.at(result.size() - 2) && !ignore_overflow) {
        std::cerr << "Overflow | Unavailable '+' operation: bitness is less then required";
        exit(3);
    }

    result.pop_back(); // removing the control bit

    BinaryNumber new_number{result};

    return new_number.m_bin_dump;
}

BinaryNumber operator+(const BinaryNumber &n1, int n2) {
    int bitness;
    if (abs(n2) == 1 || abs(n2) == 0)
        bitness = 2;
    else {
        bitness = static_cast<int>(ceil(log2(abs(n2)))) + 1;
    }
    BinaryNumber tmp{n2, bitness};
    BinaryNumber result = n1 + tmp;
    return result;
}

BinaryNumber operator+(int n1, const BinaryNumber &n2) {
    BinaryNumber result = n2 + n1;
    return result;
}

BinaryNumber operator-(BinaryNumber &n1, BinaryNumber &n2) {
    BinaryNumber twos_compl = BinaryNumber::twos_complement(n2);
    BinaryNumber result = n1 + twos_compl;

    return result;
}

BinaryNumber operator*(BinaryNumber &m, BinaryNumber &r) {
    int x = m.m_bitness;
    int y = r.m_bitness;
    std::vector<int> A;
    std::vector<int> S;
    std::vector<int> P;

    // initializing A
    for (int i = 0; i < y + 1; ++i)
        A.push_back(0);
    for (int &i: m.m_bin_dump)
        A.push_back(i);

    // initializing S
    BinaryNumber twos_compl_m = BinaryNumber::twos_complement(m);

    for (int i = 0; i < y + 1; ++i)
        S.push_back(0);
    for (int &i: twos_compl_m.m_bin_dump)
        S.push_back(i);

    // initializing P
    P.push_back(0);
    for (int &i: r.m_bin_dump)
        P.push_back(i);
    for (int i = 0; i < x; ++i) {
        P.push_back(0);
    }

    for (int i = 0; i < y; ++i) {
        BinaryNumber tmpP{P};
        BinaryNumber tmpA{A};
        BinaryNumber tmpS{S};
        if (P[0] == 1 && P[1] == 0) {
            P = sum(tmpP, tmpA, true);
        }
        if (P[0] == 0 && P[1] == 1) {
            P = sum(tmpP, tmpS, true);
        }
        right_shift(P, 1);
    }

    P.erase(P.begin());
    return BinaryNumber{P};
}
