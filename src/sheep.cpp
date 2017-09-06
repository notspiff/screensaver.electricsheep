#include "kodi/addon-instance/Screensaver.h"
#include <GL/gl.h>
#include <iostream>

#include "client.h"

class AddonSheep : public CElectricSheep {
public:
  bool init(const std::string& presets)
  {
    m_AppData = std::string(getenv("HOME"))+"/.electricsheep/";
    m_WorkingDir = presets+"/resources/";

    if (!InitStorage())
      return false;

    g_Settings()->Set("settings.app.InstallDir", presets+"/resources/");

    AttachLog();

    return true;
  }
};

////////////////////////////////////////////////////////////////////////////
// XBMC has loaded us into memory, we should set our core values
// here and load any settings we may have from our config file
//
class CScreensaverSheep
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceScreensaver
{
public:
  CScreensaverSheep()
  {
    g_Log->Startup();
    if (!sheep.init(Presets().c_str()))
    {
      kodi::Log(ADDON_LOG_ERROR, "Failed to init the sheep!");
      return;
    }
  }

  bool Start()
  {
    g_Settings()->Set("settings.player.cpuusagethreshold",
                      kodi::GetSettingInt("cpuusage_threshold"));

   g_Settings()->Set("settings.player.player_fps",
                     0.25+0.25*kodi::GetSettingInt("speed")*30.0);
   g_Settings()->Set("settings.player.SeamLessPlayback",
                     kodi::GetSettingBoolean("seamless"));
    g_Player().AddDisplay(g_Settings()->Get("settings.player.screen", 0));
    sheep.Startup();
    return true;
  }

  void Render()
  {
    sheep.Update();
  }

  void Stop()
  {
    sheep.Shutdown();
  }

  AddonSheep sheep;
};

ADDONCREATOR(CScreensaverSheep);
