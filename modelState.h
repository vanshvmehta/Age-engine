#ifndef __MODEL_STATE_H__
#define __MODEL_STATE_H__

struct ModelStateTag {};
struct CreateEntityTag: public ModelStateTag {};
struct DestroyEntityTag: public ModelStateTag {};
struct TriggerWinTag: public ModelStateTag {};
struct TriggerLossTag: public ModelStateTag {};
struct TriggerLevelEndTag: public ModelStateTag {};
struct IncrementScoreTag: public ModelStateTag {};
struct UpdateStatusTag: public ModelStateTag {};

#endif
