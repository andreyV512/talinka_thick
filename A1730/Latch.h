// ---------------------------------------------------------------------------

#ifndef LatchH
#define LatchH
#include "SignalX.h"

// ---------------------------------------------------------------------------
class Latch
{
public:
	bool value;
	CSignal* signal;
	bool terminate;
	AnsiString reason;
	Latch(bool _value, CSignal* _signal);
};
#endif
