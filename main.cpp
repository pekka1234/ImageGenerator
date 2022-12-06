#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
using namespace std;


// text is the string that will be written to the file, w is image width, h is image height
string text = "P1\n";
int w = 0;
int h = 0;


// function to get either 0 or 1 randomly
int random(int min, int max){
   static bool first = true;
   if(first){  
      srand( time(NULL) );
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}


// function that is used when typing order and when order is randomly generated with lenght, function basically creates the image content when using orders
void orde(vector<string> sequ){
    int c = 0;
    for(int i = 0; i < h; i++){
        for(int x = 0; x < w; x++){
            text += sequ[c];
            if(c != (sequ.size() - 1)){
	        c += 1;
	    }else{
	        c = 0;
	    }
	    if(x != (w - 1)){
	        text += ' ';
	    }else if(i != (h - 1)){
	        text += '\n';
	    }
	}
    }    
}


// splits string by ','
vector<string> split(string str){
    vector<string> result;
    string temp = "";
    for(int i = 0; i < str.length(); i++){
        if(str[i] != ',' && i != (str.length() - 1)){
	    temp += str[i];
	    //cout << temp << endl;
	}else if(i == (str.length() - 1)){
            temp += str[i];
	    result.push_back(temp);
	}else{
            result.push_back(temp);
            temp = "";
	}
    }
    return result;
}


// asks question of the image and runs functions
int main(){
    // black and white or color, width and height
    int prev = -1;
    string bw;
    string vs;
    cout << "Black and white(0) or color picture(1): ";
    cin >> bw;
    cout << "Enter image widht and height in pixels (for exmp. 12,14): ";
    cin >> vs;
    vector<string> res = split(vs);
    w = stoi(res[0]);
    h = stoi(res[1]);
    text += (res[0] + ' ' + res[1] + '\n');

    if(bw == "0"){
        // type order ar random question
        string sor;
	string seq;
	cout << "Sequence of blacks and whites in orded order(0) or random(1): ";
	cin >> sor;

	if(sor == "0"){
            // asking for order and running function with it
	    vector<string> relseq;
            cout << "enter sequence, black = 1, white = 0 (for exmp. 1,0,0,0,1,1,0): ";
	    cin >> seq;
	    relseq = split(seq);
	    orde(relseq);
	}else{
            char roor;
	    cout << "Random for each pixel(0) or random order(1): ";
	    cin >> roor;

	    if(roor == '1'){
                // creating random order and running orde function with it
	        string len;
		cout << "Enter order length: ";
		cin >> len;
		int rlen = stoi(len);
                vector<string> rels;
		for(int y = 0; y < rlen; y++){
                    rels.push_back(to_string(random(0,1)));		    
		}
		cout << "Used sequence: ";
		for(string i: rels)
                    cout << i << ',';
		cout << '\n';
		orde(rels);
	    }else{
                // randomizing for each pixel seperately
	        for(int d = 0; d < h; d++){
		    for(int f = 0; f < w; f++){
		        text += to_string(random(0,1));
			if(f != (w - 1)){
			    text += ' ';
			}else if(d == (h - 1)){
			    text += '\n';
			}
		    }
		}
	    }
	}
    }
    // writing string to the file
    string fname;
    cout << "Enter file name: ";
    cin >> fname;
    fname += ".bpm";
    ofstream file(fname);
    file << text;
    file.close();

    return 0;
}
