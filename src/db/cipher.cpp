#include "db/cipher.h"

Cipher::Cipher(std::string a, std::string k = "falanafaliitaksobielecifala")
{
    key = k;
    alphabet = a;
    make_maps();
}

Cipher::~Cipher()
{
}

void Cipher::make_maps()
{
    for (int i = 0; i < alphabet.size(); i++)
    {
        map_alp.insert(std::pair<char, int>(alphabet[i], i));
        map_num.insert(std::pair<int, char>(i, alphabet[i]));
    }
    
}

std::string Cipher::make_long_key(int new_key_len)
{
    std::string new_key = "";
    for (size_t i = 0; i < new_key_len; i++)
    {
        int num = i % key.size();
        new_key += key[num];
    }
    return new_key;
}

std::string Cipher::encode(std::string text)
{
    std::string key_to_use;
    if (text.size()> key.size()) 
    {
        key_to_use = make_long_key(text.size());
    }
    else 
    { 
        key_to_use = key;
    }
    std::string exit_text = "";
    for(size_t i = 0; i < text.size(); i++)
    {
        if (!if_in_alph(text[i])) exit_text+= text[i];
        else
        {
            int n = (map_alp.find(text[i])->second + map_alp.find(key[i]) -> second) % alphabet.size();
            exit_text += map_num.find(n)->second;
        }
        
    }
    #ifdef _Debug
        std::cout << "encoding: " << text << " result: " << exit_text << std::endl;
    #endif
    return exit_text;
}

std::string Cipher::decode(std::string text)
{
    std::string key_to_use;
    if (text.size()> key.size()) 
    {
        key_to_use = make_long_key(text.size());
    }
    else 
    { 
        key_to_use = key;
    }
    std::string exit_text = "";
    for(size_t i = 0; i < text.size(); i++)
    {
        if (!if_in_alph(text[i])) exit_text+= text[i];
        else
        {
            int n = (map_alp.find(text[i])->second - map_alp.find(key[i]) -> second + 26) % alphabet.size();
            exit_text += map_num.find(n)->second;
        }
        
    }
    #ifdef _Debug
        std::cout << "Decoding: " << text << " result: " << exit_text << std::endl;
    #endif
    return exit_text;
}


bool Cipher::if_in_alph(char c)
{
    if((c >= 'a' && c <= 'z'))
        return true;
    return false;
}