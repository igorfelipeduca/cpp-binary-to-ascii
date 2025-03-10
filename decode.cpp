#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;

string pilhaParaBinario(stack<int> pilha_numeros)
{
    string binario;

    while (!pilha_numeros.empty())
    {
        binario += pilha_numeros.top();
        pilha_numeros.pop();
    }

    reverse(binario.begin(), binario.end());

    return binario;
}

string binarioParaDecimal(string binario)
{
    return to_string(stoi(binario, nullptr, 2));
}

string binarioParaAscii(string binario)
{
    stringstream sstream(binario);
    string ascii;
    while (sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        ascii += c;
    }

    return ascii;
}

void parseETraduzir(stack<int> &lote_numeros, string &binario_final, string &decimal_final)
{
    string binario = pilhaParaBinario(lote_numeros);

    binario_final += binario;
    decimal_final += binarioParaDecimal(binario) + " ";

    while (!lote_numeros.empty())
    {
        lote_numeros.pop();
    }
}

int main()
{
    ifstream Leitor;
    string traducao_final;

    Leitor.open("codigo.txt");

    if (Leitor.is_open())
    {
        char numero;
        stack<int> lote_numeros;
        string string_numeros, binario_final, decimal_final;

        while (Leitor.get(numero))
        {
            if (lote_numeros.size() == 8)
            {
                parseETraduzir(lote_numeros, binario_final, decimal_final);
            }

            lote_numeros.push(numero);
        }

        parseETraduzir(lote_numeros, binario_final, decimal_final);

        stack<int> vazio;
        lote_numeros = vazio;

        cout << "\n ---------- binario ----------\n";
        cout << binario_final;

        cout << "\n\n";

        cout << "\n ---------- decimal ----------\n";
        cout << decimal_final;

        cout << "\n\n";

        cout << "\n ---------- ascii ----------\n";
        cout << binarioParaAscii(binario_final);
    }
    else
    {
        cout << "\nErro ao ler o arquivo";
    }

    return 0;
}
