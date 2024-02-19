# include <iostream>
# include <fstream>
# include <string>
# include <cstdlib>
# include <exception>
# include <unistd.h>


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
        void    getInput(char *className);
        class FailException: public std::exception{
            public:
                virtual const char* what() const throw(){
                	return "can not open file";}
        };

    private:
        std::string _fileName;
        std::string _upperFileName;
        std::string _cfileoutput;
        std::string _hfileoutput;
        std::string _path;
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

void    LazyMe::execute()
{
    setOutput();
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


void LazyMe::getInput(char *className)
{
    // something like this could work for MAC
    //
    // try {
    //     fs::path currentPath = fs::current_path();
    //     std::cout << "Current working directory: " << currentPath << std::endl;
    // } catch (const std::exception& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    //     return (NULL);
    // }
    // return 0;
    // std::string path = getPath() + "/";
    // this->_fileName = this->_fileName.insert(0, path);
    // std::cout << "file with pathname is " << this->_fileName << std::endl;

    // This works for Linux
    char path[500];
    this->_fileName = className;

    if (getcwd(path, sizeof(path)) != NULL) {
        std::string pathString(path);
        this->_path = pathString;
        this->_path.append("/");
        this->_path.append(this->_fileName);
        // std::cout << "Current path: " << this->_path << std::endl;
        // std::cout << "Current filename : " << this->_fileName << std::endl;
    } else {
        perror("getcwd() error");
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Correct usage is: <executable name> <className>" << std::endl;
        return 1;
    }
	try{
		LazyMe me;
        me.getInput(argv[1]);
		me.execute();
        std::cout << "Made the " << argv[1] << " class" << std::endl;
        }
	catch (const LazyMe::FailException& e){
		std::cerr << "Exception: " << e.what() << std::endl;}
}
