#include "CImage.h"
#include <stdexcept>
#include <string>

const int MAX_IMAGE_SIZE = 10000;
const int MIN_IMAGE_SIZE = 1;

Path CImage::GetPath() const
{
    return m_path;
}

int CImage::GetWidth() const
{
    return m_width;
}

int CImage::GetHeight() const
{
    return m_height;
}

void CImage::Resize(int width, int height)
{
    AssertSizeValid(width);
    AssertSizeValid(height);
    m_height = height;
    m_width = width;
}

void CImage::AssertSizeValid(int size) const
{
    if (size > MAX_IMAGE_SIZE || size < MIN_IMAGE_SIZE)
        throw std::invalid_argument("Invalid image size: " + std::to_string(size));
}
