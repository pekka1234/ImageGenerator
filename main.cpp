#include<iostream>
#include<string>
#include<cstring>
#include<sstream>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<time.h>
using namespace std;


string text = "P1\n";
int w = 0;
int h = 0;


int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}



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


////////   to_string(x) int -> string solution


int main(){
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
        string sor;
	string seq;
	cout << "Sequence of blacks and whites in orded order(0) or random(1): ";
	cin >> sor;
	if(sor == "0"){
	    vector<string> relseq;
            cout << "enter sequence, black = 1, white = 0 (for exmp. 1,0,0,0,1,1,0): ";
	    cin >> seq;
	    relseq = split(seq);
	    orde(relseq);
	    //cout << text << endl;
	}else{
            char roor;
	    cout << "Random for each pixel(0) or random order(1): ";
	    cin >> roor;
	    if(roor == '1'){
	        string len;
		cout << "Enter order length: ";
		cin >> len;
		int rlen = stoi(len);
                vector<string> rels;
		for(int y = 0; y < rlen; y++){
                    rels.push_back(to_string(random(0,1)));		    
		}
		orde(rels);
	    }else{
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
    string fname;
    cout << "Enter file name: ";
    cin >> fname;
    fname += ".bpm";
    ofstream file(fname);
    file << text;
    file.close();
    return 0;
}
