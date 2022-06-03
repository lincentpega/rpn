#ifndef ALGORITHMS_LAB2_BINARY_NUMBER_H
#define ALGORITHMS_LAB2_BINARY_NUMBER_H

#include <iostream>
#include <vector>

int pow(int a, int b);

class BinaryNumber {
private:
    std::vector<int> m_bin_dump;
    int m_bitness;
    bool m_negative_flag = false; // true - "+", false - "-"
    void setDump(int number);

public:
    BinaryNumber() {
        m_bin_dump.resize(0);
        m_bitness = 0;
    }

    BinaryNumber(const BinaryNumber &n) = default; // default copy-initialization

    BinaryNumber(int number, int bitness) : m_bitness(bitness) {
        if (abs(number) > pow(2, bitness - 1)) {
            std::cerr << "Isn't possible to keep number " << number << "in vector of bitness " << bitness;
            exit(2);
        }
        m_bin_dump.resize(m_bitness);
        setDump(number);
    }

    // constructor can't be used for implicit conversion and copy-initialization
    explicit BinaryNumber(const std::vector<int> &arr) {
        m_bitness = static_cast<int>(arr.size());
        m_negative_flag = arr.back() != 1;
        m_bin_dump.resize(m_bitness);
        setDump(arr);
    }

    void setDump(std::vector<int> dump);

    int getBite(int number) const;

    int getBitness() const { return m_bitness; };

    int to_decimal() const;

    static BinaryNumber ones_complement(const BinaryNumber &n);

    static BinaryNumber twos_complement(const BinaryNumber &n);

    friend BinaryNumber operator+(const BinaryNumber &n1, const BinaryNumber &n2);

    friend std::vector<int> sum(const BinaryNumber &n1, const BinaryNumber &n2, bool ignore_overflow);

    friend BinaryNumber operator+(const BinaryNumber &n1, int n2);

    friend BinaryNumber operator+(int n1, const BinaryNumber &n2);

    friend BinaryNumber operator-(BinaryNumber &n1, BinaryNumber &n2);

    friend BinaryNumber operator*(BinaryNumber &n1, BinaryNumber &n2);

    friend std::ostream &operator<<(std::ostream &out, BinaryNumber &bin_number); // output operator;
};

#endif //ALGORITHMS_LAB2_BINARY_NUMBER_H
