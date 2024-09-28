#pragma once
#pragma warning(disable:4996)
#include <fstream>
#include <iostream>
#include <cstring>

class SongNode
{
private:
	char song[512]; // song ���ڿ�
	SongNode* pnext; // ���� song

public:
	SongNode(); // �����Ҵ�� �޸𸮰� �����Ƿ� �Ҹ��� �ʿ� X

	void setSong(char* arr); // song �Է�
	void setSongNext(SongNode* ptr); // ���� ��� ����
	char* getSong(); // song ���� ��ȯ
	SongNode* getSongNext(); // ���� ��� ��ȯ
};

class ArtistNode
{
private:
	char name[512]; // artist �̸�
	SongNode* psong; // artist�� song list�� head node
	ArtistNode* pnext; // ���� artist node

public:
	ArtistNode();
	~ArtistNode();

	void setArtist(char* arr);
	void setSongList(SongNode* ptr);
	void setArtistNext(ArtistNode* pnext); // ��� ������ �� copy
	char* getArtist();
	SongNode* getSongList();
	ArtistNode* getArtistNext(); // ��� ���� ��ȯ
};

class MyMusicManagementList
{
private:
	ArtistNode* head; // artist node�� head
	ArtistNode* tail; // artist node�� tail, ���� ���� head
	void tolower_arr(char* arr); // arr�� �ҹ��ڷ� ����� �Լ�
	bool isblank(char ch); // ch�� ���鹮���� �� �Ǵ��ϴ� �Լ�
	void push(ArtistNode* art, SongNode* son); // art ��带 �����ϰ�, son ��带 ������ ��ġ�� ����

public:
	MyMusicManagementList();
	~MyMusicManagementList();

	bool make_list(char* file_name); // file_name�� �Է¹޾� ���Ͽ��� ������ �޾� ����Ʈ ����
	void print_all(); // ����Ʈ ��ü ���
	void search_next_artist(char* artist); // �Է¹��� artist�� �ִٸ� �� ���� artist�� song ���� ���
};