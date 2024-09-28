#pragma once
#pragma warning(disable:4996)
#include <fstream>
#include <iostream>
#include <cstring>

class SongNode
{
private:
	char song[512]; // song 문자열
	SongNode* pnext; // 다음 song

public:
	SongNode(); // 동적할당된 메모리가 없으므로 소멸자 필요 X

	void setSong(char* arr); // song 입력
	void setSongNext(SongNode* ptr); // 다음 노드 설정
	char* getSong(); // song 정보 반환
	SongNode* getSongNext(); // 다음 노드 반환
};

class ArtistNode
{
private:
	char name[512]; // artist 이름
	SongNode* psong; // artist의 song list의 head node
	ArtistNode* pnext; // 다음 artist node

public:
	ArtistNode();
	~ArtistNode();

	void setArtist(char* arr);
	void setSongList(SongNode* ptr);
	void setArtistNext(ArtistNode* pnext); // 멤버 변수에 값 copy
	char* getArtist();
	SongNode* getSongList();
	ArtistNode* getArtistNext(); // 멤버 변수 반환
};

class MyMusicManagementList
{
private:
	ArtistNode* head; // artist node의 head
	ArtistNode* tail; // artist node의 tail, 다음 노드는 head
	void tolower_arr(char* arr); // arr을 소문자로 만드는 함수
	bool isblank(char ch); // ch가 공백문자인 지 판단하는 함수
	void push(ArtistNode* art, SongNode* son); // art 노드를 삽입하고, son 노드를 적절한 위치에 삽입

public:
	MyMusicManagementList();
	~MyMusicManagementList();

	bool make_list(char* file_name); // file_name을 입력받아 파일에서 정보를 받아 리스트 생성
	void print_all(); // 리스트 전체 출력
	void search_next_artist(char* artist); // 입력받은 artist가 있다면 그 다음 artist와 song 정보 출력
};