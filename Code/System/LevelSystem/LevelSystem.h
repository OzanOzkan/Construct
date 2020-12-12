#pragma once

#include <System/ISystem.h>
#include <System/LevelSystem/ILevelSystem.h>

class CLevelSystem : public ILevelSystem
{
public:
    CLevelSystem(ISystem* systemContext);

    void loadLevel(const std::string& levelName) override;
    void unloadLevel() override;
    void resetLevel() override;
    std::string getCurrentLevelName() override;

protected:
    ISystem* getSystem() { return m_pSystem; }
    void publishLevelLoadEvent();

private:
    ISystem* m_pSystem;
    std::string m_currentLevelName;
};