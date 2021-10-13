#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <regex>

#include "buildAssem.cpp"
#include "parse.cpp"
//#include <string.h>

using namespace std;

int is_variable(string data, string var);

int main(int argc, char *argv[])
{
    FILE *fp;
    string assem;
    string err;
    fstream file;
    //regex reg("+|-|*|/|^|");
    char *line = NULL;
    size_t len = 0;
    string temp;
    string variable;
    string value;
    string num1;
    string num2;
    int comm;
    int comm2;
    string textVariable = "s0";
    int pos;
    int pos2;
    bool comnt = false;
    bool begin = false;
    size_t read;
    string fileName;
    string dir = "/home/slamrow/projects/cs6820/compiler/assem_output/";
    string data;
    string bss;
    string assembly;
    int add = -1;
    int sub = -1;
    int mul = -1;
    int div = -1;
    int exp = -1;
    int equ = -1;
    int var1;
    int var2;
    int var3;
    

    // if (argc != 2)
    // {
    //     printf("Error: usage: %s sample_input/<inputBinary.s>\n", argv[0]);
    //     exit(1);
    // }

    //printf("Welcome to CS6610 MIPS Assembler\n\n");
    fp = fopen(argv[1], "r");
    // fp = fopen("/home/slamrow/projects/cs6820/compiler/program_input/basics-new.txt", "r");
    if (fp == 0)
    {
        printf("Unable to open file [%s]\n", argv[1]);
        exit(1);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        trim(line);
        temp = line;
        comm = temp.find("//");
        comm2 = temp.find("/*");
        // add = temp.find("+");
        // sub = temp.find("-");
        // mul = temp.find("*");
        // div = temp.find("/");
        // exp = temp.find("^");
        equ = temp.find(" = ");
        if (comm2 >= 0 || comnt == true)
        {
            if(begin == false)
            {
                file.open(err.c_str(), ios_base::app);
                file << "This program has not begun" << endl;
                printf("This program has not begun");
                file.close();
                return -1;
            }
            comnt = true;
            comm = temp.find("*/");
            if (comm >= 0)
            {
                comnt = false;
            }
            // break;
        }
        else if (comm == 0)
        {
            if(begin == false)
            {
                file.open(err.c_str(), ios_base::app);
                file << "This program has not begun" << endl;
                printf("This program has not begun\n");
                file.close();
                return -1;
            }
        }
        // else if (comm > 1)
        // {
        //     if(begin == false)
        //     {
        //         err.open()
        //         err << "This program has not begun";
        //         printf("This program has not begun");
        //         err.close();
        //         return -1;
        //     }
        //     temp.replace(comm, string::npos, "");
        // }
        else if (temp.find("program")==0)
        {
            pos = temp.find(" ");
            pos2 = temp.find(";");
            if ((pos2 - pos) < 2)
            {
                printf("There is no name for this program.");
                return -1;
            }
            fileName = temp.substr(pos+1, pos2 - (pos +1));
            assem = dir + fileName + ".asm";
            ofstream fa(assem);
            err = dir + fileName + ".err";
            ofstream fe(err);
            fa.close();
            fe.close();
            
            //printf("program name: %s\n", newTemp.c_str());
        }
        else if (temp.find("begin") == 0)
        {
            begin = true;
            beginAssembly(fileName);
        }
        else if (temp.find("end") == 0)
        {
            begin = false;
            endAssembly(fileName);
        }
        
        else if (temp.find("num") == 0)
        {
            pos = temp.find(" ");
            pos2 = temp.find("=");
            comm = temp.find(";");
            if (pos2 == -1)
            {
                variable = temp.substr(pos + 1, comm - (pos + 1));
                data = data + "i " + variable + " ";
                unInitDataAssembly(variable, "int");
            }
            else
            {
                variable = temp.substr(pos + 1, pos2 - (pos + 1));
                value = temp.substr(pos2 + 1, comm - (pos2 + 1));
                if (strstr(data.c_str(), variable.c_str()) == NULL)
                {
                    data = data + "i " + variable + " ";
                    //unInitDataAssembly(variable, "int");
                }  
                add = value.find("+");
                sub = value.find("-");
                mul = value.find("*");
                div = value.find("/");
                exp = value.find("^");
                equ = value.find(" = ");              
                
                if (add >= 0)
                {
                    //pos = value.find("+");
                    num1 = value.substr(0, add -1);
                    num2 = value.substr(add + 1, comm - (add + 1));
                    unInitDataAssembly(variable, "int");
                    var1 = is_variable(data, num1);
                    var2 = is_variable(data, num2);
                    var3 = is_variable(data, variable);
                    addAssembly(num1, var1, num2, var2, variable, var3);
                }
                else if (sub >= 0)
                {
                    //pos = value.find("-");
                    num1 = value.substr(0, sub -1);
                    num2 = value.substr(sub + 1, comm - (sub + 1));
                    unInitDataAssembly(variable, "int");
                    var1 = is_variable(data, num1);
                    var2 = is_variable(data, num2);
                    var3 = is_variable(data, variable);
                    subAssembly(num1, var1, num2, var2, variable, var3);
                }
                else if (mul >= 0)
                {
                    //pos = value.find("*");
                    num1 = value.substr(0, mul -1);
                    num2 = value.substr(mul + 1, comm - (mul + 1));
                    unInitDataAssembly(variable, "int");
                    var1 = is_variable(data, num1);
                    var2 = is_variable(data, num2);
                    var3 = is_variable(data, variable);
                    multAssembly(num1, var1, num2, var2, variable, var3);
                }
                else if (div >= 0)
                {
                    //pos = value.find("/");
                    num1 = value.substr(0, div -1);
                    num2 = value.substr(div + 1, comm - (div + 1));
                    unInitDataAssembly(variable, "int");
                    var1 = is_variable(data, num1);
                    var2 = is_variable(data, num2);
                    var3 = is_variable(data, variable);
                    divAssembly(num1, var1, num2, var2, variable, var3);
                }
                else if (exp >= 0)
                {
                    //pos = value.find("^");
                    num1 = value.substr(0, exp -1);
                    num2 = value.substr(exp + 1, comm - (exp + 1));
                    unInitDataAssembly(variable, "int");
                    var1 = is_variable(data, num1);
                    var2 = is_variable(data, num2);
                    var3 = is_variable(data, variable);
                    expoAssembly(num1, var1, num2, var2, variable, var3);
                }
                else
                {
                    if (strstr(data.c_str(), variable.c_str()) == NULL)
                    {
                        data = data + "i " + variable + " ";
                    } 
                    dataAssembly(variable, value);
                }
            }
            
        }
        else if (temp.find("string") == 0)
        {
            pos = temp.find(" ");
            pos2 = temp.find("=");
            comm = temp.find(";");
            if (pos2 == -1)
            {
                variable = temp.substr(pos + 1, comm - (pos + 1));
                data = data + "s " + variable + " ";
                unInitDataAssembly(variable, "string ");
            }
            else
            {
                variable = temp.substr(pos + 1, pos2 - (pos + 1));
                value = temp.substr(pos2 + 1, comm - (pos2 + 1));
                if (strstr(data.c_str(), variable.c_str()) == NULL)
                    {
                        data = data + "s " + variable + " ";
                    } 
                dataAssembly(variable, value);
            }            
        }
        else if (temp.find("write") == 0)
        {
            pos = temp.find(" ");
            comm = temp.find(";");
            variable = temp.substr(0, pos);
            value = temp.substr(pos + 1, comm - (pos + 1));
            string type;
            if (value.find("\"") == 0)
            {
                value = value + ",0x0d,0x0a,0";
                dataAssembly(textVariable, value);
                data = data + "s " + value + " ";
                textVariable = textVariable + "a";
            }
            else if (strstr(data.c_str(), value.c_str()) != NULL)
            {
                pos = data.find(value);
                type = data.substr(pos - 2, 2);
                var1 = 1;
            }
            else //if (strstr(data.c_str(), value.c_str()) != NULL)
            {
                pos = data.find(value);
                type = data.substr(pos - 2, 2);
                var1 = 0;
            }
            
            callAssembly(variable, value, var1, type);
        }
        else if (equ > 2)
        {
            pos = temp.find(" ");
            pos2 = temp.find("=");
            int end = temp.find(";");
            variable = temp.substr(pos + 1, pos2 - (pos + 1));
            value = temp.substr(pos2 + 1, end - (pos2 + 1));
            if (strstr(data.c_str(), variable.c_str()) == NULL)
            {
                file.open(err.c_str(), ios_base::app);
                file << "This variable has not been declared" << endl;
                printf("This variable has not been declared");
                file.close();
                return -1;
            } 
            if (add >= 0)
            {
                //pos = value.find("+");
                num1 = value.substr(0, add -1);
                num2 = value.substr(add + 1, end - (add + 1));
                var1 = is_variable(data, num1);
                var2 = is_variable(data, num2);
                var3 = is_variable(data, variable);
                addAssembly(num1, var1, num2, var2, variable, var3);
            }
            else if (sub >= 0)
            {
                //pos = value.find("-");
                num1 = value.substr(0, sub -1);
                num2 = value.substr(sub + 1, end - (sub + 1));
                var1 = is_variable(data, num1);
                var2 = is_variable(data, num2);
                var3 = is_variable(data, variable);
                subAssembly(num1, var1, num2, var2, variable, var3);
            }
            else if (mul >= 0)
            {
                //pos = value.find("*");
                num1 = value.substr(0, mul -1);
                num2 = value.substr(mul + 1, end - (mul + 1));
                var1 = is_variable(data, num1);
                var2 = is_variable(data, num2);
                var3 = is_variable(data, variable);
                multAssembly(num1, var1, num2, var2, variable, var3);
            }
            else if (div >= 0)
            {
                //pos = value.find("/");
                num1 = value.substr(0, div -1);
                num2 = value.substr(div + 1, end - (div + 1));
                var1 = is_variable(data, num1);
                var2 = is_variable(data, num2);
                var3 = is_variable(data, variable);
                divAssembly(num1, var1, num2, var2, variable, var3);
            }
            else if (exp >= 0)
            {
                //pos = value.find("^");
                num1 = value.substr(0, exp -1);
                num2 = value.substr(exp + 1, end - (exp + 1));
                var1 = is_variable(data, num1);
                var2 = is_variable(data, num2);
                var3 = is_variable(data, variable);
                expoAssembly(num1, var1, num2, var2, variable, var3); 
            }
        }


        
    }
    
    assembly = fullAssembly();
    file.open(assem.c_str(), ios_base::app);
    file << assembly << endl;
    file.close();

    return 0;
}

int is_variable(string data, string var)
{
    if (strstr(data.c_str(), var.c_str()) != NULL)
    {
        return 1;
    }
    return 0;
}