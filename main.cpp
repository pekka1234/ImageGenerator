#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
using namespace std;




// used orde pilkku vikassa ongelma, pilkku onglelma sequenssisss eli helpompi on ei pilkkuja esim. 10001010100010101010111110 qr koodi

// text is the string that will be written to the file, w is image width, h is image height
string text = "P1\n";
int w = 0;
int h = 0;



bool lines(int modulo){
    if(w % modulo == 0){
        char conf;
        cout << "The order lenght is same as the image width (result image will be straight lines). Do you want to continue(0) or not(1): ";
        cin >> conf;
        if(conf == '1'){
            return true;
        }
    }
    return false;
}



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
vector<string> split(string str, bool smalbig){	
    vector<string> result;
    string temp = "";
    if(smalbig){
        for(int i = 0; i < str.length(); i++){
            if(str[i] != ',' && i != (str.length() - 1)){
	        temp += str[i];
	    }else if(i == (str.length() - 1)){
                temp += str[i];
	        result.push_back(temp);
	    }else{
                result.push_back(temp);
                temp = "";
	    }
        }
    }else{
        for(int ii = 0; ii < str.length(); ii++){
            temp += str[ii];
	    result.push_back(temp);
	    temp = "";
	}
    }
    return result;
}


void putseq(){
    // asking for order and running function with it
    string seq;
    vector<string> relseq;
    cout << "Enter order of blacks(1) and whites(0) the image will be filled(for exmp. 1000110): ";
    cin >> seq;
    relseq = split(seq, false);
    if(lines(relseq.size())){
        putseq();
    }else{
        orde(relseq);
    }	
}


void ranord(){
    // creating random order and running orde function with it
    string len;
    cout << "Enter order's length: ";
    cin >> len;
    int rlen = stoi(len);
    if(lines(rlen)){
        ranord();        
    }else{
        vector<string> rels;
        for(int y = 0; y < rlen; y++){
            rels.push_back(to_string(random(0,1)));
        }
        cout << "Used order: ";
        for(string i: rels)
            cout << i;
        cout << '\n';
        orde(rels);
    }
}



// asks question of the image and runs functions
int main(){
    // black and white or color, width and height
    int prev = -1;
    string bw;
    string vs;
    cout << "Black and white(0) or color picture(1): ";
    cin >> bw;
    cout << "Enter image's widht and height in pixels (for exmp. 12,14): ";
    cin >> vs;
    vector<string> res = split(vs, true);
    w = stoi(res[0]);
    h = stoi(res[1]);
    text += (res[0] + ' ' + res[1] + '\n');

    if(bw == "0"){
        // type order ar random question
        string sor;
	cout << "Blacks and whites in orded order(0) or randomly generated(1): ";
	cin >> sor;

	if(sor == "0"){
            putseq();
	}else{
            char roor;
	    cout << "Random for each pixel(0) or random order(1): ";
	    cin >> roor;

	    if(roor == '1'){
                ranord();
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
    cout << "Enter file's name (without extension): ";
    cin >> fname;
    fname += ".bpm";
    ofstream file(fname);
    file << text;
    file.close();

    return 0;
}
