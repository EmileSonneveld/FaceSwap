#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include <opencv2/videoio/videoio_c.h>
#include <opencv2/highgui/highgui_c.h>

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <iterator>

#include <stdio.h>
#include "svg_image.h"
#include "face_feed.h"


using namespace std;
using namespace cv;


const char * help_string = "\
## Swap faces from a picture with a set of faces from choice ## \n\
This program assumes hardcoded paths: \n\
- source -- must be current dir \n\
    - faceswap -- executable \n\
    - file-template.xml \n\
    - img-template.xml \n\
    - [source code] \n\
- photo_result -- will cointain the svg's \n\
    - *.svg -- The images in the svg are references \n\
- haarcascades -- image recongnition data \n\
    - haarcascade_frontalface_alt.xml \n\
    - haarcascade_frontalface_alt2.xml \n\
    - haarcascade_frontalface_alt_tree.xml \n\
    - haarcascade_frontalface_default.xml \n\
    - ... \n\
- photo_heads -- contains the photos's of heads you want to set_rect \n\
    - *.png \n\
- photo_orig -- for the sake of path's in the SVG file it's advised to place your pictures here \n\
 \n\
The outputted SVG is viewed best with a browser. \n\
";

std::vector<cv::Rect> detectAndDraw( cv::Mat& image, cv::CascadeClassifier& cascade,
    double scale, bool tryflip );

const char* cascadeNames[] =  {
    "../haarcascades/haarcascade_frontalface_alt.xml",
    "../haarcascades/haarcascade_frontalface_alt2.xml",
    "../haarcascades/haarcascade_frontalface_alt_tree.xml",
    "../haarcascades/haarcascade_frontalface_default.xml"
};

std::string file_original = "../photo_orig/pic_example.jpg";
std::string file_target_svg = "../photo_result/default_path.svg";


std::string MakeTargetSvgPath(std::string original)
{
  std::size_t pos = original.find_last_of("/");      // position of "live" in str
  auto str_tmp =  original.substr (pos, original.length()-pos-3);     // get from "live" to the end
  return std::string("../photo_result") + str_tmp + "svg";
}


int main( int argc, const char** argv )
{
    const string scaleOpt = "--scale=";
    size_t scaleOptLen = scaleOpt.length();

    const string photoOpt = "--photo=";
    size_t photoOptLen = photoOpt.length();

    const string cascadeOpt = "--cascade=";
    size_t cascadeOptLen = cascadeOpt.length();

    const string helpOpt = "--help";
    size_t helpOptLen = helpOpt.length();

    const string tryFlipOpt = "--try-flip";
    size_t tryFlipOptLen = tryFlipOpt.length();

    const string destOpt = "--dest=";
    size_t destOptLen = destOpt.length();

    bool tryflip = false;
    string destPath ="./photo_result_png/pic_example.png";
    double scale = 1;

    for( int i = 1; i < argc; i++ )
    {
        cout << "Argument " << i << ": " <<  argv[i] << endl;
        if( cascadeOpt.compare( 0, cascadeOptLen, argv[i], cascadeOptLen ) == 0 )
        {
            cascadeNames[0] = argv[i];
            cout << "  from which we have cascade1Name= " << cascadeNames[0] << endl;
        }
        else if( photoOpt.compare( 0, photoOptLen, argv[i], photoOptLen ) == 0 )
        {
            if( !sscanf( argv[i] + photoOpt.length(), "%lf", &scale ) || scale < 1 )
                file_original = string(argv[i]);
            cout << " from which we read scale = " << file_original << endl;
        }
        else if( scaleOpt.compare( 0, scaleOptLen, argv[i], scaleOptLen ) == 0 )
        {
            if( !sscanf( argv[i] + scaleOpt.length(), "%lf", &scale ) || scale < 1 )
                scale = 1;
            cout << " from which we read scale = " << scale << endl;
        }
        else if( tryFlipOpt.compare( 0, tryFlipOptLen, argv[i], tryFlipOptLen ) == 0 )
        {
            tryflip = true;
            cout << " will try to flip image horizontally to detect assymetric objects.\n";
        }
        else if( destOpt.compare( 0, destOptLen, argv[i], destOptLen ) == 0 )
        {
            destPath = string(argv[i]);
            destPath = destPath.substr(destOptLen);
            cout << " Destenation specified.\n";
        }
        else if( helpOpt.compare( 0, helpOptLen, argv[i], helpOptLen ) == 0 )
        {
            cout << help_string;
            cout << "Using OpenCV version " << CV_VERSION << "\n" << endl;
            return 0;
        }
        else if( argv[i][0] == '-' )
        {
            cerr << "WARNING: Unknown option " << argv[i] << endl;
        }
        else
            file_original.assign( argv[i] );
    }

    file_target_svg = MakeTargetSvgPath(file_original);
    cout << "Output file: " << file_target_svg << endl;
    // End of freacking input stuff //


    vector<cv::CascadeClassifier> cascades;
    for( unsigned int i = 0; i<4; ++i){
        cascades.push_back(cv::CascadeClassifier());
        if( !cascades[i].load( cascadeNames[i] ) )
        {
            cerr << "ERROR: Could not load cascade " << cascadeNames[i] << endl;
            return -1;
        }
    }




    cv::Mat bigImage = cv::imread(file_original);   // Read the file
    if(!bigImage.data )
    {
        cout <<  "Could not open or find the bigImage: " << file_original << std::endl;
        return -1;
    }

    std::vector<cv::Rect> faces_all, faces;

    faces = detectAndDraw( bigImage, cascades[1], scale, tryflip );
    faces_all.insert(faces_all.end(), faces.begin(), faces.end());

    //faces = detectAndDraw( bigImage, cascade, scale, tryflip );
    //faces_all.insert(faces_all.end(), faces.begin(), faces.end());

    face_feed();

    // Draw the found faces in a window //////////////////
    if(false) // still broken
    {
        for(cv::Rect& rec : faces_all)
        {
            cout << "rec.x: " << rec << "\n";
            cv::Mat smallImage = cv::imread("../photo_heads/birt-blue.png");

            cv::Size t = smallImage.size();
            Mat roi(bigImage, cv::Rect(0,0, t.width, t.height) );
            smallImage.copyTo(roi);

            //cv::Rect rectRoi( cv::Point( rec.x, rec.y ), cv::Size( rec.width, rec.height ));
            //cv::Mat destinationROI = bigImage( rectRoi );
            //smallImage.copyTo( destinationROI );
        }

        namedWindow( "Preview Window", CV_WINDOW_AUTOSIZE );
        imshow( "Preview Window", bigImage );
        waitKey(0);
    }

    // Now serialize the stuff //////////////////////

    std::stringstream ss("", ios_base::app | ios_base::out);

    for(auto r : faces_all)
    {
        // messy object, I know, I know
        auto svgimage = svg_image();
        svgimage.refresh();
        svgimage.set_rect(r);
        ss << svgimage.get_resulting_svg();
    }


    auto file_content = file_to_string("file-template.xml");
    replace_var(file_content, "$original_picture_here", file_original);
    replace_var(file_content, "$img_attributes_here", ss.str());
    replace_var(file_content, "$image_width", std::to_string(bigImage.cols));
    replace_var(file_content, "$image_height", std::to_string(bigImage.rows));

    ofstream myfile;
    myfile.open (file_target_svg, ios::out);
    myfile << file_content;
    myfile.close();

    string command = "../rasterize.sh ";
    command.append(destPath);
    cout << "Execute: " << command << endl;
    system(command.c_str());

    return 0;
}


std::vector<cv::Rect> detectAndDraw( cv::Mat& image, cv::CascadeClassifier& cascade,
    double scale, bool tryflip)
{
    cv::Mat imgCopy( cvRound(image.rows/scale), cvRound(image.cols/scale), CV_8UC1 );
    //cv::Mat imgCopy( 732*0.8, 1100*0.8, CV_8UC1 );
    //Size( std::min (image.rows, 100), std::min(image.cols, 100) )
    cv::Mat imgGray;
    cv::cvtColor( image, imgGray, cv::COLOR_BGR2GRAY );
    cv::resize( imgGray, imgCopy, imgCopy.size()  , 0, 0, cv::INTER_LINEAR );
    cv::equalizeHist( imgCopy, imgCopy );

    vector<cv::Rect> faces;
    cascade.detectMultiScale( imgCopy, faces,
        1.1, 2, 0
        //|cv::CASCADE_FIND_BIGGEST_OBJECT
        //|cv::CASCADE_DO_ROUGH_SEARCH
        |cv::CASCADE_SCALE_IMAGE
        ,
        cv::Size(11, 11) );
    if( tryflip )
    {
        vector<cv::Rect> faces_fliped;
        cv::flip(imgCopy, imgCopy, 1);
        cascade.detectMultiScale( imgCopy, faces_fliped,
         1.1, 2, 0
            //|cv::CASCADE_FIND_BIGGEST_OBJECT
            //|cv::CASCADE_DO_ROUGH_SEARCH
         |cv::CASCADE_SCALE_IMAGE
         ,
         cv::Size(17, 17) );

        faces.insert(faces.end(), faces_fliped.begin(), faces_fliped.end());
    }

    cout << "Number of faces: " << faces.size() << endl;


    return faces;
}
