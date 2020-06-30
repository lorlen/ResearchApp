#include <string>
#include <map>
#include <iostream>

class Cipher
{
private:
    std::string key = "falanafaliitaksobielecifala";
    std::string alphabet;
    std::string make_long_key(int new_key_len);
    std::map<int, char> map_num;
    std::map<char, int> map_alp;
    void make_maps();
    bool if_in_alph(char c);
    std::string inner_vinegar_cipher(std::string text);
public:
    std::string encode(std::string text);
    std::string decode(std::string text);
    Cipher(std::string a, std::string k);
    ~Cipher();
};

