#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdint>
#include <iomanip>

using namespace std;

// Пространство имен графической библиотеки (недоступно для изменения)
namespace graphics_lib
{
	// Холст для рисования
	class ICanvas
	{
	public:
		virtual void SetColor(uint32_t rgbColor) = 0;
		// Ставит "перо" в точку x, y
		virtual void MoveTo(int x, int y) = 0;
		// Рисует линию с текущей позиции, передвигая перо в точку x,y 
		virtual void LineTo(int x, int y) = 0;
		virtual ~ICanvas() = default;
	};

	// Реализация холста для рисования
	class CCanvas : public ICanvas
	{
	public:
		void SetColor(uint32_t rgbColor) override
		{
			int red = (rgbColor >> 16) & 0xff;
			int green = (rgbColor >> 8) & 0xff;
			int blue = rgbColor & 0xff;
			cout << "SetColor (#" << setw(2) << setfill('0') << hex << red << setw(2) << setfill('0') << green << setw(2) << setfill('0') << blue << ")" << endl;
		}
		void MoveTo(int x, int y) override
		{
			cout << "MoveTo (" << x << ", " << y << ")" << endl;
		}
		void LineTo(int x, int y) override
		{
			cout << "LineTo (" << x << ", " << y << ")" << endl;
		}
	};
}

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
	struct Point
	{
		int x;
		int y;
	};

	// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
	class ICanvasDrawable
	{
	public:
		virtual void SetCanvasColor(graphics_lib::ICanvas& canvas)const = 0;
		virtual void Draw(graphics_lib::ICanvas& canvas)const = 0;
		virtual ~ICanvasDrawable() = default;
	};

	class CDrawable : public ICanvasDrawable
	{
	protected:
		CDrawable(uint32_t color)
			: m_color(color)
		{
		}

		void SetCanvasColor(graphics_lib::ICanvas& canvas) const override
		{
			canvas.SetColor(m_color);
		}
	private:
		uint32_t m_color;
	};

	class CTriangle : public CDrawable
	{
	public:
		CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t color)
			: m_p1(p1)
			, m_p2(p2)
			, m_p3(p3)
			, CDrawable(color)
		{
		}

		void Draw(graphics_lib::ICanvas& canvas)const override
		{
			SetCanvasColor(canvas);
			canvas.MoveTo(m_p1.x, m_p1.y);
			canvas.LineTo(m_p2.x, m_p2.y);
			canvas.LineTo(m_p3.x, m_p3.y);
			canvas.LineTo(m_p1.x, m_p1.y);
		}
	private:
		Point m_p1;
		Point m_p2;
		Point m_p3;
	};

	class CRectangle : public CDrawable
	{
	public:
		CRectangle(const Point& leftTop, int width, int height, uint32_t color)
			: m_leftTop(leftTop)
			, m_width(width)
			, m_height(height)
			, CDrawable(color)
		{
		}

		void Draw(graphics_lib::ICanvas& canvas)const override
		{
			SetCanvasColor(canvas);
			canvas.MoveTo(m_leftTop.x, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_height, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_height, m_leftTop.y + m_width);
			canvas.LineTo(m_leftTop.x, m_leftTop.y + m_width);
			canvas.LineTo(m_leftTop.x, m_leftTop.y);
		}
	private:
		Point m_leftTop;
		int m_width = 0;
		int m_height = 0;
	};

	// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
	class CCanvasPainter
	{
	public:
		CCanvasPainter(graphics_lib::ICanvas& canvas)
			: m_canvas(canvas)
		{
		}
		void Draw(const ICanvasDrawable& drawable)
		{
			drawable.Draw(m_canvas);
		}
	private:
		graphics_lib::ICanvas& m_canvas;
	};
}

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
		float r, g, b, a;
	};

	// Класс для современного рисования графики
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(ostream& strm)
			: m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			if (m_drawing) // Завершаем рисование, если оно было начато
			{
				EndDraw();
			}
		}

		// Этот метод должен быть вызван в начале рисования
		void BeginDraw()
		{
			if (m_drawing)
			{
				throw logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << endl;
			m_drawing = true;
		}

		// Выполняет рисование линии
		void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
		{
			if (!m_drawing)
			{
				throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}
			m_out << "<line fromX='" << start.x << "' fromY='" << start.y << "' toX='" << end.x << "' toY='" << end.y << "'>" << endl;
			m_out << "<color r='" << color.r << "' g='" << color.g << "' b='" << color.b << "' a='" << color.a << "'/>" << endl;
			m_out << "</line>" << endl;
		}

		// Этот метод должен быть вызван в конце рисования
		void EndDraw()
		{
			if (!m_drawing)
			{
				throw logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << endl;
			m_drawing = false;
		}
	private:
		ostream& m_out;
		bool m_drawing = false;
	};
}

namespace app
{
	class CModernGraphicsRendererAdapter : public graphics_lib::ICanvas
	{
	public:
		CModernGraphicsRendererAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
			: m_renderer(renderer)
			, m_start(0, 0)
			, m_rgba(0, 0, 0, 0)
		{
			m_renderer.BeginDraw();
		}
		~CModernGraphicsRendererAdapter()
		{
			m_renderer.EndDraw();
		}
		void SetColor(uint32_t rgbColor) override
		{
			float red = (float)((rgbColor >> 16) & 0xff);
			float green = (float)((rgbColor >> 8) & 0xff);
			float blue = (float)(rgbColor & 0xff);
			modern_graphics_lib::CRGBAColor rgba(red / 100, green / 100, blue / 100, 1);
			m_rgba = rgba;
		}
		void MoveTo(int x, int y) override
		{
			m_start = modern_graphics_lib::CPoint(x, y);
		}
		void LineTo(int x, int y) override
		{
			modern_graphics_lib::CPoint end(x, y);
			m_renderer.DrawLine(m_start, end, m_rgba);
			m_start = end;
		}
	private:
		modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
		modern_graphics_lib::CPoint m_start;
		modern_graphics_lib::CRGBAColor m_rgba;
	};
}