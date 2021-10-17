#pragma once
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(const Path& path, int width, int height)
		: m_path(path)
		, m_width(width)
		, m_height(height)
	{
		AssertSizeValid(width);
		AssertSizeValid(height);
	}
	// ���������� ���� ������������ �������� ���������
	Path GetPath()const;
	// ������ ����������� � ��������
	int GetWidth()const;
	// ������ ����������� � ��������
	int GetHeight()const;
	// �������� ������ �����������
	void Resize(int width, int height);
private:
	void AssertSizeValid(int size) const;

	Path m_path;
	int m_width;
	int m_height;
};

