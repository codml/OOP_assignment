#pragma once
#pragma warning(disable:4996)
#include <cstring>

class myMusic
{
private:
	char m_title[32];
	char m_singer[32];
	char m_album[32];
	int m_track_no;
	int m_year;

public:
	myMusic();
	~myMusic();

	void setTitle(char* title);
	void setSinger(char* singer);
	void setAlbum(char* album);
	void setYear(int year);
	void setTrackNo(int track_no); // ��� ������ �� �Ҵ�

	char* getTitle();
	char* getSinger();
	char* getAlbum();
	int getYear();
	int getTrackNo(); // ��� ���� ��ȯ
};