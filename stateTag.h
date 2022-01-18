#ifndef __STATE_TAG_H__
#define __STATE_TAG_H__

struct StateTag {};
struct EmptyTag: public StateTag {};
struct BorderTag: public StateTag {};
struct EntityHeadTag: public StateTag {};
struct EntityBodyTag: public StateTag {};

#endif
