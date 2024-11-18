#include "obj2d.h"

OBJ2D* searchSet0(OBJ2D arr[], int dataNum, OBJ2D::FUNC_PTR moveAlg, VECTOR2 pos)
{
	for (int i = 0; i < dataNum; ++i) {
		if (arr[i].moveAlg)		continue;

		arr[i]			={};
		arr[i].moveAlg	= moveAlg;
		arr[i].pos		= pos;
		return &arr[i];
	}

	// ¶¬‚Å‚«‚È‚©‚Á‚½
	return NULL;
}

OBJ2D* searchSet(OBJ2D* begin, OBJ2D* end, OBJ2D::FUNC_PTR moveAlg, VECTOR2 pos)
{
	return NULL;
=======
#include "obj2d.h"

OBJ2D* searchSet0(OBJ2D arr[], int dataNum, OBJ2D::FUNC_PTR moveAlg, VECTOR2 pos)
{
	for (int i = 0; i < dataNum; ++i) {
		if (arr[i].moveAlg)		continue;

		arr[i]			={};
		arr[i].moveAlg	= moveAlg;
		arr[i].pos		= pos;
		return &arr[i];
	}

	// ¶¬‚Å‚«‚È‚©‚Á‚½
	return NULL;
>>>>>>> 3825c1a0c38d20006e0f012db0d0a8b39cc47a7a
}