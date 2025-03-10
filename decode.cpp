#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;

string stackToBinary(stack<int> numbers_stack)
{
    string binary;

    while (!numbers_stack.empty())
    {
        binary += numbers_stack.top();
        numbers_stack.pop();
    }

    reverse(binary.begin(), binary.end());

    return binary;
}

string binaryToDecimal(string binary)
{
    return to_string(stoi(binary, nullptr, 2));
}

string binaryStringToAscii(string binary)
{
    stringstream sstream(binary);
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

void parseAndTranslate(stack<int> &batch_numbers, string &final_binary, string &final_decimal)
{
    string binary = stackToBinary(batch_numbers);

    final_binary += binary;
    final_decimal += binaryToDecimal(binary) + " ";

    while (!batch_numbers.empty())
    {
        batch_numbers.pop();
    }
}

int main()
{
    ifstream Reader;
    string final_translation;

    Reader.open("codigo.txt");

    if (Reader.is_open())
    {
        char number;
        stack<int> batch_numbers;
        string numbers_string, final_binary, final_decimal;

        while (Reader.get(number))
        {
            if (batch_numbers.size() == 8)
            {
                parseAndTranslate(batch_numbers, final_binary, final_decimal);
            }

            batch_numbers.push(number);
        }

        parseAndTranslate(batch_numbers, final_binary, final_decimal);

        stack<int> empty;
        batch_numbers = empty;

        cout << "\n ---------- binario ----------\n";
        cout << final_binary;

        cout << "\n\n";

        cout << "\n ---------- decimal ----------\n";
        cout << final_decimal;

        cout << "\n\n";

        cout << "\n ---------- ascii ----------\n";
        cout << binaryStringToAscii(final_binary);
    }
    else
    {
        cout << "\nError reading file";
    }

    return 0;
}
