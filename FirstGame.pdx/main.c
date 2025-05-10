#include <pd_api.h>

#ifdef _WINDLL
__declspec(dllexport)
#endif

int update(void* ud) {
  return 1;
}

int eventHandler(PlaydateAPI *playdate, PDSystemEvent event, uint32_t arg) {
  if (event == kEventInit) {
    playdate->display->setRefreshRate(60);
    playdate->system->setUpdateCallback(update, NULL);
  }

  playdate->system->drawFPS(0, 0);

  return 0;
}
