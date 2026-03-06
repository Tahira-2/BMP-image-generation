#include <iostream>
#include <fstream>
#include <vector>

// Force the compiler to not add padding
#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{ 0x4D42 };          // "BM"
    uint32_t file_size{ 0 };               // Total file size
    uint32_t reserved1{ 0 };
    uint32_t offset_data{ 54 };            // Start of pixel data
};

struct BMPInfoHeader {
    uint32_t size{ 40 };                   // Size of this header
    int32_t width{ 0 };
    int32_t height{ 0 };
    uint16_t planes{ 1 };                  // Always 1

    uint16_t bit_count{ 24 };              // 24-bit (BGR)
    uint32_t compression{ 0 };             // 0 
    uint32_t size_image{ 0 };              // 0 for uncompressed
    int32_t x_pixels_per_meter{ 0 };
    int32_t y_pixels_per_meter{ 0 };
    uint32_t colors_used{ 0 };
    uint32_t colors_important{ 0 };
};
#pragma pack(pop)

void write_bmp_header(std::vector<uint8_t>(& data), int w, int h) {
    // Each row must be a multiple of 4 bytes
    int row_stride = w * 3;
    int padded_row_size = ((row_stride + 3) / 4) * 4;

    //Set up headers
    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    
    file_header.file_size = 54 + padded_row_size * h;
    info_header.width = w;
    info_header.height = h;

    //use pointer to the first raw byte of file_header object;
    uint8_t* ptrPixel = reinterpret_cast<uint8_t*>(&file_header);
    //store the bytes to vector
    for (int i = 0; i < 14; i++) {
        data.push_back(*(ptrPixel + i));
    }

    //use the pointer pointing to the first raw byte of info_header
    ptrPixel = reinterpret_cast<uint8_t*>(&info_header);
    //store the bytes to vector
    for (int i = 0; i < 40; i++) {
        data.push_back(*(ptrPixel + i));
    }
}

void write_pixel_data(std::vector<uint8_t>(&data), int width, int height) {
    int row_size = width * 3;
    int row_padding = (4 - (row_size % 4)) % 4;

    //Loop over the rows
    for (int x = 0; x < width; x++) {
        //loop over the colums
        for (int y = 0; y < height; y++) {

            //pixel in BGR format
            int arc = pow((x - 50), 2) + pow((y - 50), 2);
            uint8_t blue;
            uint8_t green;
            uint8_t red;

            if (arc <= pow(30, 2)) {
                blue = 0x00;
                green = 0x00;
                red = 0xFF;
            }
            else {
                blue = 0xFF;
                green = 0xFF;
                red = 0xFF;
            }
            data.push_back(blue);
            data.push_back(green);
            data.push_back(red);
        }

        //for padding
        for (int i = 0; i < row_padding; i++)
            data.push_back(0);
    }
}

void saveBitmap(std::vector<uint8_t>& data) {
    std::ofstream file("circle.bmp", std::ios::binary);

    if (!file)
        return;

    // Write the raw data
    file.write(reinterpret_cast<char*>(data.data()), data.size());
    file.close();
}


int main() {
    int width =100;
    int height = 100;

    //vector to store raw pixel data
    std::vector<uint8_t> pixel_data;

    //get data from header file
    write_bmp_header(pixel_data, width, height);

    //calculate pixel data
    write_pixel_data(pixel_data, width, height);

    //create circle
    saveBitmap(pixel_data);
    return 0;
}