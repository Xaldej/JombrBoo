
/*JoombrBoo
authours:
alexey melentyev
oleg sazonov
date: 10.12
*/

#include "head.h"

int main()
{
	player = 'L';

	o_fill_batle_field_after_start();
	o_fill_pannels();
	o_display_batle_field(panel_width, field_height, field_width);


	return 0;
}
