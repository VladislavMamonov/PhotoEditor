#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <core/mat.hpp>
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace cv;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


struct image
{
  unsigned char *img;
  int width, height, channels;
  size_t size;
  string format;
};


int load_image(image &img, const char *img_name)
{
  img.img = stbi_load(img_name, &img.width, &img.height, &img.channels, 0);
  img.size = img.width * img.height * img.channels;

  int selection;

  cout << "1. JPG format" << endl;
  cout << "2. PNG format" << endl;
  cout << "selection: ";
  cin >> selection;

  if (selection == 1) img.format = "jpg";
  else img.format = "png";

  if (img.img == NULL) {
    cout << "Image upload error" << endl;
    return 1;
  }

  cout << "Loaded image with a width of " << img.width
  << ", a height of " << img.height << " and channels " << img.channels << endl;

  return 0;
}


int convert_to_gray(image &img)
{
  unsigned char *gray_img = (unsigned char *)malloc(img.size);
  int gray_channels = img.channels == 4 ? 2 : 1;

  if (gray_img == nullptr) {
    cout << "Unable to allocate memory for the image" << endl;
    return 1;
  }

  for (unsigned char *p = img.img, *pg = gray_img; p != img.img + img.size;
    p += img.channels, pg += gray_channels) {
    *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
    if (img.channels == 4) {
      *(pg + 1) = *(p + 3);
    }
  }

  if (img.format == "jpg")
    stbi_write_jpg("gray.jpg", img.width, img.height, gray_channels, gray_img, 100);

  if (img.format == "png")
    stbi_write_png("gray.png", img.width, img.height, gray_channels, gray_img, img.width * gray_channels);

  free(gray_img);
  return 0;
}


int convert_to_sepia(image &img)
{
  unsigned char *sepia_img = (unsigned char *)malloc(img.size);

  if (sepia_img == nullptr) {
    cout << "Unable to allocate memory for the image" << endl;
    return 1;
  }

  for (unsigned char *p = img.img, *pg = sepia_img; p != img.img + img.size;
     p += img.channels, pg += img.channels) {
       *pg = (uint8_t)fmin(0.393 * *p + 0.769 * *(p + 1) + 0.189 * *(p + 2), 255.0);         // red
       *(pg + 1) = (uint8_t)fmin(0.349 * *p + 0.686 * *(p + 1) + 0.168 * *(p + 2), 255.0);  // green
       *(pg + 2) = (uint8_t)fmin(0.272 * *p + 0.534 * *(p + 1) + 0.131 * *(p + 2), 255.0);  // blue
      if (img.channels == 4) {
        *(pg + 3) = *(p + 3);
      }
    }

  if (img.format == "jpg")
    stbi_write_jpg("sepia.jpg", img.width, img.height, img.channels, sepia_img, 100);

  if (img.format == "png")
    stbi_write_png("sepia.png", img.width, img.height, img.channels, sepia_img, img.width * img.channels);


  free(sepia_img);
  return 0;
}


int convert_to_negative(image &img)
{
  unsigned char *negative_img = (unsigned char *)malloc(img.size);

  if (negative_img == nullptr) {
    cout << "Unable to allocate memory for the image" << endl;
    return 1;
  }

  for (unsigned char *p = img.img, *pg = negative_img; p != img.img + img.size;
     p += img.channels, pg += img.channels) {
       *pg = (uint8_t)(255.0 - *p);
       *(pg + 1) = (uint8_t)(255.0 - *(p + 1));
       *(pg + 2) = (uint8_t)(255.0 - *(p + 2));
      if (img.channels == 4) {
        *(pg + 3) = *(p + 3);
      }
    }

  if (img.format == "jpg")
    stbi_write_jpg("negative.jpg", img.width, img.height, img.channels, negative_img, 100);

  if (img.format == "png")
    stbi_write_png("negative.png", img.width, img.height, img.channels, negative_img, img.width * img.channels);


  free(negative_img);
  return 0;
}


int sharpening(image &img, const string file_name)
{
  Mat userImg, sharpening_img;
  userImg = imread(file_name, 1);
  sharpening_img = imread(file_name, 1);

  if (userImg.empty()) {
    cout << "Unable to allocate memory for the image" << endl;
    return 1;
  }

  float kernel[9];
  kernel[0] = -1;
  kernel[1] = -1;
  kernel[2] = -1;

  kernel[3] = -1;
  kernel[4] = 9;
  kernel[5] = -1;

  kernel[6] = -1;
  kernel[7] = -1;
  kernel[8] = -1;

  Mat kernel_matrix = Mat(3, 3, CV_32FC1, kernel);
  filter2D(userImg, sharpening_img, -1, kernel_matrix, Point(-1, -1), 0, BORDER_DEFAULT);

  if (img.format == "jpg")
    imwrite("sharpening.jpg", sharpening_img);

  if (img.format == "png")
    imwrite("sharpening.png", sharpening_img);

  return 0;
}


int convert_to_emboss(image &img, const string file_name)
{
  Mat userImg, aquarelle_img;
  userImg = imread(file_name, 1);
  aquarelle_img = imread(file_name, 1);

  if (userImg.empty()) {
    cout << "Unable to allocate memory for the image" << endl;
    return 1;
  }

  float kernel[9];
  kernel[0] = -2;
  kernel[1] = -1;
  kernel[2] = 0;

  kernel[3] = -1;
  kernel[4] = 1;
  kernel[5] = 1;

  kernel[6] = 0;
  kernel[7] = 1;
  kernel[8] = 2;

  Mat kernel_matrix = Mat(3, 3, CV_32FC1, kernel);
  filter2D(userImg, aquarelle_img, -1, kernel_matrix, Point(-1, -1), 0, BORDER_DEFAULT);

  if (img.format == "jpg")
    imwrite("emboss.jpg", aquarelle_img);

  if (img.format == "png")
    imwrite("emboss.png", aquarelle_img);

  return 0;
}


int image_quality(image &img)
{
  if (img.img == NULL) {
    cout << "Image upload error" << endl;
    return 1;
  }


  int quality_value;
  int selection;

  cout << "1. Worst quality[1]" << endl;
  cout << "2. Bad quality[25]" << endl;
  cout << "3. Satisfactory quality[50]" << endl;
  cout << "4. Slight compression[85]" << endl;
  cout << "5. Increase quality[100]" << endl;
  cout << "6. Set quality manually" << endl;

  cout << endl << "selection: ";
  cin >> selection;

  switch (selection) {
    case 1:
      quality_value = 1;
      break;
    case 2:
      quality_value = 25;
      break;
    case 3:
      quality_value = 50;
      break;
    case 4:
      quality_value = 85;
      break;
    case 5:
      quality_value = 100;
      break;
    case 6:
      cout << "quality value[1; 100]: ";
      cin >> quality_value;
      break;
    default:
      quality_value = 100;
      break;
  }

  if (img.format == "jpg")
    stbi_write_jpg("compression.jpg", img.width, img.height, img.channels, img.img, quality_value);

  if (img.format == "png") {
    stbi_write_png("compression.png", img.width, img.height, img.channels, img.img, img.width * img.channels);
  }

  return 0;
}


int image_flip(image &img, const char *img_name)
{
  if (img.img == NULL) {
    cout << "Image upload error" << endl;
    return 1;
  }

  stbi_set_flip_vertically_on_load(1);
  img.img = stbi_load(img_name, &img.width, &img.height, &img.channels, 0);

  if (img.format == "jpg")
    stbi_write_jpg("flip.jpg", img.width, img.height, img.channels, img.img, 100);

  if (img.format == "png")
    stbi_write_png("flip.png", img.width, img.height, img.channels, img.img, img.width * img.channels);

  stbi_set_flip_vertically_on_load(0);
  img.img = stbi_load(img_name, &img.width, &img.height, &img.channels, 0);

  return 0;
}
