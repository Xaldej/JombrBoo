/*JoombrBoo
authours:
alexey melentyev
mihail ignatenko
oleg sazonov
date: 10.12.18*/

#include"head.h"
extern HANDLE toPaint;

void main()
{
	char Map[I][H][W];
	bool doContinue = true;
	getTheMapFromTheFile(Map, firstMap);
	addEconomics(Map);
	addGunsList(Map);
	fillIndexesInTheMAp(Map);
	drowTheMap(Map);
	while (doContinue)
	{

	}
	return;
}
