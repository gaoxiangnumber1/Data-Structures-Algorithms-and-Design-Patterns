#include<iostream>
#include"binary_tree.h"
using namespace std;

int main()
{
	AllOperation();

	return 0;
}

/*
1
7
C B E G D F A
1
A B C D E G F
2
3
4
5
6
7
8
9
10
11
12

1
7
C B E G D F A
2
C G E F D B A
2
3
4
5
6
7
8
9
10
11
12

1
11
D B F G E A H J C I K
1
A B D E F G C H J I K
2
3
4
5
6
7
8
9
10
11
12

1
11
D B F G E A H J C I K
2
D G F E B J H K I C A
2
3
4
5
6
7
8
9
10
11
12
*/

/*
First Binary Tree:
Pre: A B C D E G F
In: C B E G D F A
Post: C G E F D B A
Level: A B C D E F G
Height: 5
NodeCount: 7

Second Binary Tree:
Pre:  A B D E F G C H J I K
In:  D B F G E A H J C I K
Post: D G F E B J H K I C A
Level: A B C D E H I F J K G
Height: 5
NodeCount: 11
*/
