#include "libraries.h"

using namespace std;

// Пространство имен приложения (доступно для модификации)
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
			modern_graphics_lib::CRGBAColor rgba(red/255, green/255, blue/255, 1);
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

	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 999999);
		CRectangle rectangle({ 30, 40 }, 18, 24, 1);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
		CModernGraphicsRendererAdapter rendererAdapter(renderer);
		shape_drawing_lib::CCanvasPainter painter(rendererAdapter);
		PaintPicture(painter);
	}
}

namespace graphics_lib_pro
{
	// Холст для рисования
	class ICanvas
	{
	public:
		// Установка цвета в формате 0xRRGGBB
		virtual void SetColor(uint32_t rgbColor) = 0;
		virtual void MoveTo(int x, int y) = 0;
		virtual void LineTo(int x, int y) = 0;
		virtual ~ICanvas() = default;
	};

	// Реализация холста для рисования
	class CCanvas : public ICanvas
	{
	public:
		void SetColor(uint32_t rgbColor) override
		{
			cout << "SetColor (#" << rgbColor << ")" << endl;
		}
		void MoveTo(int x, int y) override
		{
			// Реализация остается без изменения
		}
		void LineTo(int x, int y) override
		{
			// Реализация остается без изменения
		}
	};
}

int main()
{
	cout << "Should we use new API (y)?";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}

	return 0;
}