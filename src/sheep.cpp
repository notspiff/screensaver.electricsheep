#include "xbmc_scr_dll.h"
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

AddonSheep gSheep;

////////////////////////////////////////////////////////////////////////////
// XBMC has loaded us into memory, we should set our core values
// here and load any settings we may have from our config file
//
ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!props)
    return ADDON_STATUS_UNKNOWN;

  SCR_PROPS* p = static_cast<SCR_PROPS*>(props);

  g_Log->Startup();
  if (!gSheep.init(p->presets))
    return ADDON_STATUS_PERMANENT_FAILURE;

  g_Player().AddDisplay(g_Settings()->Get( "settings.player.screen", 0 ));
  gSheep.Startup();

  return ADDON_STATUS_OK;
}

extern "C" void Stop() 
{
}

extern "C" void Start()
{
}

////////////////////////////////////////////////////////////////////////////
// XBMC tells us to render a frame of our screensaver. This is called on
// each frame render in XBMC, you should render a single frame only - the DX
// device will already have been cleared.
//
extern "C" void Render()
{
  gSheep.Update();
}

////////////////////////////////////////////////////////////////////////////
// XBMC tells us to stop the screensaver we should free any memory and release
// any resources we have created.
//
extern "C" void ADDON_Stop()
{
  gSheep.Shutdown();
}

void ADDON_Destroy()
{
}

ADDON_STATUS ADDON_GetStatus()
{
  return ADDON_STATUS_OK;
}

bool ADDON_HasSettings()
{
  return false;
}

unsigned int ADDON_GetSettings(ADDON_StructSetting ***sSet)
{
  return 0;
}

ADDON_STATUS ADDON_SetSetting(const char *strSetting, const void *value)
{
  return ADDON_STATUS_OK;
}

void ADDON_FreeSettings()
{
}

void ADDON_Announce(const char *flag, const char *sender, const char *message, const void *data)
{
}

void GetInfo(SCR_INFO *info)
{
}
