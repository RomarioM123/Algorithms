#include "LongNumber.h"

LongNumber::LongNumber(unsigned long int value)
{
    clear();

    if (value == 0)
        m_nbits = 1;
    else
        while (value > 0)
        {
            m_bits[m_nbits++] = value % 2;
            value /= 2;
        }
}
LongNumber::LongNumber(const LongNumber& other)
{
    memcpy(m_bits, other.m_bits, MAX_BITS);
    m_nbits = other.m_nbits;
}
LongNumber::~LongNumber()
{
    clear();
}

void LongNumber::clear()
{
    memset(m_bits, 0, MAX_BITS);
    m_nbits = 0;
}

LongNumber LongNumber::operator*(LongNumber element)
{
    LongNumber result;

    result.m_nbits = m_nbits + element.m_nbits + 1;

    for (int i = 0; i < m_nbits; i++)
    {
        char carry = 0;
        for (int j = 0; j < element.m_nbits || carry; j++)
        {
            char cur = result.m_bits[i + j] + m_bits[i] * (j < element.m_nbits ? element.m_bits[j] : 0) + carry;
            result.m_bits[i + j] = cur % 2;
            carry = cur / 2;
        }
    }

    while (result.m_nbits - 1 > 0 && result.m_bits[result.m_nbits - 1] == 0)
        result.m_nbits--;

    return result;
}
LongNumber LongNumber::operator/(LongNumber element)
{
    if (*this < element || *this == 0 || element == 0)
        return 0;

    if (*this == element)
        return 1;

    if (element == 1)
        return *this;

    int i = 0;
    while (element * i <= *this)
        i++;

    return LongNumber(--i);
}
bool LongNumber::operator==(LongNumber element)
{
    if (m_nbits != element.m_nbits)
        return false;

    for (int i = 0; i < m_nbits; i++)
        if (m_bits[i] != element.m_bits[i])
            return false;

    return true;
}
bool LongNumber::operator<(LongNumber element)
{
    if (*this == element)
        return false;

    if (m_nbits != element.m_nbits)
        return m_nbits < element.m_nbits;

    for (int i = m_nbits - 1; i >= 0; i--)
        if (m_bits[i] != element.m_bits[i])
            return m_bits[i] < element.m_bits[i];

    return false;
}
bool LongNumber::operator>(LongNumber element)
{
    return (*this == element || *this < element) ? false : true;
}
bool LongNumber::operator<=(LongNumber element)
{
    return (*this < element || *this == element) ? true : false;
}
