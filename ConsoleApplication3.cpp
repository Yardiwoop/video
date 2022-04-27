#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include <math.h>
#include <opencv2/videoio.hpp>
using namespace cv;
using namespace std;
#include <fstream>
#include <iostream>
using namespace std;
#define PIXELS 655360
#define RAZRYAD 65536






int main(int argc, char* argv[])
{
    
    ifstream fin("C:\\Users\\Z\\Downloads\\dump_13122019_145433\\dump_13122019_145433.bin", ios::in | ios::binary);
    if (!fin) {
        cout << "dont opened file";
    }
    else {
       

        fin.seekg(32);
        unsigned int length = fin.tellg();
        

        unsigned char a;
        long int hist[RAZRYAD] = {};
        unsigned short* B = new unsigned short[PIXELS / 2];
        VideoWriter outputVideo;
        int codec = VideoWriter::fourcc('M', 'P', '4', 'V');
        Size sizeFrame(512, 640);
        outputVideo.open("AF.mp4", codec, 20, sizeFrame, CV_16UC1);
        for (int j = 0; j < 1000; j++) {
            B = new unsigned short[PIXELS / 2];
            for (int i = 0; i < PIXELS; i++) {
                fin.read((char*)&a, sizeof(char));

                if (i % 2 == 0) {
                    //cout << (unsigned short)a<<" ";
                    B[i / 2] = (unsigned short)a;
                    B[i / 2] = B[i / 2] << 8;
                }
                else
                {
                    //cout << (unsigned short)a << " ";
                    B[i / 2] += (unsigned short)a;
                   
                }
                if(B[i / 2]<20000)B[i/2] = pow(double(B[i/2]) / 65536, 0.5) * 65536;
                if (B[i / 2] > 40000)B[i / 2] = pow(double(B[i / 2]) / 65536, 2.0) * 65536;
                //int bin = B[i / 2] / 256; //чтобы было меньше позиций гистограммы
                //hist[B[i / 2]]++;              //заполнение гистограммы

            }

            Mat img(512, 640, CV_16UC1, B);
            //imshow("Display window", img);
            waitKey(10);
            fin.seekg(PIXELS, std::ios::cur);
            
            outputVideo.write(img);
        }
       

        
        



        cout << "HISTOGRAMMA";
        long double h = 0;
        int S[256] = {};
        for (int i = 0; i < RAZRYAD; i++)
        {
            //h += 255.0/(PIXELS*100.0)* (long double)hist[i]; //step 2 //h=255
            hist[i] = (double)RAZRYAD / (double)PIXELS  * hist[i];
            
            //cout  << hist[i] << " " <<std::endl;
        }
        //cout << h;
         long  *cum_hist=new long[RAZRYAD];

         long sum = 0;
        for (int i = 0; i < RAZRYAD; i++)
        {
            sum += hist[i];
            cum_hist[i] = sum;
        }
        cout << sum;
        /*for (int i = 1; i < 256; i++)
        {
           
            hist[i] = hist[i - 1]+hist[i];
        }*/
        long int hist2[256] = {};
        fin.seekg(32+PIXELS*250);
     
            B = new unsigned short[655360 / 2];
            for (int i = 0; i < 655360; i++) {
                
                fin.read((char*)&a, sizeof(char));

                if (i % 2 == 0) {
                    //cout << (unsigned short)a<<" ";
                    B[i / 2] = (unsigned short)a;
                    B[i / 2] = B[i / 2] << 8;
                }
                else
                {
                    //cout << (unsigned short)a << " ";
                    B[i / 2] += (unsigned short)a;
                    //ShowBin(B[i / 2]);
                }
                //int t = round(256 * B[i / 2]);
               //B[i / 2] = cum_hist[B[i / 2]]; //попытка эквализации

               B[i / 2] = pow(double(B[i / 2]) / RAZRYAD, 1.0) * RAZRYAD;
               int bin = B[i / 2] / 256; //
               hist2[bin]++;
            }
               
            for (int i = 0; i < 256; i++)
            {
                //h += 255.0/(PIXELS*100.0)* (long double)hist[i]; //step 2 //h=255
               // hist[i] = (double)RAZRYAD / (double)PIXELS * hist[i];

                cout  << hist2[i] << " " <<std::endl;
            }
        

        fin.close();

        /*Mat img(512, 640, CV_16UC1, B);
        imshow("Display window", img);
        waitKey(0);*/

    }


    system("pause");
    return 0;
}