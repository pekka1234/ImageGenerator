# RandomImageGenerator
Generates (currently black & white) images by given input or randomly

Note: Images are generated as .bpm and disable image smoothening in your image viewer app becouse images can be very small

For example:

![Screenshot from 2022-12-05 18-23-51](https://user-images.githubusercontent.com/62663286/205688609-18cf7819-a4f6-4dd0-9228-f0e541a65255.png)

![kuvaU3](https://user-images.githubusercontent.com/62663286/205688213-3865dd38-d79f-459c-93d1-1178c493c5f2.png)

# How to use it

Compile main.cpp and run the result

Image #1 above was generated followingly:

Black and white(0) or color picture(1): 0  <-- anwsered 0 and pressed Enter

Enter image widht and height in pixels (for exmp. 12,14): 30,30  <-- anwsered 30,30 and pressed Enter

Sequence of blacks and whites in orded order(0) or random(1): 0  <-- anwsered 0 and pressed Enter

enter sequence, black = 1, white = 0 (for exmp. 1,0,0,0,1,1,0): 1,0,0,1,0,0,0  <-- anwsered 1,0,0,1,0,0,0 and pressed Enter

Enter file name: img  <--anwsered img and pressed Enter

Other things are pretty simple but the sequence is more complicated, it means that the order of black and white will be repeated trought the whole picture,
for example image #1 sequence was 1,0,0,1,0,0,0 and it means black, white, white, black, white, white, white. You can check that that is the order image #1
follows from start to beginning

Random:
If you use random sequence, just give the sequence lenght and if you use random for each pixel just press enter
