#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <dir.h>
#include "split.h"
#include "data.h"
#include "load.h"
#include "whatdo.h"

using namespace std;

int mutex = 1;
database bufferdatabase;
datatable bufferuser;
int u;

int main(){

    cout <<  "welcome to my database!" << endl;

    mkdir("database");
    
    if(load() == 1){
        bufferdatabase.basesave();
        //test();
        sql();
    }

}