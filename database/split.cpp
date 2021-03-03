using namespace std;

int* mergearray(int* arr,int* brr)
{
	int num = *(arr);
	int* array;
	array = new int[*(arr)+*(brr)];
	array[0] = *(arr);

	for(int i = 0; i < *(arr); i++){
		array[i+1] = *(arr+i+1);
	}
	for(int i = 0 ; i < *(brr); i++){
		int k =0;
		for(int j = 0 ; j < *(arr) ; j ++){
			if(*(brr + i + 1) == *(arr+j+1)){
				k = 1;
			}
		}
		if(k == 0){
			array[num+1] = *(brr+i+1);
			num ++;
			array[0]++;
		}
	}
	return array;
}

int* mergearray2(int* arr,int* brr)
{
	int num = 0;
	int* array;
	array = new int[*(arr)+*(brr)];
	array[0] = 0;

	if(*(brr) > *(arr)){
		int* crr;
		crr = arr;
		arr = brr;
		brr = crr;
	}

	for(int i = 0 ; i < *(brr); i++){
		int k =0;
		for(int j = 0 ; j < *(arr) ; j ++){
			if(*(brr + i + 1) == *(arr+j+1)){
				k = 1;
			}
		}
		if(k == 1){
			array[num+1] = *(brr+i+1);
			num ++;
			array[0]++;
		}
	}
	return array;
}

vector<string>* split(const char src,string str)
{
	vector<string>* tmp;
	string st;
	tmp = new vector<string>;
	for(int i =0 ;i < str.size(); i ++){
		if(str[i] != src){
			st.push_back(str[i]);
		}
		else if(str[i] == src && st != ""){
			tmp->push_back(st);
			st = "";
		}
	}
	tmp -> push_back(st);

	return tmp;
}

string replace_all(string& str, const char strold)
{
	string tmp;
	for(int i = 0 ; i < str.size(); i++){
		if(str[i] != strold){
			tmp.push_back(str[i]);
		}
		else if(str[i] == strold){
			tmp.push_back(' ');
			tmp.push_back(strold);
			tmp.push_back(' ');
		}
	}
	return tmp;
}