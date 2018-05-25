#ifndef CODEASSIST_H
#define CODEASSIST_H

#define FILE_NAME "a.mpd"

#if defined(__APPLE__)||defined(__MACH__)
    #define PATH (getPath()+FILE_NAME).c_str()
    std::string getPath();
#else
    #define PATH FILE_NAME
#endif

template<typename T>
int getIndex(const T* arr,const unsigned int arr_size,const T input){
  for(unsigned int i=0;i<arr_size;i++){
    if(arr[i]==input)return i;
  }
  return -1;
}

#endif //CODEASSIST_H
