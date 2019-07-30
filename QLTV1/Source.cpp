#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <conio.h>
#include <sstream>

#define mauchu 240
#define maunen 31
#define DOWN 80
#define UP 72
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESC 27
#define SPACE 32
#define BACKSPACE 8
#define INSERT 82
#define END 79
#define MAXLIST 1000
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64
#define F10 68
#define F7 65
#define F8 66
using namespace std;
string thaotac[6] = { " 1/Quan ly the doc gia"," 2/ Quan ly sach"," 3/ In danh sach"," 4/ Tim kiem"," 5/ Thoat" };
string docgia[4] = { " 1/ Them the doc gia."," 2/ Chinh sua  the doc gia."," 3/ Xoa the doc gia ."," 4/ Tro lai." };
string sach[4] = { " 1/ Them sach."," 2/ Muon sach "," 3/ Tra sach .","4/ Tro lai" };
string in[5] = { " 1/ Danh sach doc gia ."," 2/ Danh sach dau sach."," 3/Doc gia muon sach qua han"," 4/ Top 10 sach.","5/ Tro lai" };
string timkiem[3] = { " 1/ Tim kiem sach."," 2/ Tim kiem sach cua doc gia.","3/ Tro lai" };
string trangthaisach[3] = { "Chua tra","Ða tra? ","Mat sach" };
string trangthaitdg[2] = { "Khoa","Hoat Dong" };
int STACK[1];
enum trangthai { Up, Down, Left, Right, Enter };
int position = 1;
int *arrMTDG;
const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31 };

//=============================================== Phan Khai Bao ===============================================
//Khai báo ngày
const int MAX_NAM = 9999;
const int MIN_NAM = 1800;
struct Ngay
{
	int ngay;
	int thang;
	int nam;
};
typedef struct Ngay ngay;
//Khai báo m??n tr?
struct MuonTra
{
	string MASACH;
	ngay ngaymuon;
	ngay ngaytra;
	int trangthai;
	string tensach;
	string vitrisach;
};
typedef struct MuonTra muon_tra;
struct NodeMuonTra
{
	muon_tra data;
	NodeMuonTra *pNext;
};
typedef struct NodeMuonTra node_mt;
struct ListMT
{
	node_mt *pHead;
	node_mt *pTail;
	int n;
};
typedef struct ListMT list_mt;
void KhoiTao_LMT(list_mt &l)
{
	l.pHead = l.pTail = NULL;
	l.n = 0;
}
//Khai bao ??u sách
struct DanhMucSach
{
	string maSach;
	int ttSach;
	string viTri;
};
typedef struct DanhMucSach danhmucsach;
struct Node_DMS
{
	danhmucsach data;
	Node_DMS *pNext;
};
typedef struct Node_DMS node_dms;
struct List_DMS
{
	node_dms *pHead, *pTail;
	int n;
};
typedef struct List_DMS list_dms;
// hàm kh?i t?o danh sách liên k?t ??n
void KhoiTaoDanhSach(list_dms &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}
struct DauSach_Info
{
	string ISBN;
	string tensach;
	string tacgia;
	string theloai;
	int sotrang;
	int namXB;
};
typedef struct DauSach_Info dauSach_info;
struct DauSach
{
	dauSach_info info;
	list_dms ldms;
};
typedef struct DauSach dausach;
typedef struct DauSach*  pDAU_SACH;
struct DS_DauSach {
	pDAU_SACH data[MAXLIST];
	int n = 0;
};
typedef struct DS_DauSach  ds_dausach;
//Khai báo danh sách th? ??c gi?
struct TheDocGia
{
	int MATHE;
	string ho;
	string ten;
	int gioitinh;
	int trangthaithe;
};
typedef struct TheDocGia the_doc_gia;
//struct DS_TDG
//{
//	the_doc_gia tdg[MAXLIST];
//	int n = 0;
//};
//typedef struct DS_TDG ds_tdg;
struct Node_TDG
{
	the_doc_gia TDG;
	Node_TDG *pLeft;
	Node_TDG *pRight;
	list_mt lmt;
};
typedef struct Node_TDG node_tdg;
typedef node_tdg *TREE;
void KhoiTaoTree(TREE &t) {
	t = NULL;
}
node_tdg* GetNode_DG(the_doc_gia tdg)
{
	node_tdg *p = new node_tdg;
	if (p == NULL) {
		return NULL;
	}
	// khoi tao danh muc sach trong node doc gia
	KhoiTao_LMT(p->lmt);
	p->TDG = tdg;
	p->pLeft = p->pRight = NULL;
	return (p);
}
void ThemTDG(TREE &t, the_doc_gia tdg)
{
	if (t == NULL) {
		t = GetNode_DG(tdg);
	}
	else if (t->TDG.MATHE > tdg.MATHE)
	{
		ThemTDG(t->pLeft, tdg);
	}
	else if (t->TDG.MATHE < tdg.MATHE)
	{
		ThemTDG(t->pRight, tdg);
	}
}
struct QuaHan
{
	int MADG;
	string hoten;
	string masach;
	string tensach;
	ngay ngaymuon;
	int songayquahan;
};
typedef struct QuaHan qua_han;
struct DSQuaHan {
	qua_han data[MAXLIST];
	int n = 0;
};
typedef struct DSQuaHan ds_qua_han;
//========================================= RANDOM ======================================
void GetNgayHienTai(ngay &d)
{
	//    int ngay,thang,nam ;
	tm today;
	time_t ltime;
	time(&ltime);
	// today = localtime( &ltime );
	localtime_s(&today, &ltime);
	d.ngay = today.tm_mday;
	d.thang = today.tm_mon + 1;
	d.nam = today.tm_year + 1900;
}
int TinhNgay(ngay d) {
	if (d.thang < 3) {
		d.nam--;
		d.thang += 12;
	}
	long int n = 365 * d.nam + d.nam / 4 - d.nam / 100 + d.nam / 400;
	for (int i = 0; i < d.thang; i++) {
		n += monthDays[i];
	}
	return n + d.ngay;
}
bool Check_MADG(TREE  t, int MADG)
{
	if (t == NULL) {
		return false;
	}
	else if (t->TDG.MATHE == MADG)
	{
		return true;
	}
	else if (MADG < t->TDG.MATHE)
	{
		return Check_MADG(t->pLeft, MADG);
	}
	else
	{
		return Check_MADG(t->pRight, MADG);
	}
}
the_doc_gia Find_MADG(TREE  t, int MADG)
{
	if (t != NULL) {
		if (t->TDG.MATHE == MADG)
		{
			return t->TDG;
		}
		else if (MADG < t->TDG.MATHE)
		{
			return Find_MADG(t->pLeft, MADG);
		}
		else
		{
			return Find_MADG(t->pRight, MADG);
		}
	}
}
node_tdg Find_NodeTDG_MADG(TREE t, int MADG)
{
	if (t != NULL) {
		if (t->TDG.MATHE == MADG)
		{
			return *t;
		}
		else if (MADG < t->TDG.MATHE)
		{
			return Find_NodeTDG_MADG(t->pLeft, MADG);
		}
		else
		{
			return Find_NodeTDG_MADG(t->pRight, MADG);
		}
	}
}
int Random()
{
	srand((int)time(0));
	int x;
	// bo ham rand() vao vong lap moi khong bi loi tang dan, hay giam dan.
	for (int i = 0; i < 1000; i++)
	{
		x = rand();
	}
	return x;
}
int Random_MADG(TREE t)
{
	int temp;
	do
	{
		temp = Random();
	} while (Check_MADG(t, temp));  // check trung , neu trung thi random lai
	return temp;
}
// cac hàm thi?t k? giao di?n
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void AnConTro() {
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}
//hien thi dau' nhay' cua? con tro?
void HienConTro() {
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = TRUE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}
//CAC HAM TO MAU
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void clrscr()
{
	COORD origin = { 0, 0 };
	unsigned long len;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	unsigned long size;
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);


	GetConsoleScreenBufferInfo(handle, &csbi);
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(handle, TEXT(' '), size, origin, &len);
	FillConsoleOutputAttribute(handle, csbi.wAttributes, size, origin, &len);
	SetConsoleCursorPosition(handle, origin);
}
void setcolor(int background, int textcolor)
{
	SetBGColor(background);
	SetColor(textcolor);
}
void ve_khungmenu(int x1, int y1, int x2, int y2, char s, int mau)
{
	textcolor(mau);
	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			gotoxy(i, j);
			cout << s;
		}
	}
	textcolor(7);
}
trangthai key(int a)
{
	if (a == 224)
	{
		char c = _getch();
		if (c == 72) return Up;
		else if (c == 80) return Down;
		else if (c == 77) return Right;
		else if (c == 75) return Left;
	}
	if (a == 13) return Enter;
}
void xoa_hoidexoa(int x, int y) {
	gotoxy(x, y); for (int i = 0; i < 29; i++) cout << " ";
	gotoxy(x, y + 1); for (int i = 0; i < 29; i++) cout << " ";
	gotoxy(x, y + 2); for (int i = 0; i < 29; i++) cout << " ";
	gotoxy(x, y + 3); for (int i = 0; i < 29; i++) cout << " ";
	gotoxy(x, y + 4); for (int i = 0; i < 29; i++) cout << " ";
	gotoxy(x, y + 5); for (int i = 0; i < 29; i++) cout << " ";
	gotoxy(x, y + 6); for (int i = 0; i < 29; i++) cout << " ";
}
void Bang_ten() {
	setcolor(6, 15);
	xoa_hoidexoa(15, 35);
	xoa_hoidexoa(45, 35);
	setcolor(6, 15);
	gotoxy(16, 36); cout << "HO VA TEN: "; gotoxy(46, 36); cout << "HO VA TEN: ";
	gotoxy(16, 38); cout << "MSSV: "; gotoxy(46, 38); cout << "MSSV: ";
	gotoxy(16, 40); cout << "LOP: "; gotoxy(46, 40); cout << "LOP: ";
	setcolor(6, 13);
	gotoxy(27, 36); cout << "TRUONG NHAT KIEN"; gotoxy(57, 36); cout << "TRAN DUC NGUYEN";
	gotoxy(22, 38); cout << "N15DCCN035"; gotoxy(52, 38); cout << "N15DCCN008";
	gotoxy(21, 40); cout << "D15CQCP01-N"; gotoxy(51, 40); cout << "D15CQCP01-N";

}
int thoat()
{
	ve_khungmenu(20, 10, 60, 21, 0, 180);
	gotoxy(21, 14);
	textcolor(180);
	cout << "!BAN CO THUC SU MUON THOAT!";
	gotoxy(23, 16);
	textcolor(180);
	cout << "CO\t\t";
	textcolor(196);
	cout << "KHONG";
	int z;
	int tt = 0;
	while (1)
	{
		z = _getch();
		trangthai stt = key(z);
		switch (stt)
		{
		case Left:
		{
			if (tt == 0)
			{
				tt++;
				gotoxy(23, 16);
				textcolor(196);
				cout << "CO";
				gotoxy(41, 16);
				textcolor(180);
				cout << "KHONG";
			}
			break;
		}
		case Right: {
			if (tt == 1) {
				tt--;
				gotoxy(23, 16);
				textcolor(180);
				cout << "CO";
				gotoxy(41, 16);
				textcolor(196);
				cout << "KHONG";

			}
			break;
		}
		case Enter: {
			textcolor(7);
			return tt;
		}

		}
	}
}
void khungThemDocGia() {
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(42, 5); cout << "THEM DOC GIA";
	for (int i = 20; i < 60; i++) {
		for (int j = 10; j < 15; j++) {
			gotoxy(i, j);
			cout << " ";
		}
	}
	gotoxy(23, 9); cout << char(218); for (int i = 0; i < 50; i++) cout << char(196); cout << char(191);
	for (int i = 0; i < 16; i++) {
		gotoxy(23, 10 + i);
		cout << char(179);
	}
	for (int i = 0; i < 16; i++) {
		gotoxy(74, 10 + i);
		cout << char(179);
	}
	gotoxy(23, 26); cout << char(192); for (int i = 0; i < 50; i++) cout << char(196); cout << char(217);

	gotoxy(27, 11); cout << "Ma Doc Gia  : ";

	gotoxy(42, 12); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 11 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 11 + i);
		cout << char(179);
	}
	gotoxy(42, 10); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);

	gotoxy(27, 15); cout << "Ho Doc Gia  : ";

	gotoxy(42, 16); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 15 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 15 + i);
		cout << char(179);
	}
	gotoxy(42, 14); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);


	gotoxy(27, 19); cout << "Ten Doc Gia : ";

	gotoxy(42, 20); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 19 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 19 + i);
		cout << char(179);
	}
	gotoxy(42, 18); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);

	gotoxy(27, 23); cout << "Phai[0-1]   : ";
	gotoxy(45, 23); cout << ">>";
	gotoxy(48, 23); cout << "Nam";
	gotoxy(65, 23); cout << "Nu";

	gotoxy(42, 24); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 23 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 23 + i);
		cout << char(179);
	}
	gotoxy(42, 22); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);

	gotoxy(43, 15); cout << setw(3) << " ";

	HienConTro();

	SetColor(12);
	gotoxy(40, 30);
	cout << "ESC: Thoat ----- F10: Luu" << endl;
	SetColor(15);
}
void khungSuaDocGia() {
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(42, 5); cout << "SUA DOC GIA";
	for (int i = 20; i < 60; i++) {
		for (int j = 10; j < 15; j++) {
			gotoxy(i, j);
			cout << " ";
		}
	}
	gotoxy(23, 9); cout << char(218); for (int i = 0; i < 50; i++) cout << char(196); cout << char(191);
	for (int i = 0; i < 16; i++) {
		gotoxy(23, 10 + i);
		cout << char(179);
	}
	for (int i = 0; i < 16; i++) {
		gotoxy(74, 10 + i);
		cout << char(179);
	}
	gotoxy(23, 26); cout << char(192); for (int i = 0; i < 50; i++) cout << char(196); cout << char(217);

	gotoxy(27, 11); cout << "Ho Doc Gia  : ";

	gotoxy(42, 12); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 11 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 11 + i);
		cout << char(179);
	}
	gotoxy(42, 10); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);

	gotoxy(27, 15); cout << "Ten Doc Gia  : ";

	gotoxy(42, 16); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 15 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 15 + i);
		cout << char(179);
	}
	gotoxy(42, 14); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);

	gotoxy(27, 19); cout << "TrangThai[1-0]: ";
	gotoxy(45, 19); cout << ">>";
	gotoxy(48, 19); cout << "Hoat Dong";
	gotoxy(65, 19); cout << "Khoa";

	gotoxy(42, 20); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 19 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 19 + i);
		cout << char(179);
	}
	gotoxy(42, 18); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);

	gotoxy(27, 23); cout << "Phai[0-1]   : ";
	gotoxy(45, 23); cout << ">>";
	gotoxy(48, 23); cout << "Nam";
	gotoxy(65, 23); cout << "Nu";

	gotoxy(42, 24); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 23 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 23 + i);
		cout << char(179);
	}
	gotoxy(42, 22); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);

	gotoxy(43, 15); cout << setw(3) << " ";

	HienConTro();
	SetColor(12);
	gotoxy(40, 30);
	cout << "ESC: Thoat ----- F10: Luu" << endl;
	SetColor(15);
}
void khungThemDauSach() {
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(42, 3); cout << "THEM DAU SACH";
	gotoxy(42, 90); cout << "CHU Y:";

	for (int i = 20; i < 60; i++) {
		for (int j = 10; j < 15; j++) {
			gotoxy(i, j);
			cout << " ";
		}
	}

	gotoxy(23, 5); cout << char(218); for (int i = 0; i < 52; i++) cout << char(196); cout << char(191);
	for (int i = 0; i < 27; i++) {
		gotoxy(23, 6 + i);
		cout << char(179);
	}
	for (int i = 0; i < 27; i++) {
		gotoxy(76, 6 + i);
		cout << char(179);
	}
	gotoxy(23, 33); cout << char(192); for (int i = 0; i < 52; i++) cout << char(196); cout << char(217);

	gotoxy(27, 7); cout << "Ten Sach  : ";

	gotoxy(42, 8); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 7 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 7 + i);
		cout << char(179);
	}
	gotoxy(42, 6); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);



	gotoxy(27, 11); cout << "JSBN  : ";

	gotoxy(42, 12); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 11 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 11 + i);
		cout << char(179);
	}
	gotoxy(42, 10); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);



	gotoxy(27, 15); cout << "Tac Gia      : ";

	gotoxy(42, 16); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 15 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 15 + i);
		cout << char(179);
	}
	gotoxy(42, 14); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);


	gotoxy(27, 19); cout << "The Loai   : ";

	gotoxy(42, 20); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 19 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 19 + i);
		cout << char(179);
	}
	gotoxy(42, 18); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);


	gotoxy(27, 23); cout << "So Trang  : ";

	gotoxy(42, 24); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 23 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 23 + i);
		cout << char(179);
	}
	gotoxy(42, 22); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);


	gotoxy(27, 27); cout << "Nam Xuat Ban  : ";


	gotoxy(42, 28); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 27 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 27 + i);
		cout << char(179);
	}
	gotoxy(42, 26); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);
	gotoxy(43, 15); cout << setw(3) << " ";

	HienConTro();
}
void khungnhap_TenSach(string s) {
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(40, 1); cout << s;
	for (int i = 20; i < 60; i++) {
		for (int j = 10; j < 15; j++) {
			gotoxy(i, j);
			cout << " ";
		}
	}

	gotoxy(29, 9); cout << char(218); for (int i = 0; i < 40; i++) cout << char(196); cout << char(191);
	for (int i = 0; i < 5; i++) {
		gotoxy(29, 10 + i);
		cout << char(179);
	}
	for (int i = 0; i < 5; i++) {
		gotoxy(70, 10 + i);
		cout << char(179);
	}
	gotoxy(29, 15); cout << char(192); for (int i = 0; i < 40; i++) cout << char(196); cout << char(217);

	gotoxy(30, 12); cout << "NHAP TEN SACH: ";

	gotoxy(50, 12); cout << setw(15) << " ";
	gotoxy(45, 12);
	HienConTro();

}
int NhapPhai(int &result) {
	AnConTro();
	int charr, flag = 0;
	while (true)
	{
		charr = _getch();
		if (charr == 224)
		{
			charr = _getch();
			if (charr == UP)
			{
				return UP;
				break;
			}
			else if (charr == DOWN) {
				gotoxy(46, 23);
				gotoxy(46, 19);
				return DOWN;
				break;
			}
			else if (charr == LEFT || charr == RIGHT) {
				if (flag == 0)
				{
					result = 1;
					gotoxy(45, 23);
					cout << "  ";
					gotoxy(62, 23); cout << ">>";
					flag = 1;
				}
				else {
					result = 0;
					gotoxy(62, 23);
					cout << "  ";
					gotoxy(45, 23); cout << ">>";
					flag = 0;
				}
			}

		}
		else if (charr == 0) {
			charr = _getch();
			if (charr == 68) {
				return charr;
			}
		}
		else if (charr == ESC) {
			return ESC;
		}
	}
}
int NhapTrangThai(int &result) {
	AnConTro();
	int charr;
	while (true)
	{
		charr = _getch();
		if (charr == 224)
		{
			charr = _getch();
			if (charr == UP)
			{
				return UP;
				break;
			}
			else if (charr == DOWN) {
				return DOWN;
				break;
			}
			else if (charr == LEFT || charr == RIGHT) {
				if (result == 0)
				{
					result = 1;
					gotoxy(45, 19);
					cout << ">>";
					gotoxy(62, 19);
					cout << "  ";
				}
				else {
					result = 0;
					gotoxy(62, 19);
					cout << ">>";
					gotoxy(45, 19);
					cout << "  ";
				}
			}

		}
		else if (charr == 0) {
			charr = _getch();
			if (charr == 68) {
				return charr;
			}
		}
		else if (charr == ESC) {
			return ESC;
		}
	}
}
int NhapChu(string &result, int &count, int size) {
	HienConTro();
	int charr;
	while (true) {
		charr = _getch();
		if (((charr >= 65 && charr <= 90) || (charr >= 97 && charr <= 122) || charr == SPACE)
			&& count < size && count >= 0) {
			count++;
			charr = toupper((char)charr);
			cout << (char)charr;
			result += (char)charr;
		}
		else if (charr == BACKSPACE && count > 0)
		{
			cout << "\b" << " " << "\b";
			count--;
			result.erase(result.length() - 1, 1);
		}
		else if (charr == 0) {
			charr = _getch();
			if (charr == 68) {
				return charr;
			}
		}
		else if (charr == 224)
		{
			charr = _getch();
			if (charr == UP)
			{
				return UP;
				break;
			}
			else if (charr == DOWN) {
				gotoxy(46, 23);
				gotoxy(46, 19);
				return DOWN;
				break;

			}
			else if (charr == LEFT) {

				return LEFT;
				break;

			}
			else if (charr == RIGHT) {
				return RIGHT;
				break;

			}
		}
		else if (charr == ENTER) {
			return ENTER;
		}
		else if (charr == ESC) {
			return ESC;
		}
	}
}
int NhapChu_So(string &result, int &count, int size) {
	int charr;
	while (true)
	{
		charr = _getch();
		if (((charr >= 65 && charr <= 90) || (charr >= 97 && charr <= 122)
			|| (charr >= 48 && charr <= 57) || charr == SPACE) && count < size && count >= 0)
		{
			count++;
			charr = toupper((char)charr);
			cout << (char)charr;
			result += (char)charr;
		}
		else if (charr == BACKSPACE && count > 0)
		{

			cout << "\b" << " " << "\b";
			count--;
			result.erase(result.length() - 1, 1);
		}
		else if (count == size) {
			gotoxy(43, 17); cout << "KHONG HOP LE";
			gotoxy(65, 12);


		}
		if (charr == ESC) {
			return ESC;
			break;
		}
	}




}
void disableScrollBar() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}
//=============================THONG BAO====================================
void thongbao(string s, int x, int y, int ColorBG, int colortext) {
	setcolor(ColorBG, colortext);
	AnConTro();
	do {
		gotoxy(x, y); cout << s;
		Sleep(600);
		gotoxy(x, y); cout << setw(s.length()) << " ";
		Sleep(300);
	} while (!_kbhit());
	gotoxy(x, y); cout << setw(s.length()) << " ";
	HienConTro();
}
void MenuChinh(string a[], int length, int x, int y)
{
	resizeConsole(800, 600);
	AnConTro();
	setcolor(55, 12);
	for (int i = 0; i < length; i++)
	{
		gotoxy(x, y + i * 4);
		cout << left << setw(35) << " ";
		gotoxy(x, (y + 1) + i * 4);
		cout << left << setw(35) << a[i];
		gotoxy(x, (y + 2) + i * 4);
		cout << left << setw(35) << " ";
	}
}
int InMenu(string a[], int length, int x, int y)//tao ra giao dien cua cac menu(gom menu chinh va cac menu con)
{
	int tt = 0;//mac dinh thao tac so 1 dc to mau
	int b;
	SetBGColor(2);
	clrscr();
bgin:
	{
		MenuChinh(a, length, x, y);
		setcolor(35, 15);
		gotoxy(x, y + tt * 4);
		cout << left << setw(35) << " ";
		gotoxy(x, (y + 1) + tt * 4);
		cout << left << setw(35) << a[tt];
		gotoxy(x, (y + 2) + tt * 4);
		cout << left << setw(35) << " ";
	}
	while (1)
	{
		b = _getch();
		trangthai stt = key(b);
		switch (stt) {
		case Up: {
			if (tt == 0)  tt = length - 1;
			else tt--;
			goto bgin;
			break;
		}
		case Down: {
			if (tt == length - 1)  tt = 0;
			else tt++;
			goto bgin;
			break;
		}
		case Enter: {
			return tt;
		}

		}
	}
}
// menu chính
int InMenuChinh(string a[], int length, int x, int y)
{
	int tt = 0;//mac dinh thao tac so 1 dc to mau
	int b;
	SetBGColor(2);
	system("cls");
	gotoxy(1, 1);  cout << setw(100) << " ";
	gotoxy(25, 1); cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG - DE TAI SO 2";
	gotoxy(40, 15);

bgin:
	{
		MenuChinh(a, length, x, y);
		setcolor(35, 15);
		gotoxy(x, y + tt * 4);
		cout << left << setw(35) << " ";
		gotoxy(x, (y + 1) + tt * 4);
		cout << left << setw(35) << a[tt];
		gotoxy(x, (y + 2) + tt * 4);
		cout << left << setw(35) << " ";
	}
	while (1)
	{
		b = _getch();
		trangthai stt = key(b);
		switch (stt) {
		case Up: {
			if (tt == 0)  tt = length - 1;
			else tt--;
			goto bgin;
		}
		case Down: {
			if (tt == length - 1)  tt = 0;
			else tt++;
			goto bgin;
		}
		case Enter: {
			return tt;
		}

		}
	}
}
int countDG(TREE tree)
{
	int c = 1;             // ban than node duoc dem la 1;
	if (tree == NULL)
		return 0;
	else
	{
		c += countDG(tree->pLeft);
		c += countDG(tree->pRight);
		return c;
	}
}
string ChuanHoaString(string result)
{

	for (size_t i = 1; i < result.length(); i++)
	{
		if (result[0] == '\r' || result[0] == ' ')
		{
			result.erase(0, 1);
			i--;
		}
		else if ((result[i - 1] == '\r' && result[i] == '\r') || (result[i - 1] == ' ' && result[i] == ' '))
		{
			result.erase(i - 1, 1);
			i--;
		}
		else if (result[result.length() - 1] == '\r' || result[result.length() - 1] == ' ')
		{
			result.erase(result.length() - 1, 1);

		}
	}
	return result;
}
list_mt Find_MT(TREE &t, int MADG)
{
	if (t != NULL) {
		if (t->TDG.MATHE == MADG)
		{
			return t->lmt;
		}
		else if (MADG < t->TDG.MATHE)
		{
			return Find_MT(t->pLeft, MADG);
		}
		else
		{
			return Find_MT(t->pRight, MADG);
		}
	}
}
void Swap_QH(qua_han qh1, qua_han qh2)
{
	qua_han temp = qh1;
	qh1 = qh2;
	qh2 = temp;
}
int Full_QuaHan(ds_qua_han  l)
{
	return l.n == MAXLIST;
}
int Insert_QuaHan(ds_qua_han &l, qua_han &qh)
{
	if (Full_QuaHan(l))
	{
		return 0;
	}
	l.data[++l.n] = qh;
	return 1;
}
void Sort_QuaHan(ds_qua_han &lqh) {

	int i, j, min_idx;
	int temp1, temp2;
	for (i = 1; i <= lqh.n; i++)
	{
		min_idx = i;
		for (j = i + 1; j <= lqh.n; j++)
		{
			temp1 = lqh.data[j].songayquahan;
			temp2 = lqh.data[min_idx].songayquahan;
			if (temp1 < temp2)
				min_idx = j;
		}
		Swap_QH(lqh.data[min_idx], lqh.data[i]);
	}

}
void Ghi_TDG(TREE t, fstream &fileout)
{
	fileout << t->TDG.MATHE << ',';
	fileout << t->TDG.ho << ' ';
	fileout << t->TDG.ten << ',';
	fileout << t->TDG.gioitinh << ',';
	fileout << t->TDG.trangthaithe << ',';
	fileout << t->lmt.n << ':';
	if (t->lmt.n >= 1) {
		for (node_mt* p = t->lmt.pHead; p != NULL; p = p->pNext)
		{
			fileout << p->data.MASACH << ',';

			fileout << p->data.ngaymuon.ngay << '/';
			fileout << p->data.ngaymuon.thang << '/';
			fileout << p->data.ngaymuon.nam << ',';

			fileout << p->data.ngaytra.ngay << '/';
			fileout << p->data.ngaytra.thang << '/';
			fileout << p->data.ngaytra.nam << ',';

			fileout << p->data.tensach << ',';
			fileout << p->data.trangthai << ',';
			fileout << p->data.vitrisach << ';';
		}
	}
	fileout << endl;
}
void OutFile_DG(TREE &t, fstream &fileout)
{
	if (t != NULL)
	{
		Ghi_TDG(t, fileout);
		arrMTDG[0] = t->TDG.MATHE;
		OutFile_DG(t->pLeft, fileout);
		OutFile_DG(t->pRight, fileout);
	}
}
void Save_TDG(TREE &t)
{
	fstream outFile;
	outFile.open("DocGia.txt", ios::out);
	if (outFile.is_open())
	{
		outFile << countDG(t) << endl;
		OutFile_DG(t, outFile);
	}
	else
	{
		cout << "KET NOI VOI FILE DocGia THAT BAI! ";
	}
	outFile.close();
}
void ThemVaoCuoi(list_mt &lmt, node_mt *pMT)
{
	// danh sách ?ang r?ng
	if (lmt.n == 0)
	{
		lmt.pHead = lmt.pTail = pMT;
		lmt.pHead->data.trangthai = 1;
		lmt.pHead->data.ngaytra.ngay = 0;
		lmt.pHead->data.ngaytra.thang = 0;
		lmt.pHead->data.ngaytra.nam = 0;
		lmt.n = 1;
	}
	else
	{
		lmt.pTail->pNext = pMT;
		lmt.pTail = pMT;
		lmt.pTail->data.trangthai = 1;
		lmt.pTail->data.ngaytra.ngay = 0;
		lmt.pTail->data.ngaytra.thang = 0;
		lmt.pTail->data.ngaytra.nam = 0;
		lmt.n++;
	}
}
node_mt *KhoiTaoMT(muon_tra mt)
{
	node_mt *p = new node_mt;
	if (p == NULL)
	{
		cout << "\nKhong du bo nho de cap phat !";
		return NULL;
	}
	p->data = mt;
	p->pNext = NULL;
	return p;
}
node_tdg* Find_DG(TREE t, int MADG)
{
	while (t != NULL && t->TDG.MATHE != MADG)
	{
		if (MADG < t->TDG.MATHE)
		{
			t = t->pLeft;
		}
		else t = t->pRight;
	}
	return (t);
}
void Doc_TDG(TREE &t, ds_qua_han &lqh)
{
	fstream filein;
	ngay ngayhientai;
	GetNgayHienTai(ngayhientai);
	filein.open("DocGia.txt", ios::in);
	int sodocgia, sosachmuontra;
	if (filein.is_open())
	{
		char temp, temp1, temp3;
		string str1;
		muon_tra mt;
		list_mt lmt;
		KhoiTao_LMT(lmt);
		the_doc_gia tdg;
		node_tdg *pTDG = NULL;
		filein >> sodocgia;
		if (arrMTDG != NULL) {
			delete arrMTDG;
		}
		arrMTDG = new int[sodocgia];
		getline(filein, str1);
		for (int i = 0; i < sodocgia; i++) {
			filein >> tdg.MATHE;
			arrMTDG[i] = tdg.MATHE;
			filein >> temp;
			getline(filein, tdg.ho, ' ');
			getline(filein, tdg.ten, ',');
			filein >> tdg.gioitinh;
			filein >> temp;
			filein >> tdg.trangthaithe;
			filein >> temp;
			ThemTDG(t, tdg);
			pTDG = Find_DG(t, tdg.MATHE);
			filein >> sosachmuontra;
			filein >> temp1;
			for (int j = 0; j < sosachmuontra; j++)
			{
				getline(filein, mt.MASACH, ',');
				filein >> mt.ngaymuon.ngay;
				filein >> temp3;
				filein >> mt.ngaymuon.thang;
				filein >> temp3;
				filein >> mt.ngaymuon.nam;
				filein >> temp;
				filein >> mt.ngaytra.ngay;
				filein >> temp3;
				filein >> mt.ngaytra.thang;
				filein >> temp3;
				filein >> mt.ngaytra.nam;
				filein >> temp;
				getline(filein, mt.tensach, ',');
				filein >> mt.trangthai;
				filein >> temp;
				getline(filein, mt.vitrisach, ';');
				if (TinhNgay(ngayhientai) - TinhNgay(mt.ngaymuon) >= 7) {
					qua_han qh;
					qh = { tdg.MATHE,(tdg.ho + tdg.ten),mt.MASACH,mt.tensach,mt.ngaymuon,(TinhNgay(ngayhientai) - TinhNgay(mt.ngaymuon)) };
					Insert_QuaHan(lqh, qh);

				}
				node_mt *nodeMT = KhoiTaoMT(mt);
				ThemVaoCuoi(pTDG->lmt, nodeMT);
			}
			getline(filein, str1);
		}
	}
	else {
		cout << "KET NOI VOI FILE DocGia THAT BAI! ";
	}
	filein.close();
}
void LoadTDGPhanTrang(TREE &t, int sodocgia, int posStart)
{
	fstream filein;
	filein.open("DocGia.txt", ios::in);
	int n, sosachmuontra;

	if (filein.is_open())
	{
		char temp, temp1, temp3;
		string str1;
		muon_tra mt;
		list_mt lmt;
		KhoiTao_LMT(lmt);
		the_doc_gia tdg;
		node_tdg *pTDG = NULL;
		filein >> n;
		getline(filein, str1);
		// n = 40, sodocgia = 40 posStar = 0
		// n = 40  sodocgia = 22 posStar = 0 + 18 = 18
		// n = 40 sodogia = 4 posStart = 18 + 18 = 36
		if (sodocgia > 18) {
			for (int i = 0; i < n; i++) {
				filein >> tdg.MATHE;
				filein >> temp;
				getline(filein, tdg.ho, ' ');
				getline(filein, tdg.ten, ',');
				filein >> tdg.gioitinh;
				filein >> temp;
				filein >> tdg.trangthaithe;
				filein >> temp;
				if (i >= posStart && i < posStart + 18) {

					ThemTDG(t, tdg);
					pTDG = Find_DG(t, tdg.MATHE);
					filein >> sosachmuontra;
					filein >> temp1;
					for (int j = 0; j < sosachmuontra; j++)
					{
						getline(filein, mt.MASACH, ',');
						filein >> mt.ngaymuon.ngay;
						filein >> temp3;
						filein >> mt.ngaymuon.thang;
						filein >> temp3;
						filein >> mt.ngaymuon.nam;
						filein >> temp;
						filein >> mt.ngaytra.ngay;
						filein >> temp3;
						filein >> mt.ngaytra.thang;
						filein >> temp3;
						filein >> mt.ngaytra.nam;
						filein >> temp;
						getline(filein, mt.tensach, ',');
						filein >> mt.trangthai;
						filein >> temp;
						getline(filein, mt.vitrisach, ';');
						node_mt *nodeMT = KhoiTaoMT(mt);
						ThemVaoCuoi(pTDG->lmt, nodeMT);
					}
				}
				else {
					filein >> sosachmuontra;
					filein >> temp1;
					for (int j = 0; j < sosachmuontra; j++)
					{
						getline(filein, mt.MASACH, ',');
						filein >> mt.ngaymuon.ngay;
						filein >> temp3;
						filein >> mt.ngaymuon.thang;
						filein >> temp3;
						filein >> mt.ngaymuon.nam;
						filein >> temp;
						filein >> mt.ngaytra.ngay;
						filein >> temp3;
						filein >> mt.ngaytra.thang;
						filein >> temp3;
						filein >> mt.ngaytra.nam;
						filein >> temp;
						getline(filein, mt.tensach, ',');
						filein >> mt.trangthai;
						filein >> temp;
						getline(filein, mt.vitrisach, ';');
					}
				}
				getline(filein, str1);

			}
		}
		else {
			for (int i = 0; i < n; i++) {
				filein >> tdg.MATHE;
				filein >> temp;
				getline(filein, tdg.ho, ' ');
				getline(filein, tdg.ten, ',');
				filein >> tdg.gioitinh;
				filein >> temp;
				filein >> tdg.trangthaithe;
				filein >> temp;
				if (i >= posStart) {
					ThemTDG(t, tdg);
					pTDG = Find_DG(t, tdg.MATHE);
					filein >> sosachmuontra;
					filein >> temp1;
					for (int j = 0; j < sosachmuontra; j++)
					{
						getline(filein, mt.MASACH, ',');
						filein >> mt.ngaymuon.ngay;
						filein >> temp3;
						filein >> mt.ngaymuon.thang;
						filein >> temp3;
						filein >> mt.ngaymuon.nam;
						filein >> temp;
						filein >> mt.ngaytra.ngay;
						filein >> temp3;
						filein >> mt.ngaytra.thang;
						filein >> temp3;
						filein >> mt.ngaytra.nam;
						filein >> temp;
						getline(filein, mt.tensach, ',');
						filein >> mt.trangthai;
						filein >> temp;
						getline(filein, mt.vitrisach, ';');
						node_mt *nodeMT = KhoiTaoMT(mt);
						ThemVaoCuoi(pTDG->lmt, nodeMT);
					}
				}
				else {
					filein >> sosachmuontra;
					filein >> temp1;
					for (int j = 0; j < sosachmuontra; j++)
					{
						getline(filein, mt.MASACH, ',');
						filein >> mt.ngaymuon.ngay;
						filein >> temp3;
						filein >> mt.ngaymuon.thang;
						filein >> temp3;
						filein >> mt.ngaymuon.nam;
						filein >> temp;
						filein >> mt.ngaytra.ngay;
						filein >> temp3;
						filein >> mt.ngaytra.thang;
						filein >> temp3;
						filein >> mt.ngaytra.nam;
						filein >> temp;
						getline(filein, mt.tensach, ',');
						filein >> mt.trangthai;
						filein >> temp;
						getline(filein, mt.vitrisach, ';');
					}
				}
				getline(filein, str1);
			}
		}
	}
	else {
		cout << "KET NOI VOI FILE DocGia THAT BAI! ";
	}
	filein.close();
}
void themDocGia(TREE &treeDG, int &maDg, string &hoDg, string tenDg, int &phai) {
	SetColor(15);
	gotoxy(46, 11);
	cout << maDg;
	int tt = 0;
	int lenHo = hoDg.length();
	int lenTen = tenDg.length();
	fstream fileout;
	fileout.open("DocGia.txt", ios::out);
ho: {
	SetColor(15);
	int len = hoDg.length();
	gotoxy(46 + len, 15);
	tt = NhapChu(hoDg, lenHo, 20);
	if (tt == DOWN)
		goto ten;
	else if (tt == 68) {
		if (hoDg.length() == 0 || tenDg.length() == 0) {
			thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
		}
		else
		{
			the_doc_gia tdg = { maDg,hoDg,tenDg,phai, 1 };
			ThemTDG(treeDG, tdg);
			Save_TDG(treeDG);
			thongbao("Da them thanh cong!", 40, 2, 6, 2);
			SetColor(15);
			gotoxy(46, 11);
			cout << maDg;
			hoDg = "";
			gotoxy(46, 15);
			cout << setw(lenHo) << " ";
			tenDg = "";
			gotoxy(46, 19);
			cout << setw(lenTen) << " ";
			phai = 0;
			SetColor(15);
			gotoxy(45, 23);
			cout << ">>";
			gotoxy(62, 23);
			cout << setw(2) << " ";

			maDg = Random_MADG(treeDG);
			SetColor(15);
			gotoxy(46, 11);
			cout << maDg;
		}
	}
	else if (tt == ESC) {
		return;
	}
	goto ho;
	}

ten: {
	SetColor(15);
	int len = tenDg.length();
	gotoxy(46 + len, 19);
	tt = NhapChu(tenDg, lenTen, 20);
	switch (tt) {
	case UP: {
		goto ho;
		break;
	}
	case DOWN: {
		goto phai;
		break;
	}
	}
	if (tt == 68) {
		if (hoDg.length() == 0 || tenDg.length() == 0) {
			thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
		}
		else
		{
			the_doc_gia tdg = { maDg,hoDg,tenDg,phai,1 };
			ThemTDG(treeDG, tdg);
			Save_TDG(treeDG);
			thongbao("Da them thanh cong!", 40, 2, 6, 2);
			SetColor(15);
			gotoxy(46, 11);
			cout << maDg;
			hoDg = "";
			gotoxy(46, 15);
			cout << setw(lenHo) << " ";
			tenDg = "";
			gotoxy(46, 19);
			cout << setw(lenTen) << " ";
			phai = 0;
			SetColor(15);
			gotoxy(45, 23);
			cout << ">>";
			gotoxy(62, 23);
			cout << setw(2) << " ";

			maDg = Random_MADG(treeDG);
			SetColor(15);
			gotoxy(46, 11);
			cout << maDg;
		}
	}
	else if (tt == ESC) {
		return;
	}

	goto ten;
}

 phai: {
	 SetColor(15);
	 gotoxy(46, 23);
	 tt = NhapPhai(phai);
	 switch (tt) {
	 case UP: {
		 goto ten;
		 break;
	 }
	 case DOWN: {
		 goto phai;
		 break;
	 }
	 }
	 if (tt == 68) {
		 if (hoDg.length() == 0 || tenDg.length() == 0) {
			 thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
		 }
		 else
		 {
			 the_doc_gia tdg = { maDg,hoDg,tenDg,phai,1 };
			 ThemTDG(treeDG, tdg);
			 Save_TDG(treeDG);
			 thongbao("Da them thanh cong!", 40, 2, 6, 2);
			 SetColor(15);
			 gotoxy(46, 11);
			 cout << maDg;
			 hoDg = "";
			 gotoxy(46, 15);
			 cout << setw(lenHo) << " ";
			 tenDg = "";
			 gotoxy(46, 19);
			 cout << setw(lenTen) << " ";
			 phai = 0;
			 SetColor(15);
			 gotoxy(45, 23);
			 cout << ">>";
			 gotoxy(62, 23);
			 cout << setw(2) << " ";

			 maDg = Random_MADG(treeDG);
			 SetColor(15);
			 gotoxy(46, 11);
			 cout << maDg;
		 }
	 }
	 else if (tt == ESC) {
		 return;
	 }

	 goto phai;
}

	   fileout.close();
}
void SuaTDG_TREE(TREE &t, the_doc_gia tdg)
{
	// n?u nh? cây ?ang r?ng
	if (t != NULL)
	{
		// n?u nh? data nh? h?n node g?c
		if (tdg.MATHE < t->TDG.MATHE)
		{
			SuaTDG_TREE(t->pLeft, tdg); // duy?t sang nhánh trái c?a cây 
		}
		else if (tdg.MATHE > t->TDG.MATHE)
		{
			SuaTDG_TREE(t->pRight, tdg); // duy?t sang nhánh ph?i c?a cây 
		}
		else // ?ã tìm ra cái node c?n xóa
		{
			t->TDG.ho = tdg.ho;
			t->TDG.ten = tdg.ten;
			t->TDG.gioitinh = tdg.gioitinh;
			t->TDG.trangthaithe = tdg.trangthaithe;
		}
	}
}
void ThemPhanTu(int a[], int &n, int val, int pos) {
	if (n >= MAXLIST) {
		return;
	}
	if (pos < 0) {
		pos = 0;
	}
	else if (pos > n) {
		pos = n;
	}
	for (int i = n; i > pos; i--) {
		a[i] = a[i - 1];
	}
	a[pos] = val;
	++n;
}
void LoadDataDG(TREE tTemp, int &indexY) {
	if (tTemp != NULL) {
		gotoxy(10, indexY);
		cout << tTemp->TDG.MATHE;
		gotoxy(22, indexY);
		cout << tTemp->TDG.ho + tTemp->TDG.ten;
		gotoxy(59, indexY);
		cout << tTemp->TDG.gioitinh;
		gotoxy(75, indexY);
		cout << tTemp->TDG.trangthaithe;
		indexY++;
		LoadDataDG(tTemp->pLeft, indexY);
		LoadDataDG(tTemp->pRight, indexY);
	}
}
void LoadDataDGLNR(TREE tTemp, int &indexY) {
	if (tTemp != NULL) {
		LoadDataDGLNR(tTemp->pLeft, indexY);
		gotoxy(10, indexY);
		cout << tTemp->TDG.MATHE;
		gotoxy(22, indexY);
		cout << tTemp->TDG.ho + tTemp->TDG.ten;
		gotoxy(59, indexY);
		cout << tTemp->TDG.gioitinh;
		gotoxy(75, indexY);
		cout << tTemp->TDG.trangthaithe;
		indexY++;
		LoadDataDGLNR(tTemp->pRight, indexY);
	}

}
//void Duyet_NLR(TREE t,int)
//{
//	// n?u cây còn ph?n t? thì ti?p t?c duy?t
//	if (t != NULL)
//	{
//		/*ltdg.tdg[ltdg.n] = t->TDG;
//		ltdg.n++;*/
//		Duyet_NLR(t->pLeft, ltdg); // duy?t qua trái
//		Duyet_NLR(t->pRight, ltdg); // duy?t qua ph?i
//	}
//}
void KhungDanhMucTDG(TREE t, int sodausach, int start, int type) {
	SetColor(15);
	SetBGColor(6);
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(32, 2); cout << "DANH MUC THE DOC GIA";
	// cái này là thanh ngang th? 1
	gotoxy(6, 3); cout << char(218); for (int i = 0; i < 86; i++) cout << char(196); cout << char(191);
	// cái này là thanh ngang th? 2
	gotoxy(6, 5);  for (int i = 0; i < 87; i++) cout << char(196);

	// thanh d?c s? 2
	for (int i = 0; i < 21; i++) {
		gotoxy(20, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 3
	for (int i = 0; i < 21; i++) {
		gotoxy(50, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 4
	for (int i = 0; i < 21; i++) {
		gotoxy(70, 4 + i);
		cout << char(179);
	}
	gotoxy(10, 4); cout << "MA THE";
	gotoxy(30, 4); cout << "HO TEN";
	gotoxy(56, 4); cout << "GIOI TINH";
	gotoxy(75, 4); cout << "TRANG THAI THE";
	int x = 8, y = 6;
	// ====== ch? này load t? cây ra =======

	TREE tTemp;
	KhoiTaoTree(tTemp);
	LoadTDGPhanTrang(tTemp, sodausach, start);
	if (type == 0) { // load bình th??ng
		LoadDataDG(tTemp, y);
	}
	else { // load theo MDG t?ng d?n
		LoadDataDGLNR(tTemp, y);
	}
	// con tr? ?? ch?n
	SetColor(17);
	gotoxy(3, 6); cout << ">>>";
	SetColor(15);
	// thanh d?c s? 1
	for (int i = 0; i < 20; i++) {
		gotoxy(6, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 5
	for (int i = 0; i < 20; i++) {
		gotoxy(93, 4 + i);
		cout << char(179);
	}
	// thanh ngang so 3
	gotoxy(6, 24);
	cout << char(192);
	for (int i = 0; i < 86; i++) cout << char(196);
	cout << char(217);
	SetColor(15);
	gotoxy(12, 26);
	cout << "ESC: Thoat ----- F2: Them doc gia ----- F3: Sua doc gia ----- F4: Xoa doc gia" << endl;
	gotoxy(17, 28);
	cout << "F5: Sap xep theo ma doc gia ----- F6: Sap xep theo ho ten doc gia" << endl;
}
void suaDocGia(TREE &treeDG, int maDg, string &hoDg, string &tenDg, int &phai, int &stt) {
	SetColor(15);
	int tt = 0;
	int lenHo = hoDg.length();
	gotoxy(46, 11);
	cout << hoDg;
	int lenTen = tenDg.length();
	gotoxy(46, 15);
	cout << tenDg;
	if (stt == 0) {
		gotoxy(45, 19);
		cout << setw(2) << " ";
		gotoxy(62, 19);
		cout << ">>";
	}
	if (phai == 1) {
		gotoxy(45, 23);
		cout << setw(2) << " ";
		gotoxy(62, 23);
		cout << ">>";
	}
ho: {
	SetColor(15);
	int len = hoDg.length();
	gotoxy(46 + len, 11);
	tt = NhapChu(hoDg, lenHo, 20);
	if (tt == DOWN)
		goto ten;
	else if (tt == 68) {
		if (hoDg.length() == 0 || tenDg.length() == 0) {
			thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
		}
		else
		{
			the_doc_gia tdg = { maDg,hoDg,tenDg,phai, stt };
			SuaTDG_TREE(treeDG, tdg);
			Save_TDG(treeDG);
			thongbao("Da sua thanh cong!", 40, 2, 6, 2);
			SetColor(15);
			gotoxy(46, 11);
			cout << hoDg;
			gotoxy(46, 15);
			cout << tenDg;
			if (stt == 0) {
				gotoxy(45, 19);
				cout << setw(2) << " ";
				gotoxy(62, 19);
				cout << ">>";
			}
			else
			{
				gotoxy(45, 19);
				cout << ">>";
				gotoxy(62, 19);
				cout << setw(2) << " ";
			}
			if (phai == 1) {
				gotoxy(45, 23);
				cout << setw(2) << " ";
				gotoxy(62, 23);
				cout << ">>";
			}
			else
			{
				gotoxy(45, 23);
				cout << ">>";
				gotoxy(62, 23);
				cout << setw(2) << " ";
			}
		}
	}
	else if (tt == ESC) {
		return;
	}
	goto ho;
	}

ten: {
	SetColor(15);
	int len = tenDg.length();
	gotoxy(46 + len, 15);
	tt = NhapChu(tenDg, lenTen, 20);
	switch (tt) {
	case UP: {
		goto ho;
		break;
	}
	case DOWN: {
		goto trangthai;
		break;
	}
	}
	if (tt == 68) {
		if (hoDg.length() == 0 || tenDg.length() == 0) {
			thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
		}
		else
		{
			the_doc_gia tdg = { maDg,hoDg,tenDg,phai,stt };
			SuaTDG_TREE(treeDG, tdg);
			Save_TDG(treeDG);
			thongbao("Da sua thanh cong!", 40, 2, 6, 2);
			SetColor(15);
			gotoxy(46, 11);
			cout << hoDg;
			gotoxy(46, 15);
			cout << tenDg;
			if (stt == 0) {
				gotoxy(45, 19);
				cout << setw(2) << " ";
				gotoxy(62, 19);
				cout << ">>";
			}
			else
			{
				gotoxy(45, 19);
				cout << ">>";
				gotoxy(62, 19);
				cout << setw(2) << " ";
			}
			if (phai == 1) {
				gotoxy(45, 23);
				cout << setw(2) << " ";
				gotoxy(62, 23);
				cout << ">>";
			}
			else
			{
				gotoxy(45, 23);
				cout << ">>";
				gotoxy(62, 23);
				cout << setw(2) << " ";
			}
		}
	}
	else if (tt == ESC) {
		return;
	}
	goto ten;
}

 trangthai: {
	 SetColor(15);
	 gotoxy(46, 19);
	 tt = NhapTrangThai(stt);
	 switch (tt) {
	 case UP: {
		 goto ten;
		 break;
	 }
	 case DOWN: {
		 goto phai;
		 break;
	 }
	 }
	 if (tt == 68) {
		 if (hoDg.length() > 0 && tenDg.length() > 0)
		 {
			 the_doc_gia tdg = { maDg,hoDg,tenDg,phai,stt };
			 SuaTDG_TREE(treeDG, tdg);
			 Save_TDG(treeDG);
			 thongbao("Da sua thanh cong!", 40, 2, 6, 2);
			 SetColor(15);
			 gotoxy(46, 11);
			 cout << hoDg;
			 gotoxy(46, 15);
			 cout << tenDg;
			 if (stt == 0) {
				 gotoxy(45, 19);
				 cout << setw(2) << " ";
				 gotoxy(62, 19);
				 cout << ">>";
			 }
			 else
			 {
				 gotoxy(45, 19);
				 cout << ">>";
				 gotoxy(62, 19);
				 cout << setw(2) << " ";
			 }
			 if (phai == 1) {
				 gotoxy(45, 23);
				 cout << setw(2) << " ";
				 gotoxy(62, 23);
				 cout << ">>";
			 }
			 else
			 {
				 gotoxy(45, 23);
				 cout << ">>";
				 gotoxy(62, 23);
				 cout << setw(2) << " ";
			 }
		 }
	 }
	 else if (tt == ESC) {
		 return;
	 }
	 goto trangthai;
}

		phai: {
			SetColor(15);
			gotoxy(46, 23);
			tt = NhapPhai(phai);
			switch (tt) {
			case UP: {
				goto trangthai;
				break;
			}
			case DOWN: {
				goto phai;
				break;
			}
			}
			if (tt == 68) {
				if (hoDg.length() > 0 && tenDg.length() > 0) {
					the_doc_gia tdg = { maDg,hoDg,tenDg,phai,stt };
					SuaTDG_TREE(treeDG, tdg);
					Save_TDG(treeDG);
					thongbao("Da sua thanh cong!", 40, 2, 6, 2);
					SetColor(15);
					gotoxy(46, 11);
					cout << hoDg;
					gotoxy(46, 15);
					cout << tenDg;
					if (stt == 0) {
						gotoxy(45, 19);
						cout << setw(2) << " ";
						gotoxy(62, 19);
						cout << ">>";
					}
					else
					{
						gotoxy(45, 19);
						cout << ">>";
						gotoxy(62, 19);
						cout << setw(2) << " ";
					}
					if (phai == 1) {
						gotoxy(45, 23);
						cout << setw(2) << " ";
						gotoxy(62, 23);
						cout << ">>";
					}
					else
					{
						gotoxy(45, 23);
						cout << ">>";
						gotoxy(62, 23);
						cout << setw(2) << " ";
					}
				}
			}
			else if (tt == ESC) {
				return;
			}
			goto phai;
 }
}
void Khung_DS_MT(TREE &t, int pos) {
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(32, 2); cout << "DANH SACH SACH MUON TRA";
	// cái này là thanh ngang th? 1
	gotoxy(6, 3); cout << char(218); for (int i = 0; i < 86; i++) cout << char(196); cout << char(191);
	// cái này là thanh ngang th? 2
	gotoxy(6, 5);  for (int i = 0; i < 87; i++) cout << char(196);

	// thanh d?c s? 2
	for (int i = 0; i < 21; i++) {
		gotoxy(20, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 3
	for (int i = 0; i < 21; i++) {
		gotoxy(50, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 4
	for (int i = 0; i < 21; i++) {
		gotoxy(70, 4 + i);
		cout << char(179);
	}

	gotoxy(10, 4); cout << "MA SACH";
	gotoxy(30, 4); cout << "NGAY MUON";
	gotoxy(56, 4); cout << "NGAY TRA";
	gotoxy(75, 4); cout << "TRANG THAI SACH";

	int x = 8, y = 5;

	// ====== ch? này load t? cây ra =======
	int i = 1;
	node_tdg *pTDG = Find_DG(t, arrMTDG[pos]);

	for (node_mt *k = pTDG->lmt.pHead; k != NULL; k = k->pNext)
	{
		gotoxy(10, y + i); cout << k->data.MASACH;
		gotoxy(30, y + i); cout << k->data.ngaymuon.ngay << "/" << k->data.ngaymuon.thang << "/" << k->data.ngaymuon.nam;
		gotoxy(56, y + i); cout << k->data.ngaytra.ngay << "/" << k->data.ngaytra.thang << "/" << k->data.ngaytra.nam;
		if (k->data.trangthai == 1) {
			gotoxy(77, y + i); cout << "Dang Muon";
		}
		else
		{
			gotoxy(77, y + i); cout << k->data.trangthai;
		}
		i++;
	}

	//con tr? ?? ch?n
	//SetColor(17);
	//gotoxy(3, 6); cout << ">>>";
	//SetColor(15);

	// thanh d?c s? 1
	for (int i = 0; i < 20; i++) {
		gotoxy(6, 4 + i);
		cout << char(179);
	}

	// thanh d?c s? 5
	for (int i = 0; i < 20; i++) {
		gotoxy(93, 4 + i);
		cout << char(179);
	}

	// thanh ngang so 3
	gotoxy(6, 24);
	cout << char(192);
	for (int i = 0; i < 86; i++) cout << char(196);
	cout << char(217);
}
void XoaTDG(TREE &t, the_doc_gia tdg)
{
	// n?u nh? cây ?ang r?ng
	if (t != NULL)
	{
		// n?u nh? data nh? h?n node g?c
		if (tdg.MATHE < t->TDG.MATHE)
		{
			XoaTDG(t->pLeft, tdg); // duy?t sang nhánh trái c?a cây 
		}
		else if (tdg.MATHE > t->TDG.MATHE)
		{
			XoaTDG(t->pRight, tdg); // duy?t sang nhánh ph?i c?a cây 
		}
		else // ?ã tìm ra cái node c?n xóa
		{
			t->TDG.trangthaithe = 0;

		}
	}
}
void Them_List_MT(TREE &t, the_doc_gia tdg, list_mt lmt)
{
	if (t != NULL)
	{
		if (tdg.MATHE < t->TDG.MATHE)
		{
			Them_List_MT(t->pLeft, tdg, lmt);
		}
		else if (tdg.MATHE > t->TDG.MATHE)
		{
			Them_List_MT(t->pRight, tdg, lmt);
		}
		else
		{
			t->lmt = lmt;
		}
	}
}
void Swap_TDG(the_doc_gia &tdg1, the_doc_gia &tdg2)
{
	the_doc_gia temp;
	temp = tdg1;
	tdg1 = tdg2;
	tdg2 = temp;
}
void SapXepMangMDG(int a[], int n)
{
	for (int i = 1; i < n; i++)
		for (int j = n - 1; j >= i; j--)
			if (a[j] < a[j - 1])
			{
				int temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
}
int ChucNangTDG(TREE &t, int &sodocgia, int &posStart) {
	if (t == NULL)
	{
		thongbao("Danh sach doc gia dang rong. Them moi doc gia de tiep tuc!", 20, 30, 6, 12);
		while (true)
		{
			int charrr = _getch();
			if (charrr) {
				AnConTro();
				break;
			}
		}
	}
	position = 0;
	int type = 0;
	int charr;
	int index = 6;
	while (true)
	{
		charr = _getch();
		if (charr == ESC) {
			return ESC;
		}
		else if (charr == ENTER) {
			node_tdg *pTDG = NULL;
			pTDG = Find_DG(t, arrMTDG[position]);
			if (pTDG->lmt.n > 0) {
				return charr;
			}
			else
			{
				thongbao(/*"Doc gia chua muon sach. Nhan phim bat ky de tiep tuc! "*/to_string(arrMTDG[position]), 25, 30, 6, 12);
				int charr = _getch();
				while (true)
				{
					if (charr) {
						AnConTro();
						break;
					}
				}
			}
		}
		else if (charr == 224) {
			charr = _getch();
			if (charr == UP) {
				if (index == 6) {
					position = posStart;
					SetColor(17);
					gotoxy(3, index); cout << "   ";
					gotoxy(3, index); cout << ">>>";
					SetColor(15);
				}
				else
				{
					position--;
					SetColor(17);
					gotoxy(3, index); cout << "   ";
					index--;
					gotoxy(3, index); cout << ">>>";
					SetColor(15);
				}
			}
			else if (charr = DOWN) {
				if (sodocgia > 18) {
					if (position == (posStart + 17)) {
						SetColor(17);
						gotoxy(3, index); cout << "   ";
						gotoxy(3, index); cout << ">>>";
						SetColor(15);
					}
					else {
						position++;
						SetColor(17);
						gotoxy(3, index); cout << "   ";
						index++;
						gotoxy(3, index); cout << ">>>";
						SetColor(15);
					}
				}
				else {
					if (position == countDG(t) - 1) {
						SetColor(17);
						gotoxy(3, index); cout << "   ";
						gotoxy(3, index); cout << ">>>";
						SetColor(15);
					}
					else {
						position++;
						SetColor(17);
						gotoxy(3, index); cout << "   ";
						index++;
						gotoxy(3, index); cout << ">>>";
						SetColor(15);
					}

				}


			}

		}
		else if (charr == 0) {
			AnConTro();
			charr = _getch();
			if (charr == F2)
			{
				return charr;
			}
			else if (charr == F3) {
				return charr;
			}
			else if (charr == F4) {

				the_doc_gia TDG_temp = Find_MADG(t, 456);
				list_mt lmt_temp;
				KhoiTao_LMT(lmt_temp);
				lmt_temp = Find_MT(t, arrMTDG[position]);
				if (TDG_temp.trangthaithe == 0) {
					thongbao("The doc gia khong ton tai!", 40, 30, 6, 12);
				}
				else if (lmt_temp.n > 0) {
					thongbao("Khong the xoa the doc gia da muon sach!", 40, 30, 6, 12);
				}
				else if ((TDG_temp.trangthaithe == 1) && (lmt_temp.n == 0)) {
					the_doc_gia tdg_temp = Find_MADG(t, arrMTDG[position]);
					tdg_temp.trangthaithe = 0;
					XoaTDG(t, tdg_temp);
					Save_TDG(t);
					/*gotoxy(76, 5 + position);
					cout << setw(9) << " ";
					gotoxy(76, 5 + position);
					cout << "Khoa";
					gotoxy(80, 1);*/
					thongbao("Xoa the doc gia thanh cong!", 40, 30, 6, 2);
				};
				SetColor(15);
				int charr2 = _getch();
				while (true)
				{
					if (charr2) {
						AnConTro();
						break;
					}
				}
			}
			else if (charr == F5)
			{
				clrscr();
				SapXepMangMDG(arrMTDG, countDG(t));
				type = 1;
				KhungDanhMucTDG(t, sodocgia, posStart, type);

			}
			else if (charr == F6)
			{
				return charr;
			}
			else if (charr == F10)
			{
				return charr;
			}
			else if (charr == F7) {
				if (sodocgia - 18 > 0) {
					sodocgia = sodocgia - 18;
					posStart = posStart + 18;
					index = 6;
					position = posStart;
					clrscr();
					KhungDanhMucTDG(t, sodocgia, posStart, type);

				}
			}
			else if (charr == F8) {
				if (sodocgia + 18 <= countDG(t)) {
					sodocgia = sodocgia + 18;
					posStart = posStart - 18;
					index = 6;
					position = posStart;
					clrscr();
					KhungDanhMucTDG(t, sodocgia, posStart, type);


				}
			}
		}
	}
}
int KhungInfoDG(the_doc_gia tdg, list_mt lmt) {
	bool checkQuaHan = false;
	AnConTro();
	gotoxy(35, 10); cout << "Ho va ten       : " << tdg.ho << " " << tdg.ten;
	if (tdg.trangthaithe == 1) {
		gotoxy(35, 11); cout << "Trang thai the  : " << "Hoat Dong";
	}
	else
	{
		gotoxy(35, 11); cout << "Trang thai the  : " << "Khoa";
	}
	if (tdg.gioitinh == 0) {
		gotoxy(35, 12); cout << "Phai            : " << "Nam";
	}
	else
	{
		gotoxy(35, 12); cout << "Phai            : " << "Nu";
	}
	gotoxy(35, 13); cout << "So sach da muon : " << lmt.n;
	SetColor(17);
	ngay ngayhientai;
	GetNgayHienTai(ngayhientai);
	if (lmt.n >= 3) {
		thongbao("Doc gia khong the muon qua 3 sach!", 40, 16, 6, 12);
	}
	else {
		for (node_mt *k = lmt.pHead; k != NULL; k = k->pNext)
		{
			if (TinhNgay(ngayhientai) - TinhNgay(k->data.ngaymuon) >= 7) {
				checkQuaHan = true;
				break;
			}
		}
		if (checkQuaHan) {
			thongbao("Co sach dang qua han, khong the muon them", 30, 16, 6, 0);
		}
		else
		{
			gotoxy(40, 16); cout << "Bam Enter de tiep tuc!";

		}
	}
	int charr;
	while (true)
	{
		charr = _getch();
		if (charr == ENTER) {
			if (lmt.n >= 3) {
				return 0;
				break;
			}
			else if (checkQuaHan)
			{
				return 1;
				break;
			}
			else {
				return 2;
				break;
			}
		}
	}
}
int NhapTheDG(TREE &t) {
	string tdg = "";
	int count = tdg.length();
	int charr;
	while (true)
	{
		charr = _getch();
		if (((charr >= 48 && charr <= 57)) && count < 10)
		{
			count++;
			charr = toupper((char)charr);
			cout << (char)charr;
			tdg += (char)charr;
		}
		else if (charr == BACKSPACE && count > 0)
		{

			cout << "\b" << " " << "\b";
			count--;
			tdg.erase(tdg.length() - 1, 1);
		}
		else if (charr == ENTER) {
			// check mã dg n?u ?úng thì ch? v? mã ??c gi? , ko ?úng thì hi?n thông báo cho nh?p l?i
			Check_MADG(t, stoi(tdg));
			if (Check_MADG(t, stoi(tdg)) == true) {
				the_doc_gia tdgg = Find_MADG(t, stoi(tdg));
				node_tdg *pTDG = NULL;
				pTDG = Find_DG(t, tdgg.MATHE);
				int tt = KhungInfoDG(tdgg, pTDG->lmt);
				if (tt == 0) {
					gotoxy(35, 10); cout << setw(50) << "";
					gotoxy(35, 11); cout << setw(50) << "";
					gotoxy(35, 11); cout << setw(50) << "";
					gotoxy(35, 12); cout << setw(50) << "";
					gotoxy(35, 12); cout << setw(50) << "";
					gotoxy(35, 13); cout << setw(50) << "";
					SetColor(15);
					gotoxy(41 + count - 1, 6);
				}
				else if (tt == 1) {
					gotoxy(35, 10); cout << setw(50) << "";
					gotoxy(35, 11); cout << setw(50) << "";
					gotoxy(35, 11); cout << setw(50) << "";
					gotoxy(35, 12); cout << setw(50) << "";
					gotoxy(35, 12); cout << setw(50) << "";
					gotoxy(35, 13); cout << setw(50) << "";
					SetColor(15);
					gotoxy(41 + count - 1, 6);
				}
				else {
					return stoi(tdg);
					break;
				}
			}
			else {
				thongbao("Ma doc gia khong ton tai.", 38, 10, 6, 0);
				int charTemp;
				charTemp = _getch();
				SetColor(15);
				gotoxy(41 + count - 1, 6);
			}
		}
		else if (charr == ESC) {
			return ESC;
			break;
		}
		else if (charr == 224)
		{
			charr = _getch();
			if (charr == UP)
			{
			}
			else if (charr == DOWN) {


			}

		}
	}
}
void KhungNhapMaDG() {
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(42, 2); cout << "NHAP MA DOC GIA";

	gotoxy(39, 5); cout << char(218); for (int i = 0; i < 20; i++) cout << char(196); cout << char(191);
	for (int i = 0; i < 1; i++) {
		gotoxy(39, 6 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(60, 6 + i);
		cout << char(179);
	}
	gotoxy(39, 7); cout << char(192); for (int i = 0; i < 20; i++) cout << char(196); cout << char(217);
	gotoxy(40, 6);
	HienConTro();
}
// hàm xóa 1 th? ??c gi? b?t kì trong cây nh? phân tìm ki?m
void XoaTDG_HT(TREE &t, the_doc_gia tdg, list_mt lmt) {
	if (thoat() != 1) {
		/*KhungDanhMucTDG(ltdg);*/
	}
}
//========================================================================================
string getString(string a)
{
	for (int i = 0; i < (int)a.length(); i++)
	{
		if (a[i] == ' ') {
			a.erase(i, 1);
			i--;
		}
	}
	return a;
}
void swap_DS(pDAU_SACH ds1, pDAU_SACH ds2)
{
	dausach temp = *ds1;
	*ds1 = *ds2;
	*ds2 = temp;
}
void selectionSortTen_DS(ds_dausach &lDS)
{
	int i, j, min_idx;
	string temp1, temp2, temp3, temp4;
	for (i = 1; i <= lDS.n; i++)
	{
		min_idx = i;
		for (j = i + 1; j <= lDS.n; j++)
		{

			temp1 = getString(lDS.data[j]->info.tensach);
			temp2 = getString(lDS.data[min_idx]->info.tensach);

			temp3 = getString(lDS.data[j]->info.theloai);
			temp4 = getString(lDS.data[min_idx]->info.theloai);
			if (temp1 < temp2 && temp3 == temp4)
				min_idx = j;
		}
		// Swap the found minimum element with the first element
		swap_DS(lDS.data[min_idx], lDS.data[i]);
	}
}
void selectionSort_DS(ds_dausach &lDS)
{
	int i, j, min_idx;
	string temp1, temp2;
	for (i = 1; i <= lDS.n; i++)
	{
		min_idx = i;
		for (j = i + 1; j <= lDS.n; j++)
		{
			temp1 = getString(lDS.data[j]->info.theloai);
			temp2 = getString(lDS.data[min_idx]->info.theloai);
			if (temp1 < temp2)
				min_idx = j;
		}
		// Swap the found minimum element with the first element
		swap_DS(lDS.data[min_idx], lDS.data[i]);
	}
}
void KhungDanhSachDauSach(ds_dausach &lds, string title, int start, int end, int maxSize) {

	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(32, 2); cout << title;
	// cái này là thanh ngang th? 1
	gotoxy(6, 3); cout << char(218); for (int i = 0; i < 86; i++) cout << char(196); cout << char(191);
	// cái này là thanh ngang th? 2
	gotoxy(6, 5);  for (int i = 0; i < 87; i++) cout << char(196);

	// thanh d?c s? 2
	for (int i = 0; i < 21; i++) {
		gotoxy(31, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 3
	for (int i = 0; i < 21; i++) {
		gotoxy(36, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 4
	for (int i = 0; i < 21; i++) {
		gotoxy(56, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 5
	for (int i = 0; i < 21; i++) {
		gotoxy(71, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 6
	for (int i = 0; i < 21; i++) {
		gotoxy(83, 4 + i);
		cout << char(179);
	}
	gotoxy(15, 4); cout << "DAU SACH";
	gotoxy(32, 4); cout << "JSBN";
	gotoxy(43, 4); cout << "TAC GIA";
	gotoxy(60, 4); cout << "THE LOAI";
	gotoxy(74, 4); cout << "SO TRANG";
	gotoxy(86, 4); cout << "NAM XB";
	int x = 8, y = 5;

	// max = 50   load 19 => max = 31  load 19 => max = 12
	// if(max >= 19) load 19   if(max<19) load max
	if (maxSize >= 19) {
		for (int i = 1; i <= 18; i++) {
			gotoxy(7, y + i); cout << lds.data[start]->info.tensach;
			gotoxy(32, y + i); cout << lds.data[start]->info.ISBN;
			gotoxy(37, y + i); cout << lds.data[start]->info.tacgia;
			gotoxy(57, y + i); cout << lds.data[start]->info.theloai;
			gotoxy(72, y + i); cout << lds.data[start]->info.sotrang;
			gotoxy(84, y + i); cout << lds.data[start]->info.namXB;
			start++;
		}
	}
	else {
		for (int i = 1; i <= maxSize; i++) {
			gotoxy(7, y + i); cout << lds.data[start]->info.tensach;
			gotoxy(32, y + i); cout << lds.data[start]->info.ISBN;
			gotoxy(37, y + i); cout << lds.data[start]->info.tacgia;
			gotoxy(57, y + i); cout << lds.data[start]->info.theloai;
			gotoxy(72, y + i); cout << lds.data[start]->info.sotrang;
			gotoxy(84, y + i); cout << lds.data[start]->info.namXB;
			start++;
		}

	}


	// con tr? ?? ch?n
	SetColor(17);
	gotoxy(3, 6); cout << ">>>";
	SetColor(15);

	// thanh d?c s? 1
	for (int i = 0; i < 20; i++) {
		gotoxy(6, 4 + i);
		cout << char(179);
	}
	// thanh d?c s? 7
	for (int i = 0; i < 20; i++) {
		gotoxy(93, 4 + i);
		cout << char(179);
	}
	// thanh ngang so 3
	gotoxy(6, 24); cout << char(192); for (int i = 0; i < 86; i++) cout << char(196); cout << char(217);



}
void KhungThemDanhMucSach() {
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(42, 2); cout << "CAP NHAP DANH MUC SACH";
	gotoxy(23, 5); cout << char(218); for (int i = 0; i < 52; i++) cout << char(196); cout << char(191);
	for (int i = 0; i < 9; i++) {
		gotoxy(23, 6 + i);
		cout << char(179);
	}
	for (int i = 0; i < 9; i++) {
		gotoxy(76, 6 + i);
		cout << char(179);
	}
	gotoxy(23, 15); cout << char(192); for (int i = 0; i < 52; i++) cout << char(196); cout << char(217);

	gotoxy(27, 7); cout << "Ma Sach     : ";

	gotoxy(42, 8); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 7 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 7 + i);
		cout << char(179);
	}
	gotoxy(42, 6); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);
	gotoxy(27, 10); cout << "Vi Tri      : ";
	gotoxy(42, 11); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 10 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 10 + i);
		cout << char(179);
	}
	gotoxy(42, 9); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);
	gotoxy(27, 13); cout << "Trang thai  : ";
	gotoxy(49, 13); cout << "0";
	gotoxy(68, 13); cout << "2";
	gotoxy(42, 14); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 13 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 13 + i);
		cout << char(179);
	}
	gotoxy(42, 12); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);
	gotoxy(43, 10); cout << setw(3) << " ";
	//HienConTro();

}
bool CheckTTDMS(ds_dausach lds, int pos) {
	for (node_dms* p = lds.data[pos]->ldms.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.ttSach == 1) {
			// false la dang co nguoi muon, ko dc xoa
			return false;
			break;
		}
	}
	// true la ko co ai muon, dc xoa
	return true;
}
int ChonTrangThaiDMS(int &result) {
	AnConTro();
	int charr;
	while (true)
	{
		charr = _getch();
		if (charr == 224)
		{
			charr = _getch();
			if (charr == UP)
			{
				return UP;
				break;
			}
			else if (charr == DOWN) {
				return DOWN;
				break;
			}
			else if (charr == LEFT || charr == RIGHT) {
				if (result == 0)
				{
					gotoxy(46, 13);
					cout << "  ";
					gotoxy(65, 13); cout << ">>";
					result = 2;
				}
				else {
					gotoxy(65, 13);
					cout << "  ";
					gotoxy(46, 13); cout << ">>";
					result = 0;
				}
			}
		}
		else if (charr == 0) {
			charr = _getch();
			if (charr == 68) {
				return charr;
				break;
			}
		}

	}


}
void Delete_DauSach(ds_dausach &l, int pos)
{
	if (position >= 1 && position <= l.n)
	{
		for (int i = position; i <= l.n; i++)
			l.data[i] = l.data[i + 1];
		l.n--;
	}
}
int searchDauSach(ds_dausach lds, string tenSach, dauSach_info &infoDausach)
{
	for (int i = 1; i <= lds.n; i++) {

		if (ChuanHoaString(getString(lds.data[i]->info.tensach)) == getString(tenSach)) {
			infoDausach = lds.data[i]->info;
			return 1;
			break;
		}
	}
	return  0;
}
danhmucsach GetDMS(ds_dausach lds, int pos, int index) {
	int i = 1;
	for (node_dms* p = lds.data[pos]->ldms.pHead; p != NULL; p = p->pNext)
	{
		if (i == index) {
			return p->data;
		}
		i++;
	}
}
void KhungDanhMucSach(ds_dausach &lds, int pos, int start, int maxSize) {
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(42, 2); cout << "DANH MUC SACH";
	gotoxy(10, 3); cout << char(218); for (int i = 0; i < 78; i++) cout << char(196); cout << char(191);

	gotoxy(10, 5);  for (int i = 0; i < 79; i++) cout << char(196);

	for (int i = 0; i < 21; i++) {
		gotoxy(30, 4 + i);
		cout << char(179);
	}

	for (int i = 0; i < 21; i++) {
		gotoxy(51, 4 + i);
		cout << char(179);
	}

	gotoxy(17, 4); cout << "MA SACH";
	gotoxy(36, 4); cout << "TRANG THAI";
	gotoxy(67, 4); cout << "VI TRI";

	int x = 8, y = 6;
	int i = 0;
	int stop = start + 18;
	if (lds.data[position]->ldms.n < 19) {
		for (node_dms* p = lds.data[pos]->ldms.pHead; p != NULL; p = p->pNext)
		{
			gotoxy(18, y + i); cout << p->data.maSach;
			gotoxy(41, y + i); cout << p->data.ttSach;
			gotoxy(63, y + i); cout << p->data.viTri;
			i++;
		}
	}
	else {
		if (maxSize > 19) {
			for (node_dms* p = lds.data[pos]->ldms.pHead; p != NULL; p = p->pNext)
			{
				if (start < stop) {
					gotoxy(18, y + i); cout << p->data.maSach;
					gotoxy(41, y + i); cout << p->data.ttSach;
					gotoxy(63, y + i); cout << p->data.viTri;
				}
				i++;
				start++;
			}
		}
		else {
			int j = 0;
			for (node_dms* p = lds.data[pos]->ldms.pHead; p != NULL; p = p->pNext)
			{
				if (j >= start) {
					gotoxy(18, y + i); cout << p->data.maSach;
					gotoxy(41, y + i); cout << p->data.ttSach;
					gotoxy(63, y + i); cout << p->data.viTri;
					i++;
				}
				j++;

			}
		}
	}



	// ch? này s?a l?i là load t?  cây ra

	for (int i = 0; i < 20; i++) {
		gotoxy(10, 4 + i);
		cout << char(179);
	}
	for (int i = 0; i < 20; i++) {
		gotoxy(89, 4 + i);
		cout << char(179);
	}
	gotoxy(10, 24); cout << char(192); for (int i = 0; i < 78; i++) cout << char(196); cout << char(217);

	SetColor(17);
	gotoxy(6, 6); cout << ">>>";
	SetColor(15);
}
void initList_DMS(list_dms &l)
{
	l.n = 0;
	l.pHead = l.pTail = NULL;
}
int Full_DauSach(ds_dausach  l)
{
	return l.n == MAXLIST;
}
int Insert_DauSach(ds_dausach &l, pDAU_SACH &pDS)
{
	if (Full_DauSach(l))
	{
		return 0;
	}
	l.data[++l.n] = pDS;
	return 1;
}
void SaveFileListDS(ds_dausach lds)
{
	fstream outFile;
	outFile.open("DauSach.txt", ios::out);
	if (outFile.is_open())
	{
		outFile << lds.n << endl;
		for (int i = 1; i <= lds.n; i++)
		{
			outFile << lds.data[i]->info.tensach << endl;
			outFile << lds.data[i]->info.ISBN << endl;
			outFile << lds.data[i]->info.tacgia << endl;
			outFile << lds.data[i]->info.theloai << endl;
			outFile << lds.data[i]->info.sotrang << endl;
			outFile << lds.data[i]->info.namXB << endl;
			outFile << lds.data[i]->ldms.n << endl;
			for (node_dms* p = lds.data[i]->ldms.pHead; p != NULL; p = p->pNext)
			{
				outFile << p->data.maSach << endl;
				outFile << p->data.ttSach << endl;
				outFile << p->data.viTri << endl;
			}
		}
	}
	else
	{
		cout << "KET NOI VOI FILE DauSach THAT BAI! ";
	}
	outFile.close(); (lds);
}
int SaveDauSach(ds_dausach &lds, string tenSach, string JSBN, string tacGia, string theLoai, string soTrang, string namXb) {
	if (tenSach.length() == 0 || JSBN.length() == 0 || tacGia.length() == 0 || theLoai.length() == 0 || soTrang.length() == 0 || namXb.length() == 0) {
		return 2;
		// bang 2 la thong tin tr?ng
	}
	else
	{
		dauSach_info info = { JSBN,tenSach,tacGia,theLoai,stoi(soTrang),stoi(namXb) };
		danhmucsach dms;
		pDAU_SACH pDS;
		pDS = new DauSach;
		pDS->info = info;
		initList_DMS(pDS->ldms);
		//AddTailList_DMS(pDS->ldms, dms);
		int kq = Insert_DauSach(lds, pDS);
		// kq = 1 là add vao ds thanh cong
		// kq = 0 là ds full
		SaveFileListDS(lds);

		return kq;
	}
}
void SaveDauSachEdit(ds_dausach &lds, int pos, string tenSach, string JSBN, string tacGia, string theLoai, string soTrang, string namXb) {
	if (tenSach.length() == 0 || JSBN.length() == 0 || tacGia.length() == 0 || theLoai.length() == 0 || soTrang.length() == 0 || namXb.length() == 0) {

		// bang 2 la thong tin tr?ng
	}
	else
	{
		lds.data[pos]->info.tacgia = tacGia;
		lds.data[pos]->info.ISBN = JSBN;
		lds.data[pos]->info.theloai = theLoai;
		lds.data[pos]->info.tensach = tenSach;
		lds.data[pos]->info.sotrang = stoi(soTrang);
		lds.data[pos]->info.namXB = stoi(namXb);
		SaveFileListDS(lds);
	}
}
int NhapSo(string &result, int &count, int size)
{
	int charr;
	while (true)
	{
		charr = _getch();
		if (((charr >= 48 && charr <= 57)) && count < size)
		{
			count++;
			charr = toupper((char)charr);
			cout << (char)charr;
			result += (char)charr;
		}
		else if (charr == BACKSPACE && count > 0)
		{

			cout << "\b" << " " << "\b";
			count--;
			result.erase(result.length() - 1, 1);
		}
		else if (charr == 0) {
			charr = _getch();
			if (charr == 68) {
				return charr;
			}
		}
		else if (charr == ENTER) {
			return charr;
			break;
		}
		else if (charr == 224)
		{
			charr = _getch();
			if (charr == UP)
			{


				return UP;
				break;
			}
			else if (charr == DOWN) {
				gotoxy(46, 23);
				gotoxy(46, 19);
				return DOWN;
				break;

			}

		}
	}

}
void themDauSach(ds_dausach &lds, string tenSach, string JSBN, string tacGia, string theLoai, string soTrang, string namSb) {
	SetColor(15);
	int viTri = 0, doDai = 20, tt = 0, state = 0;
	int sizeTenSach = tenSach.length();
	int sizeJSBN = JSBN.length();
	int sizeTacGia = tacGia.length();
	int sizeTheLoai = theLoai.length();
	int sizeSoTrang = soTrang.length();
	int sizeNamSB = namSb.length();
	// lable ten sach
tensach: {
	SetColor(15);
	int len = tenSach.length();
	gotoxy(46 + len, 7);
	tt = NhapChu(tenSach, sizeTenSach, 20);
	if (tt == DOWN)
		goto JSBN;
	else if (tt == 68) {
		if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 1) {
			thongbao("Da them thanh cong!", 40, 2, 6, 2);
			tenSach = ""; JSBN = "", tacGia = "", theLoai = "", soTrang = "", namSb = "";
			gotoxy(46, 7);
			cout << setw(sizeTenSach) << " ";
			gotoxy(46, 11);
			cout << setw(sizeJSBN) << " ";
			gotoxy(46, 15);
			cout << setw(sizeTacGia) << " ";
			gotoxy(46, 19);
			cout << setw(sizeTheLoai) << " ";
			gotoxy(46, 23);
			cout << setw(sizeSoTrang) << " ";
			gotoxy(46, 27);
			cout << setw(sizeNamSB) << " ";
		}
		else if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 2)
		{
			thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
		}
	}
	else if (tt == ESC) {
		return;
	}
	goto tensach;
	}
		 // lable JSBN
	 JSBN: {
		 SetColor(15);
		 int len = JSBN.length();
		 gotoxy(46 + len, 11);
		 tt = NhapChu(JSBN, sizeJSBN, 6);
		 switch (tt) {
		 case UP: {
			 goto tensach;
			 break;
		 }
		 case DOWN: {
			 goto tacgia;
			 break;
		 }
		 }
		 if (tt == 68) {
			 if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 1) {
				 thongbao("Da them thanh cong!", 40, 2, 6, 2);
				 tenSach = ""; JSBN = "", tacGia = "", theLoai = "", soTrang = "", namSb = "";
				 gotoxy(46, 7);
				 cout << setw(sizeTenSach) << " ";
				 gotoxy(46, 11);
				 cout << setw(sizeJSBN) << " ";
				 gotoxy(46, 15);
				 cout << setw(sizeTacGia) << " ";
				 gotoxy(46, 19);
				 cout << setw(sizeTheLoai) << " ";
				 gotoxy(46, 23);
				 cout << setw(sizeSoTrang) << " ";
				 gotoxy(46, 27);
				 cout << setw(sizeNamSB) << " ";
			 }
			 else if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 2)
			 {
				 thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
			 }

		 }
		 else if (tt == ESC) {
			 return;
		 }
		 goto JSBN;
}
		   // lable tac gia
	   tacgia: {
		   SetColor(15);
		   int len = tacGia.length();
		   gotoxy(46 + len, 15);
		   tt = NhapChu(tacGia, sizeTacGia, 20);
		   switch (tt) {
		   case UP: {
			   goto JSBN;
			   break;
		   }
		   case DOWN: {
			   goto theloai;
			   break;
		   }
		   }
		   if (tt == 68) {
			   if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 1) {
				   thongbao("Da them thanh cong!", 40, 2, 6, 2);
				   tenSach = ""; JSBN = "", tacGia = "", theLoai = "", soTrang = "", namSb = "";
				   gotoxy(46, 7);
				   cout << setw(sizeTenSach) << " ";
				   gotoxy(46, 11);
				   cout << setw(sizeJSBN) << " ";
				   gotoxy(46, 15);
				   cout << setw(sizeTacGia) << " ";
				   gotoxy(46, 19);
				   cout << setw(sizeTheLoai) << " ";
				   gotoxy(46, 23);
				   cout << setw(sizeSoTrang) << " ";
				   gotoxy(46, 27);
				   cout << setw(sizeNamSB) << " ";
			   }
			   else if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 2)
			   {
				   thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
			   }

		   }
		   else if (tt == ESC) {
			   return;
		   }
		   goto tacgia;
	 }
			   // lable the loai
		   theloai: {
			   SetColor(15);
			   int len = theLoai.length();
			   gotoxy(46 + len, 19);
			   tt = NhapChu(theLoai, sizeTheLoai, 4);
			   switch (tt) {
			   case UP: {
				   goto tacgia;
				   break;
			   }
			   case DOWN: {
				   goto sotrang;
				   break;
			   }
			   }
			   if (tt == 68) {
				   if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 1) {
					   thongbao("Da them thanh cong!", 40, 2, 6, 2);
					   tenSach = ""; JSBN = "", tacGia = "", theLoai = "", soTrang = "", namSb = "";
					   gotoxy(46, 7);
					   cout << setw(sizeTenSach) << " ";
					   gotoxy(46, 11);
					   cout << setw(sizeJSBN) << " ";
					   gotoxy(46, 15);
					   cout << setw(sizeTacGia) << " ";
					   gotoxy(46, 19);
					   cout << setw(sizeTheLoai) << " ";
					   gotoxy(46, 23);
					   cout << setw(sizeSoTrang) << " ";
					   gotoxy(46, 27);
					   cout << setw(sizeNamSB) << " ";
				   }
				   else if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 2)
				   {
					   thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
				   }

			   }
			   else if (tt == ESC) {
				   return;
			   }
			   goto theloai;
	   }
					// lable so trang
				sotrang: {
					SetColor(15);
					int len = soTrang.length();
					gotoxy(46 + len, 23);
					tt = NhapSo(soTrang, sizeSoTrang, 6);
					switch (tt) {
					case UP: {
						goto theloai;
						break;
					}
					case DOWN: {
						goto namsb;
						break;
					}
					}
					if (tt == 68) {
						if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 1) {
							thongbao("Da them thanh cong!", 40, 2, 6, 2);
							tenSach = ""; JSBN = "", tacGia = "", theLoai = "", soTrang = "", namSb = "";
							gotoxy(46, 7);
							cout << setw(sizeTenSach) << " ";
							gotoxy(46, 11);
							cout << setw(sizeJSBN) << " ";
							gotoxy(46, 15);
							cout << setw(sizeTacGia) << " ";
							gotoxy(46, 19);
							cout << setw(sizeTheLoai) << " ";
							gotoxy(46, 23);
							cout << setw(sizeSoTrang) << " ";
							gotoxy(46, 27);
							cout << setw(sizeNamSB) << " ";
						}
						else if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 2)
						{
							thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
						}

					}
					else if (tt == ESC) {
						return;
					}
					goto sotrang;
		   }
						 // lable namsb
					 namsb: {
						 SetColor(15);
						 int len = namSb.length();
						 gotoxy(46 + len, 27);
						 tt = NhapSo(namSb, sizeNamSB, 4);
						 switch (tt) {
						 case UP: {
							 goto sotrang;
							 break;
						 }
						 case DOWN: {

							 break;
						 }
						 }
						 if (tt == 68) {
							 if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 1) {
								 thongbao("Da them thanh cong!", 40, 2, 6, 2);
								 tenSach = ""; JSBN = "", tacGia = "", theLoai = "", soTrang = "", namSb = "";
								 gotoxy(46, 7);
								 cout << setw(sizeTenSach) << " ";
								 gotoxy(46, 11);
								 cout << setw(sizeJSBN) << " ";
								 gotoxy(46, 15);
								 cout << setw(sizeTacGia) << " ";
								 gotoxy(46, 19);
								 cout << setw(sizeTheLoai) << " ";
								 gotoxy(46, 23);
								 cout << setw(sizeSoTrang) << " ";
								 gotoxy(46, 27);
								 cout << setw(sizeNamSB) << " ";
							 }
							 else if (SaveDauSach(lds, tenSach, JSBN, tacGia, theLoai, soTrang, namSb) == 2)
							 {
								 thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
							 }

						 }
						 else if (tt == ESC) {
							 return;
						 }
						 goto namsb;
				}




}
int NhapTrangThaiDMS(string &result, int &count, int size) {
	HienConTro();
	int charr;
	while (true)
	{
		charr = _getch();
		if (((charr >= 48 && charr <= 50)) && count < size)
		{
			count++;
			charr = toupper((char)charr);
			cout << (char)charr;
			result += (char)charr;
		}
		else if (charr == ESC) {
			return charr;
		}
		else if (charr == BACKSPACE && count > 0)
		{

			cout << "\b" << " " << "\b";
			count--;
			result.erase(result.length() - 1, 1);
		}
		else if (charr == 0) {
			charr = _getch();
			if (charr == 68) {
				return charr;
			}
		}
		else if (charr == ENTER) {
			return charr;
			break;
		}
		else if (charr == 224)
		{
			charr = _getch();
			if (charr == UP)
			{
				return UP;
				break;
			}
			else if (charr == DOWN) {

				return DOWN;
				break;
			}
			else if (charr == LEFT) {

				return LEFT;
				break;
			}
			else if (charr == RIGHT) {

				return RIGHT;
				break;
			}

		}
		else if (charr == 0) {
			charr = _getch();
			if (charr == 68) {
				return charr;
			}
		}
	}

}
node_dms* GetNode_DMS(danhmucsach DATA)
{
	node_dms *p = new node_dms;
	if (p == NULL) {
		return NULL;
	}
	p->data = DATA;
	p->pNext = NULL;
	return (p);
}
void AddTailList_DMS(list_dms &l, danhmucsach data)
{
	// tao Node
	node_dms *p = GetNode_DMS(data);
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
	l.n++;
}
void themDanhMucSach(ds_dausach &lds, int pos, string trangThai, string viTriSach) {

	danhmucsach dms;
	list_dms lsDMS;
	initList_DMS(lsDMS);
	SetColor(15);
	string  maSach = lds.data[pos]->info.ISBN;;
	int countMaSach = lds.data[pos]->ldms.n;
	int  tt = 0, toaDoY = lds.data[pos]->ldms.n;
	int sizeViTri = viTriSach.length();
	int sizeTrangThai = trangThai.length();
	int charr;

	while (1) {
		charr = _getch();
		if (charr == ENTER) {
			countMaSach++;
			gotoxy(18, 6 + lds.data[pos]->ldms.n);
			cout << to_string(countMaSach) + maSach;
			break;
		}
		else if (charr == ESC) {
			return;
		}
	}

trangthai: {
	SetColor(15);
	int len = trangThai.length();
	gotoxy(41 + len, 6 + toaDoY);
	tt = NhapTrangThaiDMS(trangThai, sizeTrangThai, 1);
	switch (tt) {
	case UP: {
		goto trangthai;
		break;
	}
	case DOWN: {
		goto trangthai;
		break;
	}
	case LEFT: {
		goto trangthai;
		break;
	}
	case RIGHT: {
		if (trangThai.length() == 0) {
			goto trangthai;
			break;
		}
		else
		{
			goto vitri;
			break;
		}
	}
	case ENTER: {
		if (viTriSach.length() == 0 || trangThai.length() == 0) {
			goto trangthai;
			break;
		}
		else
		{

			dms.maSach = to_string(countMaSach) + maSach;
			dms.ttSach = stoi(trangThai);
			dms.viTri = viTriSach;
			AddTailList_DMS(lsDMS, dms);
			toaDoY++;
			trangThai = "";
			viTriSach = "";
			sizeViTri = viTriSach.length();
			sizeTrangThai = trangThai.length();
			countMaSach++;
			gotoxy(18, 6 + toaDoY);
			cout << to_string(countMaSach) + maSach;
			goto trangthai;
			break;
		}
	}
	case 68: {
		if (trangThai.length() != 0 && viTriSach.length() != 0) {
			dms.maSach = to_string(countMaSach) + maSach;
			dms.ttSach = stoi(trangThai);
			dms.viTri = viTriSach;
			AddTailList_DMS(lsDMS, dms);
			trangThai = "";
			viTriSach = "";
			sizeViTri = viTriSach.length();
			sizeTrangThai = trangThai.length();
		}
		for (node_dms* p = lsDMS.pHead; p != NULL; p = p->pNext)
		{
			AddTailList_DMS(lds.data[pos]->ldms, p->data);
		}
		SaveFileListDS(lds);
		thongbao("Da them thanh cong!Enter de tiep tuc.", 33, 25, 6, 2);
		SetColor(15);
		toaDoY++;
		trangThai = "";
		viTriSach = "";
		sizeViTri = viTriSach.length();
		sizeTrangThai = trangThai.length();
		countMaSach++;
		gotoxy(18, 6 + toaDoY);
		cout << to_string(countMaSach) + maSach;
		goto trangthai;

		break;

	}
	case ESC: {
		AnConTro();
		return;
	}
	}
	goto trangthai;
	}

	   vitri: {
		   SetColor(15);
		   int len = viTriSach.length();
		   gotoxy(63 + len, 6 + toaDoY);
		   tt = NhapChu(viTriSach, sizeViTri, 20);
		   switch (tt) {
		   case UP: {
			   goto vitri;
			   break;
		   }
		   case DOWN: {
			   goto vitri;
			   break;
		   }
		   case LEFT: {
			   goto trangthai;
			   break;
		   }
		   case RIGHT: {
			   goto vitri;
			   break;

		   }
		   case ENTER: {
			   if (viTriSach.length() == 0 || trangThai.length() == 0) {
				   goto vitri;
				   break;
			   }
			   else
			   {

				   dms.maSach = to_string(countMaSach) + maSach;
				   dms.ttSach = stoi(trangThai);
				   dms.viTri = viTriSach;
				   AddTailList_DMS(lsDMS, dms);
				   toaDoY++;
				   trangThai = "";
				   viTriSach = "";
				   sizeViTri = viTriSach.length();
				   sizeTrangThai = trangThai.length();

				   countMaSach++;
				   gotoxy(18, 6 + toaDoY);
				   cout << to_string(countMaSach) + maSach;
				   goto trangthai;
				   break;
			   }
		   }
		   case 68: {
			   if (trangThai.length() != 0 && viTriSach.length() != 0) {
				   dms.maSach = to_string(countMaSach) + maSach;
				   dms.ttSach = stoi(trangThai);
				   dms.viTri = viTriSach;
				   AddTailList_DMS(lsDMS, dms);
				   trangThai = "";
				   viTriSach = "";
				   sizeViTri = viTriSach.length();
				   sizeTrangThai = trangThai.length();
			   }
			   for (node_dms* p = lsDMS.pHead; p != NULL; p = p->pNext)
			   {
				   AddTailList_DMS(lds.data[pos]->ldms, p->data);
			   }
			   SaveFileListDS(lds);
			   thongbao("Da them thanh cong!Enter de tiep tuc.", 33, 25, 6, 2);
			   SetColor(15);
			   toaDoY++;
			   trangThai = "";
			   viTriSach = "";
			   sizeViTri = viTriSach.length();
			   sizeTrangThai = trangThai.length();
			   countMaSach++;
			   gotoxy(18, 6 + toaDoY);
			   cout << to_string(countMaSach) + maSach;
			   goto trangthai;

			   break;
		   }
		   case ESC: {
			   AnConTro();
			   return;
		   }
		   }
		   goto vitri;
}
}
void khungCapNhapDauSach() {
	gotoxy(1, 1); cout << setw(100) << " ";
	gotoxy(43, 3); cout << "CAP NHAP DAU SACH";
	gotoxy(33, 32); cout << "Hot key:     ESC: Thoat     F10: Luu";
	gotoxy(23, 5); cout << char(218); for (int i = 0; i < 52; i++) cout << char(196); cout << char(191);
	for (int i = 0; i < 24; i++) {
		gotoxy(23, 6 + i);
		cout << char(179);
	}
	for (int i = 0; i < 24; i++) {
		gotoxy(76, 6 + i);
		cout << char(179);
	}
	gotoxy(23, 30); cout << char(192); for (int i = 0; i < 52; i++) cout << char(196); cout << char(217);

	gotoxy(27, 7); cout << "Ten Sach     : ";

	gotoxy(42, 8); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 7 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 7 + i);
		cout << char(179);
	}
	gotoxy(42, 6); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);



	gotoxy(27, 11); cout << "JSBN         : ";

	gotoxy(42, 12); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 11 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 11 + i);
		cout << char(179);
	}
	gotoxy(42, 10); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);



	gotoxy(27, 15); cout << "Tac Gia      : ";

	gotoxy(42, 16); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 15 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 15 + i);
		cout << char(179);
	}
	gotoxy(42, 14); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);


	gotoxy(27, 19); cout << "The Loai     : ";

	gotoxy(42, 20); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 19 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 19 + i);
		cout << char(179);
	}
	gotoxy(42, 18); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);


	gotoxy(27, 23); cout << "So Trang     : ";

	gotoxy(42, 24); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 23 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 23 + i);
		cout << char(179);
	}
	gotoxy(42, 22); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);


	gotoxy(27, 27); cout << "Nam Xuat Ban : ";


	gotoxy(42, 28); cout << char(192);  for (int i = 0; i < 30; i++) cout << char(196); cout << char(217);
	for (int i = 0; i < 1; i++) {
		gotoxy(42, 27 + i);
		cout << char(179);
	}
	for (int i = 0; i < 1; i++) {
		gotoxy(73, 27 + i);
		cout << char(179);
	}
	gotoxy(42, 26); cout << char(218); for (int i = 0; i < 30; i++) cout << char(196); cout << char(191);

	gotoxy(43, 15); cout << setw(3) << " ";
	HienConTro();
}
void CapNhapDMS(ds_dausach &lds, string maSach, string viTri, int trangThai, int posLDS, int posLDMS) {
	SetColor(15);
	int tt = 0;
	int sizeVitri = viTri.length();
	gotoxy(46, 7), cout << maSach;
	gotoxy(46, 10), cout << viTri;
	if (trangThai == 0) {
		gotoxy(46, 13); cout << ">>";
	}
	else if (trangThai == 2) {
		gotoxy(65, 13); cout << ">>";
	}
vitri: {
	SetColor(15);
	int len = viTri.length();
	gotoxy(46 + len, 10);
	tt = NhapChu(viTri, sizeVitri, 20);
	if (tt == DOWN) {
		goto trangthai;

	}
	else if (tt == ESC) {
		return;
	}
	else if (tt == 68) {
		int i = 1;
		for (node_dms* p = lds.data[posLDS]->ldms.pHead; p != NULL; p = p->pNext)
		{
			if (i == posLDMS) {
				p->data.ttSach = trangThai;
				p->data.viTri = viTri;
				SaveFileListDS(lds);
				break;
			}
			i++;
		}
		thongbao("Thanh cong!", 15, 30, 6, 0);
		return;

	}
	goto vitri;
	}
   trangthai: {
	   tt = ChonTrangThaiDMS(trangThai);
	   if (tt == UP) {
		   goto vitri;
	   }
	   else if (tt == 68) {
		   int i = 1;
		   for (node_dms* p = lds.data[posLDS]->ldms.pHead; p != NULL; p = p->pNext)
		   {
			   if (i == posLDMS) {
				   p->data.ttSach = trangThai;
				   p->data.viTri = viTri;
				   SaveFileListDS(lds);
				   break;
			   }
			   i++;
		   }
		   thongbao("Thanh cong!", 45, 20, 6, 0);
		   return;
	   }
	   goto trangthai;
}
}
void CapNhapDauSach(ds_dausach &lds, string tenSach, string JSBN, string tacGia, string theLoai, string soTrang, string namSb) {
	SetColor(15);
	int viTri = 0, doDai = 20, tt = 0, state = 0;
	int sizeTenSach = tenSach.length();
	int sizeJSBN = JSBN.length();
	int sizeTacGia = tacGia.length();
	int sizeTheLoai = theLoai.length();
	int sizeSoTrang = soTrang.length();
	int sizeNamSB = namSb.length();

	gotoxy(46, 7);
	cout << tenSach;
	gotoxy(46, 11);
	cout << JSBN;
	gotoxy(46, 15);
	cout << tacGia;
	gotoxy(46, 19);
	cout << theLoai;
	gotoxy(46, 23);
	cout << soTrang;
	gotoxy(46, 27);
	cout << namSb;

tensach: {
	SetColor(15);
	int len = tenSach.length();
	gotoxy(46 + len, 7);
	tt = NhapChu(tenSach, sizeTenSach, 20);
	if (tt == DOWN)
		goto JSBN;
	else if (tt == 68) {
		if (tenSach.length() == 0 || JSBN.length() == 0 || tacGia.length() == 0 || theLoai.length() == 0 || soTrang.length() == 0 || namSb.length() == 0) {
			thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
		}


	}
	else if (tt == ESC) {
		return;
	}
	goto tensach;
	}
		 // lable JSBN
	 JSBN: {
		 SetColor(15);
		 int len = JSBN.length();
		 gotoxy(46 + len, 11);
		 tt = NhapChu(JSBN, sizeJSBN, 6);
		 switch (tt) {
		 case UP: {
			 goto tensach;
			 break;
		 }
		 case DOWN: {
			 goto tacgia;
			 break;
		 }
		 }
		 if (tt == 68) {
			 if (tenSach.length() == 0 || JSBN.length() == 0 || tacGia.length() == 0 || theLoai.length() == 0 || soTrang.length() == 0 || namSb.length() == 0) {
				 thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
			 }



		 }
		 else if (tt == ESC) {
			 return;
		 }
		 goto JSBN;
}
		   // lable tac gia
	   tacgia: {
		   SetColor(15);
		   int len = tacGia.length();
		   gotoxy(46 + len, 15);
		   tt = NhapChu(tacGia, sizeTacGia, 20);
		   switch (tt) {
		   case UP: {
			   goto JSBN;
			   break;
		   }
		   case DOWN: {
			   goto theloai;
			   break;
		   }
		   }
		   if (tt == 68) {
			   if (tenSach.length() == 0 || JSBN.length() == 0 || tacGia.length() == 0 || theLoai.length() == 0 || soTrang.length() == 0 || namSb.length() == 0) {
				   thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
			   }
			   else {
				   SaveDauSachEdit(lds, position, tenSach, JSBN, tacGia, theLoai, soTrang, namSb);
				   thongbao("Cap nhap thanh cong!", 36, 2, 6, 12);


			   }

		   }
		   else if (tt == ESC) {
			   return;
		   }
		   goto tacgia;
	 }
			   // lable the loai
		   theloai: {
			   SetColor(15);
			   int len = theLoai.length();
			   gotoxy(46 + len, 19);
			   tt = NhapChu(theLoai, sizeTheLoai, 4);
			   switch (tt) {
			   case UP: {
				   goto tacgia;
				   break;
			   }
			   case DOWN: {
				   goto sotrang;
				   break;
			   }
			   }
			   if (tt == 68) {
				   if (tenSach.length() == 0 || JSBN.length() == 0 || tacGia.length() == 0 || theLoai.length() == 0 || soTrang.length() == 0 || namSb.length() == 0) {
					   thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
				   }
				   else {
					   SaveDauSachEdit(lds, position, tenSach, JSBN, tacGia, theLoai, soTrang, namSb);
					   thongbao("Cap nhap thanh cong!", 36, 2, 6, 12);


				   }
			   }
			   else if (tt == ESC) {
				   return;
			   }
			   goto theloai;
	   }
					// lable so trang
				sotrang: {
					SetColor(15);
					int len = soTrang.length();
					gotoxy(46 + len, 23);
					tt = NhapSo(soTrang, sizeSoTrang, 6);
					switch (tt) {
					case UP: {
						goto theloai;
						break;
					}
					case DOWN: {
						goto namsb;
						break;
					}
					}
					if (tt == 68) {
						if (tenSach.length() == 0 || JSBN.length() == 0 || tacGia.length() == 0 || theLoai.length() == 0 || soTrang.length() == 0 || namSb.length() == 0) {
							thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
						}
						else {
							SaveDauSachEdit(lds, position, tenSach, JSBN, tacGia, theLoai, soTrang, namSb);
							thongbao("Cap nhap thanh cong!", 36, 2, 6, 12);


						}

					}
					else if (tt == ESC) {
						return;
					}
					goto sotrang;
		   }
						 // lable namsb
					 namsb: {
						 SetColor(15);
						 int len = namSb.length();
						 gotoxy(46 + len, 27);
						 tt = NhapSo(namSb, sizeNamSB, 4);
						 switch (tt) {
						 case UP: {
							 goto sotrang;
							 break;
						 }
						 case DOWN: {

							 break;
						 }
						 }
						 if (tt == 68) {
							 if (tenSach.length() == 0 || JSBN.length() == 0 || tacGia.length() == 0 || theLoai.length() == 0 || soTrang.length() == 0 || namSb.length() == 0) {
								 thongbao("Thong tin khong duoc trong!", 36, 2, 6, 12);
							 }
							 else {
								 SaveDauSachEdit(lds, position, tenSach, JSBN, tacGia, theLoai, soTrang, namSb);
								 thongbao("Cap nhap thanh cong!", 36, 2, 6, 12);
							 }
						 }
						 else if (tt == ESC) {
							 return;
						 }
						 goto namsb;
				}
}
void LoadListDS(ds_dausach &lds) {
	fstream data;
	int sodausach, sosach;
	dauSach_info info;
	pDAU_SACH pDs;
	danhmucsach dms;
	data.open("DauSach.txt", ios::in | ios::binary);
	if (data.is_open()) {
		string temp;
		data >> sodausach;
		getline(data, temp);
		for (int i = 0; i < sodausach; i++)
		{
			pDs = new DauSach;
			if (pDs == NULL) continue;

			// load thong tin vao bien tam.
			getline(data, info.tensach);
			getline(data, info.ISBN);
			getline(data, info.tacgia);
			getline(data, info.theloai);
			data >> info.sotrang;
			data >> info.namXB;

			// load thong tin vao dau sach
			pDs->info = info;
			data >> sosach;
			getline(data, temp);
			initList_DMS(pDs->ldms);
			for (int j = 0; j < sosach; j++)
			{
				getline(data, dms.maSach);
				data >> dms.ttSach;
				getline(data, temp);
				getline(data, dms.viTri);
				AddTailList_DMS(pDs->ldms, dms);
			}

			Insert_DauSach(lds, pDs);
		}

	}
	data.close();
}
int ChucNangCapNhapDauSach(ds_dausach &lds, int &start, int &maxSize) {
	int charr;
	int index = 6;
	position = 1;
	while (true)
	{
		charr = _getch();
		// c?n phím nào thì return phím ?ó ra sài
		if (charr == ESC) {
			return ESC;
		}
		else if (charr == ENTER) {
			/*clrscr();
			string s = "", s1 = "";
			KhungDanhMucSach(lds, pos);
			themDanhMucSach(lds, pos, s, s1);
			*/
			return charr;
		}
		else if (charr == 0) {
			charr = _getch();
			if (charr == 60) {
				return charr;
			}
			else if (charr == 61) {
				return charr;
			}
			else if (charr == 62) {
				if (CheckTTDMS(lds, position)) {
					Delete_DauSach(lds, position);
					SaveFileListDS(lds);
					thongbao("Xoa Thanh cong! Enter de tiep tuc", 25, 30, 6, 0);
					int charDel;
					while (true)
					{
						charDel = _getch();
						if (charDel == ENTER) {
							AnConTro();
							break;
						}
					}
					break;

				}
				else {
					SetColor(15);
					thongbao("Sach dang cho muon, khong duoc xoa! Enter de tiep tuc", 23, 30, 6, 0);
					int charDel;
					while (true)
					{
						charDel = _getch();
						if (charDel == ENTER) {
							AnConTro();
							break;
						}

					}
				}
			}
			else if (charr == 63) {
				if (maxSize - 19 > 0) {
					maxSize = maxSize - 18;
					start = start + 18;
					position = start;
					index = 6;
					clrscr();
					KhungDanhSachDauSach(lds, "CHON DAU SAC DE CAP NHAP DANH MUC SACH", start, 0, maxSize);
					SetColor(17);
					gotoxy(15, 25), cout << "F2: Them dau sach " << "--- F3: Sua thong tin dau sach " << "--- F4 : Xoa dau sach";
					gotoxy(27, 26), cout << "ENTER: Cap nhap danh muc sach " << "--- ESC: Thoat";
					SetColor(15);
				}
			}
			else if (charr == 64) {

				if (maxSize + 18 <= lds.n) {
					maxSize = maxSize + 18;
					start = start - 18;
					position = start;
					index = 6;
					clrscr();
					KhungDanhSachDauSach(lds, "CHON DAU SAC DE CAP NHAP DANH MUC SACH", start, 0, maxSize);
					SetColor(17);
					gotoxy(15, 25), cout << "F2: Them dau sach " << "--- F3: Sua thong tin dau sach " << "--- F4 : Xoa dau sach";
					gotoxy(27, 26), cout << "ENTER: Cap nhap danh muc sach " << "--- ESC: Thoat";
					SetColor(15);
				}

			}
			else if (charr == 67) {
				string tenSach = "";
				int a = 0;
				int size = tenSach.length();
				gotoxy(6, 28); cout << "Nhap ten sach tim kiem: ";
				HienConTro();
				int tt = NhapChu(tenSach, a, 20);
				switch (tt)
				{
				case ENTER: {
					dauSach_info info;

					if (searchDauSach(lds, tenSach, info) == 1) {
						gotoxy(6, 28); cout << setw(100) << "";
						gotoxy(40, 28); cout << "Ten Sach: " << info.tensach;
						gotoxy(40, 29); cout << "JSBN    : " << info.ISBN;
						gotoxy(40, 30); cout << "Tac Gia : " << info.tacgia;
						gotoxy(40, 31); cout << "The Loai: " << info.theloai;
						gotoxy(40, 32); cout << "So Trang: " << info.sotrang;
						gotoxy(40, 33); cout << "NamXB   : " << info.namXB;
						SetColor(0);
						thongbao("---BAM ENTER DE TIEP TUC---", 36, 35, 6, 0);
						SetColor(15);
						AnConTro();
						int charTemp = _getch();
						for (int i = 0; i < 7; i++) {
							gotoxy(40, 28 + i); cout << setw(50) << " ";
						}
					}
					else
					{
						thongbao("Sach ban tim khong co! Bam Enter de tiep tuc!", 28, 30, 6, 0);
						SetColor(15);
						AnConTro();
						int charTemp;
						while (true)
						{
							charTemp = _getch();
							if (charTemp == ENTER) {
								gotoxy(6, 28); cout << setw(100) << "";
								break;
							}

						}
					}

					break;
				}
				case ESC: {
					gotoxy(6, 30); cout << setw(100) << "";
					AnConTro();
					break;

				}
				}

			}
		}
		// x? lý con tr? lên xu?ng
		else if (charr == 224) {
			charr = _getch();
			if (charr == UP) {
				if (index == 6) {
					position = start;
					SetColor(17);
					gotoxy(3, index); cout << "   ";
					gotoxy(3, index); cout << ">>>";
					SetColor(15);
				}
				else
				{
					position--;
					SetColor(17);
					gotoxy(3, index); cout << "   ";
					index--;
					gotoxy(3, index); cout << ">>>";
					SetColor(15);
				}
			}
			else if (charr = DOWN) {
				if (maxSize >= 19) {
					if (position == (start + 17)) {
						SetColor(17);
						gotoxy(3, index); cout << "   ";
						gotoxy(3, index); cout << ">>>";
						SetColor(15);
					}
					else {
						position++;
						SetColor(17);
						gotoxy(3, index); cout << "   ";
						index++;
						gotoxy(3, index); cout << ">>>";
						SetColor(15);
					}
				}
				else {
					if (position == lds.n) {
						SetColor(17);
						gotoxy(3, index); cout << "   ";
						gotoxy(3, index); cout << ">>>";
						SetColor(15);
					}
					else {
						position++;
						SetColor(17);
						gotoxy(3, index); cout << "   ";
						index++;
						gotoxy(3, index); cout << ">>>";
						SetColor(15);
					}

				}

			}

		}
	}
}
void XuLyDMS(ds_dausach &lds, int pos, string trangThai, string viTriSach, int &start, int &maxSizee) {
	danhmucsach dms;
	list_dms lsDMS;
	initList_DMS(lsDMS);
	SetColor(15);
	int posss = 0;
	int index = 6;
	int maxSize = lds.data[position]->ldms.n;
	string  maSach = lds.data[pos]->info.ISBN;;
	int countMaSach = lds.data[pos]->ldms.n;
	int  tt = 0, toaDoY = lds.data[pos]->ldms.n;
	int sizeViTri = viTriSach.length();
	int sizeTrangThai = trangThai.length();
	int charr;

	while (1) {
		charr = _getch();
		if (charr == ENTER) {
			gotoxy(43, 26); cout << "THEM SACH MOI";
			gotoxy(40, 28); cout << "Ma Sach : " << to_string(countMaSach + 1) + maSach;
			gotoxy(40, 29); cout << "Vi tri  :";
			SetColor(15);
			int len = viTriSach.length();
			gotoxy(50 + len, 29);
			tt = NhapChu(viTriSach, sizeViTri, 20);
			switch (tt) {
			case 68: {
				if (viTriSach.length() != 0) {
					countMaSach++;
					maxSize++;
					dms.maSach = to_string(countMaSach) + maSach;
					dms.ttSach = 0;
					dms.viTri = viTriSach;
					AddTailList_DMS(lsDMS, dms);
					viTriSach = "";
					sizeViTri = viTriSach.length();
					sizeViTri = viTriSach.length();
					for (node_dms* p = lsDMS.pHead; p != NULL; p = p->pNext)
					{
						AddTailList_DMS(lds.data[pos]->ldms, p->data);
					}
					SaveFileListDS(lds);
					thongbao("Da them thanh cong!Enter de tiep tuc.", 33, 25, 6, 2);
				}
				int charTemp;
				while (true)
				{
					charTemp = _getch();
					if (charTemp == ENTER) {
						AnConTro();
						SetColor(15);
						clrscr();
						KhungDanhMucSach(lds, position, start, maxSizee);
						break;
					}
				}
				break;
			}
			case ESC: {
				gotoxy(43, 26); cout << setw(50) << "";
				gotoxy(40, 28); cout << setw(50) << "";
				gotoxy(40, 29); cout << setw(50) << "";
				AnConTro();

				break;
			}
			}

		}
		else if (charr == ESC) {
			return;
		}
		else if (charr == 224) {
			charr = _getch();
			if (charr == UP) {
				if (index == 6) {
					posss = start;
					SetColor(17);
					gotoxy(6, index); cout << "   ";
					gotoxy(6, index); cout << ">>>";
					SetColor(15);
				}
				else
				{
					posss--;
					SetColor(17);
					gotoxy(6, index); cout << "   ";
					index--;
					gotoxy(6, index); cout << ">>>";
					SetColor(15);
				}
			}
			else if (charr = DOWN) {
				if (maxSizee >= 18) {
					if (posss == start + 17) {
						SetColor(17);
						gotoxy(6, index); cout << "   ";
						gotoxy(6, index); cout << ">>>";
						SetColor(15);
					}
					else {
						posss++;
						SetColor(17);
						gotoxy(6, index); cout << "   ";
						index++;
						gotoxy(6, index); cout << ">>>";
						SetColor(15);
					}
				}
				else {
					if (posss == maxSize - 1) {
						SetColor(17);
						gotoxy(6, index); cout << "   ";
						gotoxy(6, index); cout << ">>>";
						SetColor(15);
					}
					else {
						posss++;
						SetColor(17);
						gotoxy(6, index); cout << "   ";
						index++;
						gotoxy(6, index); cout << ">>>";
						SetColor(15);
					}
				}

			}
		}
		else if (charr == 0) {
			charr = _getch();
			if (charr == 61) {
				danhmucsach dms = GetDMS(lds, pos, posss + 1);
				if (dms.ttSach == 1) {
					thongbao("Sach dang duoc muon, khong duoc chinh sua! Bam phim bat ki de tiep tuc", 15, 30, 6, 0);
					SetColor(15);
					AnConTro();
					int charTemp = _getch();
				}
				else
				{
					clrscr();
					KhungThemDanhMucSach();
					CapNhapDMS(lds, dms.maSach, ChuanHoaString(dms.viTri), dms.ttSach, pos, posss + 1);
					return;
				}
			}
			else if (charr == 63) {
				if (maxSizee - 18 > 0) {
					maxSizee = maxSizee - 18;
					start = start + 18;
					posss = start;
					index = 6;
					clrscr();
					KhungDanhMucSach(lds, position, start, maxSizee);


				}
			}
			else if (charr == 64) {
				if (maxSizee + 18 <= lds.n) {
					maxSizee = maxSizee + 18;
					start = start - 18;
					posss = start;
					index = 6;
					clrscr();
					KhungDanhMucSach(lds, position, start, maxSizee);

				}

			}
		}
	}

vitri: {

	}
}
void ChonSachDeMuon(TREE &t, ds_dausach &lds, list_mt &lmt, the_doc_gia tdg, int &start, int &maxSizee) {
	muon_tra sachmuon;
	int charr;
	string tensach = lds.data[position]->info.tensach;
	int maxSize = lds.data[position]->ldms.n;
	ngay d;
	GetNgayHienTai(d);
	int pos = 0;
	int index = 6;
	while (true)
	{
		charr = _getch();
		if (charr == ENTER) {

			int i = 1;
			for (node_dms* p = lds.data[position]->ldms.pHead; p != NULL; p = p->pNext)
			{
				if (i == pos + 1) {
					if (p->data.ttSach == 0) {
						sachmuon = { ChuanHoaString(p->data.maSach),d,d,p->data.ttSach,ChuanHoaString(tensach),ChuanHoaString(p->data.viTri) };
						gotoxy(11, 27), cout << "Sach    :" << sachmuon.tensach;
						gotoxy(11, 28), cout << "Ma Sach :" << sachmuon.MASACH;
						gotoxy(11, 29), cout << "Se duoc muon vao ngay thu: " << d.ngay << "-" << d.thang << "-" << d.nam << endl;
						gotoxy(37, 32), cout << "Bam F10 de luu thong tin";
						break;
					}
					else {
						gotoxy(37, 32), cout << "Sach khong duoc muon!";
					}
				}
				i++;
			}
			int charEnter;
			while (true)
			{
				charEnter = _getch();
				if (charEnter == ESC) {
					gotoxy(11, 27), cout << setw(100) << " ";
					gotoxy(11, 28), cout << setw(100) << " ";
					gotoxy(11, 29), cout << setw(100) << " ";
					gotoxy(37, 32), cout << setw(100) << " ";
					break;
				}
				else if (charEnter == 0) {
					charEnter = _getch();
					if (charEnter == 68) {
						//l?u vào file
						i = 1;
						for (node_dms* p = lds.data[position]->ldms.pHead; p != NULL; p = p->pNext)
						{
							if (i == pos) {
								p->data.ttSach = 1;
								break;
							}
							i++;
						}
						node_mt *tempMT = KhoiTaoMT(sachmuon);
						node_tdg *pTDG = NULL;
						pTDG = Find_DG(t, tdg.MATHE);
						ThemVaoCuoi(pTDG->lmt, tempMT);
						Them_List_MT(t, tdg, pTDG->lmt);
						Save_TDG(t);
						SaveFileListDS(lds);
						gotoxy(11, 27), cout << setw(100) << " ";
						gotoxy(11, 28), cout << setw(100) << " ";
						gotoxy(11, 29), cout << setw(100) << " ";
						gotoxy(37, 32), cout << setw(100) << " ";
						break;
					}
				}

			}
		}
		else if (charr == ESC) {
			break;
		}
		else if (charr == 0) {
			charr = _getch();

			if (charr == 63) {
				if (maxSizee - 18 > 0) {
					maxSizee = maxSizee - 18;
					start = start + 18;
					pos = start;
					index = 6;
					clrscr();
					KhungDanhMucSach(lds, position, start, maxSizee);


				}
			}
			else if (charr == 64) {

				if (maxSizee + 18 <= lds.n) {
					maxSizee = maxSizee + 18;
					start = start - 18;
					pos = start;
					index = 6;
					clrscr();
					KhungDanhMucSach(lds, position, start, maxSizee);

				}

			}
		}
		else if (charr == 224) {
			charr = _getch();
			if (charr == UP) {
				if (index == 6) {
					pos = start;
					SetColor(17);
					gotoxy(6, index); cout << "   ";
					gotoxy(6, index); cout << ">>>";
					SetColor(15);
				}
				else
				{
					pos--;
					SetColor(17);
					gotoxy(6, index); cout << "   ";
					index--;
					gotoxy(6, index); cout << ">>>";
					SetColor(15);
				}
			}
			else if (charr = DOWN) {
				if (maxSizee >= 18) {
					if (pos == start + 17) {
						SetColor(17);
						gotoxy(6, index); cout << "   ";
						gotoxy(6, index); cout << ">>>";
						SetColor(15);
					}
					else {
						pos++;
						SetColor(17);
						gotoxy(6, index); cout << "   ";
						index++;
						gotoxy(6, index); cout << ">>>";
						SetColor(15);
					}
				}
				else {
					if (pos == maxSize - 1) {
						SetColor(17);
						gotoxy(6, index); cout << "   ";
						gotoxy(6, index); cout << ">>>";
						SetColor(15);
					}
					else {
						pos++;
						SetColor(17);
						gotoxy(6, index); cout << "   ";
						index++;
						gotoxy(6, index); cout << ">>>";
						SetColor(15);
					}
				}

			}
		}
	}
}
void disableMaximumButton() {
	HWND hwnd = GetConsoleWindow();
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	SetWindowLong(hwnd, GWL_STYLE, style);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}
void setDefaultConfig() {
	disableScrollBar();
	resizeConsole(800, 600);
	disableMaximumButton();
}
void xuly(TREE &treeDG, ds_dausach &lds, ds_qua_han lqh)
{
	position = 1;
	auto a = 0;
	while (1) {
		setcolor(6, 15);
		a = InMenuChinh(thaotac, 5, 2, 10);
		switch (a) {
		case 0: {
			SetBGColor(2);
			clrscr();
			system("cls");
			setcolor(6, 15);
			clrscr();
			cout << countDG(treeDG);
			int sodocgia = countDG(treeDG);
			int start = 0;
			KhungDanhMucTDG(treeDG, sodocgia, start, 0);
			int chucnang = ChucNangTDG(treeDG, sodocgia, start);
			switch (chucnang) {
			case ENTER: {
				clrscr();
				Khung_DS_MT(treeDG, position);
				int charr1 = _getch();
				while (true)
				{
				thoat: {
					if (charr1 == ESC) {
						break;
					}
					}
					   if (charr1 != ESC) {
						   charr1 = _getch();
						   goto thoat;
					   }
				}
				clrscr();
				//KhungDanhMucTDG(treeDG);
				break;
			}
			case F2: {
				int maDg = Random_MADG(treeDG);
				string hoDg = "", tenDg = "";
				int phai = 0;
				setcolor(6, 15);
				clrscr();
				khungThemDocGia();
				themDocGia(treeDG, maDg, hoDg, tenDg, phai);
				break;
			}
			case F3: {
				clrscr();
				SetColor(15);
				the_doc_gia TDG_temp = Find_MADG(treeDG, arrMTDG[position - 1]);
				khungSuaDocGia();
				suaDocGia(treeDG, TDG_temp.MATHE, TDG_temp.ho, TDG_temp.ten, TDG_temp.gioitinh, TDG_temp.trangthaithe);
			}
			case ESC: {
				break;
			}
			}
			break;
		}

		case 1: {
			SetBGColor(2);
			clrscr();
			int a = InMenu(sach, 4, 2, 10);
			while (1) {
				switch (a) {
				case 0: {
					setcolor(6, 15);
					clrscr();
					SetColor(17);
					gotoxy(15, 25), cout << "F2: Them dau sach " << "--- F3: Sua thong tin dau sach " << "--- F4 : Xoa dau sach";
					gotoxy(27, 26), cout << "ENTER: Cap nhap danh muc sach " << "--- ESC: Thoat";
					SetColor(15);
					int maxSize = lds.n;
					int start = 1;
					KhungDanhSachDauSach(lds, "CHON DAU SAC DE CAP NHAP DANH MUC SACH", 1, 0, maxSize);
					int chucnang = ChucNangCapNhapDauSach(lds, start, maxSize);
					switch (chucnang)
					{
					case ENTER: {
						string s = "", s1 = "";
						clrscr();
						int maxSize = lds.data[position]->ldms.n;
						int start = 0;
						KhungDanhMucSach(lds, position, start, maxSize);
						XuLyDMS(lds, position, s, s1, start, maxSize);

						break;
					}case 60: { // 60  == F2
						clrscr();
						string s1 = "", s2 = "", s3 = "", s4 = "", s5 = "", s6 = "";
						khungThemDauSach();
						themDauSach(lds, s1, s2, s3, s4, s5, s6);
						break;
					}case 61: { // 61 == F3
						string s = "", s1 = "";
						clrscr();
						khungCapNhapDauSach();
						int a = lds.data[position]->info.tensach.length();
						CapNhapDauSach(lds, ChuanHoaString(lds.data[position]->info.tensach), ChuanHoaString(lds.data[position]->info.ISBN), ChuanHoaString(lds.data[position]->info.tacgia), ChuanHoaString(lds.data[position]->info.theloai), ChuanHoaString(to_string(lds.data[position]->info.sotrang)), ChuanHoaString(to_string(lds.data[position]->info.namXB)));
					}case 62: {// 62 == F4

					}

					}
					a = InMenu(sach, 4, 2, 10);
					break;
				}
				case 1: {
					setcolor(6, 15);
					clrscr();
					KhungNhapMaDG();
					int maDG = NhapTheDG(treeDG);
					if (maDG != ESC) {
						the_doc_gia tdg = Find_MADG(treeDG, maDG);
						node_tdg *pTDG = NULL;
						pTDG = Find_DG(treeDG, tdg.MATHE);
						clrscr();
						setcolor(6, 15);
						int maxSize = lds.n;
						int start = 1;
						KhungDanhSachDauSach(lds, "     VUI LONG CHON MOT DAU SACH    ", 1, 0, maxSize);
						int chucnang = ChucNangCapNhapDauSach(lds, start, maxSize);
						if (chucnang == ENTER) {
							clrscr();
							int maxSize = lds.data[position]->ldms.n;
							int start = 0;
							KhungDanhMucSach(lds, position, start, maxSize);
							ChonSachDeMuon(treeDG, lds, pTDG->lmt, tdg, start, maxSize);
						}
					}
					a = InMenu(sach, 4, 2, 10);
					break;
				}
				case 2: {
					clrscr();
					break;
				}
				case 3: {
					clrscr();
					break;
				}
				}
				break;
			}
			xuly(treeDG, lds, lqh);
			break;
		}

		case 2: {
			system("cls");
			int a = InMenu(in, 5, 2, 10);
			switch (a) {
			case 0: {
				system("cls");

				break;
			}
			case 1: {
				system("cls");

				break;
			}
			case 2: {
				system("cls");

				break;
			}
			case 3: {
				system("cls");

				break;
			}
			case 4: {
				system("cls");
				xuly(treeDG, lds, lqh);
				break;
			}
			}
			break;
		}

		case 3: {
			system("cls");
			int a = InMenu(timkiem, 3, 2, 10);
			switch (a) {
			case 0: {
				//resizeConsole(800, 600);
				//disableScrollBar();
				setcolor(6, 15);
				clrscr();

				khungnhap_TenSach("TIM KIEM THEO TEN SACH");
				string tensach;
				int vitri = 0;
				int dodai = 20;


				break;
			}
			case 1: {
				system("cls");

				break;
			}
			case 2: {
				system("cls");
				xuly(treeDG, lds, lqh);

				break;
			}
			}

			break;
		}

		case 4: {
			if (thoat() == 1) exit(1);
			else
				xuly(treeDG, lds, lqh);
			break;
		}
		}
	}
}
int main() {
	setDefaultConfig();
	setcolor(6, 15);
	system("cls");
	AnConTro();
	TREE treeDG;
	ds_dausach lds;
	ds_qua_han lqh;
	KhoiTaoTree(treeDG);
	Doc_TDG(treeDG, lqh);
	int index = 0;
	LoadListDS(lds);
	int n = countDG(treeDG);
	selectionSort_DS(lds);
	selectionSortTen_DS(lds);
	Sort_QuaHan(lqh);
	xuly(treeDG, lds, lqh);
	system("pause");
	return 0;
}
