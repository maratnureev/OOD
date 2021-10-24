#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Lab5/CAbstractCommand.h"
#include "../Lab5/CDeleteItemCommand.h"
#include "../Lab5/CDocumentItem.h"
#include "../Lab5/CHtmlDocument.h"
#include "../Lab5/CImage.h"
#include "../Lab5/CInsertImageCommand.h"
#include "../Lab5/CInsertParagraphCommand.h"
#include "../Lab5/CMenu.h"
#include "../Lab5/CParagraph.h"
#include "../Lab5/CReplaceTextCommand.h"
#include "../Lab5/CResizeImageCommand.h"
#include "../Lab5/CSetTiltleCommand.h"
#include "../Lab5/ICommand.h"
#include "../Lab5/IDocument.h"
#include "../Lab5/IImage.h"
#include "../Lab5/IParagraph.h"
#include "../Lab5/History.h"
#include "../Lab5/HtmlEncoder.h"
#include "CMockCommand.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>


using namespace std;


void IsParagraphValid(IDocument& document, int position, string const& text)
{
	CDocumentItem item = document.GetItem(position);
	shared_ptr<IParagraph> paragraph = item.GetParagraph();
	REQUIRE(paragraph != nullptr);
	REQUIRE(paragraph->GetText() == text);
}

void IsImageValid(IDocument& document, int position, string const& path, int width, int heigth)
{
	CDocumentItem item = document.GetItem(position);
	shared_ptr<IImage> image = item.GetImage();
	REQUIRE(image != nullptr);
	REQUIRE(image->GetPath() == path);
	REQUIRE(image->GetHeight() == heigth);
	REQUIRE(image->GetWidth() == width);
}

SCENARIO("tests paragraph")
{
	CParagraph paragraph("text");
	REQUIRE(paragraph.GetText() == "text");

	paragraph.SetText("new text");
	REQUIRE(paragraph.GetText() == "new text");
}

SCENARIO("tests image")
{
	CImage image("image.jpg", 100, 200);
	REQUIRE(image.GetHeight() == 200);
	REQUIRE(image.GetWidth() == 100);
	REQUIRE(image.GetPath() == "image.jpg");

	image.Resize(150, 350);
	REQUIRE(image.GetHeight() == 350);
	REQUIRE(image.GetWidth() == 150);
}

SCENARIO("tests document item")
{
	shared_ptr<IParagraph> paragraph = make_shared<CParagraph>("text");
	shared_ptr<IImage> image = make_shared<CImage>("file.jpg", 100, 100);
	CDocumentItem item1(nullptr, paragraph);
	CDocumentItem item2(image, nullptr);

	REQUIRE(item1.GetParagraph() == paragraph);
	REQUIRE(item2.GetImage() == image);
}

SCENARIO("tests Document")
{
	CHtmlDocument document;
	REQUIRE(document.GetTitle() == "");
	REQUIRE(document.GetItemsCount() == 0);

	WHEN("set title")
	{
		document.SetTitle("title");
		REQUIRE(document.GetTitle() == "title");
	}
	WHEN("insert paragraph")
	{
		document.InsertParagraph("text", 0);
		REQUIRE(document.GetItemsCount() == 1);
		CDocumentItem item = document.GetItem(0);
		shared_ptr<IParagraph> paragraph = item.GetParagraph();
		shared_ptr<IImage> image = item.GetImage();
		REQUIRE(image == nullptr);
		REQUIRE(paragraph->GetText() == "text");

		REQUIRE_THROWS(document.InsertParagraph("invalid", 2));
		REQUIRE_THROWS(document.GetItem(1));
	}
	WHEN("insert Image")
	{
		ofstream stream("img");
		stream << "test";
		stream.close();
		document.InsertImage("img", 100, 200, 0);
		REQUIRE(document.GetItemsCount() == 1);
		CDocumentItem item = document.GetItem(0);
		shared_ptr<IParagraph> paragraph = item.GetParagraph();
		shared_ptr<IImage> image = item.GetImage();
		REQUIRE(image->GetHeight() == 200);
		REQUIRE(image->GetWidth() == 100);
		REQUIRE(image->GetPath() == "images//image0");
		REQUIRE(paragraph == nullptr);
	}
	WHEN("Delete item")
	{
		document.InsertParagraph("text", 0);
		REQUIRE_THROWS(document.DeleteItem(1));
		document.DeleteItem(0);
		REQUIRE(document.GetItemsCount() == 0);
	}
	WHEN("apply/undo/redo")
	{
		unique_ptr<ICommand> setTitleCommand = make_unique<CSetTitleCommand>(document, "title");
		document.HandleCommand(move(setTitleCommand));
		REQUIRE(document.GetTitle() == "title");
		REQUIRE(document.CanUndo());
		REQUIRE(!document.CanRedo());

		document.Undo();
		REQUIRE(document.GetTitle() == "");
		REQUIRE(!document.CanUndo());
		REQUIRE(document.CanRedo());

		document.Redo();
		REQUIRE(document.GetTitle() == "title");
		REQUIRE(document.CanUndo());
		REQUIRE(!document.CanRedo());
	}
}

SCENARIO("test command set title")
{
	CHtmlDocument document;

	unique_ptr<ICommand> setTitleCommand = make_unique<CSetTitleCommand>(document, "title");
	setTitleCommand->Execute();
	REQUIRE(document.GetTitle() == "title");
	setTitleCommand->Unexecute();
	REQUIRE(document.GetTitle() == "");
}

SCENARIO("test commands insert paragraph")
{
	CHtmlDocument document;

	unique_ptr<ICommand> insertParagraphCommand = make_unique<CInsertParagraphCommand>(document, "text 1", 0);
	insertParagraphCommand->Execute();
	REQUIRE(document.GetItemsCount() == 1);
	IsParagraphValid(document, 0, "text 1");
	insertParagraphCommand->Unexecute();
	REQUIRE(document.GetItemsCount() == 0);
}

SCENARIO("test commands insert image")
{
	ofstream stream("image.jpg");
	stream << "test";
	stream.close();
	CHtmlDocument document;
	unique_ptr<ICommand> insertImageCommand = make_unique<CInsertImageCommand>(document, "image.jpg", 100, 200, 0);
	insertImageCommand->Execute();
	REQUIRE(document.GetItemsCount() == 1);
	IsImageValid(document, 0, "images//image0.jpg", 100, 200);
	insertImageCommand->Unexecute();
	REQUIRE(document.GetItemsCount() == 0);
}

SCENARIO("test commands replace text")
{
	CHtmlDocument document;

	document.InsertParagraph("text", 0);
	unique_ptr<ICommand> replaceTextCommand = make_unique<CReplaceTextCommand>(document, 0, "new Text");
	replaceTextCommand->Execute();
	IsParagraphValid(document, 0, "new Text");
	replaceTextCommand->Unexecute();
	IsParagraphValid(document, 0, "text");
}

SCENARIO("test commands resize image")
{
	CHtmlDocument document;

	document.InsertImage("image.jpg", 100, 200);
	unique_ptr<ICommand> resizeImage = make_unique<CResizeImageCommand>(document, 0, 150, 300);
	resizeImage->Execute();
	IsImageValid(document, 0, "images//image0.jpg", 150, 300);
	resizeImage->Unexecute();
	IsImageValid(document, 0, "images//image0.jpg", 100, 200);
}

SCENARIO("test commands delete item")
{
	CHtmlDocument document;

	document.InsertParagraph("text");
	document.InsertImage("image.jpg", 100, 200);
	REQUIRE(document.GetItemsCount() == 2);
	unique_ptr<ICommand> deleteItem = make_unique<CDeleteItemCommand>(document, 0);
	deleteItem->Execute();
	REQUIRE(document.GetItemsCount() == 1);
	IsImageValid(document, 0, "images//image0.jpg", 100, 200);
	deleteItem->Unexecute();
	REQUIRE(document.GetItemsCount() == 2);
	IsParagraphValid(document, 0, "text");
	IsImageValid(document, 1, "images//image0.jpg", 100, 200);
}


SCENARIO("Test history undo/redo boundaries")
{
	CHistory history;
	unique_ptr<ICommand> mockCommand1 = make_unique<CMockCommand>();
	unique_ptr<ICommand> mockCommand2 = make_unique<CMockCommand>();
	history.AddAndExecuteCommand(move(mockCommand1));
	history.AddAndExecuteCommand(move(mockCommand2));
	REQUIRE(history.CanUndo());
	REQUIRE(!history.CanRedo());
	history.Undo();
	REQUIRE(history.CanUndo());
	REQUIRE(history.CanRedo());
	history.Undo();
	REQUIRE(!history.CanUndo());
	REQUIRE(history.CanRedo());
	history.Redo();
	REQUIRE(history.CanUndo());
	REQUIRE(history.CanRedo());
	history.Redo();
	REQUIRE(history.CanUndo());
	REQUIRE(!history.CanRedo());
}

SCENARIO("test erase history by adding new command")
{
	CHistory history;
	unique_ptr<ICommand> mockCommand1 = make_unique<CMockCommand>();
	unique_ptr<ICommand> mockCommand2 = make_unique<CMockCommand>();

	history.AddAndExecuteCommand(move(mockCommand1));
	history.AddAndExecuteCommand(move(mockCommand2));

	history.Undo();
	history.Undo();
	REQUIRE(!history.CanUndo());
	REQUIRE(history.CanRedo());
	unique_ptr<ICommand> mockCommand3 = make_unique<CMockCommand>();
	history.AddAndExecuteCommand(move(mockCommand3));
	REQUIRE(history.CanUndo());
	REQUIRE(!history.CanRedo());
	history.Undo();
	REQUIRE(!history.CanUndo());
	REQUIRE(history.CanRedo());
}

SCENARIO("Test history maximum")
{
	CHistory history;
	for (int i = 0; i < 11; i++)
	{
		unique_ptr<ICommand> mockCommand = make_unique<CMockCommand>();
		history.AddAndExecuteCommand(move(mockCommand));
	}

	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();
	history.Undo();

	REQUIRE(!history.CanUndo());
	REQUIRE(history.CanRedo());
}

SCENARIO("Handle empty string")
{
	std::string emptyString;
	REQUIRE(HtmlEncode(emptyString) == "");
}

SCENARIO("Handle string with all html characters")
{
	string inString = "Cat <says> \"Meow\". M&M's";
	string outString = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	REQUIRE(HtmlEncode(inString) == outString);
}