#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string import;
string InputFile;
string OutFile;

string stringToHex(const string& str) {
    stringstream hexStream;
    hexStream << uppercase << hex;

    for (size_t i = 0; i < str.length(); ++i) {
        hexStream << setw(2) << setfill('0') << static_cast<int>(str[i]);
    }
    return hexStream.str();
}


string hexToAscii(const string& hex) {
    string ascii;
    for (size_t i = 0; i < hex.length(); i += 2) {
        string byteString = hex.substr(i, 2);
        char byte = (char)strtol(byteString.c_str(), nullptr, 16);
        ascii.push_back(byte);
    }
    return ascii;
}

string xorDecrypt(const string& input, const string& key) {
    string decrypted;
    for (size_t i = 0; i < input.size(); ++i) {
        decrypted += input[i] ^ key[i % key.size()];
    }
    return decrypted;
}



int main() {
		
	getline(cin,import);
	getline(cin,InputFile);
	getline(cin,OutFile);
	

    ifstream inputFile(InputFile); // 替换为你的输入文件路径
    if (!inputFile) {
        cout << "无法打开输入文件" << endl;
        return 1;
    }

    ofstream outputFile(OutFile); // 替换为你的输出文件路径
    if (!outputFile) {
        cout << "无法创建输出文件" << endl;
        return 1;
    }

    string line;
    if ( import == "-e")
    {
     while (getline(inputFile, line))
      {
    
        size_t pos = line.find("+CVars=");
        if (pos != string::npos) 
        {                                
            string hex = line.substr(pos + 7); // 7 是 "+CVars=" 的长度
            string key = hexToAscii("79");//密钥
            string decrypted = xorDecrypt(hex, key);//进行xor计算
            
            string outstring =  stringToHex(decrypted);            
            string outputLine = line.substr(0, pos + 7) + outstring;
            
            outputFile << outputLine << endl;            
        } 
        
        else
        {
            outputFile << line << endl;
        }
      }
            cout << "加密完成，并将结果写入输出文件" << endl;
    }
     
       else if ( import == "-d")
       
       {              
           while (getline(inputFile, line))
           
         {
           size_t pos = line.find("+CVars=");
           
            if (pos != string::npos)
          {
            string hex = line.substr(pos + 7); // 7 是 "+CVars=" 的长度
            string encrypted = hexToAscii(hex);
            string key = hexToAscii("79"); // 将十六进制密钥转换为ASCII字符串

            string decrypted = xorDecrypt(encrypted, key);
            string outputLine = line.substr(0, pos + 7) + decrypted;

            outputFile << outputLine << endl;
            
         }                   
          else
        {
            outputFile << line << endl;
        }        
     }       
        cout << "解密完成，并将结果写入输出文件" << endl;
   }
        else      
       {            
          cout << "指令错误 (ÒωÓױ)！" << endl;
       }
       
    inputFile.close();
    outputFile.close();

    return 0;
}