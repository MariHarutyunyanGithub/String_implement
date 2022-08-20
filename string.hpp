#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
class String
{
    public:
        String() = default;
        String(const char*);
        String(const String&);
        String(const String&&);
        ~String();
    public:
        String& operator=(const String&);
        String& operator=(const String&&);
        String operator+=(const String&);
        char& operator[](size_t);
        const char& operator[](size_t) const;
        friend  std::ostream& operator<<(std::ostream&, const String&);
    public:
        size_t get_length();
        void push_back(const char);
        void insert(size_t, const String&);
        String& erase(const size_t, const int);
        String& erase_spaces();
        String substr(size_t, size_t);
    private:
        size_t m_size;
        char* m_buf;
};
#endif//STRING_HPP