#pragma once

#include "resource.h"
#include "resource.h"
#include "afxsock.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
#include <fstream>

using namespace std;


typedef SOCKET Socket;
//Ta sẽ tiến hành trả về chuỗi này nếu nằm trong blacklist

//"<span style=\"font - size:50px; color: red\">403<span style=\"font - size : 30px; color: black\"> Forbidden<BR><span style = \"font-size:20px;color: black\">You cannot access this website< / span>";
bool load1 = 1;
//struct chứa Sever và Client để phân nhiều luồng thực hiện Request get and post
// Phân nhiều luồng giữa bằng cách sử dụng thread
void Thoat();
void Goto(int x, int y);
void TextColor(int x);

struct Socket_sever_client
{

	bool Sever_Close;
	bool Client_Close;
	SOCKET Server;
	SOCKET Client;
};

//struct chứa các thông tin của một truy vấn Như địa chỉ port của nó ...
struct Param {
	string address;
	Socket_sever_client *pair;
	int port;
	HANDLE handle;

};
void inputfile(char *, char*);
void outputfile(char *, string &);
//Hàm Bắt đầu khởi tạo  Server để lắng nghe các kết nối từ client chuyển đến cho proxy 
void StartSocket();

// Hàm Thread giao tiếp giữa Proxy Server và WedServer( Remote Server)
unsigned int Proxy_to_websever(void *);

// Hàm thread Giao tiep của client đến proxy thực hiện truy cập từ client đến proxy
unsigned int Client_to_proxy(void *);

// Hàm Đóng các sever lại (đóng cổng giao tiêp lại)
void CloseSocket();

// Hàm Lấy Address và port  đông thời tạo truy vấn   từ truy vấn nhận được từ Client truyền tới
void Get_port(string &b, string &add, int &P);

// Hàm Nhập   Input từ màn Hình conSole Nếu muốn dừng lại thì nhập q vào console .......
unsigned int Get_down(void *);

// Hàm tách chuỗi string
void str_Split(string str, vector<string> &conten, char im = ' ');

// Hàm chuyển char array sang dạng LPCWSTR từ Ví dụ webclient của thầy đưa.


// Hàm chạy file Blacklist Nếu không tồn tại thì cout ra Khong the load được blacklist
// Yêu cầu phải để file Blacklist Chung vs .exe.
void Star_load_blackList(vector<string> &arra);

// Hàm này sẽ tiến hành kiểm tra những địa chỉ mà ta cần tìm trong nằm trong blacklist hay. Hàm trả về giá trị 1 hoặc 0
bool Check_sever_name_inBlackList(string );

/*
struct sockaddr_in {
short            sin_family;   // e.g. AF_INET - 2 bytes
unsigned short   sin_port;     // e.g. htons(3490) - 2 bytes
struct in_addr   sin_addr;     // see struct in_addr, below - 4 bytes
char             sin_zero[8];  // zero this if you want to - 8 bytes
};
*/
// Hàm tiến hành lấy địa chỉ IP để yêu cầu kết nối.
sockaddr_in* Get_IP_Sever(string , char*Domain);


#define HTTPPORT 80
#define HTTP "http://"
#define PORT 8888
#define BUFFERSIZE 



