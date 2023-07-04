#ifndef __PROGTEST__
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#endif /* __PROGTEST__ */

int pow(int x, int y){
    if(y == 0) return 1;
    return x * pow(x, y-1);
}

void fibonacci(vector<int> & fib){   
    fib.push_back(1);
    fib.push_back(1);  
    for(size_t i = 2; i < 30; i++){
        fib.push_back(fib[i - 1] + fib[i - 2]);
    }
}

int convertToInt(const vector<bool> & row){
    int res = 0;
    for(int i = row.size()-1; i >= 0; i--){
        if(row[i]) res += pow(2, (row.size() - 1) - i);
    }
    return res;
}

string convertToFib(int x, const vector<int> & fib){
    vector<int> pos;
    string res;
    for(int i = fib.size()-1; i >= 1; i--){
        if(x >= fib[i]){
            pos.push_back(i);
            x-=fib[i];
        }
    }
    int start = 1;
    for(int i = pos.size()-1; i >= 0; i--){
        while(start != pos[i]){
            start++;
            res.push_back('0');
        }
        start++;
        res.push_back('1');
    }
    res.push_back('1');
    return res;
}

void makeAnswer(string & result, vector<int> & answer){
    vector<bool> bitAnswer;
    int n =result.size() / 8;
    for(int i = 0; i < n; i++){
        for(int ii = 8*i + 7; ii >= 8*i ;ii--){
            bitAnswer.push_back(result[ii] - '0');
        }
        answer.push_back(convertToInt(bitAnswer));
        bitAnswer.clear();
    }
    for(int i = 0; i < n; i++){
        result.erase(0, 8);
    }

}

bool countSeq( bool bit, vector<int> & result, vector<int> &row, const vector<int> & fib){
    result.push_back(-1);
    if(row.size()-1 > 29) return false;
    for(size_t i =0; i < row.size() - 1; i++){
        if(row[i]) result[result.size()-1] += fib[i+1];
    }
    row.clear();
    return true;
}

bool               utf8ToFibonacci                         ( const char      * inFile, 
                                                             const char      * outFile )
{
    ifstream file(inFile, ios::binary);
    if (!file.is_open()) {
        return false;
    }

    vector<int> fib;
    fibonacci(fib);
    ofstream out(outFile, std::ios::out | std::ios::binary);
    if (!out.is_open()) {
        return false;
    }

    char byte;
    vector<bool> row;
    string result;
    vector<int> answer;
    int size_of_utf = 0;
    while (file.read(&byte, 1)) {
        for (int i = 7; i >= 0; i--) {
            bool bit = (byte >> i) & 1;
            if(i == 7 && size_of_utf){
                if(!bit) return false;
                else{
                    i--;
                    bit = (byte >> i) & 1;
                    if(bit) return false;
                    size_of_utf--;
                }
            }
            else if(i == 7 && bit) {
                i--;
                if((byte >> i) & 1){
                    i--;
                    size_of_utf++;
                    if((byte >> i) & 1){
                        i--;
                        size_of_utf++;
                        if((byte >> i) & 1){
                            i--;
                            size_of_utf++;
                            bit = (byte >> i) & 1;
                            if(bit){
                                return false;
                            }
                        }
                    }
                }
                else return false;
            }
            else row.push_back(bit); 
        }
        if(!size_of_utf) {
            int x = convertToInt(row);
            if(x > 1114111) return false; 
            result.append(convertToFib(x + 1, fib));
            makeAnswer(result, answer);
            if(!answer.empty()){
                for(size_t i = 0; i < answer.size(); i++){
                    out.write((char *) &(answer[i]), 1);
                }
                answer.clear();
            }
            if(!out.good()) return false;

            row.clear();
        }
    }
    if(size_of_utf != 0) return false;
    file.close();
    while(result.size() % 8){
        result.push_back('0');
    }
    makeAnswer(result, answer);
    for(size_t i = 0; i < answer.size(); i++){
        out.write((char *) &(answer[i]), 1);
    }
    if(!out.good()) return false;
    out.close();
    return true;
}

bool convertToUtf8(const vector<int>& result, vector<int>& answer) {
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] < 128) {
            answer.push_back(result[i]);
        } else if (result[i] < 2048) {
            answer.push_back(192 | (result[i] >> 6));
            answer.push_back(128 | (result[i] & 63));
        } else if (result[i] < 65536) {
            answer.push_back(224 | (result[i] >> 12));
            answer.push_back(128 | ((result[i] >> 6) & 63));
            answer.push_back(128 | (result[i] & 63));
        } else if (result[i] < 1114112) {
            answer.push_back(240 | (result[i] >> 18));
            answer.push_back(128 | ((result[i] >> 12) & 63));
            answer.push_back(128 | ((result[i] >> 6) & 63));
            answer.push_back(128 | (result[i] & 63));
        } else {
            return false;
        }
    }
    return true;
}

bool               fibonacciToUtf8                         ( const char      * inFile, 
                                                             const char      * outFile )
{
    ifstream file(inFile, ios::binary);
    if (!file.is_open()) {
        return false;
    }

    ofstream out(outFile, std::ios::out | std::ios::binary);
    if (!out.is_open()) {
        return false;
    }

    vector<int> fib;
    fibonacci(fib);

    char byte;
    vector<int> row;
    vector<int> result;
    vector<int> answer;
    while (file.read(&byte, 1)) {
        for (int i = 0; i <= 7; i++) {
            bool bit = (byte >> i) & 1;
            row.push_back(bit);
            if(row.size() >= 2) if(bit && row[row.size() - 2]){
                if(!countSeq(bit, result, row, fib)){
                    return false;
                }
                else{
                    if(!convertToUtf8(result, answer)) return false;
                    else{
                        for(size_t i = 0; i < answer.size(); i++){
                            out.write((char *) &(answer[i]), 1);
                        }
                        answer.clear();
                        result.clear();
                    }
                }
            }
        }
    }
    file.close();
    if(row.size()>=8) return false;
    if(!convertToUtf8(result, answer)) return false;
    for(size_t i = 0; i < answer.size(); i++){
        out.write((char *) &(answer[i]), 1);
    }
    if(!out.good()) return false;

    out.close();
    return true;
}
  
#ifndef __PROGTEST__

int main ( int argc, char * argv [] )
{
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
