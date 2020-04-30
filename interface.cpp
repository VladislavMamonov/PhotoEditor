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
    cout << "2. Gray Filter" << endl;
    cout << "3. Sepia Filter" << endl;
    cout << "4. Quality settings" << endl;
    cout << "Any key to exit" << endl << endl;

    cout << "Selection: ";
    cin >> selection;

    if (selection == 1) {
      string str;
      cout << "File name: ";
      cin >> str;

      const char *file_name = str.c_str();
      load_image(img, file_name);

      sleep(2);
      system("clear");
    }

    if (selection == 2) {
      convert_to_gray(img);
      sleep(2);
      system("clear");
    }

    if (selection == 3) {
      convert_to_sepia(img);
      sleep(2);
      system("clear");
    }

    if (selection == 4) {
      image_quality(img);
      sleep(2);
      system("clear");
    }

    if (selection < 1 || selection > 4)
      isExit = true;
  }
}


int main()
{
  interface();

  return 0;
}
