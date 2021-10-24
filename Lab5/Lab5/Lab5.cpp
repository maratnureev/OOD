#include <string>
#include <iostream>
#include <memory>
#include <filesystem>
#include <optional>
#include "CHtmlDocument.h"
#include "CSetTiltleCommand.h"
#include "CInsertImageCommand.h"
#include "CInsertParagraphCommand.h"
#include "CReplaceTextCommand.h"
#include "CResizeImageCommand.h"
#include "CDeleteItemCommand.h"
#include "CMenu.h"

using namespace std;

typedef filesystem::path Path;

class IParagraph;
class IImage;

using namespace std::placeholders;

namespace
{

	class CEditor
	{
	public:
		CEditor(istream& in, ostream& out)
			: m_document(make_unique<CHtmlDocument>())
			, m_menu(in, out)
		{
			m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
			m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
			AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
			AddMenuItem("insertParagraph", "Insert paragraph into given position. Args: <position>|end <text>", &CEditor::InsertParagraph);
			AddMenuItem("insertImage", "Insert image into given position. Args: <position>|end <width> <height> <path>", &CEditor::InsertImage);
			AddMenuItem("list", "List all document items and title", &CEditor::List);
			AddMenuItem("replaceText", "Replace text in paragraph in given position. Args: <position> <text>", &CEditor::ReplaceText);
			AddMenuItem("resizeImage", "Resize image in given position. Args: <position> <width> <height>", &CEditor::ResizeImage);
			AddMenuItem("deleteItem", "Remove item in given position. Args: <position>", &CEditor::DeleteItem);
			AddMenuItem("save", "Save file in given path. Args: <path>", &CEditor::Save);
			AddMenuItem("undo", "Undo command", &CEditor::Undo);
			AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
		}

		void Start()
		{
			m_menu.Run();
		}

	private:
		// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
		typedef void (CEditor::* MenuHandler)(istream& in);

		void AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
		{
			m_menu.AddItem(shortcut, description, bind(handler, this, _1));
		}

		void SetTitle(istream& in)
		{
			string head;
			string tail;

			if (in >> head)
			{
				getline(in, tail);
			}
			string title = head + tail;

			std::unique_ptr<ICommand> command = make_unique<CSetTitleCommand>(*m_document, title);
			m_document->HandleCommand(move(command));
		}

		void InsertParagraph(istream& in)
		{
			string position;
			string text;
			in >> position;
			getline(in, text);
			optional<size_t> numberPosition = nullopt;
			if (position != "end")
				numberPosition = stoi(position);

			std::unique_ptr<ICommand> command = make_unique<CInsertParagraphCommand>(*m_document, text, numberPosition);
			m_document->HandleCommand(move(command));
		}

		void InsertImage(istream& in)
		{
			string position;
			int width = 0;
			int height = 0;
			Path path;
			in >> position >> width >> height >> path;
			optional<size_t> numberPosition = nullopt;
			if (position != "end")
				numberPosition = stoi(position);

			std::unique_ptr<ICommand> command = make_unique<CInsertImageCommand>(*m_document, path, width, height, numberPosition);
			m_document->HandleCommand(move(command));
		}

		void ReplaceText(istream& in)
		{
			size_t position;
			string text;
			in >> position >> text;

			std::unique_ptr<ICommand> command = make_unique<CReplaceTextCommand>(*m_document, position, text);
			m_document->HandleCommand(move(command));
		}

		void ResizeImage(istream& in)
		{
			size_t position;
			int width;
			int height;
			in >> position >> width >> height;

			std::unique_ptr<ICommand> command = make_unique<CResizeImageCommand>(*m_document, position, width, height);
			m_document->HandleCommand(move(command));
		}

		void DeleteItem(istream& in)
		{
			size_t position;
			in >> position;

			std::unique_ptr<ICommand> command = make_unique<CDeleteItemCommand>(*m_document, position);
			m_document->HandleCommand(move(command));
		}

		void List(istream&)
		{
			cout << m_document->GetTitle() << endl;
			for (size_t i = 0; i < m_document->GetItemsCount(); i++)
			{
				auto item = m_document->GetItem(i);
				auto paragraph = item.GetParagraph();
				auto image = item.GetImage();
				cout << i << ".";
				if (paragraph != nullptr)
					cout << " Paragraph: " << paragraph->GetText() << endl;
				else
					cout << " Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << endl;
			}
		}

		void Undo(istream&)
		{
			if (m_document->CanUndo())
			{
				m_document->Undo();
			}
			else
			{
				cout << "Can't undo" << endl;
			}
		}

		void Redo(istream&)
		{
			if (m_document->CanRedo())
			{
				m_document->Redo();
			}
			else
			{
				cout << "Can't redo" << endl;
			}
		}

		void Save(istream& in)
		{
			Path path;
			in >> path;

			m_document->Save(path);
		}

		CMenu m_menu;
		unique_ptr<IDocument> m_document;
	};

}

int main()
{
	CEditor editor(cin, cout);
	editor.Start();
	return 0;
}