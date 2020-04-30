#include <iostream>
#include <unistd.h>

using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STBIW_ZLIB_COMPRESS


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
    cout << "Unable to allocate memory for the gray image" << endl;
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
    stbi_write_jpg("gray.jpg", img.width, img.height, gray_channels, gray_img, 0);

  if (img.format == "png")
    stbi_write_png("gray.png", img.width, img.height, gray_channels, gray_img, img.width * gray_channels);

  free(gray_img);
  return 0;
}


int convert_to_sepia(image &img)
{
  unsigned char *sepia_img = (unsigned char *)malloc(img.size);

  if (sepia_img == nullptr) {
    cout << "Unable to allocate memory for the sepia image" << endl;
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
    stbi_write_jpg("sepia.jpg", img.width, img.height, img.channels, sepia_img, 0);

  if (img.format == "png")
    stbi_write_png("sepia.png", img.width, img.height, img.channels, sepia_img, img.width * img.channels);


  free(sepia_img);
  return 0;
}


int image_quality(image &img)
{
  if (img.img == NULL) {
    cout << "Image upload error" << endl;
    return 1;
  }

  //Добавить готовые пресеты

  int quality_value;
  cout << "quality value[1; 100]: ";
  cin >> quality_value;

  if (img.format == "jpg")
    stbi_write_jpg("compression.jpg", img.width, img.height, img.channels, img.img, quality_value);

  if (img.format == "png") {
    stbi_write_png_compression_level = 40;
    stbi_write_png("compression.png", img.width, img.height, img.channels, img.img, img.width * img.channels);
  }

  return 0;
}
