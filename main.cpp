# include "opencv2/opencv.hpp"
# include <iostream>
# include <string>

using namespace std;
using namespace cv;

void print_help(char * progname)
{
    std::cout << "Usage: " << progname << " [OPTIONS]\n"
              << "Options:\n"
              << "  -h, --help\n"
              << "    Print this help message and exit.\n"
              << "  -i, --input\n"
              << "    input path.\n"
                << "  -o, --output\n"
                << "    output path.\n"
              ;


    return;
}


int main (int argc, char *argv[])
{
    string input_path, output_path;
    bool is_input, is_output;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            print_help(argv[0]);
            return 0;
        }
        else if (strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-i") == 0)
        {
            is_input = 1;
            input_path = argv[++i];
        }
        else if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0)
        {
            is_output = 1;
            output_path = argv[++i];
        }
    }

    if (!is_input || !is_output)
    {
        print_help(argv[0]);
        return 1;
    }

    cout << "input_path: " << input_path << endl;
    cout << "output_path: " << output_path << endl << endl;

    VideoCapture cap(input_path);
    if(!cap.isOpened())
    {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    long original_fps = cap.get(cv::CAP_PROP_FPS);
    int original_frame_count = cap.get(cv::CAP_PROP_FRAME_COUNT);

    long fps = original_fps * 2;

	VideoWriter video("outcpp.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, Size(frame_width,frame_height));

    while(1)
    {
    Mat frame;
    cap >> frame;

    if (frame.empty())

      break;

    video.write(frame);

    imshow( "Frame", frame );
    char c = (char)waitKey(1);

    if( c == 27 )
      break;

    }

  cap.release();
  video.release();


  destroyAllWindows();
  return 0;



    
}