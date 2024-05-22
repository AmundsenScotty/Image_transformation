#ifndef IMAGE_H
#define IMAGE_H

    #include <string>

    #include "point.h"
    #include "vector.h"


    /// Image class
    // @biref This class is responsible for handling the image data and the image manipulation functions
    // @param fileName The name of the file that contains the image
    // @param colorChannels The number of color channels in the image
	// @param imageHeight The height of the image
	// @param imageWidth The width of the image
	// @param imageData The data of the image
	// @param my_image A flag that indicates if the image is created by the program
	// @param corners The corners of the image
    class Image
    {
        std::string fileName;

        int colorChannels;
        int imageHeight;
        int imageWidth;

        unsigned char* imageData;
        bool my_image;

        Point corners[4];

        unsigned char* indexPixel(Point const& p);
        unsigned char* indexPixel(int px, int py);
        unsigned char const* readPixel(int px, int py) const;

        unsigned char interpolateIndex(double x_idx, double y_idx, int colorChannels, int k) const;

    public:
        Image();
        Image(std::string const& file_name);
        ~Image();

        std::string const& get_file_name() const;
        void set_file_name(std::string const& new_file_name);

        Image(Image const& other);
        void operator=(Image const& other);

        Point* get_corners();
        void set_corner(unsigned idx, Point const& corner);

        static void check_file_name(std::string const& file_name);

        void open_image_window() const;
        static void open_image_window(std::string const& file_name);
        static void close_image_window();

        void print_parameters() const;

        void in_frame(Point const& p) const;

        void write_image_to_file(std::string const& new_file_name = "...", unsigned quality = 100, bool final_save = true);

        void colorPixel(Point const& p, unsigned char* color);

        void yellowDotAt(Point const& center, unsigned radius = 0);

        void lineAt(Point const& start, int length, int width = 5, bool dir = true);

        void draw_line(Point const& from, Point const& to);

        void createGrid(int spacing = 20, int width = 5);

        void yellowCrossAt(Point const& p, unsigned size = 10, unsigned width = 2);

        Image* draw_corners(Point* corners) const;
        Image* draw_rectangle(Point* corners) const;

        static Point* arrange_corners(Point* corners);

        Image* extract_rectangle(Point* corners, unsigned p_image_width = 1600, unsigned p_image_height = 900) const;
    };

#endif