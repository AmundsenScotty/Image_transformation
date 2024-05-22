#include <iostream>
#include <stdexcept>

#ifndef STB_IMPLEMENTATION
#define STB_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

#include "image.h"
#include "point.h"

#define MEMTRACE
#include "memtrace.h"

/// Default constructor for the Image class.
Image::Image() : imageData(nullptr), my_image(true), imageHeight(0), imageWidth(0), colorChannels(0), fileName("")
{
    for (int i = 0; i < 4; i++)
        corners[i] = Point(0, 0);
}

/// Constructor that loads an image from a file.
/// @param file_name The name of the file to load the image from.
Image::Image(std::string const& file_name)
{
    fileName = file_name;
    imageData = stbi_load(fileName.c_str(), &imageWidth, &imageHeight, &colorChannels, 0);

    if (imageData == nullptr || imageHeight > 100000 || imageWidth > 100000)
        throw std::exception("Nincs ilyen kép!");

    my_image = false;

    for (int i = 0; i < 4; i++)
        corners[i] = Point(0, 0);
}

/// Destructor for the Image class.
Image::~Image()
{
    if (my_image)
        delete[] imageData;
}

/// Gets the file name of the image.
/// @return The file name as a constant reference.
std::string const& Image::get_file_name() const
{
    return fileName;
}

/// Sets the file name of the image.
/// @param new_file_name The new file name to set.
void Image::set_file_name(std::string const& new_file_name)
{
    try
    {
        Image::check_file_name(new_file_name);
    }
    catch (std::exception const& err)
    {
        std::cout << "Hiba: " << err.what() << std::endl;
    }

    fileName = new_file_name;
}

/// Copy constructor for the Image class.
/// @param other The Image object to copy from.
Image::Image(Image const& other)
{
    *this = other;
}

/// Assignment operator for the Image class.
/// @param other The Image object to assign from.
void Image::operator=(Image const& other)
{
    fileName = other.fileName.substr(0, other.fileName.find_last_of('.'))
        + "_in_progress"
        + other.fileName.substr(other.fileName.find_last_of('.'));

    colorChannels = other.colorChannels;
    imageHeight = other.imageHeight;
    imageWidth = other.imageWidth;

    imageData = new unsigned char[imageHeight * imageWidth * colorChannels];

    for (int i = 0; i < 4; i++)
        corners[i] = other.corners[i];

    for (size_t i = 0; i < (size_t)imageHeight * imageWidth * colorChannels; i++)
        imageData[i] = other.imageData[i];

    this->write_image_to_file("...", 100, false);
}

/// Gets the corners of the image.
/// @return A pointer to the array of corners.
Point* Image::get_corners()
{
    return corners;
}

/// Sets a corner of the image.
/// @param idx The index of the corner to set.
/// @param corner The Point object representing the new corner.
void Image::set_corner(unsigned idx, Point const& corner)
{
    if (idx < 4)
        corners[idx] = corner;
    else
        throw std::exception("Index out of range");
}

/// Checks if the file name is valid.
/// @param file_name The file name to check.
void Image::check_file_name(std::string const& file_name)
{
    unsigned dotIndex = file_name.find_first_of('.');

    if (dotIndex == 0 || dotIndex > file_name.size())
        throw std::exception("Helytelen file formátum!");

    std::string exstention = file_name.substr(dotIndex + 1);

    if (exstention != "jpg"
        && exstention != "jpeg"
        && exstention != "png"
        && exstention != "bmp")
        throw std::exception("Helytelen file formátum!");
}

/// Opens the image in a window.
void Image::open_image_window() const
{
    system(fileName.c_str());
}

/// Opens the image in a window using a specified file name.
/// @param file_name The name of the file to open.
void Image::open_image_window(std::string const& file_name)
{
    system(file_name.c_str());
}

/// Closes the image window.
void Image::close_image_window()
{
    system("TASKKILL /F /IM PhotosApp.exe");
}

/// Prints the parameters of the image.
void Image::print_parameters() const
{
    std::cout << "Név: " << fileName << std::endl;
    std::cout << "Szélesség: " << imageWidth << " || Magasság: " << imageHeight << std::endl;

    std::cout << "Szín tartalom: ";
    switch (colorChannels)
    {
    case 1:
        std::cout << "szürkeárnyalatos";
        break;
    case 3:
        std::cout << "színes";
        break;
    case 4:
        std::cout << "színes mélységgel";
    default:
        std::cout << "unknown";
        break;
    }
    std::cout << std::endl;
}

/// Checks if a point is within the frame of the image.
/// @param p The Point object to check.
void Image::in_frame(Point const& p) const
{
    if (p.x < 0 || p.x > imageHeight || p.y > imageWidth)
        throw std::exception("A megadott pont nincs rajta a képen!");
}

/// Writes the image to a file.
/// @param new_file_name The name of the new file.
/// @param quality The quality of the saved image.
/// @param final_save Boolean indicating if this is the final save.
void Image::write_image_to_file(std::string const& new_file_name, unsigned quality, bool final_save)
{
    std::string output_name;
    if (new_file_name == "...")
    {
        if (final_save)
        {
            if (fileName.find("_in_progress") == std::string::npos)
                output_name = fileName.substr(0, fileName.find_last_of('.'))
                + "_changed"
                + fileName.substr(fileName.find_last_of('.'));

            else
                output_name = fileName.substr(0, fileName.find("_in_progress"))
                + "_changed"
                + fileName.substr(fileName.find("_in_progress") + sizeof("_in_progress") - 1);

            fileName = output_name;
        }
        else
        {
            output_name = fileName;
        }
    }
    else
    {
        try
        {
            Image::check_file_name(new_file_name);
        }
        catch (std::exception const& err)
        {
            std::cout << "Hiba: " << err.what() << std::endl;
        }
        //TODO: valamit kéne
        output_name = new_file_name;
    }

    stbi_write_jpg(output_name.c_str(), imageWidth, imageHeight, colorChannels, imageData, quality);
}

/// Gets the pixel data at a specific point.
/// @param p The Point object representing the pixel.
/// @return A pointer to the pixel data.
unsigned char* Image::indexPixel(Point const& p)
{
    if (p.x > imageHeight || p.y > imageWidth)
        throw "Overindexing in the image";

    return &imageData[(p.x * imageWidth + p.y) * colorChannels];
}

/// Gets the pixel data at specific coordinates.
/// @param px The x-coordinate of the pixel.
/// @param py The y-coordinate of the pixel.
/// @return A pointer to the pixel data.
unsigned char* Image::indexPixel(int px, int py)
{
    if (px > imageHeight || py > imageWidth)
        throw "Overindexing in the image";

    return &imageData[(px * imageWidth + py) * colorChannels];
}

/// @brief Reads a pixel value from the image.
/// @param px The x-coordinate of the pixel.
/// @param py The y-coordinate of the pixel.
/// @return unsigned char const* Pointer to the pixel value.
/// @throws Throws an exception if the coordinates are out of bounds.
unsigned char const* Image::readPixel(int px, int py) const
{
    if (px > imageHeight || py > imageWidth)
        throw "Overindexing in the image";

    return &imageData[(px * imageWidth + py) * colorChannels];
}

/// @brief Colors a pixel at a specific point with the given color.
/// @param p The point where the pixel is located.
/// @param color The color to apply to the pixel.
void Image::colorPixel(Point const& p, unsigned char* color)
{
    for (int i = 0; i < colorChannels; i++)
        indexPixel(p)[i] = color[i];
}

/// @brief Draws a yellow dot at a specific point with a given radius.
/// @param p The center point of the dot.
/// @param radius The radius of the dot.
void Image::yellowDotAt(Point const& p, unsigned radius)
{
    unsigned char* color = new unsigned char[colorChannels];

    if (colorChannels >= 3)
    {
        color[0] = 250;
        color[1] = 250;
        color[2] = 25;
    }

    for (int i = p.x - radius; i <= p.x + radius; i++)
        for (int j = p.y - radius; j <= p.y + radius; j++)
            if (Point::distance(p, Point(i, j)) <= radius)
                colorPixel(Point(i, j), color);

    delete[] color;
}

/// @brief Draws a line at a specific starting point with given length, width, and direction.
/// @param start The starting point of the line.
/// @param length The length of the line.
/// @param width The width of the line.
/// @param dir The direction of the line, true for horizontal and false for vertical.
void Image::lineAt(Point const& start, int length, int width, bool dir)
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < length; j++)
            if (dir)
                yellowDotAt(Point(start.x + j, start.y + i));
            else
                yellowDotAt(Point(start.x + i, start.y + j));
}

/// @brief Checks if a vector is around a point within a small epsilon range.
/// @param rhs The vector to compare.
/// @param lhs The point to compare.
/// @return True if the vector is around the point, otherwise false.
static bool around(Vector const& rhs, Point const& lhs)
{
    double epsilon = 0.01;

    if (abs(rhs.x - lhs.x) <= epsilon && abs(rhs.y - lhs.y) <= epsilon)
        return true;
    else
        return false;
}

/// @brief Returns the sign of a double value.
/// @param d The double value.
/// @return 1 if the value is non-negative, otherwise -1.
static double sign(double d)
{
    return d >= 0 ? 1 : -1;
}

/// @brief Draws a line from one point to another.
/// @param from The starting point of the line.
/// @param to The ending point of the line.
void Image::draw_line(Point const& from, Point const& to)
{
    Vector step(0, 0);

    if (from.x == to.x)
    {
        step.x = 0;
        step.y = sign(to.y - from.y);
    }
    else
    {
        if (from.y == to.y)
        {
            step.x = sign(to.x - from.x);
            step.y = 0;
        }
        else
        {
            double decline = (double)(to.x - from.x) / (to.y - from.y);

            if (abs(decline) <= 1)
            {
                step.x = abs(decline) * sign(to.x - from.x);
                step.y = sign(to.y - from.y);
            }
            else
            {
                step.x = sign(to.x - from.x);
                step.y = 1 / decline * sign(to.y - from.y);
            }
        }
    }

    Vector index(from.x, from.y);
    for (; !around(index, to); index.x += step.x, index.y += step.y)
    {
        yellowDotAt(Point((int)index.x, (int)index.y - 1));
        yellowDotAt(Point((int)index.x, (int)index.y));
        yellowDotAt(Point((int)index.x, (int)index.y + 1));
        yellowDotAt(Point((int)index.x + 1, (int)index.y - 1));
        yellowDotAt(Point((int)index.x + 1, (int)index.y));
        yellowDotAt(Point((int)index.x + 1, (int)index.y + 1));
    }
}

/// @brief Creates a grid on the image with specified spacing and width.
/// @param spacing The spacing between grid lines.
/// @param width The width of the grid lines.
void Image::createGrid(int spacing, int width)
{
    for (int i = spacing; i < imageHeight - width; i += spacing)
        lineAt(Point(i, 0), imageWidth, width, false);

    for (int i = spacing; i < imageWidth - width; i += spacing + width)
        lineAt(Point(0, i), imageHeight, width, true);
}

/// @brief Draws a yellow cross at a specific point with given size and width.
/// @param p The center point of the cross.
/// @param size The size of the cross.
/// @param width The width of the cross.
void Image::yellowCrossAt(Point const& p, unsigned size, unsigned width)
{
    unsigned char* color = new unsigned char[colorChannels];

    if (colorChannels >= 3)
    {
        color[0] = 250;
        color[1] = 250;
        color[2] = 25;
    }

    for (int i = p.x - size; i < p.x + size; i++)
        for (int j = p.y - size; j < p.y + size; j++)
            if (abs(i - p.x) <= width / 2 || abs(j - p.y) <= width / 2)
                colorPixel(Point(i, j), color);

    delete[] color;
}

/// @brief Interpolates the color index of a pixel.
/// @param x_idx The x index of the pixel.
/// @param y_idx The y index of the pixel.
/// @param colorChannels The number of color channels.
/// @param k The specific color channel to interpolate.
/// @return The interpolated color value.
unsigned char Image::interpolateIndex(double x_idx, double y_idx, int colorChannels, int k) const
{
    double x_left_ratio = x_idx - (int)x_idx;
    double x_right_ratio = (int)x_idx + 1 - x_idx;

    double y_top_ratio = y_idx - (int)y_idx;
    double y_bot_ratio = (int)y_idx + 1 - y_idx;

    unsigned char corners[4] = { 0 };
    corners[0] = readPixel((int)x_idx, (int)y_idx)[k];
    corners[1] = readPixel((int)x_idx + 1, (int)y_idx)[k];
    corners[2] = readPixel((int)x_idx + 1, (int)y_idx + 1)[k];
    corners[3] = readPixel((int)x_idx, (int)y_idx + 1)[k];

    unsigned char c = (corners[0] * x_left_ratio + corners[1] * x_right_ratio) * y_top_ratio + (corners[2] * x_left_ratio + corners[3] * x_right_ratio) * y_bot_ratio;

    return c;
}

/// @brief Draws yellow crosses at the corners of an image.
/// @param corners The points representing the corners.
/// @return A new image with yellow crosses drawn at the corners.
Image* Image::draw_corners(Point* corners) const
{
    Image* output = new Image;
    *output = *this;

    for (size_t i = 0; i < 4; i++)
        output->yellowCrossAt(corners[i]);

    return output;
}

/// @brief Draws a rectangle by connecting the given corners with lines.
/// @param corners The points representing the corners of the rectangle.
/// @return A new image with the rectangle drawn.
Image* Image::draw_rectangle(Point* corners) const
{
    Image* output = new Image;
    *output = *this;

    for (size_t i = 0; i < 4; i++)
        output->draw_line(corners[i], corners[(i + 1) % 4]);

    return output;
}

/// @brief Arranges the corners of a rectangle in a specific order.
/// @param corners The points representing the corners of the rectangle.
/// @return A new array of points representing the arranged corners.
Point* Image::arrange_corners(Point* corners)
{
    Point* out = new Point[4];

    unsigned xy_sum = 0;
    unsigned max_xy = 0, max_idx = 0, min_xy = corners[0].x + corners[0].y, min_idx = 0;
    for (int i = 0; i < 4; i++)
    {
        xy_sum = corners[i].x + corners[i].y;
        if (xy_sum

    > max_xy)
        {
            max_xy = xy_sum;
            max_idx = i;
        }
        if (xy_sum < min_xy)
        {
            min_xy = xy_sum;
            min_idx = i;
        }
    }

    out[0] = corners[max_idx];
    out[2] = corners[min_idx];

    unsigned other_two[2] = { 0 };

    switch (max_idx + min_idx)
    {
    case 1:
        other_two[0] = 2;
        other_two[1] = 3;
        break;
    case 2:
        other_two[0] = 1;
        other_two[1] = 3;
        break;
    case 3:
        if (min_idx == 0 || max_idx == 0)
        {
            other_two[0] = 1;
            other_two[1] = 2;
            break;
        }
        else
        {
            other_two[0] = 0;
            other_two[1] = 3;
            break;
        }
        break;
    case 4:
        other_two[0] = 0;
        other_two[1] = 2;
        break;
    case 5:
        other_two[0] = 0;
        other_two[1] = 1;
        break;
    }

    if (corners[other_two[0]].x > corners[other_two[1]].x)
    {
        out[1] = corners[other_two[1]];
        out[3] = corners[other_two[0]];
    }
    else
    {
        out[1] = corners[other_two[0]];
        out[3] = corners[other_two[1]];
    }

    return out;
}

/// @brief Extracts a rectangle from the image defined by the given corners.
/// @param corners The points representing the corners of the rectangle.
/// @param p_image_width The width of the extracted rectangle.
/// @param p_image_height The height of the extracted rectangle.
/// @return A new image containing the extracted rectangle.
Image* Image::extract_rectangle(Point* corners, unsigned p_image_width, unsigned p_image_height) const
{
    Point* arranged_corners = arrange_corners(corners);

    Image* new_image(new Image);

    new_image->fileName = fileName.substr(0, fileName.find_last_of('.'))
        + "_in_progress"
        + fileName.substr(fileName.find_last_of('.'));

    unsigned distances[4] = { 0 };

    for (int i = 0; i < 4; i++)
        distances[i] = Point::distance(arranged_corners[i], arranged_corners[(i + 1) % 4]);

    // ratio = original height / width
    double ratio = (double)(distances[0] + distances[2]) / (distances[1] + distances[3]);

    new_image->imageWidth = p_image_width;
    new_image->imageHeight = p_image_width * ratio;
    new_image->colorChannels = colorChannels;

    new_image->imageData = new unsigned char[new_image->imageWidth * new_image->imageHeight * colorChannels];

    double n[4] = { 0 };

    for (int i = 0; i < new_image->imageHeight; i++)
        for (int j = 0; j < new_image->imageWidth; j++)
        {
            double u = (double)i / (new_image->imageHeight / 2.0) - 1;
            double v = (double)j / (new_image->imageWidth / 2.0) - 1;

            n[0] = (1 + u) * (1 + v) / 4.0;
            n[1] = (1 - u) * (1 + v) / 4.0;
            n[2] = (1 - u) * (1 - v) / 4.0;
            n[3] = (1 + u) * (1 - v) / 4.0;

            double x_idx = 0;
            double y_idx = 0;

            for (int k = 0; k < 4; k++)
            {
                x_idx += n[k] * arranged_corners[k].x;
                y_idx += n[k] * arranged_corners[k].y;
            }

            if (0 && i % 10 == 0 && j % 10 == 0)
            {
                std::cout << i << " " << j << " ";
                std::cout << u << " " << v << " ";
                for (int h = 0; h < 4; h++)
                    std::cout << n[h] << " ";
                std::cout << x_idx << " " << y_idx << " ";
                std::cout << std::endl;
            }

            for (int k = 0; k < colorChannels; k++)
                new_image->indexPixel(i, j)[k] = interpolateIndex(x_idx, y_idx, colorChannels, k);
        }

    delete[] arranged_corners;

    return new_image;
}