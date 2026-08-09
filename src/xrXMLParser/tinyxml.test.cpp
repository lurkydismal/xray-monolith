#include "stdafx.h"

#include "tinyxml.h"

#include <gtest/gtest.h>

#include <cstring>
#include <string>
#include <vector>

namespace
{

class TinyXmlTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        oldCondenseWhiteSpace = TiXmlBase::IsWhiteSpaceCondensed();
    }

    void TearDown() override
    {
        TiXmlBase::SetCondenseWhiteSpace(oldCondenseWhiteSpace);
    }

    bool oldCondenseWhiteSpace = true;
};

// -----------------------------------------------------------------------------
// Basic construction / node properties
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, DocumentStartsEmpty)
{
    TiXmlDocument doc;

    EXPECT_EQ(doc.Type(), TiXmlNode::DOCUMENT);
    EXPECT_STREQ(doc.Value(), "");
    EXPECT_EQ(doc.FirstChild(), nullptr);
    EXPECT_EQ(doc.LastChild(), nullptr);
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorId(), TiXmlBase::TIXML_NO_ERROR);
}

TEST_F(TinyXmlTest, ElementConstruction)
{
    TiXmlElement element("root");

    EXPECT_EQ(element.Type(), TiXmlNode::ELEMENT);
    EXPECT_STREQ(element.Value(), "root");
    EXPECT_EQ(element.ToElement(), &element);
    EXPECT_EQ(element.ToDocument(), nullptr);
    EXPECT_EQ(element.ToComment(), nullptr);
    EXPECT_EQ(element.ToText(), nullptr);
    EXPECT_EQ(element.ToDeclaration(), nullptr);
    EXPECT_EQ(element.ToUnknown(), nullptr);

    EXPECT_EQ(element.Parent(), nullptr);
    EXPECT_EQ(element.GetDocument(), nullptr);
    EXPECT_TRUE(element.NoChildren());
}

TEST_F(TinyXmlTest, TextConstruction)
{
    TiXmlText text("hello");

    EXPECT_EQ(text.Type(), TiXmlNode::TEXT);
    EXPECT_STREQ(text.Value(), "hello");
    EXPECT_EQ(text.ToText(), &text);
    EXPECT_FALSE(text.CDATA());

    text.SetCDATA(true);

    EXPECT_TRUE(text.CDATA());

    text.SetCDATA(false);

    EXPECT_FALSE(text.CDATA());
}

TEST_F(TinyXmlTest, CommentConstruction)
{
    TiXmlComment comment("hello");

    EXPECT_EQ(comment.Type(), TiXmlNode::COMMENT);
    EXPECT_STREQ(comment.Value(), "hello");
    EXPECT_EQ(comment.ToComment(), &comment);
}

TEST_F(TinyXmlTest, UnknownConstruction)
{
    TiXmlUnknown unknown;

    EXPECT_EQ(unknown.Type(), TiXmlNode::UNKNOWN);
    EXPECT_EQ(unknown.ToUnknown(), &unknown);
}

TEST_F(TinyXmlTest, DeclarationConstruction)
{
    TiXmlDeclaration declaration("1.0", "UTF-8", "yes");

    EXPECT_EQ(declaration.Type(), TiXmlNode::DECLARATION);
    EXPECT_STREQ(declaration.Version(), "1.0");
    EXPECT_STREQ(declaration.Encoding(), "UTF-8");
    EXPECT_STREQ(declaration.Standalone(), "yes");
    EXPECT_EQ(declaration.ToDeclaration(), &declaration);
}

// -----------------------------------------------------------------------------
// DOM linking
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, LinkEndChildBuildsParentChildRelationship)
{
    TiXmlDocument doc;

    auto* root = new TiXmlElement("root");
    auto* child = new TiXmlElement("child");

    EXPECT_EQ(doc.LinkEndChild(root), root);
    EXPECT_EQ(root->LinkEndChild(child), child);

    EXPECT_EQ(doc.FirstChild(), root);
    EXPECT_EQ(doc.LastChild(), root);

    EXPECT_EQ(root->Parent(), &doc);
    EXPECT_EQ(root->GetDocument(), &doc);

    EXPECT_EQ(root->FirstChild(), child);
    EXPECT_EQ(root->LastChild(), child);

    EXPECT_EQ(child->Parent(), root);
    EXPECT_EQ(child->GetDocument(), &doc);

    EXPECT_EQ(child->PreviousSibling(), nullptr);
    EXPECT_EQ(child->NextSibling(), nullptr);
}

TEST_F(TinyXmlTest, LinkEndChildMaintainsSiblingLinks)
{
    TiXmlDocument doc;

    auto* root = new TiXmlElement("root");
    auto* a = new TiXmlElement("a");
    auto* b = new TiXmlElement("b");
    auto* c = new TiXmlElement("c");

    doc.LinkEndChild(root);
    root->LinkEndChild(a);
    root->LinkEndChild(b);
    root->LinkEndChild(c);

    EXPECT_EQ(root->FirstChild(), a);
    EXPECT_EQ(root->LastChild(), c);

    EXPECT_EQ(a->PreviousSibling(), nullptr);
    EXPECT_EQ(a->NextSibling(), b);

    EXPECT_EQ(b->PreviousSibling(), a);
    EXPECT_EQ(b->NextSibling(), c);

    EXPECT_EQ(c->PreviousSibling(), b);
    EXPECT_EQ(c->NextSibling(), nullptr);
}

TEST_F(TinyXmlTest, ClearRemovesAllChildren)
{
    TiXmlDocument doc;

    auto* root = new TiXmlElement("root");
    root->LinkEndChild(new TiXmlElement("a"));
    root->LinkEndChild(new TiXmlElement("b"));

    doc.LinkEndChild(root);

    EXPECT_NE(root->FirstChild(), nullptr);
    EXPECT_NE(root->LastChild(), nullptr);

    root->Clear();

    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
    EXPECT_TRUE(root->NoChildren());

    // Root itself remains alive.
    EXPECT_EQ(doc.RootElement(), root);
}

// -----------------------------------------------------------------------------
// Child/sibling lookup
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, FirstAndLastChildByValue)
{
    TiXmlElement root("root");

    auto* a1 = new TiXmlElement("a");
    auto* b = new TiXmlElement("b");
    auto* a2 = new TiXmlElement("a");

    root.LinkEndChild(a1);
    root.LinkEndChild(b);
    root.LinkEndChild(a2);

    EXPECT_EQ(root.FirstChild("a"), a1);
    EXPECT_EQ(root.LastChild("a"), a2);
    EXPECT_EQ(root.FirstChild("missing"), nullptr);
    EXPECT_EQ(root.LastChild("missing"), nullptr);
}

TEST_F(TinyXmlTest, NextAndPreviousSiblingByValue)
{
    TiXmlElement root("root");

    auto* a1 = new TiXmlElement("a");
    auto* b1 = new TiXmlElement("b");
    auto* a2 = new TiXmlElement("a");
    auto* b2 = new TiXmlElement("b");

    root.LinkEndChild(a1);
    root.LinkEndChild(b1);
    root.LinkEndChild(a2);
    root.LinkEndChild(b2);

    EXPECT_EQ(a1->NextSibling("a"), a2);
    EXPECT_EQ(a1->NextSibling("b"), b1);
    EXPECT_EQ(a2->NextSibling("a"), nullptr);

    EXPECT_EQ(b2->PreviousSibling("b"), b1);
    EXPECT_EQ(b2->PreviousSibling("a"), a2);
    EXPECT_EQ(b1->PreviousSibling("b"), nullptr);
}

TEST_F(TinyXmlTest, IterateChildren)
{
    TiXmlElement root("root");

    auto* a = new TiXmlElement("a");
    auto* b = new TiXmlElement("b");
    auto* c = new TiXmlElement("c");

    root.LinkEndChild(a);
    root.LinkEndChild(b);
    root.LinkEndChild(c);

    EXPECT_EQ(root.IterateChildren(nullptr), a);
    EXPECT_EQ(root.IterateChildren(a), b);
    EXPECT_EQ(root.IterateChildren(b), c);
    EXPECT_EQ(root.IterateChildren(c), nullptr);
}

TEST_F(TinyXmlTest, IterateChildrenByValue)
{
    TiXmlElement root("root");

    auto* a1 = new TiXmlElement("a");
    auto* b = new TiXmlElement("b");
    auto* a2 = new TiXmlElement("a");

    root.LinkEndChild(a1);
    root.LinkEndChild(b);
    root.LinkEndChild(a2);

    EXPECT_EQ(root.IterateChildren("a", nullptr), a1);
    EXPECT_EQ(root.IterateChildren("a", a1), a2);
    EXPECT_EQ(root.IterateChildren("a", a2), nullptr);
}

TEST_F(TinyXmlTest, FirstChildElementSkipsNonElements)
{
    TiXmlElement root("root");

    root.LinkEndChild(new TiXmlComment("comment"));
    root.LinkEndChild(new TiXmlText("text"));

    auto* child = new TiXmlElement("child");
    root.LinkEndChild(child);

    EXPECT_EQ(root.FirstChildElement(), child);
    EXPECT_EQ(root.FirstChildElement("child"), child);
    EXPECT_EQ(root.FirstChildElement("missing"), nullptr);
}

TEST_F(TinyXmlTest, NextSiblingElementSkipsNonElements)
{
    TiXmlElement root("root");

    auto* a = new TiXmlElement("a");
    auto* b = new TiXmlElement("b");

    root.LinkEndChild(a);
    root.LinkEndChild(new TiXmlComment("comment"));
    root.LinkEndChild(new TiXmlText("text"));
    root.LinkEndChild(b);

    EXPECT_EQ(a->NextSiblingElement(), b);
    EXPECT_EQ(a->NextSiblingElement("b"), b);
    EXPECT_EQ(b->NextSiblingElement(), nullptr);
}

// -----------------------------------------------------------------------------
// User data
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, UserDataRoundTrip)
{
    TiXmlElement element("root");

    int value = 42;

    EXPECT_EQ(element.GetUserData(), nullptr);

    element.SetUserData(&value);

    EXPECT_EQ(element.GetUserData(), &value);
    EXPECT_EQ(
        static_cast<const TiXmlElement&>(element).GetUserData(),
        &value);
}

// -----------------------------------------------------------------------------
// Parsing
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, ParseSimpleDocument)
{
    TiXmlDocument doc;

    const char* xml =
        "<root>"
        "<child>hello</child>"
        "</root>";

    const char* result = doc.Parse(&doc, xml);

    EXPECT_NE(result, nullptr);
    EXPECT_FALSE(doc.Error());

    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Value(), "root");

    const TiXmlElement* child = doc.RootElement()->FirstChildElement("child");

    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->GetText(), "hello");
}

TEST_F(TinyXmlTest, ParseNestedDocument)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<root>"
            "  <a>"
            "    <b>value</b>"
            "  </a>"
            "</root>"),
        nullptr);

    ASSERT_FALSE(doc.Error());

    const TiXmlElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const TiXmlElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    const TiXmlElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    EXPECT_STREQ(b->GetText(), "value");
}

TEST_F(TinyXmlTest, ParseAttributes)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<root "
            "name=\"test\" "
            "count=\"42\" "
            "value=\"3.5\" "
            "negative=\"-7\"/>"),
        nullptr);

    ASSERT_FALSE(doc.Error());

    const TiXmlElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    EXPECT_STREQ(root->Attribute("name"), "test");
    EXPECT_STREQ(root->Attribute("missing"), nullptr);

    int count = 0;
    EXPECT_STREQ(root->Attribute("count", &count), "42");
    EXPECT_EQ(count, 42);

    double value = 0;
    EXPECT_STREQ(root->Attribute("value", &value), "3.5");
    EXPECT_DOUBLE_EQ(value, 3.5);

    int negative = 0;
    ASSERT_EQ(root->QueryIntAttribute("negative", &negative), TIXML_SUCCESS);
    EXPECT_EQ(negative, -7);
}

TEST_F(TinyXmlTest, ParseMultipleAttributesAndIterate)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<root first=\"1\" second=\"2\" third=\"3\"/>"),
        nullptr);

    ASSERT_FALSE(doc.Error());

    const TiXmlElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const TiXmlAttribute* attr = root->FirstAttribute();

    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
    EXPECT_STREQ(attr->Value(), "1");

    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "second");
    EXPECT_STREQ(attr->Value(), "2");

    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "third");
    EXPECT_STREQ(attr->Value(), "3");

    EXPECT_EQ(attr->Next(), nullptr);
}

TEST_F(TinyXmlTest, QueryMissingAttribute)
{
    TiXmlDocument doc;

    ASSERT_NE(doc.Parse(&doc,"<root/>"), nullptr);

    int value = 123;

    EXPECT_EQ(
        doc.RootElement()->QueryIntAttribute("missing", &value),
        TIXML_NO_ATTRIBUTE);

    EXPECT_EQ(value, 123);
}

TEST_F(TinyXmlTest, QueryWrongIntegerType)
{
    TiXmlDocument doc;

    ASSERT_NE(doc.Parse(&doc,"<root value=\"hello\"/>"), nullptr);

    int value = 123;

    EXPECT_EQ(
        doc.RootElement()->QueryIntAttribute("value", &value),
        TIXML_WRONG_TYPE);

    EXPECT_EQ(value, 123);
}

TEST_F(TinyXmlTest, QueryWrongDoubleType)
{
    TiXmlDocument doc;

    ASSERT_NE(doc.Parse(&doc,"<root value=\"hello\"/>"), nullptr);

    double value = 123.0;

    EXPECT_EQ(
        doc.RootElement()->QueryDoubleAttribute("value", &value),
        TIXML_WRONG_TYPE);

    EXPECT_DOUBLE_EQ(value, 123.0);
}

TEST_F(TinyXmlTest, AttributeIntegerAndDoubleConversions)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,"<root integer=\"123\" real=\"12.5\"/>"),
        nullptr);

    const TiXmlElement* root = doc.RootElement();

    EXPECT_EQ(root->FirstAttribute()->IntValue(), 123);
    EXPECT_DOUBLE_EQ(root->FirstAttribute()->DoubleValue(), 123.0);

    const TiXmlAttribute* real = root->FirstAttribute()->Next();

    ASSERT_NE(real, nullptr);

    EXPECT_EQ(real->IntValue(), 12);
    EXPECT_DOUBLE_EQ(real->DoubleValue(), 12.5);
}

TEST_F(TinyXmlTest, AttributeSetAndValueModification)
{
    TiXmlAttribute attr("name", "123");

    EXPECT_STREQ(attr.Name(), "name");
    EXPECT_STREQ(attr.Value(), "123");
    EXPECT_EQ(attr.IntValue(), 123);

    attr.SetName("new_name");
    attr.SetValue("456");

    EXPECT_STREQ(attr.Name(), "new_name");
    EXPECT_STREQ(attr.Value(), "456");
    EXPECT_EQ(attr.IntValue(), 456);
}

TEST_F(TinyXmlTest, AttributeSetIntValue)
{
    TiXmlAttribute attr;

    attr.SetIntValue(123456);

    EXPECT_STREQ(attr.Value(), "123456");
    EXPECT_EQ(attr.IntValue(), 123456);
}

TEST_F(TinyXmlTest, AttributeSetDoubleValue)
{
    TiXmlAttribute attr;

    attr.SetDoubleValue(12.5);

    EXPECT_DOUBLE_EQ(attr.DoubleValue(), 12.5);
}

TEST_F(TinyXmlTest, GetTextOnlyReturnsFirstTextChild)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,"<root>hello<child>world</child></root>"),
        nullptr);

    const TiXmlElement* root = doc.RootElement();

    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "hello");
}

TEST_F(TinyXmlTest, GetTextReturnsNullWhenFirstChildIsElement)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,"<root><child>hello</child></root>"),
        nullptr);

    const TiXmlElement* root = doc.RootElement();

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetText(), nullptr);
}

// -----------------------------------------------------------------------------
// XML node types
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, ParseDifferentNodeTypes)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<root>"
            "<!-- comment -->"
            "<child>text</child>"
            "<![CDATA[raw <xml> & text]]>"
            "<!DOCTYPE root>"
            "</root>"),
        nullptr);

    ASSERT_FALSE(doc.Error());

    bool foundDeclaration = false;
    bool foundComment = false;
    bool foundElement = false;
    bool foundText = false;
    bool foundUnknown = false;

    for (const TiXmlNode* node = doc.FirstChild();
         node;
         node = node->NextSibling())
    {
        switch (node->Type())
        {
        case TiXmlNode::DECLARATION:
            foundDeclaration = true;
            break;

        case TiXmlNode::ELEMENT:
            foundElement = true;
            break;

        case TiXmlNode::COMMENT:
            foundComment = true;
            break;

        case TiXmlNode::TEXT:
            foundText = true;
            break;

        case TiXmlNode::UNKNOWN:
            foundUnknown = true;
            break;

        default:
            break;
        }
    }

    EXPECT_TRUE(foundDeclaration);
    EXPECT_TRUE(foundElement);

    // These are useful regression checks for the parser's handling
    // of miscellaneous node types.
    EXPECT_TRUE(foundComment);
    EXPECT_TRUE(foundText);
    EXPECT_TRUE(foundUnknown);
}

TEST_F(TinyXmlTest, ParseCDataPreservesContent)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,"<root><![CDATA[a < b && c > d]]></root>"),
        nullptr);

    const TiXmlElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const TiXmlText* text = root->FirstChild()
        ? root->FirstChild()->ToText()
        : nullptr;

    ASSERT_NE(text, nullptr);

    EXPECT_TRUE(text->CDATA());
    EXPECT_STREQ(text->Value(), "a < b && c > d");
}

// -----------------------------------------------------------------------------
// Entities
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, ParseXmlEntities)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<root>"
            "&amp;"
            "&lt;"
            "&gt;"
            "&quot;"
            "&apos;"
            "</root>"),
        nullptr);

    ASSERT_FALSE(doc.Error());

    const TiXmlElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    ASSERT_NE(root->GetText(), nullptr);

    EXPECT_STREQ(root->GetText(), "&<>\"'");
}

TEST_F(TinyXmlTest, ParseNumericEntities)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,"<root>&#65;&#x42;</root>"),
        nullptr);

    ASSERT_FALSE(doc.Error());

    ASSERT_NE(doc.RootElement(), nullptr);
    ASSERT_NE(doc.RootElement()->GetText(), nullptr);

    EXPECT_STREQ(doc.RootElement()->GetText(), "AB");
}

// -----------------------------------------------------------------------------
// Whitespace
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, CondenseWhitespaceCanBeChanged)
{
    TiXmlBase::SetCondenseWhiteSpace(false);
    EXPECT_FALSE(TiXmlBase::IsWhiteSpaceCondensed());

    TiXmlBase::SetCondenseWhiteSpace(true);
    EXPECT_TRUE(TiXmlBase::IsWhiteSpaceCondensed());
}

TEST_F(TinyXmlTest, CondensedWhitespaceIsParsedConsistently)
{
    TiXmlBase::SetCondenseWhiteSpace(true);

    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,"<root>one   two\n three\tfour</root>"),
        nullptr);

    ASSERT_NE(doc.RootElement(), nullptr);
    ASSERT_NE(doc.RootElement()->GetText(), nullptr);

    EXPECT_STREQ(
        doc.RootElement()->GetText(),
        "one two three four");
}

TEST_F(TinyXmlTest, NonCondensedWhitespaceIsPreserved)
{
    TiXmlBase::SetCondenseWhiteSpace(false);

    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,"<root>one   two\n three\tfour</root>"),
        nullptr);

    ASSERT_NE(doc.RootElement(), nullptr);
    ASSERT_NE(doc.RootElement()->GetText(), nullptr);

    EXPECT_STREQ(
        doc.RootElement()->GetText(),
        "one   two\n three\tfour");
}

// -----------------------------------------------------------------------------
// Locations
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, NodeLocationsAreReported)
{
    TiXmlDocument doc;

    doc.SetTabSize(4);

    ASSERT_NE(
        doc.Parse(&doc,
            "<root>\n"
            "    <child>text</child>\n"
            "</root>"),
        nullptr);

    ASSERT_FALSE(doc.Error());

    const TiXmlElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const TiXmlElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    EXPECT_EQ(root->Row(), 1);
    EXPECT_EQ(root->Column(), 1);

    EXPECT_EQ(child->Row(), 2);
    EXPECT_EQ(child->Column(), 5);
}

TEST_F(TinyXmlTest, TabSizeCanBeDisabled)
{
    TiXmlDocument doc;

    doc.SetTabSize(0);

    ASSERT_NE(
        doc.Parse(&doc,"<root><child/></root>"),
        nullptr);

    EXPECT_EQ(doc.TabSize(), 0);
}

// -----------------------------------------------------------------------------
// Error handling
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, InvalidXmlSetsError)
{
    TiXmlDocument doc;

    const char* result = doc.Parse(&doc,"<root>");

    EXPECT_EQ(result, nullptr);
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorId(), TiXmlBase::TIXML_NO_ERROR);
    EXPECT_NE(doc.ErrorDesc(), nullptr);
    EXPECT_NE(doc.ErrorDesc()[0], '\0');
}

TEST_F(TinyXmlTest, EmptyDocumentReportsError)
{
    TiXmlDocument doc;

    const char* result = doc.Parse(&doc,"");

    EXPECT_EQ(result, nullptr);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorId(), TiXmlBase::TIXML_ERROR_DOCUMENT_EMPTY);
}

TEST_F(TinyXmlTest, ClearErrorResetsErrorState)
{
    TiXmlDocument doc;

    ASSERT_EQ(doc.Parse(&doc,""), nullptr);
    ASSERT_TRUE(doc.Error());

    doc.ClearError();

    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorId(), TiXmlBase::TIXML_NO_ERROR);
    EXPECT_STREQ(doc.ErrorDesc(), "");
    EXPECT_EQ(doc.ErrorRow(), 1);
    EXPECT_EQ(doc.ErrorCol(), 1);
}

TEST_F(TinyXmlTest, SuccessfulParseClearsPreviousError)
{
    TiXmlDocument doc;

    ASSERT_EQ(doc.Parse(&doc,"<root>"), nullptr);
    ASSERT_TRUE(doc.Error());

    ASSERT_NE(doc.Parse(&doc,"<root/>"), nullptr);

    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorId(), TiXmlBase::TIXML_NO_ERROR);
}

// -----------------------------------------------------------------------------
// Document relationships
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, GetDocumentWalksToDocument)
{
    TiXmlDocument doc;

    auto* root = new TiXmlElement("root");
    auto* child = new TiXmlElement("child");
    auto* grandchild = new TiXmlElement("grandchild");

    doc.LinkEndChild(root);
    root->LinkEndChild(child);
    child->LinkEndChild(grandchild);

    EXPECT_EQ(root->GetDocument(), &doc);
    EXPECT_EQ(child->GetDocument(), &doc);
    EXPECT_EQ(grandchild->GetDocument(), &doc);
}

TEST_F(TinyXmlTest, StandaloneNodeHasNoDocument)
{
    TiXmlElement element("root");

    EXPECT_EQ(element.GetDocument(), nullptr);
}

// -----------------------------------------------------------------------------
// Visitor
// -----------------------------------------------------------------------------

class RecordingVisitor final : public TiXmlVisitor
{
public:
    bool VisitEnter(const TiXmlDocument&) override
    {
        events.emplace_back("document-enter");
        return true;
    }

    bool VisitExit(const TiXmlDocument&) override
    {
        events.emplace_back("document-exit");
        return true;
    }

    bool VisitEnter(
        const TiXmlElement& element,
        const TiXmlAttribute*) override
    {
        events.emplace_back(
            std::string("element-enter:") + element.Value());

        return true;
    }

    bool VisitExit(const TiXmlElement& element) override
    {
        events.emplace_back(
            std::string("element-exit:") + element.Value());

        return true;
    }

    bool Visit(const TiXmlText& text) override
    {
        events.emplace_back(
            std::string("text:") + text.Value());

        return true;
    }

    bool Visit(const TiXmlComment& comment) override
    {
        events.emplace_back(
            std::string("comment:") + comment.Value());

        return true;
    }

    bool Visit(const TiXmlDeclaration& declaration) override
    {
        events.emplace_back(
            std::string("declaration:") + declaration.Version());

        return true;
    }

    bool Visit(const TiXmlUnknown& unknown) override
    {
        events.emplace_back(
            std::string("unknown:") + unknown.Value());

        return true;
    }

    std::vector<std::string> events;
};

TEST_F(TinyXmlTest, VisitorTraversesDocumentDepthFirst)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<?xml version=\"1.0\"?>"
            "<root>"
            "<a>hello</a>"
            "<b/>"
            "</root>"),
        nullptr);

    RecordingVisitor visitor;

    ASSERT_TRUE(doc.Accept(&visitor));

    const std::vector<std::string> expected = {
        "document-enter",
        "declaration:1.0",
        "element-enter:root",
        "element-enter:a",
        "text:hello",
        "element-exit:a",
        "element-enter:b",
        "element-exit:b",
        "element-exit:root",
        "document-exit",
    };

    EXPECT_EQ(visitor.events, expected);
}

class StoppingVisitor final : public TiXmlVisitor
{
public:
    bool VisitEnter(const TiXmlDocument&) override
    {
        events.push_back("document-enter");
        return true;
    }

    bool VisitEnter(
        const TiXmlElement& element,
        const TiXmlAttribute*) override
    {
        events.push_back(
            std::string("element-enter:") + element.Value());

        return element.Value() != "stop";
    }

    bool VisitExit(const TiXmlElement& element) override
    {
        events.push_back(
            std::string("element-exit:") + element.Value());

        return true;
    }

    bool Visit(const TiXmlText& text) override
    {
        events.push_back(
            std::string("text:") + text.Value());

        return true;
    }

    bool VisitExit(const TiXmlDocument&) override
    {
        events.push_back("document-exit");
        return true;
    }

    std::vector<std::string> events;
};

TEST_F(TinyXmlTest, VisitorCanStopChildTraversal)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<root>"
            "<before>one</before>"
            "<stop>"
            "  <child>should-not-be-visited</child>"
            "</stop>"
            "<after>three</after>"
            "</root>"),
        nullptr);

    StoppingVisitor visitor;

    ASSERT_TRUE(doc.Accept(&visitor));

    const std::vector<std::string> expected = {
        "document-enter",
        "element-enter:root",
        "element-enter:before",
        "text:one",
        "element-exit:before",
        "element-enter:stop",
        "element-exit:stop",
        "element-enter:after",
        "text:three",
        "element-exit:after",
        "element-exit:root",
        "document-exit",
    };

    EXPECT_EQ(visitor.events, expected);
}

// -----------------------------------------------------------------------------
// UTF-8
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, ParseUtf8Text)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<root>Привет мир — 世界</root>",
            nullptr,
            TIXML_ENCODING_UTF8),
        nullptr);

    ASSERT_FALSE(doc.Error());
    ASSERT_NE(doc.RootElement(), nullptr);
    ASSERT_NE(doc.RootElement()->GetText(), nullptr);

    EXPECT_STREQ(
        doc.RootElement()->GetText(),
        "Привет мир — 世界");
}

TEST_F(TinyXmlTest, ParseUtf8Attribute)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<root name=\"тест\"/>",
            nullptr,
            TIXML_ENCODING_UTF8),
        nullptr);

    ASSERT_FALSE(doc.Error());
    ASSERT_NE(doc.RootElement(), nullptr);

    EXPECT_STREQ(
        doc.RootElement()->Attribute("name"),
        "тест");
}

// -----------------------------------------------------------------------------
// SetValue / ValueTStr / ValueStr
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, SetValueChangesNodeValue)
{
    TiXmlElement element("old");

    EXPECT_STREQ(element.Value(), "old");

    element.SetValue("new");

    EXPECT_STREQ(element.Value(), "new");
    EXPECT_STREQ(element.ValueTStr().c_str(), "new");

#ifdef TIXML_USE_STL
    EXPECT_STREQ(element.ValueStr().c_str(), "new");
#endif
}

TEST_F(TinyXmlTest, SetValueWithString)
{
    TiXmlElement element("old");

    xr_string value = "new value";

    element.SetValue(value);

    EXPECT_STREQ(element.Value(), "new value");
}

// -----------------------------------------------------------------------------
// Parse / DOM consistency
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, ParsedTreeHasCorrectParentRelationships)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<root>"
            "<a>"
            "<b/>"
            "</a>"
            "</root>"),
        nullptr);

    TiXmlElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    TiXmlElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    TiXmlElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    EXPECT_EQ(root->Parent(), &doc);
    EXPECT_EQ(a->Parent(), root);
    EXPECT_EQ(b->Parent(), a);

    EXPECT_EQ(root->GetDocument(), &doc);
    EXPECT_EQ(a->GetDocument(), &doc);
    EXPECT_EQ(b->GetDocument(), &doc);
}

TEST_F(TinyXmlTest, ParsedSiblingOrderingIsPreserved)
{
    TiXmlDocument doc;

    ASSERT_NE(
        doc.Parse(&doc,
            "<root>"
            "<one/>"
            "<two/>"
            "<three/>"
            "</root>"),
        nullptr);

    TiXmlElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    TiXmlElement* one = root->FirstChildElement();
    TiXmlElement* two = one->NextSiblingElement();
    TiXmlElement* three = two->NextSiblingElement();

    ASSERT_NE(one, nullptr);
    ASSERT_NE(two, nullptr);
    ASSERT_NE(three, nullptr);

    EXPECT_STREQ(one->Value(), "one");
    EXPECT_STREQ(two->Value(), "two");
    EXPECT_STREQ(three->Value(), "three");

    EXPECT_EQ(three->NextSiblingElement(), nullptr);
    EXPECT_STREQ(one->Value(), "one");
    EXPECT_STREQ(two->Value(), "two");
    EXPECT_STREQ(three->Value(), "three");

    EXPECT_EQ(three->NextSiblingElement(), nullptr);
}

TEST_F(TinyXmlTest, LinkingDocumentAsChildFails)
{
    TiXmlDocument doc;

    auto* root = new TiXmlElement("root");
    doc.LinkEndChild(root);

    auto* nestedDocument = new TiXmlDocument;

    EXPECT_EQ(root->LinkEndChild(nestedDocument), nullptr);

    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(
        doc.ErrorId(),
        TiXmlBase::TIXML_ERROR_DOCUMENT_TOP_ONLY);

    EXPECT_EQ(root->FirstChild(), nullptr);
}

// -----------------------------------------------------------------------------
// Error strings
// -----------------------------------------------------------------------------

TEST_F(TinyXmlTest, ErrorDescriptionsMatchErrorIds)
{
    struct ErrorCase
    {
        int id;
        const char* description;
    };

    constexpr ErrorCase cases[] = {
        { TiXmlBase::TIXML_NO_ERROR,
          "No error" },

        { TiXmlBase::TIXML_ERROR,
          "Error" },

        { TiXmlBase::TIXML_ERROR_OPENING_FILE,
          "Failed to open file" },

        { TiXmlBase::TIXML_ERROR_OUT_OF_MEMORY,
          "Memory allocation failed." },

        { TiXmlBase::TIXML_ERROR_PARSING_ELEMENT,
          "Error parsing Element." },

        { TiXmlBase::TIXML_ERROR_FAILED_TO_READ_ELEMENT_NAME,
          "Failed to read Element name" },

        { TiXmlBase::TIXML_ERROR_READING_ELEMENT_VALUE,
          "Error reading Element value." },

        { TiXmlBase::TIXML_ERROR_READING_ATTRIBUTES,
          "Error reading Attributes." },

        { TiXmlBase::TIXML_ERROR_PARSING_EMPTY,
          "Error: empty tag." },

        { TiXmlBase::TIXML_ERROR_READING_END_TAG,
          "Error reading end tag." },

        { TiXmlBase::TIXML_ERROR_PARSING_UNKNOWN,
          "Error parsing Unknown." },

        { TiXmlBase::TIXML_ERROR_PARSING_COMMENT,
          "Error parsing Comment." },

        { TiXmlBase::TIXML_ERROR_PARSING_DECLARATION,
          "Error parsing Declaration." },

        { TiXmlBase::TIXML_ERROR_DOCUMENT_EMPTY,
          "Error document empty." },

        { TiXmlBase::TIXML_ERROR_EMBEDDED_NULL,
          "Error null (0) or unexpected EOF found in input stream." },

        { TiXmlBase::TIXML_ERROR_PARSING_CDATA,
          "Error parsing CDATA." },

        { TiXmlBase::TIXML_ERROR_DOCUMENT_TOP_ONLY,
          "Error when TiXmlDocument added to document, because TiXmlDocument can only be at the root." },
    };

    for (const auto& test : cases)
    {
        TiXmlDocument doc;

        // SetError() is public specifically for manipulating the
        // document error state.
        doc.SetError(
            test.id,
            nullptr,
            nullptr,
            TIXML_ENCODING_UNKNOWN);

        EXPECT_TRUE(doc.Error())
            << "Error ID: " << test.id;

        EXPECT_EQ(doc.ErrorId(), test.id)
            << "Error ID: " << test.id;

        EXPECT_STREQ(doc.ErrorDesc(), test.description)
            << "Error ID: " << test.id;
    }
}

TEST_F(TinyXmlTest, EmptyDocumentErrorDescription)
{
    TiXmlDocument doc;

    ASSERT_EQ(doc.Parse(&doc, ""), nullptr);

    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(
        doc.ErrorId(),
        TiXmlBase::TIXML_ERROR_DOCUMENT_EMPTY);

    EXPECT_STREQ(
        doc.ErrorDesc(),
        "Error document empty.");
}

TEST_F(TinyXmlTest, UnterminatedElementError)
{
    TiXmlDocument doc;

    ASSERT_EQ(doc.Parse(&doc, "<root>"), nullptr);

    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorId(), TiXmlBase::TIXML_NO_ERROR);
    EXPECT_STREQ(doc.ErrorDesc(), "Error reading end tag.");
}

TEST_F(TinyXmlTest, UnterminatedCommentError)
{
    TiXmlDocument doc;

    ASSERT_EQ(doc.Parse(&doc, "<!-- comment"), nullptr);

    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(
        doc.ErrorId(),
        TiXmlBase::TIXML_ERROR_PARSING_COMMENT);

    EXPECT_STREQ(
        doc.ErrorDesc(),
        "Error parsing Comment.");
}

TEST_F(TinyXmlTest, UnterminatedCDataError)
{
    TiXmlDocument doc;

    ASSERT_EQ(
        doc.Parse(&doc, "<root><![CDATA[test</root>"),
        nullptr);

    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(
        doc.ErrorId(),
        TiXmlBase::TIXML_ERROR_PARSING_CDATA);

    EXPECT_STREQ(
        doc.ErrorDesc(),
        "Error parsing CDATA.");
}

TEST_F(TinyXmlTest, InvalidDeclarationError)
{
    TiXmlDocument doc;

    ASSERT_EQ(
        doc.Parse(&doc, "<?xml version=\"1.0\""),
        nullptr);

    EXPECT_TRUE(doc.Error());

    EXPECT_EQ(
        doc.ErrorId(),
        TiXmlBase::TIXML_ERROR_PARSING_DECLARATION);

    EXPECT_STREQ(
        doc.ErrorDesc(),
        "Error parsing Declaration.");
}

TEST_F(TinyXmlTest, ClearErrorRestoresDefaultState)
{
    TiXmlDocument doc;

    ASSERT_EQ(doc.Parse(&doc, ""), nullptr);
    ASSERT_TRUE(doc.Error());

    doc.ClearError();

    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorId(), TiXmlBase::TIXML_NO_ERROR);
    EXPECT_STREQ(doc.ErrorDesc(), "No error");
    EXPECT_EQ(doc.ErrorRow(), 1);
    EXPECT_EQ(doc.ErrorCol(), 1);
}

TEST_F(TinyXmlTest, EveryErrorIdHasAnErrorString)
{
    for (int id = 0; id < TiXmlBase::TIXML_ERROR_STRING_COUNT; ++id)
    {
        TiXmlDocument doc;

        doc.SetError(
            id,
            nullptr,
            nullptr,
            TIXML_ENCODING_UNKNOWN);

        EXPECT_NE(doc.ErrorDesc(), nullptr)
            << "Error ID: " << id;

        EXPECT_NE(doc.ErrorDesc()[0], '\0')
            << "Error ID: " << id;
    }
}

} // namespace
