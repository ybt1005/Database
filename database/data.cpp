using namespace std;

class database{
    private:
    string databasename;
    int length;
    vector<string>* datatablename;

    public:
    database(string name = "noname"){
        databasename = name;
        length = 0;
        datatablename = new vector<string>;
    }

    ~database(){
        delete(datatablename);
    }

    string getname(){
        return databasename;
    }

    void addtablename(string name){
        datatablename -> push_back(name);
        length ++;
    }

    void removetablename(string name){
        for(int i = 0; i < datatablename -> size() ; i ++){
            if(datatablename->at(i) == name){
                datatablename -> erase((datatablename -> begin() + i));
                length --;
                i--;
            }
            if(datatablename -> size() == 1){return;}
        }
    }

    void show(){
         cout<<"--------------database ---------------------"<<endl;
         cout<<" basename :"<<databasename<<endl;
         cout<<" Number of tables :"<<length<<endl;
         if(length == 0){
             cout << " no table!"<<endl;
         }
         else{
             cout << " table :" <<endl;
             for(int i =0 ;i < length ; i ++){
                 cout << " "<< datatablename->at(i) << endl;
             }
         }
         cout<<"--------------------------------------------"<<endl;
    }

    int basesave(){
        int i;
        string p = "D:\\My\\icode\\database\\database\\" + databasename;
        mkdir(p.c_str());
        string path = "D:\\My\\icode\\database\\database\\" + databasename + ".txt";
        ofstream in(path.c_str());
        if(in.fail()){cout << "openfile error!" <<endl;return 0;}
        in << databasename << endl << length <<endl;
        i = 0;
        while( i < datatablename->size()){
            in << datatablename->at(i) << " ";
            i++;  
        }
        in<<endl;
        in.close();
        return 1;
    }

    int baseload(string name){
        string path = "D:\\My\\icode\\database\\database\\" + name + ".txt";
        ifstream in(path.c_str());
        if(in.fail()){cout << "openfile error!" <<endl;return 0;}
        char buffer[100];
        in.getline(buffer,100) ;
        databasename = buffer;
        in.getline(buffer,100);
        length = (int)buffer[0]-'0';
        in.getline(buffer,100);
        string tmp = buffer;

        datatablename = split(' ',tmp);

        in.close();
        return 1;
    }
};

class datatable{
private:
    string datatablename;
    int rowlength;
    int length;
    string path;
    vector<vector<string>>* ve;
    vector<string>* row;
    vector<string>* rowanother;

public:
    datatable(string name = "noname")
    {
        datatablename = name;
        rowlength = 0;
        length = 0;
        path = "nopath";
        row = new vector<string>;
        ve = new vector<vector<string>>;
        rowanother = new vector<string>;
    }

    ~datatable(){
        delete(ve);
        delete(row);
    }

    void show(){
        cout<<"-------------table-----------------"<<endl;
        cout << datatablename <<":"<< endl;
        for(int i =0 ; i < row->size(); i ++){
            cout<< row->at(i)<<"  ";
        }
        cout<<endl;
        for(int i = 0 ; i < ve -> size(); i ++){
            for(int j = 0 ; j < (ve->begin()+ i )->size(); j ++){
                cout << (ve->begin()+ i ) ->at(j) <<"   ";
            }
            cout <<endl;
        }
        cout<<"-----------------------------------"<<endl;
    };

    void show(string r){
        cout<<"-------------table-----------------"<<endl;
           int n = 0;
            int m = 1;
            cout << datatablename <<":"<< endl;
            for(int i =0 ; i < row->size(); i ++){
                if(row -> at(i) == r){
                    cout<< row->at(i)<<"  ";
                    n = i;
                }
            }
            cout<<endl;
            for(int i = 0 ; i < ve -> size(); i ++){
                cout << (ve->begin()+ i ) ->at(n) <<"  ";
                m++;
                cout << endl;
            }
        cout<<"-----------------------------------"<<endl;
    };

    void show(int *arr,string r = "0"){
        cout<<"-------------table-----------------"<<endl;
        if(r == "0"){
            int m = 1;
            cout << datatablename <<":"<< endl;
        for(int i =0 ; i < row->size(); i ++){
                cout<< row->at(i)<<"  ";
            }
            cout<<endl;
            for(int i = 0 ; i < ve -> size(); i ++){
                if(i == *(arr+m) && m <= *arr){
                    for(int j = 0 ; j < (ve->begin()+ i )->size(); j ++){
                        cout << (ve->begin()+ i ) ->at(j) <<"  ";
                    }
                    m++;
                    cout << endl;
                }
            }
        }
        else{
            int n = 0;
            int m = 1;
            cout << datatablename <<":"<< endl;
            for(int i =0 ; i < row->size(); i ++){
                if(row -> at(i) == r){
                    cout<< row->at(i)<<"  ";
                    n = i;
                }
            }
            cout<<endl;
            for(int i = 0 ; i < ve -> size(); i ++){
                if(i == *(arr+m) && m <= *arr){
                    cout << (ve->begin()+ i ) ->at(n) <<"  ";
                    m++;
                    cout << endl;
                }
            }
        }
        cout<<"-----------------------------------"<<endl;
    }

    int addline(string tmp[],int i)//加行，需要元素数组和元素个数
    {
        vector<string> tmp1;
        if(i!=row->size()){
            return 0;
        }
        else{
            for(int j = 0;j < i;j++){
                tmp1.push_back(tmp[j]);
            }
            ve->push_back(tmp1);
            return 1;
        }
    };

    void addrow(string r,string r1,string r2)//加属性
    {
        row -> push_back(r);
        rowanother -> push_back(r1);
        rowanother -> push_back(r2);
    }

    void deletedata()//删全部数据
    {
        ve -> clear();
    }
    
    void deletedata(int* arr )//删行，需要seleteline返回值
    {
        int k = 0;
        for(int i = 0; i < *(arr) ; i++){
            ve -> erase(ve -> begin() +*(arr+1+i) -k);
            k++;
        }
        delete(arr);
    }

    int* selectline(string name,string what,string data){
        int* arr = new int[50];
        int num = 0;
        int j =0;
        for(int i = 0; i < row->size();i++){
            if(row->at(i) == name){
                j = i;
            }
        }
        if(what == "="){
            for(int i = 0 ;i < ve->size();i++){
                if(((ve->begin()+i)->at(j)) == data){
                    arr[num +1] = i;
                    num++;
                }
            }
        }
        else if(what == ">"){
            for(int i = 0 ;i < ve->size();i++){
                if(((ve->begin()+i)->at(j)) > data){
                    arr[num +1] = i;
                    num++;
                }
            }
        }
        else if(what == "<"){
            for(int i = 0 ;i < ve->size();i++){
                if(((ve->begin()+i)->at(j)) < data){
                    arr[num +1] = i;
                    num++;
                }
            }
        }
        else if(what == ">="){
            for(int i = 0 ;i < ve->size();i++){
                if(((ve->begin()+i)->at(j)) >= data){
                    arr[num +1] = i;
                    num++;
                }
            }
        }
        else if(what == "<="){
            for(int i = 0 ;i < ve->size();i++){
                if(((ve->begin()+i)->at(j)) <= data){
                    arr[num +1] = i;
                    num++;
                }
            }
        }
        else if(what == "<>"){
            for(int i = 0 ;i < ve->size();i++){
                if(((ve->begin()+i)->at(j)) != data){
                    arr[num +1] = i;
                    num++;
                }
            }
        }
        arr[0] = num;
        return arr;
    }

    int updatedata(string name,string data){
        int j =0;
        for(int i = 0; i < row->size();i++){
            if(row->at(i) == name){
                j = i;
            }
        }
        for(int i = 0 ;i < ve->size();i++){
            ((ve->begin()+i)->at(j)) = data;
        }
    }

    int updatedata(string name,string data,int* arr){
        int j =0;
        for(int i = 0; i < row->size();i++){
            if(row->at(i) == name){
                j = i;
            }
        }
        for(int i = 0; i < *arr ; i ++){
            ((ve -> begin() + *(arr + i + 1)) -> at(j)) = data;
        }
    }

    int save(string basename){
        int i;
        length = ve -> size();
        rowlength = row->size();
        path = "D:\\My\\icode\\database\\database\\"+basename+"\\" + datatablename + ".txt";
        ofstream in(path.c_str());
        if(in.fail()){cout << "openfile error!" <<endl;return 0;}
        in << datatablename << endl << rowlength <<endl<<length<<endl<<path<<endl;
        i = 0;
        while(rowlength){
            in << row->at(i)<<" ";
            rowlength--;
            i++;  
        }
        in<<endl;
        i = 0;
        while(i<rowanother -> size()){
            in << rowanother -> at(i)<<" ";
            i ++;  
        }
        in<<endl;
        i = 0;
        while(length){
            rowlength = row ->size();
            int k =0;
            while(rowlength){
                in << (ve->begin()+i)->at(k) << " ";
                rowlength--;
                k++;
            }
            in << endl;
            length--;
            i++;
        }

        in.close();
        return 1;
    }

    int load(string name,string basename){
        string p = "D:\\My\\icode\\database\\database\\"+basename+"\\" + name + ".txt";
        ifstream in(p.c_str());
        if(in.fail()){cout << "No table exists!" <<endl;return 0;}
        char buffer[100];

        in.getline(buffer,100) ;
        datatablename = buffer;

        in.getline(buffer,100) ;
        rowlength = (int)buffer[0]-'0';

        in.getline(buffer,100);
        length = (int)buffer[0]-'0';

        in.getline(buffer,100) ;
        path = buffer;

        in.getline(buffer,100);
        string tmp = buffer;

        row = split(' ',tmp);
        row -> pop_back();

        in.getline(buffer,100);
        rowanother = split(' ',buffer);

        int i=0;

        vector<string>* tmp1;
        tmp1 = new vector<string>;
        while(length){
            in.getline(buffer,100);
            tmp = buffer;
            tmp1 = split(' ',tmp);
            ve -> push_back(*tmp1);
            length--;
            i++;
        }

        in.close();
        delete(tmp1);

        return 1;
    }

    void deletetable(){
        if(remove(path.c_str()) == 0){
            cout << "delete success!"<<endl;
        }
        else{
            cout << "delete fail!" <<endl;
        }
    }

    int compare(string name,int pos,string data){
        int j =0;
        for(int i = 0; i < row->size();i++){
            if(row->at(i) == name){
                j = i;
            }
        }
        if((ve -> begin() + pos) -> at(j)  == data){
            return 1;
        }
        return 0;
    }
};