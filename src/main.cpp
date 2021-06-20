// #include <SDL/SDL.h>

// #ifdef __EMSCRIPTEN__
#include <iostream>
#include <emscripten.h>
#include <unordered_map>
#include "canvas.h"
#include "window.h"
#include "assetsManager.h"
#include <vector>
#include "./input/mouseManager.h"
#include "./ui/uiButton.h"
// #include "string"
// #include <html5.h>
// #include <SDL2/SDL.h>
// #endif

// EM_JS(void, call_alert, ());
// EMSCRIPTEN_KEEPALIVE

void getNumDigits(unsigned int& num, std::vector<int>& nums) {
  if(num<10){
      nums.push_back(num);
      return;
  }
  int lastChar = num%10;
  nums.push_back(lastChar);
  unsigned int remainingChars = (num - lastChar)/10;
  if(remainingChars>=10) {
      getNumDigits(remainingChars, nums);
  } else {
      nums.push_back(remainingChars);
  }
}

const char* concateStr(const char* str, unsigned int& num){
    const char values[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::vector<int> nums;
    getNumDigits(num, nums);
    int length = strlen(str);
    char* newStr = new char[length+nums.size()];
    memcpy(newStr, str, length);
    for(int i=nums.size()-1; i>=0; i--){
        newStr[length+nums.size()-1-i] = values[nums[i]];
    }
    newStr[length+nums.size()]= '\0';
    return newStr;
}
const char* concateStr(const char* str, const char* str2){
  int length1 = strlen(str);
  int length2 = strlen(str2);
  char* newStr = new char[length1+length2];
  // memcpy(newStr, str, length1);
  for(int i=0; i<length1; i++){
      newStr[i] = str[i];
  }
  for(int i=0; i<length2; i++){
      newStr[length1+i] = str2[i];
  }
  newStr[length1+length2]= '\0';
  return newStr;
}






static Canvas canvas = Canvas("canvas");
static float x = 0, y = 0;
static int incX = 1, incY =1;
static unsigned int imgNum = 1;
static UiButton button = UiButton(101.5, 106.4, 80, 25); 
void draw(){
  
  canvas.clearRect(0, 0, 1366, 768);
  canvas.drawImage(AssetsManager::picutres.find("pawan")->second, 100, 50);
  canvas.save();
  canvas.fillStyle("red");
  canvas.fillRect(x, y, 200, 200);
  canvas.restore();
  canvas.save();
  canvas.drawImage(AssetsManager::picutres.find(concateStr("img", imgNum))->second, x, y, 200, 200);
  canvas.restore();
  button.update();
  button.render(&canvas);
  x += incX;
  y += incY;
  if(x>1366 || x<0){
    incX *= -1; 
  }
  if(y>768 || y<0){
    incY *= -1; 
  }
  imgNum++;
  if(imgNum==4){
    imgNum = 1;
  }
}


void loop() {
   draw();
}

void resize() {
  std::cout << "window resize\n";
}

int totalItems = 5;
void res() {
  std::cout << "callback" << std::endl;
  std::cout << AssetsManager::loadedItems << std::endl;
  if(AssetsManager::loadedItems==totalItems){
    Window window;
    window.requestAnimationFrame(loop);
    // draw();
  }
}
void getValPtr(const int* val){
  std::cout << val << std::endl;
   std::cout << &val << std::endl;
}

std::unordered_map<std::string, const char*> unmap;
extern "C" {
  // EMSCRIPTEN_KEEPALIVE
  // void getValRef(const int& val){
  //   std::cout << val << std::endl;
  //   std::cout << &val << std::endl;
  // }
  
  // EMSCRIPTEN_KEEPALIVE
  // void getVal(const int val){
  //   std::cout << val << std::endl;
  //   std::cout << &val << std::endl;
  // }


  // EMSCRIPTEN_KEEPALIVE
  // void getStrVal(const char* val){
  //   const char* newVal = val;
  //   std::cout << newVal << std::endl;
  //   if(strcmp(val, "pawan")==0){
  //     std::cout << "matched!" << std::endl;  
  //   } else {
  //     std::cout << "not matched!" << std::endl;  
  //   }
  //   unmap.insert({val, val});
  //   std::cout << val << std::endl;
  //   std::cout << &val << std::endl;
  //   std::cout << unmap.find(val)->first << " " << unmap.find(val)->second << std::endl;
  //   std::cout << unmap.find("pawan")->first << " " << unmap.find("pawan")->second << std::endl;
  // }
  EMSCRIPTEN_KEEPALIVE
  const char* GetString(const char* string, int& num){
    const char values[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int length = strlen(string);
    char* newStr = new char[length+1];
    memcpy(newStr, string, length+1);
    newStr[length] = values[num];
    // newStr[size+1] ='\0';
    // delete[] string;
    return newStr;
  }
}

void loadAssets() {
  AssetsManager::loadPicture("pawan", "../assets/pawan.jpg", res);
  for(int i=0; i<4; i++){
    unsigned int num = i+1;
    const char* name = concateStr("img", num);
    const char* locationHalf = concateStr("../assets/", num);
    const char* location = concateStr(locationHalf, ".png");
    AssetsManager::loadPicture(name, location, res);
    delete[] locationHalf;
    // delete[] location;
    // delete[] name;
  }

}

void mouseDown() {
  std::cout << "mouse down" << std::endl;
}
int main() {

  // const std::map<const char*, const char*>::iterator iter  = AssetsManager::picutres.find("pawan");
  // const char* img = AssetsManager::picutres.find("pawan")->second;
  std::vector<int> numbers;
  std::cout << numbers.size() << std::endl;
  MouseManager::initialize();
  MouseManager::addObject(&button);
  loadAssets();

  


  // const char* name = "pawan";
  // const char* name2 = "pawan";
  // if(name==name2){
  //   std::cout<< "matched! names" << std::endl;
  // } else {
  //   std::cout<< "dose not matched! names" << std::endl;
  // }

  // if(name=="pawan"){
  //   std::cout<< "matched! name1" << std::endl;
  // } else {
  //   std::cout<< "dose not matched! name1" << std::endl;
  // }

  // if(name2=="pawan"){
  //   std::cout<< "matched! name2" << std::endl;
  // } else {
  //   std::cout<< "dose not matched! name2" << std::endl;
  // }
  // std::cout<< &name << std::endl;
  // std::cout<< *name << std::endl;
  // std::cout<< &name2 << std::endl;
  // std::cout<< *name2 << std::endl;

  // // window.onResize(resize);
  // // emscripten_request_animation_frame_loop(loop, 0);
  // int q = 5;
  // int* p = &q;

  // std::cout<< "======================" << std::endl;
  // std::cout<< p << std::endl;
  // std::cout<< &p << std::endl;
  // std::cout<< *p << std::endl;
  // std::cout<< "q======================q" << std::endl;
  // std::cout<< q << std::endl;
  // std::cout<< &q << std::endl;
  // std::cout << "pass by prt" << std::endl;
  // getValPtr(&p);
  // std::cout << "pass by ref" << std::endl;
  // getValRef(p);
  // std::cout << "pass by val" << std::endl;
  // getVal(p);
 
  // requestAnimationFrame(loop);
  // draw(canvas);
  // delete canvas ;
  return 0;
}







#ifdef __cplusplus
extern "C" {
#endif


int int_sqrt(int x) {
  return 5;
}

// EMSCRIPTEN_KEEPALIVE
int add(int x, int y){
  return 5;
}

//EMSCRIPTEN_KEEPALIVE 
const char* getString() {
  return "dfsdf";
}


#ifdef __cplusplus
}
#endif