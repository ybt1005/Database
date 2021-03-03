using namespace std;

extern int mutex;
extern int u;
extern database bufferdatabase;
extern datatable bufferuser;

int create();
int drop();
int select();
int delete1();
int insert();
int update();
int help();
int use();
int add();


void test(){
    while(1){
        string command;
        cin >> command;
        if(command == "1")
            {
            datatable dt("207");
            dt.addrow("name","char","10");
            dt.addrow("id","int","10");
            dt.addrow("age","int","10");
            string tmp[3] = {"ybt","123","20"};
            dt.addline(tmp,3);
            string tmp1[3] = {"sk","124","21"};
            dt.addline(tmp1,3);
            string tmp11[3] = {"shm","125","22"};
            dt.addline(tmp11,3);
            string tmp111[3] = {"sjx","126","23"};
            dt.addline(tmp111,3);
            string tmp1111[3] = {"xhr","127","20"};
            dt.addline(tmp1111,3);
            string tmp11111[3] = {"wcl","128","20"};
            dt.addline(tmp11111,3);

            //bufferdatabase.baseload("database");
            //bufferdatabase.show();

            //dt.deletedata(dt.selectline("age","=","20"));
            //dt.show();

            dt.updatedata("age","27",dt.selectline("name","=","sk"));
            dt.show();

            /*int *t = dt.selectline("age","=","20");
            dt.show(t,"id");
            delete t;*/

            //dt.save(bufferdatabase.getname());

            //datatable d;
            //d.load("207",bufferdatabase.getname());
            //d.show();
            }
    }
    /*string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    cout << command;*/
    
}

void sql(){
    while(1){
        string command;
        cin >> command;
        transform(command.begin(), command.end(),command.begin(), ::tolower);
        if(command == "create" ){
            create();
        }
        else if(command == "drop"){
            drop();
        }
        else if(command == "select"){
            select();
        }
        else if(command == "delete"){
            delete1();
        }
        else if(command == "insert"){
            insert();
        }
        else if(command == "update"){
            update();
        }
        else if(command == "help"){
            help();
        }
        else if(command == "using"){
            use();
        }
        else if(command == "use"){
            use();
        }
        else if(command == "add"){
            add();
        }
        else if(command == "exit"){

        }
        else if(mutex == 1){
            cout << "please enter the database!" <<endl;
        }
        else{
            cout << "Missing keywords!"<<endl;
        }
        //cout<<"--------------------------------------------"<<endl;
        
    }
}

int create(){
    int i = 0;
    string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    command = replace_all(command, ',' );
    command = replace_all(command, ';' );
    command = replace_all(command, '*' );

    vector<string>* tmp = split(' ',command);

    if(bufferuser.compare("create",u,"1") == 0){
        cout << "The account has no power"  << endl;
        return 0;
    }
    if(mutex == 1){
        cout << "please enter the database!" <<endl;
        return 0;
    }

    //vector<string>* tmp = split(' ',command);

    /*for(int k = 0 ; k < tmp->size() ;k++){
        cout << tmp->at(k)<<" ";
    }
    cout<<endl;*/

    if(tmp -> at(0) == "table"){
        /*******************************************************/
        datatable d;
        if(d.load(tmp -> at(1),bufferdatabase.getname()) == 1){cout << "The table has existed!"<<endl;return 0;}
        /*******************************************************/
        datatable dt(tmp->at(1));
        while(tmp->at(i) != ";"){
            if(tmp->at(i) == "("){
                dt.addrow(tmp->at(i+1),tmp -> at(i+2), tmp -> at(i+3));
            }
            else if(tmp->at(i) == ","){
                dt.addrow(tmp->at(i+1),tmp -> at(i+2), tmp -> at(i+3));
            }
            i++;
            /*******************error correction********************/
            if(i > tmp -> size()){
                cout << "Missing ';'" <<endl;
                return 0;
            }
            /*******************************************************/
        }
        bufferdatabase.addtablename(tmp->at(1));
        bufferdatabase.basesave();
        dt.save(bufferdatabase.getname());
        delete(tmp);
        dt.show();
        string name = bufferdatabase.getname();
        if(bufferdatabase.baseload(name) == 0){return 0;}
        bufferdatabase.show();
    }
    else if(tmp -> at(0) == "view"){
        
    }
    else if(tmp -> at(0) == "index"){

    }
    else if(tmp -> at(0) == "database"){
        database db(tmp->at(1));
        db.basesave();
    }
    /*******************error correction********************/
    else{
        cout << "What type do you want to create？" <<endl;
        return 0;
    }
    /*******************************************************/
    return 1;
}

int select(){
    string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    command = replace_all(command, ',' );
    command = replace_all(command, ';' );
    command = replace_all(command, '*' );

    vector<string>* tmp = split(' ',command);

    if(bufferuser.compare("select",u,"1") == 0){
        cout << "The account has no power"  << endl;
        return 0;
    }
    if(mutex == 1){
        cout << "please enter the database!" <<endl;
        return 0;
    }

    if(tmp -> at(0) == "*"){
        datatable dt;
        if(dt.load(tmp -> at(2),bufferdatabase.getname()) == 0){return 0;};
        /*******************error correction********************/
        if(tmp -> at(1) != "from"){
            cout << "Missing keyword 'from'" <<endl;
            return 0;
        }
        /*******************************************************/
        int* arr = 0;
        int* brr = 0;
        int* crr = 0;
        int m = 2;
        while(tmp -> at(m) != ";"){
            if(tmp -> at(m) == "where"){
                arr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "and"){
                brr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "or"){
                crr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "between"){
                arr = dt.selectline(tmp -> at(m-1),">=",tmp -> at(m+1));
                brr = dt.selectline(tmp -> at(m-1),"<=",tmp -> at(m+3));
                break;             
            }
            m++;
            /*******************error correction********************/
            if(m > tmp -> size()){
                cout << "Missing ';'" <<endl;
                return 0;
            }
            /*******************************************************/
        }
        if(arr == 0 && brr == 0 && crr ==0){
            dt.show();
        }
        else if(brr == 0 && crr ==0){
            dt.show(arr);
        }
        else if(crr == 0){
            arr = mergearray2(arr,brr);
            dt.show(arr);
        }
        else if(brr == 0){
            arr = mergearray(arr,crr);
            dt.show(arr);
        }
        /*******************error correction********************/
        else{
            cout << "Format error" <<endl;
            return 0;
        }
        /*******************************************************/
    }
    else{
        string r = tmp -> at(0);
        datatable dt;
        if(dt.load(tmp -> at(2),bufferdatabase.getname()) == 0){return 0;}
        int* arr = 0;
        int* brr = 0;
        int* crr = 0;
        int m = 2;
        while(tmp -> at(m) != ";"){
            if(tmp -> at(m) == "where"){
                arr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "and"){
                brr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "or"){
                crr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "between"){
                arr = dt.selectline(tmp -> at(m-1),">=",tmp -> at(m+1));
                brr = dt.selectline(tmp -> at(m-1),"<=",tmp -> at(m+3));
                break;                
            }
            m++;
            /*******************error correction********************/
            if(m > tmp -> size()){
                cout << "Missing ';'" <<endl;
                return 0;
            }
            /*******************************************************/
        }
        if(arr == 0 && brr == 0 && crr ==0){
            dt.show(r);
        }
        else if(brr == 0 && crr ==0){
            dt.show(arr,r);
        }
        else if(crr == 0){
            arr = mergearray2(arr,brr);
            dt.show(arr,r);
        }
        else if(brr == 0){
            arr = mergearray(arr,crr);
            dt.show(arr,r);
        }
        /*******************error correction********************/
        else{
            cout << "Format error" <<endl;
            return 0;
        }
        /*******************************************************/
    }
}

int insert(){
    int i = 0;
    string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    command = replace_all(command, ',' );
    command = replace_all(command, ';' );

    vector<string>* tmp = split(' ',command);

    if(bufferuser.compare("insert",u,"1") == 0){
        cout << "The account has no power"  << endl;
        return 0;
    }
    if(mutex == 1){
        cout << "please enter the database!" <<endl;
        return 0;
    }

    datatable dt;

    /*******************error correction********************/
    if(tmp -> at(0) != "into"){
        cout << "Missing keyword 'into'" <<endl;
        return 0;
    }
    if(tmp -> at(2) != "values"){
        cout << "Missing keyword 'values'" <<endl;
        return 0;
    }
    /*******************************************************/

    while(tmp->at(i) != ";"){
        if(tmp->at(i) == "into"){
            if(dt.load(tmp->at(i+1),bufferdatabase.getname()) == 0){return 0;}
        }
        else if(tmp->at(i) == "values"){
            string* t = new string[tmp->size()-i-5];

            for(int k =0; k < (tmp->size()-5-i);k++){
                *(t+k) = tmp->at(i+2+k);
            }
            dt.addline(t,tmp->size()-i-5);
            delete(t);
        }
        i++;
        /*******************error correction********************/
        if(i > tmp -> size()){
            cout << "Missing ';'" <<endl;
            return 0;
        }
        /*******************************************************/
    }
    dt.show();
    dt.save(bufferdatabase.getname());
    delete(tmp);
}

int help(){
    string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    command = replace_all(command, ',' );
    command = replace_all(command, ';' );

    vector<string>* tmp = split(' ',command);
    
    if(bufferuser.compare("help",u,"1") == 0){
        cout << "The account has no power"  << endl;
        return 0;
    }

    int m = 0;
    while(tmp -> at(m) != ";"){
        if(tmp -> at(m) == "table"){
            if(mutex <= 0){
                datatable dt;
                if(dt.load(tmp -> at(m+1),bufferdatabase.getname()) == 0){return 0;}
                dt.show();
            }
            else{
                cout <<"please enter database!"<<endl;
            }
        }
        else if(tmp -> at(m) == "database"){
            bufferdatabase.baseload(tmp -> at(m));
            bufferdatabase.show();
        }
        m++;
        /*******************error correction********************/
        if(m > tmp -> size()){
            cout << "Missing ';'" <<endl;
            return 0;
        }
        /*******************************************************/
    }
}

int use(){
    string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    command = replace_all(command, ',' );
    command = replace_all(command, ';' );

    vector<string>* tmp = split(' ',command);

    if(bufferuser.compare("use",u,"1") == 0){
        cout << "The account has no power"  << endl;
        return 0;
    }

    if(bufferdatabase.baseload(tmp -> at(0)) == 0){return 0;}
    bufferdatabase.show();
    delete(tmp);
    mutex--;
    return 1;
}

int drop(){
    string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    command = replace_all(command, ',' );
    command = replace_all(command, ';' );

    vector<string>* tmp = split(' ',command);

    if(bufferuser.compare("drop",u,"1") == 0){
        cout << "The account has no power"  << endl;
        return 0;
    }

    if(tmp -> at(0) == "table"){
        datatable dt;
        if(dt.load(tmp->at(1),bufferdatabase.getname()) == 0) return 0;
        dt.deletetable();
        bufferdatabase.removetablename(tmp -> at(1));
        bufferdatabase.basesave();
    }
}

int delete1(){
    string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    command = replace_all(command, ',' );
    command = replace_all(command, ';' );

    vector<string>* tmp = split(' ',command);

    if(bufferuser.compare("delete",u,"1") == 0){
        cout << "The account has no power"  << endl;
        return 0;
    }
    if(mutex == 1){
        cout << "please enter the database!" <<endl;
        return 0;
    }

    if( tmp -> at(0) == "from"){
        datatable dt;
        if(dt.load( tmp -> at(1),bufferdatabase.getname()) == 0){return 0;}
        int* arr = 0;
        int* brr = 0;
        int* crr = 0;
        int m = 2;
        while(tmp -> at(m) != ";"){
            if(tmp -> at(m) == "where"){
                arr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "and"){
                brr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "or"){
                crr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "between"){
                arr = dt.selectline(tmp -> at(m-1),">=",tmp -> at(m+1));
                brr = dt.selectline(tmp -> at(m-1),"<=",tmp -> at(m+3));
                break;             
            }
            m++;
            /*******************error correction********************/
            if(m > tmp -> size()){
                cout << "Missing ';'" <<endl;
                return 0;
            }
            /*******************************************************/
        }
        if(arr == 0 && brr == 0 && crr ==0){
            dt.deletedata();
            dt.show();
        }
        else if(brr == 0 && crr ==0){
            dt.deletedata(arr);
            dt.show();
        }
        else if(crr == 0){
            arr = mergearray2(arr,brr);
            dt.deletedata(arr);
            dt.show();
        }
        else if(brr == 0){
            arr = mergearray(arr,crr);
            dt.deletedata(arr);
            dt.show();
        }
        /*******************error correction********************/
        else{
            cout << "Format error" <<endl;
            return 0;
        }
        /*******************************************************/
        dt.save(bufferdatabase.getname());
    }
    /*******************error correction********************/
    else{
        cout << "Missing 'from'" <<endl;
        return 0;
    }
    /*******************************************************/
}

int update(){
    string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    command = replace_all(command, ',' );
    command = replace_all(command, ';' );

    vector<string>* tmp = split(' ',command);

    if(bufferuser.compare("update",u,"1") == 0){
        cout << "The account has no power"  << endl;
        return 0;
    }
    if(mutex == 1){
        cout << "please enter the database!" <<endl;
        return 0;
    }

    string a,b;
    datatable dt;
    if(dt.load(tmp -> at(0),bufferdatabase.getname()) == 0){return 0;}
    if(tmp -> at(1) == "set"){
        a = tmp -> at(2);
        b = tmp -> at(4);
        int* arr = 0;
        int* brr = 0;
        int* crr = 0;
        int m = 5;
        while(tmp -> at(m) != ";"){
            if(tmp -> at(m) == "where"){
                arr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "and"){
                brr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "or"){
                crr = dt.selectline(tmp->at(m+1),tmp -> at(m+2),tmp -> at(m+3));
            }
            else if(tmp -> at(m) == "between"){
                arr = dt.selectline(tmp -> at(m-1),">=",tmp -> at(m+1));
                brr = dt.selectline(tmp -> at(m-1),"<=",tmp -> at(m+3));
                break;             
            }
            m++;
            /*******************error correction********************/
            if(m > tmp -> size()){
                cout << "Missing ';'" <<endl;
                return 0;
            }
            /*******************************************************/
        }
        if(arr == 0 && brr == 0 && crr ==0){
            dt.updatedata(a,b);
            dt.show();
        }
        else if(brr == 0 && crr ==0){
            dt.updatedata(a,b,arr);
            dt.show();
        }
        else if(crr == 0){
            arr = mergearray2(arr,brr);
            dt.updatedata(a,b,arr);
            dt.show();
        }
        else if(brr == 0){
            arr = mergearray(arr,crr);
            dt.updatedata(a,b,arr);
            dt.show();
        }
        /*******************error correction********************/
        else{
            cout << "Format error" <<endl;
            return 0;
        }
        /*******************************************************/
        dt.save(bufferdatabase.getname());
    }
    /*******************error correction********************/
    else{
        cout << "Missing 'set'" <<endl;
        return 0;
    }
    /*******************************************************/
    return 1;
}

int add(){
    int i = 0;
    string command;
    getline(cin,command);
    transform(command.begin(), command.end(),command.begin(), ::tolower);
    command = replace_all(command,'(' );
    command = replace_all(command, ')' );
    command = replace_all(command, ',' );
    command = replace_all(command, ';' );

    vector<string>* tmp = split(' ',command);

    if(tmp -> at(0) == "user" && bufferuser.compare("add",u,"1")){
        string name = tmp -> at(1);
        if(*bufferuser.selectline("id","=",name) == 1){cout << "The user has existed!" << endl;return 0;}
        if(tmp -> at(2) == "by" ){
            string password = tmp -> at(3);
            string tmp1[12] = {name,password,"0","0","1","0","0","0","1","1","0","0"};
            bufferuser.addline(tmp1,12);
            bufferuser.save("user");
        }
    }
    else{
        cout << "The account has no power"  << endl;
    }
}
