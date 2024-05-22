#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "point.h"
#include "vector.h"

/// @brief This class is responsible for handling the image data and the image manipulation functions.
class Image
{
    std::string fileName; ///< The name of the file that contains the image.

    int colorChannels; ///< The number of color channels in the image.
    int imageHeight; ///< The height of the image.
    int imageWidth; ///< The width of the image.

    unsigned char* imageData; ///< The data of the image.
    bool my_image; ///< A flag that indicates if the image is created by the program.

    Point corners[4]; ///< The corners of the image.

    /// @brief Gets a pointer to the pixel at a specific point.
    /// @param p The point of the pixel.
    /// @return A pointer to the pixel.
    unsigned char* indexPixel(Point const& p);

    /// @brief Gets a pointer to the pixel at specific coordinates.
    /// @param px The x-coordinate of the pixel.
    /// @param py The y-coordinate of the pixel.
    /// @return A pointer to the pixel.
    unsigned char* indexPixel(int px, int py);

    /// @brief Reads a pixel value from the image.
    /// @param px The x-coordinate of the pixel.
    /// @param py The y-coordinate of the pixel.
    /// @return A pointer to the pixel value.
    unsigned char const* readPixel(int px, int py) const;

    /// @brief Interpolates the color index of a pixel.
    /// @param x_idx The x index of the pixel.
    /// @param y_idx The y index of the pixel.
    /// @param colorChannels The number of color channels.
    /// @param k The specific color channel to interpolate.
    /// @return The interpolated color value.
    unsigned char interpolateIndex(double x_idx, double y_idx, int colorChannels, int k) const;

public:
    /// @brief Default constructor for the Image class.
    Image();

    /// @brief Constructor for the Image class with a file name.
    /// @param file_name The name of the file to load.
    Image(std::string const& file_name);

    /// @brief Destructor for the Image class.
    ~Image();

    /// @brief Gets the file name of the image.
    /// @return The file name of the image.
    std::string const& get_file_name() const;

    /// @brief Sets a new file name for the image.
    /// @param new_file_name The new file name to set.
    void set_file_name(std::string const& new_file_name);

    /// @brief Copy constructor for the Image class.
    /// @param other The other image to copy from.
    Image(Image const& other);

    /// @brief Assignment operator for the Image class.
    /// @param other The other image to assign from.
    void operator=(Image const& other);

    /// @brief Gets the corners of the image.
    /// @return An array of points representing the corners of the image.
    Point* get_corners();

    /// @brief Sets a corner of the image.
    /// @param idx The index of the corner to set.
    /// @param corner The point representing the new corner.
    void set_corner(unsigned idx, Point const& corner);

    /// @brief Checks if the file name is valid.
    /// @param file_name The file name to check.
    static void check_file_name(std::string const& file_name);

    /// @brief Opens an image window for the current image.
    void open_image_window() const;

    /// @brief Opens an image window for a specified file name.
    /// @param file_name The name of the file to open.
    static void open_image_window(std::string const& file_name);

    /// @brief Closes the image window.
    static void close_image_window();

    /// @brief Prints the parameters of the image.
    void print_parameters() const;

    /// @brief Checks if a point is within the frame of the image.
    /// @param p The point to check.
    void in_frame(Point const& p) const;

    /// @brief Writes the image to a file.
    /// @param new_file_name The name of the file to save to.
    /// @param quality The quality of the saved image.
    /// @param final_save Indicates if this is the final save.
    void write_image_to_file(std::string const& new_file_name = "...", unsigned quality = 100, bool final_save = true);

    /// @brief Colors a pixel at a specific point with the given color.
    /// @param p The point where the pixel is located.
    /// @param color The color to apply to the pixel.
    void colorPixel(Point const& p, unsigned char* color);

    /// @brief Draws a yellow dot at a specific point with a given radius.
    /// @param center The center point of the dot.
    /// @param radius The radius of the dot.
    void yellowDotAt(Point const& center, unsigned radius = 0);

    /// @brief Draws a line at a specific starting point with given length, width, and direction.
    /// @param start The starting point of the line.
    /// @param length The length of the line.
    /// @param width The width of the line.
    /// @param dir The direction of the line, true for horizontal and false for vertical.
    void lineAt(Point const& start, int length, int width = 5, bool dir = true);

    /// @brief Draws a line from one point to another.
    /// @param from The starting point of the line.
    /// @param to The ending point of the line.
    void draw_line(Point const& from, Point const& to);

    /// @brief Creates a grid on the image with specified spacing and width.
    /// @param spacing The spacing between grid lines.
    /// @param width The width of the grid lines.
    void createGrid(int spacing = 20, int width = 5);

    /// @brief Draws a yellow cross at a specific point with given size and width.
    /// @param p The center point of the cross.
    /// @param size The size of the cross.
    /// @param width The width of the cross.
    void yellowCrossAt(Point const& p, unsigned size = 10, unsigned width = 2);

    /// @brief Draws yellow crosses at the corners of an image.
    /// @param corners The points representing the corners.
    /// @return A new image with yellow crosses drawn at the corners.
    Image* draw_corners(Point* corners) const;

    /// @brief Draws a rectangle by connecting the given corners with lines.
    /// @param corners The points representing the corners of the rectangle.
    /// @return A new image with the rectangle drawn.
    Image* draw_rectangle(Point* corners) const;

    /// @brief Arranges the corners of a rectangle in a specific order.
    /// @param corners The points representing the corners of the rectangle.
    /// @return A new array of points representing the arranged corners.
    static Point* arrange_corners(Point* corners);

    /// @brief Extracts a rectangle from the image defined by the given corners.
    /// @param corners The points representing the corners of the rectangle.
    /// @param p_image_width The width of the extracted rectangle.
    /// @param p_image_height The height of the extracted rectangle.
    /// @return A new image containing the extracted rectangle.
    Image* extract_rectangle(Point* corners, unsigned p_image_width = 1600, unsigned p_image_height = 900) const;
};

#endif
