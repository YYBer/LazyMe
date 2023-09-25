# include <iostream>
# include <fstream>
# include <string>
# include <cstdlib>
# include <exception>

#ifndef LAZYME_HPP
#define LAZYME_HPP
class LazyMe
{
    public:
        LazyMe(void){};
        ~LazyMe(void) {};

        void    setOutput(void);
        void    setUpperFileName(void);
        std::string&    getCfileOutput(void);
        std::string&    getHfileOutput(void);
        std::string&    getFileName(void);
        std::string&    getUpperFileName(void);
        void    convertcustomization(void);
        void    execute(void);
        class FailException: public std::exception{
            public:
                virtual const char* what() const throw();
        };

    private:
        std::string _fileName;
        std::string _upperFileName;
        std::string _cfileoutput;
        std::string _hfileoutput;
};
#endif

std::string&    LazyMe::getFileName(void)
{
    return this->_fileName;
}

std::string&    LazyMe::getUpperFileName(void)
{
    return this->_upperFileName;
}

std::string&    LazyMe::getCfileOutput(void)
{
    return this->_cfileoutput;
}

std::string&    LazyMe::getHfileOutput(void)
{
    return this->_hfileoutput;
}

void    LazyMe::setUpperFileName(void)
{
    std::string tmp = "";
    for (int i = 0; i < getFileName().size(); ++i)
        tmp += toupper(this->_fileName[i]);
    this->_upperFileName = tmp;
}

void    LazyMe::setOutput(void)
{
    this->_hfileoutput =
"#ifndef    SM_HPP\n"
"#define    SM_HPP\n"
"\n"
"#include <iostream>\n"
"\n"
"class sm\n"
"{\n"
"    public:\n"
"        sm(void);\n"
"        ~sm(void);\n"
"        sm(const sm& other);\n"
"        sm& operator=(const sm& other);\n"
"\n"
"    private:\n"
"};\n"
"\n"
"#endif\n";

    this->_cfileoutput = 
"#include SM\n"
"\n"
"sm::sm(void) {}\n"
"\n"
"sm::~sm(void) {}\n"
"\n"
"sm::sm(const sm& other)\n"
"{\n"
"   *this = other;\n"
"}\n"
"\n"
"sm&    sm::operator=(const sm& other)\n"
"{\n"
"   (void)other;\n"
"   return *this;\n"
"}\n";
}

void    LazyMe::convertcustomization(void)
{
    std::string& ctmp = getCfileOutput();
    std::string& htmp = getHfileOutput();
    size_t found = ctmp.find("sm");
    while (found != std::string::npos)
    {
        ctmp.replace(found, 2, getFileName());
        found = ctmp.find("sm", 2 + getFileName().length());
    }

    size_t found1 = ctmp.find("SM");
    std::string tmp = "\"" + getFileName() + ".hpp" + "\"";
    while (found1 != std::string::npos)
    {
        ctmp.replace(found1, 2, tmp);
        found1 = ctmp.find("SM", 2 + tmp.length());
    }

    size_t found2 = htmp.find("sm");
    while (found2 != std::string::npos)
    {
        htmp.replace(found2, 2, getFileName());
        found2 = htmp.find("sm", 2 + getFileName().length());
    }

    size_t found3 = htmp.find("SM");
    while (found3 != std::string::npos)
    {
        htmp.replace(found3, 2, getUpperFileName());
        found3 = htmp.find("SM", 2 + getUpperFileName().length());
    }
}

void    LazyMe::execute(void)
{
    setOutput();
    std::cout<< "please type the name of class you want to create: " << std::endl;
    std::string input = "";
    std::getline(std::cin, input);
    this->_fileName = input;
    setUpperFileName();
    convertcustomization();
    std::string tmp1 = getFileName() + ".cpp";
    std::string tmp2 = getFileName() + ".hpp";
    std::ofstream ofsc(tmp1.c_str());
    if (!ofsc.is_open())
        throw FailException();
    ofsc << getCfileOutput();
    ofsc.close();
    std::ofstream ofsh(tmp2.c_str());
    if (!ofsh.is_open())
        throw FailException();
    ofsh << getHfileOutput();
    ofsh.close();
}

int main (void)
{
    LazyMe me;
    me.execute();
}