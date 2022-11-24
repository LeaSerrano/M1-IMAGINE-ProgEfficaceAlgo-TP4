#include <string>
#include <iostream>
#include "image-pnm.h"
#include <algorithm>
using namespace std;

using ImagePBM = Image<uint8_t>;
using ImagePGM = Image<uint8_t>;
using ImagePGMf= Image<float>;
using RGB256 = RGB<uint8_t>;
using ImagePPM = Image<RGB256>;

int B = 4;

void blur_pbm(ImagePBM Img, ImagePBM ImgResult, char *fileIn) {
    float* HG = new float[2];
    float* BD = new float[2];
    float moyenne;
    float nbPixels;

    for (int i = 0; i < Img.width(); i++) {
        for (int j = 0; j < Img.height(); j++) {
            HG[0] = max(0, i-B);
            HG[1] = max(0, j-B);
            BD[0] = min((int)Img.width(), i+B);
            BD[1] = min((int)Img.height(), j+B);

            moyenne = 0;
            nbPixels = 0;

            for (int x = HG[0]; x < BD[0]; x++) {
                for (int y = HG[1]; y < BD[1]; y++) {
                    moyenne += Img.get(x, y);
                    nbPixels++;
                }
            }

            moyenne = moyenne/nbPixels;
            ImgResult.get(i, j) = moyenne;
        }
    }

    string fileOut(fileIn);
    fileOut=fileOut.substr(0,fileOut.find_first_of("."))+string("-out.pbm");
    
    ImgResult.write(fileOut.c_str());
    cout<<"Image written to "<<fileOut<<endl;
}

void blur_pgm(ImagePGM Img, ImagePGM ImgResult, char *fileIn) {
    float* HG = new float[2];
    float* BD = new float[2];
    float moyenne;
    float nbPixels;

    for (int i = 0; i < Img.width(); i++) {
        for (int j = 0; j < Img.height(); j++) {
            HG[0] = max(0, i-B);
            HG[1] = max(0, j-B);
            BD[0] = min((int)Img.width(), i+B);
            BD[1] = min((int)Img.height(), j+B);

            moyenne = 0;
            nbPixels = 0;

            for (int x = HG[0]; x < BD[0]; x++) {
                for (int y = HG[1]; y < BD[1]; y++) {
                    moyenne += Img.get(x, y);
                    nbPixels++;
                }
            }

            moyenne = moyenne/nbPixels;
            ImgResult.get(i, j) = moyenne;
        }
    }

     string fileOut(fileIn);
    fileOut=fileOut.substr(0,fileOut.find_first_of("."))+string("-out.pgm");
    ImgResult.write(fileOut.c_str());
    cout<<"Image written to "<<fileOut<<endl;
}

int main(int argc, char** argv){

  if (argc!=2){
    cerr<<"Error: using with parameters: fileIn \n";
    return EXIT_FAILURE;
  }

  // get the 1st argument as the input image filename
  char *fileIn;
  fileIn=argv[1];

  // open the image file through a stream
  ifstream is(fileIn);
  if (!is.is_open()){
    cerr<<"Error: problem opening image "<< fileIn<<endl;
    return EXIT_FAILURE;  
  }
  string  magic_number;
  getline(is,magic_number);
  is.close();
  if (magic_number!= "P1" and magic_number!= "P2" and magic_number!= "P3"){
    cerr<<"Error: image in "<< fileIn<<" does not have the correct format (pbm,pgm,ppm with ASCII encoding)"<<endl;
    return EXIT_FAILURE;  
  }
    
  

  if (magic_number == "P1"){  
    ImagePBM Img("P1");
    ImagePBM ImgResult("P1");

    Img.read(fileIn);
    ImgResult.read(fileIn);

    blur_pbm(Img, ImgResult, fileIn);
  }
  if (magic_number == "P2"){
    ImagePGM Img("P2");
    ImagePGM ImgResult("P2");

    Img.read(fileIn);   
    ImgResult.read(fileIn);

    blur_pgm(Img, ImgResult, fileIn);
  }
  /*if (magic_number == "P3"){
    string fileOut(fileIn);
    ImagePPM Img("P3");
    fileOut=fileOut.substr(0,fileOut.find_first_of("."))+string("-out.pgm");
    Img.read(fileIn);   
    Img.write(fileOut.c_str());
    cout<<"Image written to "<<fileOut<<endl;    
  }*/




  return 0;
}