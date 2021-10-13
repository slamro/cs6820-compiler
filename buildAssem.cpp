#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <ctype.h>

using namespace std;

void beginAssembly(string name);
void dataAssembly(string name, string value);
void unInitDataAssembly(string name, string type);
void addAssembly(string num1, int var1, string num2, int var2, string result, int var3);
void subAssembly(string num1, int var1, string num2, int var2, string result, int var3);
void multAssembly(string num1, int var1, string num2, int var2, string result, int var3);
void divAssembly(string num1, int var1, string num2, int var2, string result, int var3);
void expoAssembly(string num1, int var1, string num2, int var2, string result, int var3);
void callAssembly(string call, string variable, int var, string type);
void functionAssembly();
void fullAssembly(string *assem);
void endAssembly(string name);


string beginAsm;
string dataAsm = "\nsection .data\n";
string unInitDataAsm = "\nsection .bss\n";
string textAsm = "\nsection .text\n";
string funcAsm;
string mainAsm = "main:\n";
string endAsm;
bool initData = false;
string expr;
string temp;



void beginAssembly(string name)
{
    string initial = ";--------------\n;Program Name: " + name + "\n;--------------\nGLOBAL main\n \nextern printf\nextern scanf\nextern exit \n\n";
    beginAsm += initial;
    functionAssembly();
}
void functionAssembly()
{
    string printInt = "printInt:\n\n";
    string pushStack = "\tpush \trbp \n\tpush \trax \n\tpush \trcx\n\n";
    string movPrint = "\tmov \trdi, numberPrinter\n \tmov \trsi, rax\n \txor \trax, rax\n\n";
    string movString = "\tmov \trdi, stringPrinter\n \tmov \trsi, rax\n \txor \trax, rax\n\n";
    string callPrint = "\tcall    [rel printf wrt ..got]\n";
    string popStack = "\tpop \trcx \n\tpop \trax \n\tpop \trbp \n\tret\n\n";
    string printString = "printString:\n";  

    printInt = printInt + pushStack + movPrint + callPrint + popStack;
    printString = printString + pushStack + movString + callPrint + popStack; 
    funcAsm = printInt + printString; 
}
void dataAssembly(string name, string value)
{
    if (initData == false)
    {
        string initial = "\tstringPrinter   db \"%s\",0 \n\tnumberPrinter   db \"%d\",0x0d,0x0a,0 \n\tint_format      db \"%i\", 0\n";
        dataAsm = dataAsm + initial;
        initData = true;
    }
    dataAsm = dataAsm + "\t" + name + "\tdw   " + value + "\n";
}
void unInitDataAssembly(string name, string type)
{
    unInitDataAsm = unInitDataAsm + "\t" + name + "\tresb\t1\t;an " + type + "\n";
}
void addAssembly(string num1, int var1, string num2, int var2, string result, int var3)
{
    if (var1 == 1)
    {
        num1 = "[dword " + num1 + "]";
    }
    if (var2 == 1)
    {
        num2 = "[dword " + num2 + "]";
    }
    if (var3 ==1)
    {
        result = "[dword " + result + "]";
    }
    
    expr = "\tmov     rax, " + num1 + " \n\tadd     rax, " + num2 + " \n\tmov     " + result + ", rax\n\n";
    mainAsm  = mainAsm + expr;
}
void subAssembly(string num1, int var1, string num2, int var2, string result, int var3)
{
    if (var1 == 1)
    {
        num1 = "[dword " + num1 + "]";
    }
    if (var2 == 1)
    {
        num2 = "[dword " + num2 + "]";
    }
    if (var3 ==1)
    {
        result = "[dword " + result + "]";
    }

    expr = "\tmov     rax, " + num1 + " \n\tsub     rax,  " + num2 + " \n\tmov     " + result + ", rax\n\n";
    mainAsm  = mainAsm + expr;
}
void multAssembly(string num1, int var1, string num2, int var2, string result, int var3)
{
    if (var1 == 1)
    {
        num1 = "[dword " + num1 + "]";
    }
    if (var2 == 1)
    {
        num2 = "[dword " + num2 + "]";
    }
    if (var3 ==1)
    {
        result = "[dword " + result + "]";
    }
    
    expr = "\tmov     rax, " + num1 + " \n\timul     rax, " + num2 + " \n\tmov     " + result + ", rax\n\n";
    mainAsm  = mainAsm + expr;
}
void divAssembly(string num1, int var1, string num2, int var2, string result, int var3)
{
    if (var1 == 1)
    {
        num1 = "[dword " + num1 + "]";
    }
    if (var2 == 1)
    {
        num2 = "[dword " + num2 + "]";
    }
    if (var3 ==1)
    {
        result = "[dword " + result + "]";
    }
    
    expr = "\tmov     rax, " + num1 + " \n\tdiv     rax, " + num2 + " \n\tmov     " + result + ", rax\n\n";
    mainAsm  = mainAsm + expr;
}
void expoAssembly(string num1, int var1, string num2, int var2, string result, int var3)
{
    string prepLoop;
    string expoLoop;
    string answer;

    if (var1 == 1)
    {
        num1 = "[dword " + num1 + "]";
    }
    if (var2 == 1)
    {
        num2 = "[dword " + num2 + "]";
    }
    if (var3 ==1)
    {
        result = "[dword " + result + "]";
    }
    
    prepLoop = "\n\txor     rdi, rdi \n\tmov     rcx, 1 \n\tmov     rax, " + num2 + " \n\tmov     rdx, rax \n\tmov     rax, 1\n";
    expoLoop = "exp_start: \n\tcmp     rdi, rdx \n\tjz      exp_done \n\timul    rax, " + num1 + " \n\tinc     rdi \n\tjmp     exp_start \n";
    answer = "exp_done: \n\tmov     " + result + ", rax\n";
        
    mainAsm = mainAsm + prepLoop + expoLoop + answer;


}
void callAssembly(string call, string variable, int var, string type)
{
    if (var = 1)
    {
        variable = "[dword " + variable + "]";
    }
    
    temp = "\tmov \trax, " + variable + "\n";
    
    if (type.find("i") == 0)
    {
        temp = temp + "\tcall \tprintInt\n";
    }
    if (type.find("s") == 0)
    {
        temp = temp + "\tcall \tprintString\n";
    }
    mainAsm = mainAsm + temp;

}
string fullAssembly()
{  
    temp = beginAsm + dataAsm + unInitDataAsm + textAsm + funcAsm + mainAsm + endAsm;
    return temp;
}
void endAssembly(string name)
{
    endAsm = "my_exit: \n\tmov \trax, 60 \n\txor \trdi, rdi \n\tsyscall";
}