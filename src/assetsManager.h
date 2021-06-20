#pragma once
#include <unordered_map>

namespace AssetsManager {
  namespace Private{
    void loadingDone(const char* name, const int type);
  }
  extern std::unordered_map<std::string, const char*> picutres;
  extern std::unordered_map<std::string, const char*> audios;
  extern int loadedItems;
  extern void(*func)();
  void loadPicture(const char* name, const char* location, void(*callback)());
  void loadAudio(const char* name, const char* location);
};
