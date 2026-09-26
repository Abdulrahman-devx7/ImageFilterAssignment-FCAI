#include <iostream>
#include <stdlib.h>
#include <string>
#include "Image_Class.h"
using namespace std;

class cls_darken_or_lighten_image_screen
{
private:
    enum submenuChoice
    {
        darken_image = 1,
        lighten_image = 2
    };

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
    
    static void execute_lighten_image(Image &target)
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

    static void execute_darken_image(Image &target)
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

    static void run_chosen_filter(const submenuChoice option, Image &target)
    {
        switch (option)
        {
        case submenuChoice::darken_image:

            system("cls");
            execute_darken_image(target);
            break;

        case submenuChoice::lighten_image:
            system("cls");
            execute_lighten_image(target);
            break;
        }
        cout << "Filter applied successfully!\n\n";
    }

public:
    static void run_filter(Image &target)
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

    static void determineSaveDestination(Image &originalImage,Image &croppedImage, const string &imageFileName)
    {
        cout << "Do you want to save this image to a new file? (y/n)\n\nWARNING: Choosing 'n' would overwrite the current image in the system\n";

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
    static void run_filter(Image &target, const string &imageFileName)
    {
        Image croppedImage = applyFilter(target);
        cout << "Cropping applied successfully!\n\n";
        determineSaveDestination(target, croppedImage, imageFileName);
    }
};

class cls_main_screen
{
private:
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
        making_image_look_purple = 17,
        making_image_look_infrared = 18,
        apply_sepia_filter = 19,
        sharpen_image = 20,
        exit = 21
    };

    static Image currentImage;
    static string currentImageName;

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
    }

    static void execute_grayscale_conversion()
    {
        cout << "execute_grayscale_conversion will be here\n";
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

    static void execute_adding_image()
    {
        cout << "execute_adding_image will be here\n";
    }

    static void execute_flipping_image()
    {
        cout << "execute_flipping_image will be here\n";
    }

    static void execute_rotating_image()
    {
        cout << "execute_rotating_image will be here\n";
    }

    static void execute_darkening_or_lightening_conversion()
    {
        cls_darken_or_lighten_image_screen::run_filter(currentImage);
    }

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
        cout << "\nChoose resizing mode:\n";
        cout << "1 Enter explicit new dimensions (width & height)\n";
        cout << "2 Enter scale ratio (like 0.5 for half, 2 for double)\n";
        cout << "enter choice [1, 2]: ";
        int choice;
        cin >> choice;

        int newWidth, newHeight;
        if (choice == 1)
        {
            cout << "enter new width and new height: ";
            cin >> newWidth >> newHeight;
        }
        else if (choice == 2)
        {
            float ratio;
            cout << "enter scale ratio (max = 20): ";
            cin >> ratio;
            if (ratio > 20)
                ratio = 20;
            newWidth = currentImage.width * ratio;
            newHeight = currentImage.height * ratio;
        }
        else
        {
            cout << "Invalid\n";
            return;
        }

        if (newWidth <= 0 || newHeight <= 0)
        {
            cout << "Invalid\n";
            return;
        }

        currentImage = apply_resize(newWidth, newHeight);
    }

    static void execute_merging_image()
    {
        cout << "execute_merging_image will be here\n";
    }

    static void execute_detecting_image()
    {
        cout << "execute_detecting_image will be here\n";
    }

    static void execute_cropping_image()
    {
        cls_execute_cropping_image::run_filter(currentImage, currentImageName);
    }

    static void execute_blurring_image()
    {
        cout << "execute_blurring_image will be here\n";
    }

    static void execute_making_good_natural_sunlight_to_image()
    {
        cout << "execute_making_good_natural_sunlight_to_image will be here\n";
    }

    static void execute_making_image_like_it_is_in_Den_Den_Mushi_television()
    {
        cout << "execute_making_image_like_it_is_in_Den_Den_Mushi_television will be here\n";
    }

    static void execute_making_image_look_purple()
    {
        cout << "execute_making_image_look_purple will be here\n";
    }

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

    static void execute_apply_sepia_filter()
    {
        cout << "execute_apply_sepia_filter will be here\n";
    }

    static void execute_sharpen_image()
    {
        cout << "execute_sharpen_image will be here\n";
    }

    static void execute_exit()
    {
        execute_save_image();
    }

    static void execute_main_screen_option(en_main_screen_option option)
    {
        switch (option)
        {
        case cls_main_screen::load_image:
            system("cls");
            execute_load_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::save_image:
            system("cls");
            execute_save_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::grayscale_conversion:
            system("cls");
            execute_grayscale_conversion();
            go_back_to_main_screen();
            break;

        case cls_main_screen::black_and_white_conversion:
            system("cls");
            execute_black_and_white_conversion();
            go_back_to_main_screen();
            break;

        case cls_main_screen::inverting_image:
            system("cls");
            execute_inverting_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::adding_image:
            system("cls");
            execute_adding_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::flipping_image:
            system("cls");
            execute_flipping_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::rotating_image:
            system("cls");
            execute_rotating_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::darkening_or_lightening_conversion:
            system("cls");
            execute_darkening_or_lightening_conversion();
            go_back_to_main_screen();
            break;

        case cls_main_screen::resizing_image:
            system("cls");
            execute_resizing_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::merging_image:
            system("cls");
            execute_merging_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::detecting_image:
            system("cls");
            execute_detecting_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::cropping_image:
            system("cls");
            execute_cropping_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::blurring_image:
            system("cls");
            execute_blurring_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::making_good_natural_sunlight_to_image:
            system("cls");
            execute_making_good_natural_sunlight_to_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::making_image_like_it_is_in_Den_Den_Mushi_television:
            system("cls");
            execute_making_image_like_it_is_in_Den_Den_Mushi_television();
            go_back_to_main_screen();
            break;

        case cls_main_screen::making_image_look_purple:
            system("cls");
            execute_making_image_look_purple();
            go_back_to_main_screen();
            break;

        case cls_main_screen::making_image_look_infrared:
            system("cls");
            execute_making_image_look_infrared();
            go_back_to_main_screen();
            break;

        case cls_main_screen::apply_sepia_filter:
            system("cls");
            execute_apply_sepia_filter();
            go_back_to_main_screen();
            break;

        case cls_main_screen::sharpen_image:
            system("cls");
            execute_sharpen_image();
            go_back_to_main_screen();
            break;

        case cls_main_screen::exit:
            execute_exit();
            break;

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
        cout << "[17] Make image look purple\n";
        cout << "[18] Make image infrared\n";
        cout << "[19] Apply sepia filter\n";
        cout << "[20] Sharpen image\n";
        cout << "[21] Exit\n";
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