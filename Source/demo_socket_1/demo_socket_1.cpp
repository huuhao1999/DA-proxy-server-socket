// demo_socket_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "demo_socket_1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object
CWinApp theApp;
vector<string> BLACKLIST;
//Socket dùng để lắng nghe các truy cập mới
Socket Listen_new_access;
#define BUFFERSIZE 20000
// chuỗi html in ra 403forbidden
string Prohibit_access="<!DOCTYPE html><html><head></head><body><center><table border = \"10\" cellpadding = \"20\" cellspacing = \"5\"><tr><td><b><span style = \"font-size:60px;color: red\">403<span style = \"font-size:40px;color: black\"> Forbidden<BR></b><span style = \"font-size:23px;color: black\">You cannot access this website</span></td></tr></table></center></body></html>";
//
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			
			// TODO: code your application's behavior here.
			AfxSocketInit();

			//outputfile("forbidden403.txt", Prohibit_access);
			TextColor(8);
			cout << "\n\t\t\t\t   -------------DO AN PROXY-SEVER-------------";
			cout << "\n\t\t\t\t     Nguyen Huu Hao             MSSV:1712419";
			cout << "\n\t\t\t\t     Mang Vien Trieu            MSSV:1712837";
			cout << "\n\t\t\t\t     Tran Quoc Toan             MSSV:1712827";
			cout << "\n\t\t\t\t     Ho Nguyen Chi Trung        MSSV:1712844";
			cout << "\n------------------------------------------------------------------------------------------------------------------------";
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			TextColor(7);
			StartSocket();
			while (load1) {
				Sleep(1200);
			}

			//Đóng

			CloseSocket();

			//socket
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
void TextColor(int x)//Xac dinh mau cua chu
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void Goto(int x, int y){
	COORD co = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co);
}
void Thoat()
{

	system("cls");
	TextColor(10);

	int dem = 0;
	while (dem <= 25)
	{
		if (dem % 2 == 0)
		{

			Goto(45 + dem * 2, 3 + dem);
			if (dem<12)
				TextColor(dem);
			else{
				TextColor(dem - 9);
			}
			cout << "XIN CHAO! HEN GAP LAI!" << endl;
			Sleep(70);
			dem++;
		}
		else{

			Goto(45 - dem * 2, 3 + dem);
			if (dem<12)
				TextColor(dem);
			else{
				TextColor(dem - 10);
			}
			cout << "GOODBYE! SEE YOU AGAIN!" << endl;
			Sleep(70);
			if (dem % 3 == 0){ system("cls"); TextColor(7); };
			dem++;
		}

	}
	TextColor(7);
	//	ExitProcess(0);
}

void StartSocket()
{
	
	//listen socket
	Socket Soket_Listen_dt;
	WSADATA Data;
	cout << "\nIf you want to close the socket Then Input string:'end'\n";
	sockaddr_in lcl;
	//Cài đặt các Socket
	//Một con trỏ tới cấu trúc dữ liệu WSADATA để nhận chi tiết về việc triển khai Windows Sockets.
	//Nếu thành công, hàm WSAStartup trả về 0. Mặt khác, nó trả về một trong các mã lỗi được liệt kê dưới đây.
	if (WSAStartup(0x202, &Data) != 0)
	{
		// Lỗi khởi tạo socket.
		cout << "\nSocket initialization error!\n";
		// Đóng socket lu
		WSACleanup();
		return;
	}

	//Khởi tạo địa chỉ máy chủ và cổng 
	lcl.sin_family = AF_INET; // Phân biệt socket thuoc họ gì IPv4 Hoặc IPv6... 2bytes
	// gán port đầu vào  8888
	lcl.sin_port = htons(PORT);
	lcl.sin_addr.s_addr = INADDR_ANY;
	
	// loại socket la sock stream vì dùng cho connection nhu TCP
	//int socket(int domain, int type, int protocol);
	Soket_Listen_dt = socket(AF_INET, SOCK_STREAM, 0);
	// Create a SOCKET for connecting to server
	if (Soket_Listen_dt == INVALID_SOCKET)
	{
		// Socket khởi tạo không hợp lệ
		cout << "\Invalid initialization socket.";
		WSACleanup();
		return;
	}
	//Bind Socket 
	// dungf bin để ép kiểu qua lại giữa sockaddr và sockaddr_in
	if (bind(Soket_Listen_dt, (sockaddr *)&lcl, sizeof(lcl)) != 0)
	{
		cout << "\nBind failed with error.";
		WSACleanup();
		return;
	};
	//Bắt đầu lắng nghe các truy cập, listen tra về 0 nếu k nghe được
	// số kết nối cho phép của hàng đợi là 5 các yêu cầu của đối tác sẽ đc lưu trong quêu cho tới khi accept
	if (listen(Soket_Listen_dt, 5) != FALSE)
	{
		cout << "\n listen failed with error:";
		WSACleanup();	return;
	}
	//Bắt đầu tiến chạy black list. 
	Star_load_blackList(BLACKLIST);
	if (BLACKLIST.size() == 0)
	{
		cout << "Blacklist cannot load!!!" << endl;
	}
	Listen_new_access = Soket_Listen_dt;
	//Bắt đầu thread đợi input console để dừng nhập end để dừng.!!!
	CWinThread* pa = AfxBeginThread(Get_down, &load1);

	//star thread comunicate between Client and Proxy Server
	AfxBeginThread(Client_to_proxy, (LPVOID)Soket_Listen_dt);
}

// con tro void có thể trỏ đến bất kì kiểu dữ liệu nào.
// con trỏ voi cần phải ép kiểu dữ liệu qua kiểu dữ kiệu cần dùng mới sài đc
unsigned int Client_to_proxy(void * lPm)
{

	Socket_sever_client paraccess;
	SOCKET SocketClient;
	// Khởi tạo máy chủ
	sockaddr_in DiaCh;
	char Buffer[BUFFERSIZE];
	Socket socket_to = (Socket)lPm;
	// Lấy kích thước của addr
	int addr_Lenght = sizeof(DiaCh);

	//Truy cập mới
	// Truyền vào socket file, poiter trỏ tới sockaddr, và kích thước của sockaddr_in
	SocketClient = accept(socket_to, (sockaddr*)&DiaCh, &addr_Lenght);

	// Khởi tạo mới một thread khác để tiếp tục lắng nghe. đa luồng
	AfxBeginThread(Client_to_proxy, lPm);

	//gán
	paraccess.Client = SocketClient;
	
	Sleep(500);
	//gán các giá trị về False mặc định.
	paraccess.Sever_Close = FALSE;
	paraccess.Client_Close = FALSE;
	//Nhận truy vấn gởi tới từ Client
	//nếu temp_1 = SOCKET_ERROR đồng nghĩa recv failed
	int temp_1 = recv(paraccess.Client, Buffer, BUFFERSIZE, 0);
	if (temp_1 == SOCKET_ERROR)
	{
		cout << "\nError!!! When receive request.\n";
		//Tiến hành đóng
		if (!paraccess.Client_Close)
		{
			closesocket(paraccess.Client);
			paraccess.Client_Close = TRUE;
		}
	}
	//Client ngắt kết nối.
	if (temp_1 == 0)
	{
		cout << "\nClient- Disconnect!." << endl;
		if (!paraccess.Client_Close) {
			closesocket(paraccess.Client);
			paraccess.Client_Close = TRUE;
		}
	}
	Sleep(1200);

	if (temp_1 >= BUFFERSIZE)
		Buffer[temp_1 - 1] = 0;
	else
	if (temp_1 > 0)  Buffer[temp_1] = 0;
	else Buffer[0] = 0;
	//Xuất truy vấn ra bao nhieu data vaf nhung dữ liệu đc nhận về
	cout << "\n Client received " << temp_1 << " data \n["<< Buffer <<"]";
	//
	//sao chep toan bo dự liệu của bufer vào buf
	string strbuf = Buffer;
	int check_list = 0;
	string address_inbl;
	int Port;
	Get_port(strbuf, address_inbl, Port);
	if (!Check_sever_name_inBlackList(address_inbl))
	{
		//Nếu địa chỉ nằm trong black list sẽ trả về Error 403 mà không phải gởi truy vấn tới remote server
		temp_1 = send(paraccess.Client, Prohibit_access.c_str(), Prohibit_access.size(), 0);
		check_list = 1;
		Sleep(2000);
	}
	Param Pa;
	Pa.handle = CreateEvent(NULL, TRUE, FALSE, NULL);
	Pa.address = address_inbl;
	Pa.port = Port;
	Pa.pair = &paraccess;
	if (check_list == 0)
	{
		//Bắt đầu thread giao tiếp giữa Proxy Server và Remote Server.... Tiến hành chạy Proxy_to_websever 
		CWinThread* pThread = AfxBeginThread(Proxy_to_websever, (LPVOID)&Pa);
		//Đợi cho Proxy kết nối với Server
		// chờ 5000 mili giay
		WaitForSingleObject(Pa.handle,5000);
		/*
		DWORD WaitForSingleObject(
        HANDLE hHandle,
        DWORD  dwMilliseconds
        );*/
		CloseHandle(Pa.handle);

		while ((paraccess.Client_Close != TRUE) && (paraccess.Sever_Close != TRUE))
		{
			//Proxy gửi truy vấn tới .
			Sleep(1200);
			Sleep(1200);
			temp_1 = send(paraccess.Server, strbuf.c_str(), strbuf.size(), 0);

			if (temp_1 == SOCKET_ERROR)
			{
				Sleep(500);
				cout << "Send Failed, Error: ";
				cout << GetLastError() << endl;

				Sleep(500);
				if (paraccess.Sever_Close != TRUE) {
					closesocket(paraccess.Server);
					paraccess.Sever_Close = TRUE;
				}
				//tiep tục
				continue;
			}
			//Continue revice cách truy vấn từ client gửi tới
			// Dự lieeeuj sau khi sever nhân đc sẽ phản hồi lại với proxy để gửi lại cho client
			//CHạy Cho đến khi hết dữ liệu thì 1 trong 2 client hoặc sever sẽ ngắt kết nối
			// Nhận gói tin
			//BUFFERSIZE mặc định 20000
			temp_1 = recv(paraccess.Client, Buffer, BUFFERSIZE, 0);
			//Fail
			if (temp_1 == SOCKET_ERROR)
			{
				cout << "C Receive Failed, Error: ";
				cout << GetLastError();
				if (paraccess.Client_Close != TRUE) {
					closesocket(paraccess.Client);
					paraccess.Client_Close = TRUE;
				}
				continue;

			}
			if (temp_1 == 0)
			{
				Sleep(1200);
				cout << "Client closed " << endl;
				if (paraccess.Client_Close != TRUE) {
					closesocket(paraccess.Server);
					paraccess.Client_Close = TRUE;
				}
				break;
			}
			if (temp_1 >= BUFFERSIZE) {
				Buffer[temp_1 - 1] = 0;
			}
			else
			{
				if (temp_1 > 0)
				{
					Buffer[temp_1] = 0;
				}
				else
				{
					Buffer[0] = 0;
				}
			}
		
			//Client gửi lại...
			Sleep(1200);

			cout << "\n Client received: " << temp_1 << "data :\n[" << Buffer << "]";
		}
		if (paraccess.Sever_Close != TRUE)
		{
			closesocket(paraccess.Server);
			paraccess.Sever_Close = TRUE;
		}
		if (paraccess.Client_Close != TRUE)
		{
			closesocket(paraccess.Client);
			paraccess.Client_Close = TRUE;
		}
		//Đếm thời gian
		WaitForSingleObject(pThread->m_hThread, 20000);
	}
	else {
		if (paraccess.Client_Close != TRUE) {
			closesocket(paraccess.Client);
			paraccess.Client_Close = TRUE;
		}
	}
	return 0;
}
void inputfile(char *filename, char *a)
{
	ofstream fs;
	fs.open(filename);
	for (int i = 0; i < strlen(a); i++)
	{
		fs << a[i];
	}
	fs.close();
}
void outputfile(char *filename, string &a)
{

	char buffer[406];
	ifstream ifs("forbidden403.txt", ifstream::in);

	ifs.getline(buffer, 406, NULL);
	a = buffer;
	

	ifs.close();
}
unsigned int Proxy_to_websever(void * lPm)
{
	char Buffer[BUFFERSIZE];
	sockaddr_in *server_temp = NULL;
	Socket Server;
	Param *Pa = (Param*)lPm;
	string servername = Pa->address;
	int Port = Pa->port;
	cout << "Server Name: " << servername;
	cout << "\n";
	Sleep(1200);
	Sleep(1200);
	char Host_name[32] = "";
	server_temp = Get_IP_Sever(servername, Host_name);
	if (server_temp == NULL)
	{
		//cout << "\nCan't get IP address";
		cout << "\n";
		send(Pa->pair->Client, Prohibit_access.c_str(), Prohibit_access.size(), 0);
		return -1;
	}
	if (strlen(Host_name) > 0)
	{
		cout << "Connecting to:";
		cout<<Host_name << endl;
		int rtl;
		Server = socket(AF_INET, SOCK_STREAM, 0);
		//Sau đó tiến hành kết nối đến địa chỉ ip vừa nhận đc
		if (!(connect(Server, (sockaddr*)server_temp, sizeof(sockaddr)) == 0))
		{
			//
			cout << "Cannot connect.";
			//send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );Kết nối thành công
			send(Pa->pair->Client, Prohibit_access.c_str(), Prohibit_access.size(), 0);

			return -1;
		}
		else
		{
			Pa->pair->Server = Server;
			cout << "Connect successfully \n";
			// gán bằng false thực thiện bước tiếp theo
			Pa->pair->Sever_Close == FALSE;
			SetEvent(Pa->handle);
			while ((Pa->pair->Client_Close != TRUE) && (Pa->pair->Sever_Close !=TRUE))
			{
				//Nhận Dữ liệu đc gởi từ Server tới Proxy.. sao đó .
				rtl = recv(Pa->pair->Server, Buffer, BUFFERSIZE, 0);
				// lỗi tiến hánh đóng sever
				if (rtl == SOCKET_ERROR)
				{
					closesocket(Pa->pair->Server);
					Pa->pair->Sever_Close = TRUE;
					break;
				}
				// không nhận đc dữ liệu
				if (rtl == 0)
				{
					cout << "\nServer Closed.!\n";
					//đóng sever
					closesocket(Pa->pair->Server);
					Pa->pair->Sever_Close = TRUE;
				}
				//sau đó tiến hành gửi data về cho client 
				//Kết thúc vòng lặp khi đã nhận và gởi hết data
				//tiến hành vòng lặp while liên tục v để gửi và nhận dữ liệu nó chỉ đóng khi cả hai close trở về true
				rtl = send(Pa->pair->Client, Buffer, rtl, 0);
				if (rtl == SOCKET_ERROR)
				{
					cout << "\nSend Failed, Error: ";
					cout<< GetLastError();
					Pa->pair->Client_Close = TRUE;
					closesocket(Pa->pair->Client);
					
					break;
				}
				if (rtl >= BUFFERSIZE) 
				{
					Buffer[rtl - 1] = 0; 
				}
				else
				{ 
					Buffer[rtl] = 0;
				}
				cout << "\nServer received: " << rtl << "data :\n[" << "\naaaaaaaa\n" << Buffer << "\naaaaaa\n" << "]";
				// cấp phát
				ZeroMemory(Buffer, BUFFERSIZE);
				inputfile("hao.html", Buffer);
			}
			
			//Việc thay đổi giá trị ở thread này sẽ ảnh hưởng tới thread Client_to_proxy
			//Việc đóng Socket ở thread này dẫn đến các giá trị thread kia cũng thay đổi
			//Close socket
			if (Pa->pair->Client_Close != TRUE)
			{
				closesocket(Pa->pair->Client);
				Pa->pair->Client_Close = TRUE;
			}
			if (Pa->pair->Sever_Close != TRUE)
			{
				closesocket(Pa->pair->Server);
				Pa->pair->Sever_Close = TRUE;
			}
		}
	}
	return 0;
}


void CloseSocket()
{
	//Đóng Socket lắng nghe
	cout << "Close Socket!" << endl;

	Thoat();
	closesocket(Listen_new_access);
	int temp = WSACleanup();
	if (temp == 0)
	{
		cout << "CLOSE SUCCESSFULLY!\n";
	}



}
// Neêu nhận được phím end Từ bàn phím thì sẽ tiến hành đóng soc ket
unsigned int Get_down(void * lParam)
{
	bool * load1 = (bool*)lParam;
	while (*load1)
	{
		string c;
		getline(cin, c);
		if (c.compare("end") == 0)
		{
			*load1 = 0;
		}
	}
	return 0;
}

// tách bỏ khoảng trắng sau đó lưu vào cont
// Đọc  DomainName vào arr
void Star_load_blackList(vector<string>& Arr)
{
	// Mặc định chế độ lưu trong blacklist là tên miền (Ex: www.vietmoz.net)
	//Nếu khác định dạng thì hàm   Check_sever_name_inBlackList(...) trả về 0
	fstream fout;
	fout.open("blacklist.conf", ios::in | ios::out);
	//Mở file ra đọc vào temp r push temp vào Arr
	if (fout.is_open())
	{
		while (!fout.eof())
		{
			string temp;
			getline(fout, temp);
			if (temp.back() == '\n')
			{
				temp.pop_back();
			}
			Arr.push_back(temp);
		}
	}
}

bool Check_sever_name_inBlackList(string server_name) {
	if (BLACKLIST.size() > 0)
	{
		for (auto i : BLACKLIST)
		{
			// Nếu tìm không thấy sever_name thì i.find sẽ trả về npos 
			if (i.find(server_name) != string::npos)
			{
				//cout << i.find(server_name);
				return 0;
			}
		}
	}
	return 1;
}
// lấy địa chỉ address ex http://www.google.com/csjkdcnsdkbsd
//qua hàm get_port sẽ trả về www.google.com và port=80
void Get_port(string &buf, string &address, int &port)
{
	vector<string> conten;
	//conten 0: command, 1: link, 2: proto

	str_Split(buf, conten);
	// lớn  là tách chuối và push vào conten thành công
	if (conten.size() > 0)
	{
		// tìm chuỗi http:// có xuất hiện trong conten k.
		int pos = conten[1].find(HTTP);
		if (pos != -1) {
			// lấy chuỗi từ sau http://
			// tiến hành lấy chuỗi từ sau http:// chở đi
			string add = conten[1].substr(pos + strlen(HTTP));
			// lấy tên trước dấu /
			//Gán port bằng 80
			port = 80;
			address = add.substr(0, add.find('/'));
			//Port của HTTP là 80

			string temp;
			int dem = strlen(HTTP) + address.length();
			//push khoảng trắng vào trong temp để tiến hành thay thế domain name
			while (dem > 0)
			{
				temp.push_back(' ');
				dem--;
			}
			// Thay thế toàn bộ địa chỉ thành dấu cách
			buf = buf.replace(buf.find(HTTP + address), strlen(HTTP) + address.length(), temp);
		}
	}
}

//cact chuoi
void str_Split(string str, vector<string> &cont, char delim)
{

	string ts;
	istringstream sstr(str);
	if (str[0] != NULL)
	{

		while (getline(sstr, ts, delim))
		{
			cont.push_back(ts);
		}
	}
}
/*

cấu trúc addrinfo {
int ai_flags;
int ai_f Family;
int ai_socktype;
int ai_protatio;
socklen_t ai_addrlen;
struct sockaddr * ai_addr;
char * ai_canonname;
struct addrinfo * ai_next;
};
*/
sockaddr_in* Get_IP_Sever(string Tenserver, char * Domain_name)
{

	// khởi tạo sever
	sockaddr_in *server_acc = NULL;
	int stt;
	if (Tenserver.size() > 0)
	{
		//Check thuộc dạng nào IP hay domain nảm
		if (isalpha(Tenserver.at(0)))
		{
			// thực hiện chuyển domain name thành địa chỉ ip
			addrinfo hts;
			addrinfo *rs = NULL;
			ZeroMemory(&hts, sizeof(hts));
			hts.ai_family = AF_UNSPEC;
			hts.ai_socktype = SOCK_STREAM;
			//Lấy thông tin từ địa chỉ lấy được 
			if ((stt = getaddrinfo(Tenserver.c_str(), "80", &hts, &rs)) != 0)
			{
				cout << "Getaddrinfo failed:";
				cout<< gai_strerror(stt);
				return NULL;
			}
			while (rs->ai_next != NULL)
			{
				rs = rs->ai_next;
			}
			//fflush(stdin);
			sockaddr_in * temp = (sockaddr_in*)rs->ai_addr;
			inet_ntop(rs->ai_family, &temp->sin_addr, Domain_name, 32);
			server_acc = (sockaddr_in*)rs->ai_addr;
			unsigned long addre;
			inet_pton(AF_INET, Domain_name, &addre);
			// Gán
			server_acc->sin_addr.s_addr = addre;
			//port 80
			server_acc->sin_port = htons(80);
			server_acc->sin_family = AF_INET;
		}
		else
		{
			unsigned long addr;
			inet_pton(AF_INET, Tenserver.c_str(), &addr);

			sockaddr_in sys;

			sys.sin_family = AF_INET;
			sys.sin_addr.s_addr = addr;
			Sleep(1200);

			if ((stt = getnameinfo((sockaddr*)&sys,	sizeof(sockaddr), Domain_name, NI_MAXHOST, NULL, NI_MAXSERV, NI_NUMERICSERV)) != 0)
			{
				return NULL;
			}
			Sleep(1200);
			server_acc->sin_family = AF_INET;
			server_acc->sin_port = htons(80);
			server_acc->sin_addr.s_addr = addr;
		}
	}
	return server_acc;
}
