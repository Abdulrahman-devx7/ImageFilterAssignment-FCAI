#include <iostream>
#include <stdlib.h>
#include <string>
#include "Image_Class.h"
using namespace std;

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

    static string read_file_name()
    {
        string filename;
        cin.ignore();
        cin.clear();
        getline(cin, filename);

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

    static bool execute_save_image()
    {
        cout << "Would you like to save the current image to a different file before proceeding? (y/n) ";
        char answer = 'n';
        cin >> answer;

        if (tolower(answer) == 'y')
        {
            cout << "Please, enter the file name: ";

            string fileName = read_file_name();
            return currentImage.saveImage(fileName);
        }
    }

    static bool execute_load_image()
    {
        cout << "Please, enter the name of the image you'd like to load: \n";
        string fileName = read_file_name();

        return currentImage.loadNewImage(fileName);
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
        cout << "execute_inverting_image will be here\n";
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
        cout << "execute_darkening_or_lightening_conversion will be here\n";
    }

    static void execute_resizing_image()
    {
        cout << "execute_resizing_image will be here\n";
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
        cout << "execute_cropping_image will be here\n";
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
        cout << "execute_image_look_infrared will be here\n";
    }

    static void execute_apply_sepia_filter()
    {
        cout << "execute_apply_sepia_filter will be here\n";
    }

    static void execute_sharpen_image()
    {
        cout << "execute_sharpen_image will be here\n";
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
        if(execute_load_image())
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

int main()
{
    
    cls_main_screen::Run();
}