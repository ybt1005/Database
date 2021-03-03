using namespace std;

extern datatable bufferuser;
extern int u;

int load(){
    mkdir("D:\\My\\icode\\database\\database\\user");
    if(bufferuser.load("user","user") == 0){
        datatable user("user");
        user.addrow("id","char","10");
        user.addrow("password","char","10");
        user.addrow("create","char","10");
        user.addrow("drop","char","10");
        user.addrow("select","char","10");
        user.addrow("delete","char","10");
        user.addrow("insert","char","10");
        user.addrow("update","char","10");
        user.addrow("help","char","10");
        user.addrow("use","char","10");
        user.addrow("delete","char","10");
        user.addrow("add","char","10");        
        string tmp[12] = {"root","root","1","1","1","1","1","1","1","1","1","1"};
        user.addline(tmp,12);
        user.save("user");
    }
    while(1){
        string name,p;
        cout << "Log in" <<endl;
        cout << "username:";
        cin >> name;
        if(*(bufferuser.selectline("id","=",name)) == 1){
            int k = *(bufferuser.selectline("id","=",name) + 1);
            cout << "password:" ;
            cin >> p;
            if(bufferuser.compare("password",k,p) == 1){
                u = k;
                cout << "hello " << name << "!"<<endl;
                return 1;
            }
            else{
                cout << "password error!" << endl;
            }
        }
        else{
            cout <<"user doesn't exist!" <<endl;
        }
    }
}