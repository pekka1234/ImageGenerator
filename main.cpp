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


// function that checks if image widht is divisible by order lenght (if so, the image will be line in a bar code style)
bool lines(int modulo){
    if(w % modulo == 0){
        // informing program user about it adn asking if the user wants to continue and returting either true ofŕ false based on that
        char conf;
        cout << "The order lenght is same as the image width (result image will be straight lines). Do you want to continue(0) or not(1): ";
        cin >> conf;
        if(conf == '1'){
            return true;
        }
    }
    return false;
}



// function to get random value between min and max (black & white uses it to generate random value between 0 and 1. color images use it to range between 0 and 255 (rgb)
int random(int min, int max){
   // uses variable first and srand and time to generate random values
   static bool first = true;
   if(first){  
      srand(time(NULL));
      first = false;
   }
   return min + rand() % ((max + 1) - min);
}


// function that is used when typing order and when order is randomly generated with lenght, function basically creates the image content when using orders and it is the most important function in this program since 90% of tge time orders are used when running this script adn this is the final most important step in the .bmp file content creation. and it is important to note that if you want to understand this function, you will need to also understand the bitmap image file format.
void orde(vector<string> order, bool bwc){
    // int c is just used to count that which point of the order are we going
    int c = 0;
    // bwc true (for black & white images)
    if(bwc){
        // for loops goes trough height and width
        for(int i = 0; i < h; i++){
            for(int x = 0; x < w; x++){
                // adds right object order to the text (file content)
                text += order[c];
                // checks if all of order has been added, then it will start again
                if(c != (order.size() - 1)){
                    c += 1;
                }else{
                    c = 0;
                }
                // adds spacebars and newlines when needed to the text (file content)
                if(x != (w - 1)){
                    text += ' ';
                }else{
                    text += '\n';
                }
            }
        }
        // above code always add newline to end of one pixel line of the image, but the last one is useless because after that no new pixel line comes (could also cause trouble to the bitmap file reader) so ot removes last char of the str
        text.pop_back();    
    // bwc false (for color images)
    }else{ 
        // finale is list that has the strings that the file should be filled. current is the current object of the order that is processed. orderlen is the lenght of the order
        // temp contains single chars of one rgb value string and bigtemp is the string that temps get added to and at the end bigtemp conatsins one color in rgb values adn it is pushed to finale
        vector<string> finale;
        string bigtemp;
        string temp;
        string current;
        int orderlen = order.size();
        // code down below takes the order and removes leading zeroes from it and makes one rgb color in to a single string that is pushed to finale
        // note: for loop down below is done because bitmap color image file format will not take leading zeroes in front of numbers
        for(int u = 0; u < orderlen; u++){
            bigtemp = {};
            current = order[u];
            for(int y = 0; y < 9; y++){
                // divisibility by three is used becouse one rgb value is three digits long (if leading zeors are counted)
                if((y + 1) % 3 != 0){
                    // if not divisible by three, temp gets added another char of the current string from the order
                    temp += current[y];
                }else{
                    // if it is divisible by three, that means that ine rgb value of the current color is complete in temp, so it gets added to bigtemp (and alose space bar to seperate the values)
                    temp += current[y];
                    bigtemp += (to_string((stoi(temp))) + ' ');
                    // temp is set so noting becouse it will be a new rgb value soon
                    temp = "";
                }
            }
            // after bigtemp is complete, the last spacebar will be removed becouse it is not needed beocuse no value comes after it
            bigtemp.pop_back();
            // now the one color is added to finale in bitmap readable format
            finale.push_back((bigtemp));
        }
        // code down below adds finales objects to the text (file content variable)
        int lenf = finale.size();
        // for loop will be done widht * height times because that is how many pixels will be in the image
        // int c is used to know the number of the object/element of finale that is added to text (global variable that contains the file content)
        for(int i = 0; i < (w * h); i++){
            text += (finale[c] + '\n');
            if(c < (lenf - 1)){
                c += 1;
            }else{
                c = 0;
            }
        }
        // last char of text will be removed becouse it is a newline that is not needed
        text.pop_back();
    }
}

// splits string to vector<strings>
vector<string> split(string str, bool notcom){	
    // result is the final result that will be returned, temp is one object of result that will be push_backed to it (temp is set to a new value many times)
    vector<string> result;
    string temp = "";
    // notcom means that is the seperator nothing or comma (comma for color images, nothing black & white)
    if(notcom){
        // for loop goes trough the string and if it detects a comma, it adds the current temp to result, if not, then it adds the char to temp
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
        // for black & white images it just goes trought the string and adds every char to the vector<string>
        for(int i = 0; i < str.length(); i++){
            temp += str[i];
	        result.push_back(temp);
	        temp = "";
	    }
    }

    return result;
}

// asking to manually type order and sending it to orde
void putseq(bool bwc){
    string strmanord;
    vector<string> vecmanord;
    // if bwc (black & white or color is true (meaning black & white)) then code down below will run
    if(bwc){
        // asking for the order
        cout << "Enter order of blacks(1) and whites(0) the image will be filled(for exmp. 1000110): ";
        cin >> strmanord;
        // splitting strmanord string and setting vecmanord equal to it
        vecmanord = split(strmanord, false);
        // checking if order lenght is divisible by image widht witl lines function (if it is the image will be just lines in a bar code style) and if so, then this function will just run again, otherwise vecmanord will be sent to orde
        if(lines(vecmanord.size())){
            putseq(true);
        }else{
            orde(vecmanord, true);
        } 
    // bwc false, so color image operation is done instead of black & white
    }else{
        // doing the same thing as above but just with diferent question and diferent arguments (those arguments say that this is about color image) to the functions that will be run
        cout << "Enter order of rgb values (max 255) seperated by ',' (for exmp. 012233002,111123010,255001000): ";
        cin >> strmanord;
        vecmanord = split(strmanord, true);
        if(lines(vecmanord.size())){
            putseq(false);
        }else{
            orde(vecmanord, false);
        }
    }
}

// randomizing black / white or color for each pixel seperately
void eachsep(bool bwc){
    // if bwc is true (meaning black & white image), code down below will run
    if(bwc){
        // for loop goes trough height and inside that for loop goes trough width 
        for(int d = 0; d < h; d++){
            for(int f = 0; f < w; f++){
                // randomizing if 0 (white) or 1 (black) is selected to the pixel
                text += to_string(random(0,1));
                // adding spaces and newlines to seperate pixels and pixel rows
                if(f != (w - 1)){
                    text += ' ';
                }else{
                    text += '\n';
                }
            }
        }
    // for colors images code down below is run
    }else{
        // for loop goes trough width * height becouse it is the amount of pixels in the image
        for(int i = 0; i < (w * h); i++){
            // three random rgb values are added to the text (global variable for file content)
            text += (to_string(random(0,255)) + ' ' + to_string(random(0,255)) + ' ' + to_string(random(0,255)) + '\n');
        }
    }
    // removing last char becouse it is newline that is not needed
    text.pop_back();
}

// tells order what was used generating the image (when random order by lenght is used)
void usedorder(vector<string> ord, char del){
    // black & white images use delimeter '\0' (nothing) and color images use ' ' (space bar)
    cout << "Used order: ";
    for(string i: ord)
        cout << i << del;
    cout << '\n';
}

// creates a random order and send it to orde (function)
void ranord(bool bwc){
    // asking for the order's length
    string len;
    cout << "Enter order's length: ";
    cin >> len;  
    int intlen = stoi(len);
    vector<string> order;
    // checking if order's length is divisible by image width trough lines function (the image will be basically just lines in a bar code style if the length is divisible by the width)
    if(lines(intlen)){
        // if so, this function will just run again
        ranord(bwc);   
    // if bwc is true it means that black & white option will be used        
    }else if(bwc){
        // putting randomly either "0" or "1" to order list until it's length is reached
        for(int y = 0; y < intlen; y++){
            order.push_back(to_string(random(0,1)));
        }
        usedorder(order, '\0');
        // sending randomly generated order to orde with true argument meaning black & white mode
        orde(order, true);
    // bwc false means color image
    }else{
        // filling order list but now it is filled with random strings like 100020255 and so on (that is rgb color code Note: leading zeroes are to number smaller than 100)
        for(int i = 0; i < intlen; i++){
            string onestr = "";
            for(int h = 0; h < 3; h++){
                int ran = random(0, 255);
                string onerbg = "";
                // adding leading zeros
                for(int g = 0; g < (3 - to_string(ran).length()); g++){
                    onerbg += '0';
                }
                onerbg += to_string(ran);
                // adding one rgb value (line 200 or 100 or 255 or 001 or 020...) to onestr
                onestr += onerbg;
            }
            // pushing onestr (onestr is a strig like 255255000 or 010200100 so it is one color in rgb values so it is part of the color order)
            order.push_back(onestr);
        }
        usedorder(order, ' ');
        // sending randomly generated order to orde with false meaning color mode
        orde(order, false);
    }
}

// asks question of the image and runs functions
int main(){
    // asking for black & white or color image and for width and height
    string bwc;
    string wh;
    char ordran;
    char eachord;
    cout << "Black and white(0) or color picture(1): ";
    cin >> bwc;
    cout << "Enter image's width and height in pixels (for exmp. 12,14): ";
    cin >> wh;
    vector<string> res = split(wh, true);
    w = stoi(res[0]);
    h = stoi(res[1]);
    text += (res[0] + ' ' + res[1]);
    // if black & white is selected
    if(bwc == "0"){
        // adding black & white file signature and widht & height information
        text = "P1\n" + text + '\n';
        // asking for manually typed black & white order or randomly generated image
        cout << "Blacks and whites in orded order(0) or randomly generated(1): ";
        cin >> ordran;
        // if manually typed order is selected, putseq will run, otherwise randomly generated will run in else{}
        if(ordran == '0'){
            putseq(true);
        }else{
            // manually typed order is not selected (randomly generated is selected) so asking for each pixel seperately randomized or randomized order
            cout << "Random for each pixel(0) or random order(1): ";
            cin >> eachord;
            // if random order is selected, ranord will be run, otherwise eachsep
            if(eachord == '1'){
                ranord(true);
            }else{
                eachsep(true);
            }
        }
    }else{
        // adding color images file signature and width & height information and maximum rgb value
        text = "P3 " + text + " 255\n";
        cout << "Colors in orded order(0) or randomly generated(1): ";
        cin >> ordran;
        // if order is selected putseq will run, otherwise randomly generated will eun in else{}
        if(ordran == '0'){
            putseq(false);
        }else{
            cout << "Random for each pixel(0) or random order(1): ";
            cin >> eachord;
            // if random order is selected, ranord will be run, otherwise eachsep
            if(eachord == '1'){
                ranord(false);
            }else{
                eachsep(false);
            }
        }
    }
    // asking for file name and writing & saving the file
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
