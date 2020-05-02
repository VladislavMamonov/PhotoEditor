#include "editor.hpp"


void interface()
{
  image img;
  string str;
  int selection;
  bool isExit = false;

  while (isExit == false)
  {
    cout << "_______________" << endl << endl;
    cout << "PHOTO EDITOR" << endl;
    cout << "_______________" << endl << endl;

    cout << "1. Load image" << endl;
    cout << "2. Gray filter" << endl;
    cout << "3. Sepia filter" << endl;
    cout << "4. Negative filter" << endl;
    cout << "5. Sharpening" << endl;
    cout << "6. Emboss filter" << endl;
    cout << "7. Quality settings(jpg only)" << endl;
    cout << "8. Image rotation" << endl;
    cout << "Any key to exit" << endl << endl;

    cout << "Selection: ";
    cin >> selection;

    const char *file_name;
    static string str;

    switch (selection)
    {
      case 1: {
        cout << "File name: ";
        cin >> str;

        file_name = str.c_str();
        load_image(img, file_name);

        sleep(2);
        system("clear");
        break;
      }

      case 2:
        convert_to_gray(img);
        sleep(2);
        system("clear");
        break;

      case 3:
        convert_to_sepia(img);
        sleep(2);
        system("clear");
        break;

      case 4:
        convert_to_negative(img);
        sleep(2);
        system("clear");
        break;

      case 5:
        sharpening(img, str);
        sleep(2);
        system("clear");
        break;

      case 6:
        convert_to_emboss(img, str);
        sleep(2);
        system("clear");
        break;

      case 7:
        image_quality(img);
        sleep(2);
        system("clear");
        break;

      case 8:
        image_flip(img, file_name);
        sleep(2);
        system("clear");
        break;

      default:
        isExit = true;
        break;
    }
  }
}


int main()
{
  interface();

  return 0;
}
