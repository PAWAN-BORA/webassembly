#include  "assetsManager.h"
#include <iostream>
#include <emscripten.h>

std::unordered_map<std::string, const char*> AssetsManager::picutres;
std::unordered_map<std::string, const char*> AssetsManager::audios;
int AssetsManager::loadedItems = 0;
void(*AssetsManager::func)();
void AssetsManager::Private::loadingDone(const char* name, const int type) {
    if(type==0) {
        picutres.insert({name, name});
    } else if(type==1){
        audios.insert({name, name});
    }
    // std::cout << "loaded img "<< name << std::endl;
    // std::cout << type << std::endl;
    loadedItems++;
    func();
    
}
void AssetsManager::loadPicture(const char* name, const char* location, void(*callback)()) {
    func = callback;
    EM_ASM({
    let image = new Image();
    image.onload = ()=>{
        let name = UTF8ToString($0);
        pictures[name] = image;
        wasmTable.get($2)($0, 0);
    };
    image.onerror = (err)=>{
        console.log(UTF8ToString($0));
        console.log("first=======");
        console.log(UTF8ToString($1));
        console.log("second======");
        console.log(err);
    };
    image.src = UTF8ToString($1);
    }, name, location, Private::loadingDone);
}
void AssetsManager::loadAudio(const char* name, const char* location) {

}