#include "string.hpp"
#include <iostream>
#include <cstring> 

String::String(const char* str) : m_size{strlen(str)}
{
    if (strlen(str) != 0) {
        m_buf = new char[m_size];
        for (size_t i{}; i < m_size; ++i) {
            m_buf[i] = str[i];
        }
    }
}

String::String(const String& oth) : m_size{oth.m_size}, m_buf{oth.m_buf}
{
    if (oth.m_size != 0) {
        for (size_t i{}; i < m_size; ++i) {
            m_buf[i] = oth.m_buf[i];
        }
    }
}

String::String(const String&& oth) : m_size{oth.m_size}, m_buf{oth.m_buf}
{
    if (oth.m_size != 0) {
        for (size_t i{}; i < m_size; ++i) {
            m_buf[i] = std::move(oth.m_buf[i]);
        }
    }
}

String::~String()
{
    delete []m_buf;
    m_buf = nullptr;
}

String& String::operator=(const String& oth)
{
    if (this == &oth) {
        return *this;
    }
    if (oth.m_size != 0) {
        m_size = oth.m_size;
        m_buf = new char[m_size];
        for (size_t i{}; i < m_size; ++i) {
            m_buf[i] = oth.m_buf[i];
        }
    }
    return *this;
}

String& String::operator=(const String&& oth)
{
    if (this == &oth) {
        return *this;
    }
    if (oth.m_size != 0) {
        m_size = std::move(oth.m_size);
        m_buf = new char[m_size];
        for (size_t i{}; i < m_size; ++i) {
            m_buf[i] = std::move(oth.m_buf[i]);
        }
    }
    return *this;
}

String& String::operator+=(const String& oth)
{
    if (oth.m_size == 0) {
        return *this;
    }
    if (m_size == 0) {
        *this = oth;
        return *this;
    }
    size_t old_size = m_size;
    m_size += oth.m_size;
    char* tmp = new char[m_size];
    for (size_t i{}; i < old_size; ++i) {
        tmp[i] = m_buf[i];
    }
    for (size_t i{}; i < oth.m_size; ++i) {
        tmp[old_size + i] = oth.m_buf[i];
    }
    delete[] m_buf;
    m_buf = tmp;
    tmp = nullptr;
    return *this;
}

char& String::operator[](size_t index)
{
    return m_buf[index];
}

const char& String::operator[](size_t index) const
{
    return m_buf[index];
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str.m_buf;
    return os;

}

size_t String::get_length()
{
    return m_size;
}

void String::push_back(const char val)
{
    char* tmp = new char[++m_size];
    for (size_t i{}; i < m_size - 1; ++i){
        tmp[i] = m_buf[i];
    }
    tmp[m_size - 1] = val;
    delete[] m_buf;
    m_buf = tmp;
    tmp = nullptr;
}

void String::insert(size_t pos, const String& str)
{
    if (pos <= m_size){
        char* tmp = new char[m_size + str.m_size];
        for (size_t i{}; i < pos; ++i) {
            tmp[i] = m_buf[i];
        }
        for (size_t i{}; i < str.m_size; ++i) {
            tmp[pos + i] = str[i];
        }
        for (size_t i{pos}; i < m_size; ++i) {
            tmp[str.m_size + i] = m_buf[i];
        }
        delete[]m_buf;
        m_buf = tmp;
        tmp = nullptr;
    }
    else {std::cout << "out of range" << std::endl;}
}

String& String::erase(const size_t pos,const int count)
{
    if (pos + count <= m_size) {
        char* tmp = new char[m_size - count];
        for (size_t i{}; i < pos; ++i) {
            tmp[i] = m_buf[i];
        }
        for (size_t i{pos}; i < m_size; ++i) {
            tmp[i] = m_buf[count + i];
        }
        delete[]m_buf;
        m_buf = tmp;
        tmp = nullptr;
    }
    else {std::cout << "out of range." << std::endl;}
    return *this;
}

String& String::erase_spaces()
{
    for (size_t i{}; i < m_size; ++i) {
        if (m_buf[i] == ' ') {
            erase(i, 1);
            i--;
            m_size --;
        }
    }
    return *this;
}

String String::substr(const size_t left,const size_t right)
{
    if (left < right && right <= m_size) {
        char* str = new char[right - left + 1];
        for (size_t i{}; i < right - left; ++i) {
            str[i] = m_buf[left + i];
        }
        return str;
    }
    else {std::cout << "out of range." << std::endl;}
    return *this;
}

int main() {
    String str1 {"hello"};
    String str2 = {" World!"};
    str1 += str2;
    std::cout << str1 << std::endl;
}
