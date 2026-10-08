#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm> 
#include <cmath>
#include "Image_Class.h"
using namespace std;

class cls_main_screen; // Forward declaration

class cls_common_functions
{
public:
    static void execute_grayscale_conversion(Image& my_image)
    {
        for (int x = 0; x < my_image.width; x++)
        {
            for (int y = 0; y < my_image.height; y++)
            {
                int average{};
                for (int rgb_color = 0; rgb_color < my_image.channels; rgb_color++)
                {
                    average += my_image(x, y, rgb_color);
                }

                average /= 3;

                for (int rgb_color = 0; rgb_color < my_image.channels; rgb_color++)
                {
                    my_image(x, y, rgb_color) = average;
                }
            }
        }
    }
};

class cls_black_and_White_conversion_screen
{
private:
    enum en_black_and_White_conversion_screen_option
    {
        make_black_and_white_conversion = 1,
        save_image,
        load_image
    };

    static void exectue_make_black_and_white_conversion()
    {
        // سيتم ربطها لاحقاً
    }

    static void execute_saving_image() { cout << "exectue_saving_image will be here\n"; }
    static void execute_loading_image() { cout << "exeute_loading_image will be here\n"; }

    static void execute_black_and_White_conversion_screen_option(en_black_and_White_conversion_screen_option option)
    {
        switch (option)
        {
        case make_black_and_white_conversion:
            system("cls");
            exectue_make_black_and_white_conversion();
            go_back_to_black_and_White_conversion_screen();
            break;
        case save_image:
            system("cls");
            execute_saving_image();
            go_back_to_black_and_White_conversion_screen();
            break;
        case load_image:
            system("cls");
            execute_loading_image();
            go_back_to_black_and_White_conversion_screen();
            break;
        default:
            break;
        }
    }

    static void execute_black_and_White_conversion_screen()
    {
        cout << "[1]  make black and white conversion.\n";
        cout << "[2]  save image.\n";
        cout << "[3]  load image.\n";
    }

    static void go_back_to_black_and_White_conversion_screen()
    {
        cout << "press any key to go back....";
        system("pause>0");
        system("cls");
        execute_black_and_White_conversion_screen();
    }
};

class cls_rotating_image_screen
{
    // شاشة التدوير
};

class cls_darken_or_lighten_image_screen
{
private:
    enum submenuChoice { darken_image = 1, lighten_image = 2 };

    static short readUserInput()
    {
        short choice = 0;
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return choice;
    }

    static void execute_lighten_image(Image& target)
    {
        cout << "\n\nPlease, determine the percentage of lightening(0-100%): ";
        short percentage = readUserInput();

        for (int i = 0; i < target.width; ++i)
        {
            for (int j = 0; j < target.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    int overflowCheck = static_cast<int>(target(i, j, k) * ((100 + percentage) / 100.0));
                    if (overflowCheck > 255)
                        target(i, j, k) = 255;
                    else
                        target(i, j, k) = overflowCheck;
                }
            }
        }
    }

    static void execute_darken_image(Image& target)
    {
        cout << "\n\nPlease, determine the percentage of darkening(0-100%): ";
        short percentage = readUserInput();

        for (int i = 0; i < target.width; ++i)
        {
            for (int j = 0; j < target.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    target(i, j, k) = target(i, j, k) * ((100 - percentage) / 100.0);
                }
            }
        }
    }

    static void run_chosen_filter(const submenuChoice option, Image& target)
    {
        switch (option)
        {
        case darken_image:
            system("cls");
            execute_darken_image(target);
            break;
        case lighten_image:
            system("cls");
            execute_lighten_image(target);
            break;
        }
        cout << "Filter applied successfully!\n\n";
    }

public:
    static void run_filter(Image& target)
    {
        cout << "[1]  Darken Image\n";
        cout << "[2]  Lighten Image\n";
        run_chosen_filter(static_cast<submenuChoice>(readUserInput()), target);
    }
};

class cls_execute_cropping_image
{
private:
    static string read_file_name()
    {
        string filename;
        getline(cin >> ws, filename);
        return filename;
    }

    struct cropImageData
    {
        int startPointX = 0;
        int startPointY = 0;
        int dimensionHeight = 0;
        int dimensionWidth = 0;
    };

    static cropImageData readImageCropData()
    {
        cropImageData data;
        cout << "Please, input the X coordinate for the starting point for cropping\n";
        cin >> data.startPointX;
        cout << "\nPlease, input the Y coordinate for the starting point\n";
        cin >> data.startPointY;
        cout << "\nPlease, input the width dimension\n";
        cin >> data.dimensionWidth;
        cout << "\nPlease, input the height dimension\n";
        cin >> data.dimensionHeight;
        return data;
    }

    static Image applyFilter(const Image target)
    {
        cropImageData imageData = readImageCropData();
        Image croppedImage(imageData.dimensionWidth, imageData.dimensionHeight);

        for (int i = 0; i < imageData.dimensionWidth; ++i)
        {
            for (int j = 0; j < imageData.dimensionHeight; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    croppedImage(i, j, k) = target(imageData.startPointY + i, imageData.startPointX + j, k);
                }
            }
        }
        return croppedImage;
    }

    static void determineSaveDestination(Image& originalImage, Image& croppedImage, const string& imageFileName)
    {
        cout << "Do you want to save this image to a new file? (y/n)\n";
        char answer = 'n';
        cin >> answer;

        if (tolower(answer) == 'y')
        {
            cout << "\nPlease, enter the file name: ";
            string fileName = read_file_name();
            croppedImage.saveImage(fileName);
        }
        else
            originalImage = croppedImage;
    }

public:
    static void run_filter(Image& target, const string& imageFileName)
    {
        Image croppedImage = applyFilter(target);
        cout << "Cropping applied successfully!\n\n";
        determineSaveDestination(target, croppedImage, imageFileName);
    }
};


class cls_skewing_image_screen
{
private:
    static string read_file_name()
    {
        string filename;
        getline(cin >> ws, filename);
        return filename;
    }

    static Image applyFilter(const Image& target)
    {
        double angleDeg;
        cout << "Enter the degree of skewness along the vertical axis (e.g., 20 to 45): ";
        cin >> angleDeg;

        double angleRad = angleDeg * 3.14159265358979323846 / 180.0;

        int originalWidth = target.width;
        int originalHeight = target.height;
        int channels = target.channels;

        int skewOffsetMax = static_cast<int>(originalHeight * tan(angleRad));
        int newWidth = originalWidth + abs(skewOffsetMax);

        Image skewedImage(newWidth, originalHeight);

        
        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < originalHeight; ++j) {
                for (int c = 0; c < channels; ++c) {
                    skewedImage(i, j, c) = 255;
                }
            }
        }

        for (int j = 0; j < originalHeight; ++j) {
            int shift = 0;
            if (angleDeg > 0) {
                shift = static_cast<int>((originalHeight - 1 - j) * tan(angleRad));
            }
            else {
                shift = static_cast<int>(j * tan(angleRad));
            }

            for (int i = 0; i < originalWidth; ++i) {
                int newX = i + abs(shift);
                if (newX >= 0 && newX < newWidth) {
                    for (int c = 0; c < channels; ++c) {
                        unsigned char pixelValue = target(i, j, c);
                        skewedImage(newX, j, c) = pixelValue;
                    }
                }
            }
        }

        return skewedImage;
    }

    static void determineSaveDestination(Image& originalImage, Image& skewedImage)
    {
        cout << "Do you want to save this image to a new file? (y/n)\n";
        char answer = 'n';
        cin >> answer;

        if (tolower(answer) == 'y')
        {
            cout << "\nPlease, enter the file name: ";
            string fileName = read_file_name();
            skewedImage.saveImage(fileName);
        }
        else
            originalImage = skewedImage;
    }

public:
    static void run_filter(Image& target)
    {
        Image skewedImage = applyFilter(target);
        cout << "Image skewed successfully!\n\n";
        determineSaveDestination(target, skewedImage);
    }
};

class cls_main_screen
{
public:
    static Image currentImage;
    static string currentImageName;

    enum en_main_screen_option
    {
        load_image = 1,
        save_image = 2,
        grayscale_conversion = 3,
        black_and_white_conversion = 4,
        inverting_image = 5,
        adding_image = 6,
        flipping_image = 7,
        rotating_image = 8,
        darkening_or_lightening_conversion = 9,
        resizing_image = 10,
        merging_image = 11,
        detecting_image = 12,
        cropping_image = 13,
        blurring_image = 14,
        making_good_natural_sunlight_to_image = 15,
        making_image_like_it_is_in_Den_Den_Mushi_television = 16,
        skewing_image = 17,
        making_image_look_purple = 18,
        making_image_look_infrared = 19,
        apply_sepia_filter = 20,
        sharpen_image = 21,
        exit = 22
    };

private:
    static string read_file_name()
    {
        string filename;
        getline(cin >> ws, filename);
        return filename;
    }

    static en_main_screen_option read_main_screen_option()
    {
        int x;
        while (!(cin >> x))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return en_main_screen_option(x);
    }

    static void execute_save_image()
    {
        cout << "Would you like to save the current image to a different file before proceeding? (y/n) ";
        char answer = 'n';
        cin >> answer;

        if (tolower(answer) == 'y')
        {
            cout << "Please, enter the file name: ";
            string fileName = read_file_name();
            currentImage.saveImage(fileName);
        }
        else
            currentImage.saveImage(currentImageName);
    }

    static void execute_load_image_bootup()
    {
        cout << "Please, enter the name of the image you'd like to load: \n";
        currentImageName = read_file_name();
        currentImage.loadNewImage(currentImageName);
    }

    static void execute_load_image()
    {
        execute_save_image();
        cout << "Please, enter the name of the image you'd like to load: \n";
        currentImageName = read_file_name();
        currentImage.loadNewImage(currentImageName);
    }

    static void execute_grayscale_conversion()
    {
        for (int i = 0; i < currentImage.width; ++i) {
            for (int j = 0; j < currentImage.height; ++j) {
                unsigned int avg = 0;
                for (int k = 0; k < 3; ++k) {
                    avg += currentImage(i, j, k);
                }
                avg /= 3;
                currentImage(i, j, 0) = avg;
                currentImage(i, j, 1) = avg;
                currentImage(i, j, 2) = avg;
            }
        }
        cout << "Grayscale applied successfully!\n";
    }

    static void execute_black_and_white_conversion()
    {
        cout << "execute_black_and_white_conversion will be here\n";
    }

    static void execute_inverting_image()
    {
        for (int i = 0; i < currentImage.width; ++i)
        {
            for (int j = 0; j < currentImage.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    currentImage(i, j, k) = 255 - currentImage(i, j, k);
                }
            }
        }
        cout << "Filter applied successfully!\n\n";
    }

    static void execute_adding_image() { cout << "execute_adding_image will be here\n"; }

    static void execute_flipping_image()
    {
        int flipChoice;
        cout << "Do you want to flip (1) Horizontally or (2) Vertically? Enter 1 or 2: ";
        cin >> flipChoice;
        cin.ignore();

        if (flipChoice == 1)
        {
            for (int i = 0; i < currentImage.width / 2; ++i)
            {
                for (int j = 0; j < currentImage.height; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        unsigned int temp = currentImage(i, j, k);
                        currentImage(i, j, k) = currentImage(currentImage.width - 1 - i, j, k);
                        currentImage(currentImage.width - 1 - i, j, k) = temp;
                    }
                }
            }
            cout << "Horizontal flip applied successfully!\n";
        }
        else if (flipChoice == 2)
        {
            for (int i = 0; i < currentImage.width; ++i)
            {
                for (int j = 0; j < currentImage.height / 2; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        unsigned int temp = currentImage(i, j, k);
                        currentImage(i, j, k) = currentImage(i, currentImage.height - 1 - j, k);
                        currentImage(i, currentImage.height - 1 - j, k) = temp;
                    }
                }
            }
            cout << "Vertical flip applied successfully!\n";
        }
    }

    static void execute_rotating_image() { cout << "execute_rotating_image will be here\n"; }
    static void execute_darkening_or_lightening_conversion() { cls_darken_or_lighten_image_screen::run_filter(currentImage); }

    static Image apply_resize(int newWidth, int newHeight)
    {
        Image newImage(newWidth, newHeight);
        float scaleWidth = static_cast<float>(currentImage.width) / newWidth;
        float scaleHeight = static_cast<float>(currentImage.height) / newHeight;
        for (int h = 0; h < newHeight; h++)
        {
            int oldHeightIndex = min(static_cast<int>(h * scaleHeight), currentImage.height - 1);
            for (int w = 0; w < newWidth; w++)
            {
                int oldWidthIndex = min(static_cast<int>(w * scaleWidth), currentImage.width - 1);
                for (int c = 0; c < currentImage.channels; c++)
                {
                    newImage(w, h, c) = currentImage(oldWidthIndex, oldHeightIndex, c);
                }
            }
        }
        return newImage;
    }

    static void execute_resizing_image()
    {
        cout << "\nChoose resizing mode:\n1 Enter explicit new dimensions\n2 Enter scale ratio\nenter choice [1, 2]: ";
        int choice;
        cin >> choice;
        int newWidth, newHeight;
        if (choice == 1) {
            cin >> newWidth >> newHeight;
        }
        else if (choice == 2) {
            float ratio;
            cin >> ratio;
            newWidth = currentImage.width * ratio;
            newHeight = currentImage.height * ratio;
        }
        else return;
        currentImage = apply_resize(newWidth, newHeight);
    }

    static void execute_merging_image() { cout << "Merge logic...\n"; }
    static void execute_detecting_image() { cout << "Detect edges...\n"; }
    static void execute_cropping_image() { cls_execute_cropping_image::run_filter(currentImage, currentImageName); }
    static void execute_blurring_image() { cout << "Blur...\n"; }

    static void execute_making_good_natural_sunlight_to_image()
    {
        for (int i = 0; i < currentImage.width; ++i) {
            for (int j = 0; j < currentImage.height; ++j) {
                int R = min(255, (int)currentImage(i, j, 0) + 40);
                int G = min(255, (int)currentImage(i, j, 1) + 40);
                int B = min(255, (int)currentImage(i, j, 2) + 40);
                currentImage(i, j, 0) = R;
                currentImage(i, j, 1) = G;
                currentImage(i, j, 2) = B;
            }
        }
        cout << "Sunlight Filter applied!\n";
    }

    static void execute_making_image_like_it_is_in_Den_Den_Mushi_television() { cout << "Den Den Mushi...\n"; }
    static void execute_making_image_look_purple() { cout << "Purple...\n"; }

    static void execute_making_image_look_infrared()
    {
        for (int h = 0; h < currentImage.height; h++)
        {
            for (int w = 0; w < currentImage.width; w++)
            {
                currentImage(w, h, 0) = 255;
                currentImage(w, h, 1) = 255 - currentImage(w, h, 1);
                currentImage(w, h, 2) = 255 - currentImage(w, h, 2);
            }
        }
    }

    static void execute_apply_sepia_filter() { cout << "Sepia...\n"; }
    static void execute_sharpen_image() { cout << "Sharpen...\n"; }
    static void execute_exit() { execute_save_image(); }

    static void execute_skewing_image()
    {
        cls_skewing_image_screen::run_filter(currentImage);
    }

    static void execute_main_screen_option(en_main_screen_option option)
    {
        switch (option)
        {
        case load_image:
            system("cls"); execute_load_image(); go_back_to_main_screen(); break;
        case save_image:
            system("cls"); execute_save_image(); go_back_to_main_screen(); break;
        case grayscale_conversion:
            system("cls"); execute_grayscale_conversion(); go_back_to_main_screen(); break;
        case black_and_white_conversion:
            system("cls"); execute_black_and_white_conversion(); go_back_to_main_screen(); break;
        case inverting_image:
            system("cls"); execute_inverting_image(); go_back_to_main_screen(); break;
        case adding_image:
            system("cls"); execute_adding_image(); go_back_to_main_screen(); break;
        case flipping_image:
            system("cls"); execute_flipping_image(); go_back_to_main_screen(); break;
        case rotating_image:
            system("cls"); execute_rotating_image(); go_back_to_main_screen(); break;
        case darkening_or_lightening_conversion:
            system("cls"); execute_darkening_or_lightening_conversion(); go_back_to_main_screen(); break;
        case resizing_image:
            system("cls"); execute_resizing_image(); go_back_to_main_screen(); break;
        case merging_image:
            system("cls"); execute_merging_image(); go_back_to_main_screen(); break;
        case detecting_image:
            system("cls"); execute_detecting_image(); go_back_to_main_screen(); break;
        case cropping_image:
            system("cls"); execute_cropping_image(); go_back_to_main_screen(); break;
        case blurring_image:
            system("cls"); execute_blurring_image(); go_back_to_main_screen(); break;
        case making_good_natural_sunlight_to_image:
            system("cls"); execute_making_good_natural_sunlight_to_image(); go_back_to_main_screen(); break;
        case making_image_like_it_is_in_Den_Den_Mushi_television:
            system("cls"); execute_making_image_like_it_is_in_Den_Den_Mushi_television(); go_back_to_main_screen(); break;
        case skewing_image:
            system("cls"); execute_skewing_image(); go_back_to_main_screen(); break;
        case making_image_look_purple:
            system("cls"); execute_making_image_look_purple(); go_back_to_main_screen(); break;
        case making_image_look_infrared:
            system("cls"); execute_making_image_look_infrared(); go_back_to_main_screen(); break;
        case apply_sepia_filter:
            system("cls"); execute_apply_sepia_filter(); go_back_to_main_screen(); break;
        case sharpen_image:
            system("cls"); execute_sharpen_image(); go_back_to_main_screen(); break;
        case exit:
            execute_exit(); break;
        default:
            break;
        }
    }

    static void execute_main_screen()
    {
        system("cls");
        cout << "[1]  Load image\n";
        cout << "[2]  Save image\n";
        cout << "[3]  Grayscale conversion filter\n";
        cout << "[4]  Black and white conversion filter\n";
        cout << "[5]  Invert image\n";
        cout << "[6]  Add a frame\n";
        cout << "[7]  Flip image\n";
        cout << "[8]  Rotate image\n";
        cout << "[9]  Darken or lighten image\n";
        cout << "[10] Resize image\n";
        cout << "[11] Merge image\n";
        cout << "[12] Detect image edges\n";
        cout << "[13] Crop image\n";
        cout << "[14] Blur image\n";
        cout << "[15] Make a good natural sunlight to image\n";
        cout << "[16] Making image like it is in Den Den Mushi (Television)\n";
        cout << "[17] Image Skewing Filter (Bonus)\n";
        cout << "[18] Make image look purple\n";
        cout << "[19] Make image look infrared\n";
        cout << "[20] Apply sepia filter\n";
        cout << "[21] Sharpen image\n";
        cout << "[22] Exit\n";

        execute_main_screen_option(read_main_screen_option());
    }

public:
    static void Run()
    {
        execute_load_image_bootup();
        execute_main_screen();
    }

private:
    static void go_back_to_main_screen()
    {
        cout << "Press anything to go back to the main screen.....";
        system("pause>0");
        execute_main_screen();
    }
};

Image cls_main_screen::currentImage;
string cls_main_screen::currentImageName;

int main()
{
    cls_main_screen::Run();
}