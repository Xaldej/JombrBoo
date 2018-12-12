/*JoombrBoo
authours:
alexey melentyev
mihail ignatenko
oleg sazonov
date: 10.12.18*/

#include"head.h"
using namespace std;

const int M = 5;
const int N = 100;
int Database_user_1[M][N];
int Database_user_2[M][N];
/*each column contain information about element
0 line: type of element
	 1 - wall
	 2 - usual gun
	 3 - in progress =)
1st line: remaining hp
2nd line: remaining shots
3rd and 4th lines: position of element
*/

void main()
{
	testFunction();

	system("pause");
	return;
}