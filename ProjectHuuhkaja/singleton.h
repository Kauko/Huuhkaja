#ifndef SINGLETON_H
#define SINGLETON_H

#include <assert.h>

template <class T> class Singleton {
        static T* mInstance;
public:
        static T* instance() {
                if(!mInstance) {
                        mInstance = new T;
                }
                assert(mInstance != NULL);
                return mInstance;
        }
        static void destroy() {
                if(mInstance) {
                        delete mInstance;
                        mInstance = NULL;
                }
        }
protected:
        Singleton(){}
        virtual ~Singleton(){}
private:
        Singleton(Singleton const&);
        Singleton& operator=(Singleton const&);
};

template<class T> T* Singleton<T>::mInstance = NULL;

#endif
