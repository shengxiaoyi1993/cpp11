#include<iostream>

using namespace std;

class Base

{

public:

    Base(int){}

    virtual ~Base(void){}
    int getIBase() const{}

    static int instanceCount(){}

    virtual void print() const{}
    virtual void write() const{}



protected:


    int iBase;

    static int count;

};

