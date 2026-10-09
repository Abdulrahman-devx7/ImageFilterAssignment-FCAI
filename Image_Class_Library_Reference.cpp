// ════════════════════════════════════════════════════════════════════════
// IMAGE CLASS LIBRARY REFERENCE
// ════════════════════════════════════════════════════════════════════════
/*
── Image Class Overview & Initialization ───────────────────────
Core class representing RGB images with dynamic memory management, multi-format I/O, and pixel channel access.

Key Notes:
    - Default channels: 3 (RGB format: 0 = Red, 1 = Green, 2 = Blue).
    - Supported File Extensions: .PNG, .BMP, .TGA, .JPG, .JPEG.
    - Memory Management: Handles memory allocation and cleanup automatically upon destruction or reassignment.
    - Exceptions: Throws std::invalid_argument for invalid file inputs, std::out_of_range for illegal pixel coordinates.

Practical Usage / Commands / Code:
    // Initialize blank image, load file, or duplicate image:
    Image imgObj;                            // Default constructor
    Image imgLoaded("<filename>.<ext>");     // Load image directly from disk
    Image imgBlank(mWidth, mHeight);         // Create blank image with given width/height
    Image imgCopy(imgObj);                   // Deep copy constructor

Operations / Best Practices:
    - imgObj.width                           // Read/access image width in pixels
    - imgObj.height                          // Read/access image height in pixels
    - imgObj.channels                        // Read/access channel count (default 3)

── File I/O Operations ─────────────────────────────────────────
Methods to read images from disk into memory and save modified pixel buffers to output files.

Key Notes:
    - loadNewImage automatically frees previous pixel data before loading a new file.
    - saveImage automatically chooses export encoding based on output file extension.

Practical Usage / Commands / Code:
    // Load and save operations:
    imgObj.loadNewImage("<path_to_input_file>");
    imgObj.saveImage("<path_to_output_file>");

Operations / Best Practices:
    - loadNewImage("<filename>")             // Returns true on success; throws std::invalid_argument if missing or unsupported
    - saveImage("<filename>")                // Returns true on success; throws std::invalid_argument if format is unsupported

── Pixel Access & Manipulation ─────────────────────────────────
Functions for getting and setting individual channel intensity values (0–255) at pixel coordinates (x, y).

Key Notes:
    - Bounds: 0 <= x < width, 0 <= y < height, channel c in {0, 1, 2}.
    - Coordinate System: x = column / horizontal index, y = row / vertical index.
    - Direct Operator: operator() serves as a convenient reference wrapper around getPixel().

Practical Usage / Commands / Code:
    // Direct method access:
    unsigned char redVal = imgObj.getPixel(x, y, 0);
    imgObj.setPixel(x, y, 1, greenValue);

    // Overloaded function operator access:
    imgObj(x, y, 2) = blueValue;             // Read/Write pixel channel directly

Operations / Best Practices:
    - imgObj.getPixel(x, y, c)               // Returns ref to pixel channel; throws std::out_of_range if out of bounds
    - imgObj.setPixel(x, y, c, val)          // Assigns byte value to pixel channel; throws std::out_of_range if out of bounds
    - imgObj(x, y, c)                        // Operator shorthand for getPixel/setPixel reference

*/

#include "Image_Class.h"

int main()
{
    Image image("egypt.jpg");
    for (int w = 0; w * 2 < image.width; w++)
    {
        for (int h = 0; h < image.height; h++)
        {
            unsigned avg = image(w, h, 0) + image(w, h, 1) + image(w, h, 2);
            avg /= 3;
            for (int c = 0; c < image.channels; c++)
            {
                image(w, h, c) = avg;
            }
        }
    }
    image.saveImage("hi.jpg");
    
    return 0;
}