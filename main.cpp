#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
using namespace std;






// text is the string that will be written to the file, w is image width, h is image height
string text;
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

// manual input order for color images
void corde(vector<string> cequ){
    vector<string> finale;
    string temp;
    string tempi;
    int ier = 0;
    string cur;
    int cequz = cequ.size();
    //for (string g: cequ)
    //    cout << g << ' ';
    //cout << cequz << 'g';    
    for(int u = 0; u < cequz; u++){
        temp = {};
        cur = cequ[u];
        for(int y = 0; y < 9; y++){
            if((y + 1) % 3 != 0){
                tempi += cur[y];
            }else{
                tempi += cur[y];
                temp += (to_string((stoi(tempi))) + ' ');
                tempi = "";
            }
        }
        temp.pop_back();
        finale.push_back((temp));
    }
    /*
    for(string h: finale)
        cout << h << ' ';
    */
    int lenf = finale.size();
    for(int i = 0; i < (w * h); i++){
        if(i != (w * h - 1)){
            text += (finale[ier] + '\n');
        }else{
            text += finale[ier];
        }
        if(ier < (lenf - 1)){
            ier += 1;
        }else{
            ier = 0;
        }
    }
    
}

void cutseq(){
    string ceq;
    cout << "Enter order of rgb values (max 255) seperated by ',' (for exmp. 012233002,111123010,255001000): ";
    cin >> ceq;
    vector<string> celseq = split(ceq, true);
    if(lines(celseq.size())){
        cutseq();
    }else{
        corde(celseq);
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
    text += (res[0] + ' ' + res[1]);

    if(bw == "0"){
        text = "P1\n" + text + '\n';
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
    }else{
        text = "P3 " + text + " 255\n";
        char csor;
        cout << "Colors in orded order(0) or randomly generated(1): ";
        cin >> csor;
        if(csor == '0'){
            cutseq();
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
    cout << "File saved succesfully in current directory" << endl;

    return 0;
}
