#include <iostream>
#include "map.h"

using namespace std;

int main()
{
	Map a;

	a.setBasicMap(5, 5);
	a.setMapByDfs();
	a.setVisitFalse();
	cout << "Map" << endl;
	a.printMap();
	cout << endl << endl;
	a.findPathByDfs(0, 0, 4, 4);
	cout << "DFS: " << endl;
	a.printMap();
	cout << endl << endl;
	a.setVisitFalse();
	a.findPathByBfs(0, 0, 4, 4);
	cout << "BFS: " << endl;
	a.printMap();
	return 0;
}