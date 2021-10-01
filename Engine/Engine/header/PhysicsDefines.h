#pragma once

#define PxRelease(x)		if(x)	{ x->release(); x = NULL;	}

#define ToPxVec3(v)			PxVec3((v).x, (v).y, (v).z)

#define FromPxVec3(v)		Vec3((v).x, (v).y, (v).z)

#define ToPxQuat(q)			PxQuat((q).x, (q).y, (q).z, (q).w)

#define FromPxQuat(q)		Quat((q).x, (q).y, (q).z, (q).w)