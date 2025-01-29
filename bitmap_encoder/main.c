/*
 * https://ricardolovelace.com/blog/creating-bitmap-images-with-c-on-windows/
 * https://www-user.tu-chemnitz.de/~heha/hs/chm/petzold.chm/petzoldi/ch15b.htm
 * https://en.wikipedia.org/wiki/BMP_file_format
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

; // clang issue
#pragma pack(push, 1)

// File Header (14 bytes)
// Bitmap Header (40 bytes) image dimensions,color depth and compression
// Pixel Data: actual data
typedef struct {
  uint16_t bftypes;
  uint32_t bfsize;
  uint16_t bfReserved1;
  uint16_t bfReserved2;
  uint32_t bfOffBits;
} BITMAPFILEHEADER;

// Bitmap Info header
typedef struct {
  uint32_t biSize;
  int32_t biWidth;
  int32_t biHeight;
  uint16_t biPlanes;
  uint16_t biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  int32_t biXPelsPerMeter;
  int32_t biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)

void save_bitmap(const char *filename, int width, int height,
                 uint8_t *pixel_data) {
  BITMAPFILEHEADER bfh;
  BITMAPINFOHEADER bih;

  bfh.bftypes = 0x4D42; // ascii 'BM' 0x4D  = 'M' 0x42 = 'B' little-endian
  bfh.bfsize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
               (width * height * 3);
  bfh.bfReserved1 = 0;
  bfh.bfReserved2 = 0;
  bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  bih.biSize = sizeof(BITMAPINFOHEADER);
  bih.biWidth = width;
  bih.biHeight = height;
  bih.biPlanes = 1;
  bih.biBitCount = 24;   // 24 bits per pixel
  bih.biCompression = 0; // No compression
  bih.biSizeImage = width * height * 3;
  bih.biXPelsPerMeter = 2835;
  bih.biYPelsPerMeter = 2835;
  bih.biClrUsed = 0;
  bih.biClrImportant = 0;
  FILE *file = fopen(filename, "wb");
  // write header to file
  fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
  fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, file);

  // write pixer data
  int padding = (4 - (width * 3) % 4) % 4;
  uint8_t padding_bytes[3] = {0, 0, 0};
  for (int y = height - 1; y >= 0; y--) {
    for (int x = 0; x < width; x++) {
      int index = (y * width + x) * 3;
      fwrite(&pixel_data[index + 2], 1, 1, file); // Blue
      fwrite(&pixel_data[index + 1], 1, 1, file); // Green
      fwrite(&pixel_data[index], 1, 1, file);     // Red
    }
    if (padding > 0) {
      fwrite(padding_bytes, 1, padding, file);
    }
  }

  fclose(file);
}

int main() {
  int width = 100;
  int height = 100;
  uint8_t *pixels = malloc(width * height * 3);
  // fill pixel data
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int index = (y * width + x) * 3;
      pixels[index] = 255;   // red
      pixels[index + 1] = 0; // Green
      pixels[index + 2] = 0; // blue
    }
  }
  // make a solid rectangle of 255 color
  save_bitmap("output.bmp", width, height, pixels);
  free(pixels);
  return 0;
}
