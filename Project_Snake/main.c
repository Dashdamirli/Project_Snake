#include"cellList.c"
#include"ppm.c"
#include"cell.c"

int	main(int argc, char const *argv[])
{
	srand(time(0));
	struct cell c1 = C_new(3,3);

	struct arena ar;
	ar.nb_cols=10;
	ar.nb_rows=10;

	struct cellList cr = CL_new();
	cr=CL_randomPath(c1,30,ar);
	CL_print(cr,"random path");

	CL_draw(cr, ar.nb_rows, ar.nb_cols, "snake");
	CL_animate(cr, ar.nb_rows, ar.nb_cols, "snake");

	return 0;
}