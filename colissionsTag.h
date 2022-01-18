#ifndef __COLISSIONS_TAG_H__
#define __COLISSIONS_TAG_H__

struct ColissionsTag {};
struct PassThrough: public ColissionsTag {};
struct CollideAndBounce: public ColissionsTag {};
struct CollideAndStop: public ColissionsTag {};
struct CollideAndTakeDamage: public ColissionsTag {};
struct CollideAndTriggerWin: public ColissionsTag {};
struct CollideAndTriggerLoss: public ColissionsTag {};
struct CollideAndDestroy: public ColissionsTag {};
struct CollideAndHeal: public ColissionsTag {};

#endif
