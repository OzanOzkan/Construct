#include <ILog.h>

class CLog : public ILog
{
public:
	virtual ~CLog() {}

	virtual void Log(const char* text) override;
};