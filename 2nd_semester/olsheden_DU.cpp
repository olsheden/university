//------------------------------------------
// Name         : Server.cpp
// Author       : Denis Olshevskiy
// Version      :
// Copyright    : 
// Description  : TCP-server test
//-----------------------------------------
#include <iostream>
#include <unistd.h>         
#include <string.h>        
#include <sys/wait.h>       
#include <arpa/inet.h>
#include <cmath>
#include <sstream>

#define PORT 9090
#define BUFFER_SIZE 1000

using namespace std;


int getCmdLine(string* str, int* number_of_letter, int max_size, int connect);
//------------------------------------ERRORS------------------------------------------------------

int loginError(int connect){
    send (connect, "300 LOGIN FAILED\a\b", 18, 0);
    cout << "300 LOGIN FAILED\a\b" << endl;  
    close(connect); 
    return 1;
}

int syntaxError(int connect){
    send (connect, "301 SYNTAX ERROR\a\b", 18, 0);
    cout << "301 SYNTAX ERROR\a\b" << endl;
    close(connect);
    return 1;
}

int keyError(int connect){
    send (connect, "303 KEY OUT OF RANGE\a\b", 22, 0);
    cout << "303 KEY OUT OF RANGE\a\b" << endl;
    close(connect);
    return 1;
}

int logError(int connect){
    send (connect, "302 LOGIC ERROR\a\b", 17, 0);
    cout << "302 LOGIC ERROR\a\b" << endl;
    close(connect);
    return 1;
}

//--------------------------USERNAME--------------------------------------------------------------

int checkSpaces(string str, int size, int x, int connect){
    int number_of_spaces = 0;
    for(int i = 0; i < size; i++){
        if(str[i] == ' ')number_of_spaces++;
    }
    if(number_of_spaces != x){
        return syntaxError(connect);
    }
    else return 0;
}

int findDelimiter(string str, int* size){
    for(int i = 0; i < str.size(); i++){
        if(str[i] == '\a' && str[i+1] == '\b'){
            *size = i+2;
            return 1;
        }
    }
    return 0;
}

string convertToString(char* a, int size)
{
    string s = "";
    for (int i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int transformation(string username, int size){
    int result = 0;
    for(int i = 0; i < size; i++){
        result += username[i];
    }
    return ((result*1000)%65536);
}

void sendresult(int confirm, int connect){
    string arr = to_string(confirm);
    char serv_conf[arr.length() + 2];
    strcpy(serv_conf, arr.c_str());
    strcat(serv_conf, "\a\b");
    send (connect, serv_conf, sizeof(serv_conf), 0);
}

int convertToInt(string client_conf, int size, int connect){
    if(checkSpaces(client_conf, size, 0, connect)) return 1;
    int result = 0;
    for(int i = size-1; i >= 0; i--){
        result += ((((int)client_conf[i] - 48))*pow(10, ((size-1)-i)));
    }
    return result;
}

bool checkKeys(int connect, char key_id){
    if((int)key_id < 48 || (int)key_id > 57){
        syntaxError(connect);
        return false;
    }
    else if((int)key_id > 52){
        keyError(connect);
        return false;
    }
    else return true;
}

bool compareKeys(int cl_conf, int key, int hash){
    int client_key[5] = {32037, 29295, 13603, 29533, 21952}; //client key
    int confirm = (hash + client_key[key]) % 65536;
    if(cl_conf == confirm) {
        return true;
    }
    else return false;
}
//-----------------------TRANSPORTATION-----------------------------------------------------------
bool check(int x1, int y1, int x2, int y2){
    if(x1 == x2 && y2 == y1) return true;
    else {
        return false;
    }
}

int recharging(int connect, string* str, int number_of_letter){
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    for(int i = 0; i < number_of_letter; i++) {
        (*str).erase(0,1);
    }
    setsockopt(connect, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    if(getCmdLine(str, &number_of_letter, 12, connect)) return 1;
    string copy = *str;
    copy.erase(number_of_letter-2, copy.size() - (number_of_letter - 2));
    stringstream ss(copy);
    string word[number_of_letter];
    int number_of_word = 0;
    while(ss){
        ss >> word[number_of_word];
        number_of_word++;
    }
    if(word[0] == "FULL" && word[1] == "POWER") {
        (*str).erase(0, number_of_letter);
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        setsockopt(connect, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        return 0;
    }
    else {
        logError(connect);
        return 1;
    }
}

int rechargingInMain(string* str, int connect){
    int number_of_letter = 0;
    findDelimiter(*str, &number_of_letter);
    if(number_of_letter < 12) return 3;
    string copy = *str;
    copy.erase(number_of_letter-2, copy.size() - (number_of_letter - 2));
    stringstream ss(copy);
    string word[BUFFER_SIZE];
    int number_of_word = 0;
    while(ss){
        ss >> word[number_of_word];
        number_of_word++;
    }
    if(word[0] == "RECHARGING"){
        if(recharging(connect, str, number_of_letter)) return 1;
        return 0;
    }
    return 3;
}

int get_message(int* x, int* y, int connect, string* str);

int sendTurns(string* str, int x2, int y2, const char* x, int size, int connect){
    int check_x, check_y;
    cout << x << endl;
    send (connect, x, size, 0);
    if(get_message( &check_x, &check_y, connect, str)) return 1;
    if (!check(x2, y2, check_x, check_y)) return 1;
    return 0;
}

int assignment(int* x, int* y, string* str, int number_of_letter, int connect){
    string copy = *str;
    copy.erase(number_of_letter-2, copy.size() - (number_of_letter - 2));
    stringstream ss(copy);
    string word[BUFFER_SIZE];
    int number_of_word = 0;
    while(ss){
        ss >> word[number_of_word];
        number_of_word++;
    }   
    if(word[0] == "OK"){
        if(checkSpaces(*str, number_of_letter-2, 2, connect)) return 1;
        if(number_of_word != 4){
            syntaxError(connect);
            return 1;
        }
        char arr1[word[1].length()];
        strcpy(arr1,word[1].c_str());
        for (int i = 0; i < word[1].length(); i++)
        {
            if(isalpha(arr1[i] || (int)arr1[i] == 46)){
                syntaxError(connect);
                return -1;
                break;
            } else {
                *x = stoi(word[1]);
            }
        }
        char arr2[word[2].length()];
        strcpy(arr2,word[2].c_str());
        for (int i = 0; i < (word[2].length()); i++)
        {
            if(isalpha(arr2[i]) || (int)arr2[i] == 46){
                syntaxError(connect);
                return -1;
                break;
            } else {
                *y = stoi(word[2]);
            }
        }
        (*str).erase(0, number_of_letter);
        return 0;
    } 
    else if(word[0] == "RECHARGING"){
        if(checkSpaces(*str, number_of_letter-2, 0, connect)) return 1;
        if(recharging(connect, str, number_of_letter)) return 1;
        if(get_message(x, y, connect, str) ) return 1;
        return 0;
    }
    else {
        return syntaxError(connect);
    }


}

int get_message(int* x, int* y, int connect, string* str){
    int number_of_letter;    
    char buffer[BUFFER_SIZE]; // field of characters
    if(getCmdLine(str, &number_of_letter, 12, connect)) return 1;
    if(assignment(x, y, str, number_of_letter, connect)) return 1;
    cout << "[" << *x << ", " << *y << "]" << endl;
    return 0;
}

string determDirection(int x1, int y1, int x2, int y2){
    if(!((x2 - x1 == 1 && y1 == y2) || (x2 - x1 == -1 && y1 == y2) || (x1 == x2 && y2 - y1 == 1) || (x1 == x2 && y2 - y1 == -1))) return "Error";
    if(x1 == x2){
        if(y1 < y2) return "Up";
        else return "Down";
    }
    else{
        if(x1 < x2) return "Right";
        else return "Left";
    }
}

int Turn_x(int x2, int y2, string* dir, int connect, string* str){
    int check_x;
    int check_y;
    if(x2 < 0){
        if((*dir) == "Right")return 0;
        else if((*dir) == "Left"){
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            *dir = "Right";
            return 0;
        }
        else if( *dir == "Up"){
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            *dir = "Right";
            return 0;
        }
        else{
            if(sendTurns(str, x2, y2, "103 TURN LEFT\a\b", 15, connect)) return 1;
            *dir = "Right";
            return 0;
        }
    }
    else if(x2 > 0){
        if((*dir) == "Left")return 0;
        else if((*dir) == "Right"){
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            *dir = "Left";
            return 0;
        }
        else if(*dir == "Up"){
            if(sendTurns(str, x2, y2, "103 TURN LEFT\a\b", 15, connect)) return 1;
            *dir = "Left";
            return 0;
        }
        else{
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            *dir = "Left";
            return 0;
        }
    }
    return 0;
}

int Turn_y(int x2, int y2, string* dir, int connect, string* str){
    int check_x;
    int check_y;
    if(y2 < 0){
        if((*dir) == "Up")return 0;
        else if((*dir) == "Left"){
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            *dir = "Up";
            return 0;
        }
        else if(*dir == "Right"){
            if(sendTurns(str, x2, y2, "103 TURN LEFT\a\b", 15, connect)) return 1;
            *dir = "Up";
            return 0;
        }
        else if(*dir == "Down"){
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            *dir = "Up";
            return 0;
        }
    }
    else if (y2 > 0){
        if((*dir) == "Down")return 0;
        else if((*dir) == "Left"){
            if(sendTurns(str, x2, y2, "103 TURN LEFT\a\b", 15, connect)) return 1;
            *dir = "Down";
            return 0;
        }
        else if(*dir == "Right"){
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            *dir = "Down";
            return 0;
        }
        else if(*dir == "Up"){
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            if(sendTurns(str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
            *dir = "Down";
            return 0;
        }
    }
    return 0;
}

int MoveIncy(int x, int* y, int connect, string* str){
    int check_x;
    int check_y;
    cout << "102 MOVE\a\b" << endl;
    send (connect, "102 MOVE\a\b", 10, 0);
    if(get_message( &check_x, &check_y, connect, str)) return 1;
    (*y)++;
    if (!check(x, *y, check_x, check_y)){
        return 1;
    }
    return 0;
}

int MoveDecy(int x, int* y, int connect, string* str){
    int check_x;
    int check_y;
    cout << "102 MOVE\a\b" << endl;
    send (connect, "102 MOVE\a\b", 10, 0);
    if(get_message( &check_x, &check_y, connect, str)) return 1;
    (*y)--;
    if (!check(x, *y, check_x, check_y)){
        return 1;
    }
    return 0;
}

int MoveIncx(int* x, int y, int connect, string* str){
    int check_x;
    int check_y;
    cout << "102 MOVE\a\b" << endl;
    send (connect, "102 MOVE\a\b", 10, 0);
    if(get_message( &check_x, &check_y, connect, str)) return 1;
    (*x)++;
    if (!check(*x, y, check_x, check_y)){
        return 1;
    }
    return 0;
}

int MoveDecx(int* x, int y, int connect, string* str){
    int check_x;
    int check_y;
    cout << "102 MOVE\a\b" << endl;
    send (connect, "102 MOVE\a\b", 10, 0);
    if(get_message( &check_x, &check_y, connect, str)) return 1;
    (*x)--;
    if (!check(*x, y, check_x, check_y)){
        return 1;
    }
    return 0;
}

int MOVEx(int* x, int* y, string* dir, int* m_stav, int connect, string* str){
    int check_x;
    int check_y;
    cout << "102 MOVE\a\b" << endl;
    send (connect, "102 MOVE\a\b", 10, 0);
    if(get_message( &check_x, &check_y, connect, str)) return 1;
    if(*dir == "Right"){
        if (check(*x, *y, check_x, check_y)){
            if(*y != 0) {
                if(Turn_y(*x, *y, dir, connect, str)) return 1;
            }
            else {
                if(sendTurns(str, *x, *y, "104 TURN RIGHT\a\b", 16, connect)) return 1;
                *dir = "Down";
            }
            if(*dir == "Down"){
                if(MoveDecy(*x, y, connect, str)) return 1;
            }
            else if(*dir == "Up"){ 
                if(MoveIncy(*x, y, connect, str)) return 1;
            }
            if(Turn_x(*x, *y, dir, connect, str)) return 1;
            if(MoveIncx(x, *y, connect, str)) return 1;
            (*m_stav)--;
            if(*m_stav == 0) {
                return 1;
            }
            return 0;
        }
        else{ 
            (*x)++;
            if (!check(*x, *y, check_x, check_y)) return 1;
            return 0;
        }
    }
    else if(*dir == "Left"){
        if (check(*x, *y, check_x, check_y)){
            if(*y != 0) {
                if(Turn_y(*x, *y, dir, connect, str)) return 1;
            }
            else {
                if(sendTurns(str, *x, *y, "104 TURN RIGHT\a\b", 16, connect)) return 1;
                *dir = "Up";
            }
            if(*dir == "Down") {
                if(MoveDecy(*x, y, connect, str)) return 1;
            }
            else if(*dir == "Up") {
                if(MoveIncy(*x, y, connect, str)) return 1;
            }
            if(Turn_x(*x, *y, dir, connect, str)) return 1;
            if(MoveDecx(x, *y, connect, str)) return 1;
            (*m_stav)--;
            if(*m_stav == 0){
                return 1;
            }
            return 0;
        }
        else{
            (*x)--;
            if (!check(*x, *y, check_x, check_y)){
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

int MOVEy(int* x, int* y, string* dir, int* m_stav, int connect, string* str){
    int check_x;
    int check_y;
    cout << "102 MOVE\a\b" << endl;
    send (connect, "102 MOVE\a\b", 10, 0);
    if(get_message( &check_x, &check_y, connect, str)) return 1;
    if(*dir == "Up"){
        if(check(*x, *y, check_x, check_y)){
            if(*x != 0) {
                if(Turn_x(*x, *y, dir, connect, str)) return 1;
            }
            else {
                if(sendTurns(str, *x, *y, "104 TURN RIGHT\a\b", 16, connect)) return 1;
                *dir = "Right";
            }
            if(*dir == "Left"){
                if(MoveDecx(x, *y, connect, str))return 1;
            }
            else if(*dir == "Right"){
                if(MoveIncx(x, *y, connect, str)) return 1;
            }
            if(Turn_y(*x, *y, dir, connect, str)) return 1;
            if(MoveIncy(*x, y, connect, str)) return 1;
            (*m_stav)--;
            if(*m_stav == 0){
                return 1;
            }
            return 0;
        }
        else{ 
            (*y)++;
            if (!check(*x, *y, check_x, check_y)){
                return 1;
            }
            return 0;
        }
    }
    else if(*dir == "Down"){
        if (check(*x, *y, check_x, check_y)){
            if(*x != 0) {
                if(Turn_x(*x, *y, dir, connect, str)) return 1;
            }
            else {
                if(sendTurns(str, *x, *y, "104 TURN RIGHT\a\b", 16, connect)) return 1;
                *dir = "Left";
            }
            if(*dir == "Left") {
                if(MoveDecx(x, *y, connect, str)) return 1;
            }
            else if(*dir == "Right"){ 
                if(MoveIncx(x, *y, connect, str)) return 1;
            }
            if(Turn_y(*x, *y, dir, connect, str)) return 1;
            if(MoveDecy(*x, y, connect, str)) return 1;
            (*m_stav)--;
            if(*m_stav == 0){
                cout << "ok" << endl;
                return 1;
            }
            return 0;
        }
        else{
            (*y)--;
            if (!check(*x, *y, check_x, check_y)){
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

int transportation(int* x2, int* y2, string* dir, int* m_stav, int connect, string* str){
    while(!(*x2 == 0 && *y2 == 0)){
        if((*x2) != 0) if(Turn_x(*x2, *y2, dir, connect, str)) return 1;
        while(*x2 != 0){
            if(MOVEx(x2, y2, dir, m_stav, connect, str)) return 1;
        }
        if(*y2 != 0) if(Turn_y(*x2, *y2, dir, connect, str)) return 1;
        while(*y2 != 0){
            if(MOVEy(x2, y2, dir, m_stav, connect, str)) return 1;
        }
    }
    return 0;
}

//-------------------------------------input-------------------------------------------------------

int getCmdLine(string* str, int* number_of_letter, int max_size, int connect)
{
    char buffer[BUFFER_SIZE]; 
    int res;
    while(true){
        if(findDelimiter(*str, number_of_letter)){
            if((res =rechargingInMain(str, connect)) == 0){
                continue;
            }
            else if(res == 1) return 1;
            else break;
        }
        int bytesRead = recv(connect, buffer, BUFFER_SIZE, 0); 
        if (bytesRead <= 0){
            perror("Can't read a socket: ");
            close(connect);
            return -3;
        }
        buffer[bytesRead] = '\0';
        *str += convertToString(buffer, bytesRead);
        if(findDelimiter(*str, number_of_letter)){
            if((res =rechargingInMain(str, connect)) == 0){
                continue;
            }
            else if(res == 1) return 1;
            else break;
        }
        if((*str).size() >= max_size) {
            return syntaxError(connect);
        }
    }
    return 0;
}

//-------------------------------------EXIT--------------------------------------------------------

int exitCom(int connect){
    cout << "106 LOGOUT\a\b" << endl;
    send (connect, "106 LOGOUT\a\b", 12, 0);
    close (connect);
    return -1;
}

int exitMessage(int connect, string* str){
    int number_of_letter;    
    char buffer[BUFFER_SIZE];
    int res;
    while(true){
        if(findDelimiter(*str, &number_of_letter)){
            if((res =rechargingInMain(str, connect)) == 0){
                continue;
            }
            else if(res == 1) return 1;
            else break;
        }
        int bytesRead = recv(connect, buffer, BUFFER_SIZE, 0);
        if (bytesRead <= 0){
            perror("Can't read a socket: ");
            close(connect);
            return -3;
        }
        buffer[bytesRead] = '\0';
        *str += convertToString(buffer, bytesRead);
        if(findDelimiter(*str, &number_of_letter)){
            if((res =rechargingInMain(str, connect)) == 0){
                continue;
            }
            else if(res == 1) return 1;
            else break;
        }
        if((*str).size() >= 100) {
            return syntaxError(connect);
        }
    }
    exitCom(connect);
    return -1;
}
//-------------------------------------------------------------------------------------------------

int main (int argc, char **argv) 
{
    int listening = socket(AF_INET, SOCK_STREAM, 0); 
    if (listening < 0){
        perror("Can't create a socket!");
        return -1;
    }
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET; 
    address.sin_port = htons(PORT); 
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listening,(struct sockaddr*)&address, sizeof(address)) == -1){
        perror("Can't bind: ");
        close(listening);
        return -1;
    }

    if (listen(listening, 10) < 0){
        perror("Can't listen: ");
        close(listening);
        return -1;
    }

    struct sockaddr_in remote_address;
    socklen_t size;

    while(true){
        int connect = accept(listening, (struct sockaddr*) &remote_address, &size);
        if (connect < 0){
            perror("Accept error!");
            close(listening);
            return -1;
        }

        pid_t pid = fork();   
        if (pid == 0){              
            close(listening);       
            fd_set sockets;
            int retval; 
            while(true){
                
                struct timeval timeout;
                timeout.tv_sec = 1;
                timeout.tv_usec = 0;
                if (setsockopt (connect, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout)) < 0){
                    perror("setsockopt failed\n");
                }
                if (setsockopt (connect, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof (timeout)) < 0){
                    perror("setsockopt failed\n");
                }
                
                //------------------------------------------USERNAME---------------------------------------------
                int number_of_letter;
                string str = "";
                if(getCmdLine(&str, &number_of_letter, 20, connect)) return 1;
                if (number_of_letter >= 20){
                    syntaxError(connect);
                    break;
                }
                int hash = transformation(str, number_of_letter - 2); 
                str.erase(0, number_of_letter);
                cout << str << endl;
                //-----------------------------------------KEY-REQUEST-------------------------------------------- 
                cout << "107 KEY REQUEST\a\b" << endl;
                send (connect, "107 KEY REQUEST\a\b", 17, 0);
                int server_key[5] = {23019, 32037, 18789, 16443, 18189}; 
                getCmdLine(&str, &number_of_letter, 5, connect);
                if(!checkKeys(connect, str[0])) break;
                
                if (number_of_letter > 6){
                    syntaxError(connect);
                    break;
                }
                int key = str[0] - 48;
                int server_conf = (hash + server_key[key]) % 65536;
                sendresult(server_conf, connect);
                //------------------------------------CLIENT-CONF----------------------------------------------------------------------------
                str.erase(0, number_of_letter);
                getCmdLine(&str, &number_of_letter, 7, connect);
                if (number_of_letter > 7){
                    syntaxError(connect);
                    break;
                }
                int cl_conf = convertToInt(str, number_of_letter-2, connect);
                if(cl_conf == -1){
                    syntaxError(connect);
                    break;
                }
                if(!compareKeys(cl_conf, key, hash)){
                    loginError(connect);
                    break;
                }
                cout << "200 OK\a\b" << endl;
                send (connect, "200 OK\a\b", 8, 0);
                str.erase(0, number_of_letter);
//-------------------------------------------------------------------------------------------------------                  
                int x2, y2, x1, y1; 
                int m_stav = 20;
                int turns = 0;
                cout << "102 MOVE\a\b" << endl;
                send (connect, "102 MOVE\a\b", 10, 0);
                if(get_message( &x1, &y1, connect, &str)) break;
                cout << "102 MOVE\a\b" << endl;
                send (connect, "102 MOVE\a\b", 10, 0);
                if(get_message( &x2, &y2, connect, &str)) break;
                while(check(x1, y1, x2, y2) && turns != 3){
                    if(sendTurns(&str, x2, y2, "104 TURN RIGHT\a\b", 16, connect)) return 1;
                    cout << "102 MOVE\a\b" << endl;
                    send (connect, "102 MOVE\a\b", 10, 0);
                    if(get_message( &x2, &y2, connect, &str)) return 1;
                    if(check(x1, y1, x2, y2)) turns++;
                    if(turns == 3) return 1;
                }
                string dir = determDirection(x1, y1, x2, y2);
                if(dir == "Error"){ 
                    break;
                }
                if(transportation(&x2, &y2, &dir, &m_stav, connect, &str)){
                    return 1;
                }
                cout << "105 GET MESSAGE\a\b" << endl;
                send (connect, "105 GET MESSAGE\a\b", 17, 0);
                exitMessage(connect, &str);
                //-------------------------------------------------------------------------------------------------------
                break;
            }
            close(connect);
            return 0;
        }
    int status = 0;
    waitpid(0, &status, WNOHANG);
    close(connect);
    }
    return 0;
}