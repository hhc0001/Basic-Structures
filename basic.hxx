#include <new>
#include <stdexcept>

namespace vir {
  #define SIZE_T long long
  #ifndef __VVECTOR
  #define __VVECTOR 1
  template<
  class T
  >class vvector {
    public:
      SIZE_T Size, LCap;
      T* Start;

      vvector() : Size(0), LCap(0), Start(new T) {
      }
      vvector<T>(vvector<T> &x) : Size(x.Size), LCap(x.LCap), Start(new T[1 << x.LCap]) {
        for(int i = 0; i < x.Size; i++) {
          *(Start + i) = *(x.Start + i);
        }
      }

      void push_back(T x) {
        if(Size == (1 << LCap)) {
          LCap++;
          T* tmp = Start;
          Start = new T[1 << LCap];
          for(int i = 0; i < Size; i++) {
            *(Start + i) = *(tmp + i);
          }
          delete tmp;
        }
        *(Start + Size) = x;
        Size++;
      }
      void pop_back() {
        Size--;
        if(LCap && Size == (1 << LCap - 1)) {
          LCap--;
          T* tmp = Start;
          Start = new T[1 << LCap];
          for(int i = 0; i < Size; i++) {
            *(Start + i) = *(tmp + i);
          }
          delete tmp;
        }
      }
      void clear() {
        Size = 0, LCap = 0;
        T* tmp = Start;
        delete tmp;
        Start = new T;
      }
      void resize(SIZE_T x) {
        if(x >= 1000000000ll) {
          throw std::bad_array_new_length();
        }
        for(; Size > x; ) {
          pop_back();
        }
        for(; Size < x;) {
          push_back(T()); // 原本这里有一个 UB，现在修复了，没有 UB 了
        }
      }

      SIZE_T size() {
        return Size;
      }
      bool empty() {
        return !Size;
      }
      SIZE_T capacity() {
        return (1ll << LCap);
      }

      T& at(SIZE_T x) {
        if(x >= Size) {
          throw std::out_of_range("It's same as normal vector.");
        }
        return *(Start + x);
      }
      T& operator [](SIZE_T x) {
        return *(Start + x); // 如果 x >= Size，这就会是 UB（旧的种类或是新的种类得看 LCap）
      }
      T& front() {
        return at(0);
      }
      T& back() {
        return at(Size - 1);
      }
      vvector<T>& operator =(vvector<T> b) {
        Size = (b.Size), LCap = (b.LCap), Start = (new T[1 << b.LCap]);
        for(int i = 0; i < b.Size; i++) {
          *(Start + i) = *(b.Start + i);
        }
        return *this;
      }
  };
  #endif

  // 这里有一个位子留给 deque
}
