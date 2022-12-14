#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
using namespace std;



// functuionazing copied code (ranord atleast) TEXT:POPBACKAUSmuuallaki kuin eachepissä JAORDER PATTERNS ELI ESIM. paljon musttaa ja valkoista peräkkäin


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
void orde(vector<string> sequ, bool swwi){
    int c = 0;
    if(swwi){
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
    }else{
        vector<string> finale;
        string temp;
        string tempi;
        string cur;
        int sequz = sequ.size();

        for(int u = 0; u < sequz; u++){
            temp = {};
            cur = sequ[u];
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

        int lenf = finale.size();
        for(int i = 0; i < (w * h); i++){
            if(i != (w * h - 1)){
                text += (finale[c] + '\n');
            }else{
                text += finale[c];
            }
            if(c < (lenf - 1)){
                c += 1;
            }else{
                c = 0;
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


void putseq(bool swi){
    // asking for order and running function with it
    string seq;
    vector<string> relseq;
    if(swi){
        cout << "Enter order of blacks(1) and whites(0) the image will be filled(for exmp. 1000110): ";
        cin >> seq;
        relseq = split(seq, false);
        if(lines(relseq.size())){
            putseq(true);
        }else{
            orde(relseq, true);
        } 
    }else{
        cout << "Enter order of rgb values (max 255) seperated by ',' (for exmp. 012233002,111123010,255001000): ";
        cin >> seq;
        relseq = split(seq, true);
        if(lines(relseq.size())){
            putseq(false);
        }else{
            orde(relseq, false);
        }
    }
}


void eachsep(bool swt){
    // randomizing for each pixel seperately
    if(swt){
        for(int d = 0; d < h; d++){
            for(int f = 0; f < w; f++){
                text += to_string(random(0,1));
                if(f != (w - 1)){
                    text += ' ';
                }else{
                    text += '\n';
                }
            }
        }
    }else{
        for(int i = 0; i < (w * h); i++){
            text += (to_string(random(0,255)) + ' ' + to_string(random(0,255)) + ' ' + to_string(random(0,255)) + '\n');
        }
    }
    text.pop_back();
}

// tells order what was used generating the image (when random order is thing is used)
void usedorder(vector<string> ord, char del){
    cout << "Used order: ";
    for(string i: ord)
        cout << i << del;
    cout << '\n';
}

void rcord(bool sw){
    // creating random order and running orde function with it
    string len;
    cout << "Enter order's length: ";
    cin >> len;  
    int rlen = stoi(len);
    if(lines(rlen)){
        rcord(sw);        
    }else if(sw){
        vector<string> rels;
        for(int y = 0; y < rlen; y++){
            rels.push_back(to_string(random(0,1)));
        }
        usedorder(rels, '\0');
        orde(rels, true);
    }else{
        vector<string> cels;
        for(int i = 0; i < rlen; i++){
            string rs = "";
            for(int h = 0; h < 3; h++){
                int ran = random(0, 255);
                string sran = "";
                for(int g = 0; g < (3 - to_string(ran).length()); g++){
                    sran += '0';
                }
                sran += to_string(ran);
                rs += sran;
            }
            cels.push_back(rs);
        }
        usedorder(cels, ' ');
        orde(cels, false);
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
            putseq(true);
        }else{
            char roor;
            cout << "Random for each pixel(0) or random order(1): ";
            cin >> roor;
            if(roor == '1'){
                rcord(true);
            }else{
                eachsep(true);
            }
        }
    }else{
        text = "P3 " + text + " 255\n";
        char csor;
        cout << "Colors in orded order(0) or randomly generated(1): ";
        cin >> csor;
        if(csor == '0'){
            putseq(false);
        }else{
            char anw;
            cout << "Random for each pixel(0) or random order(1): ";
            cin >> anw;
            if(anw == '1'){
                rcord(false);
            }else{
                eachsep(false);
            }
        }
    }
    // writing string to the file
    string fname;
    cout << "Enter file's name (without extension): ";
    cin >> fname;
    fname += ".bmp";
    ofstream file(fname);
    file << text;
    file.close();
    cout << "File saved succesfully in current directory" << endl;

    return 0;
}
