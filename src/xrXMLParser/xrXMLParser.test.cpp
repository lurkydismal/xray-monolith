#include "stdafx.h"

#include "xrXMLParser.h"

#include <gtest/gtest.h>

namespace
{

constexpr LPCSTR TEST_XML = R"xml(
<?xml version="1.0" encoding="UTF-8"?>
<root id="42" name="test">
    <item id="10" value="first">hello</item>
    <item id="20" value="second">world</item>
    <item id="30" value="third">
        <nested>nested text</nested>
    </item>

    <group name="group1">
        <entry key="a">100</entry>
        <entry key="b">200</entry>
        <entry key="a">300</entry>
    </group>

    <mixed>
        <!-- comment -->
        <element>element text</element>
        <element>another text</element>
    </mixed>
</root>
)xml";

class CXmlTest : public ::testing::Test
{
protected:
    CXml xml;

    void SetUp() override
    {
        xml.LoadFromString(TEST_XML);
    }
};

} // namespace

// -----------------------------------------------------------------------------
// Loading / root
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, LoadFromStringCreatesRoot)
{
    ASSERT_NE(xml.GetRoot(), nullptr);
    EXPECT_EQ(xml.GetRoot()->Type(), TiXmlNode::ELEMENT);
    EXPECT_STREQ(xml.GetRoot()->Value(), "root");
}

TEST_F(CXmlTest, RootElementIsSameAsGetRoot)
{
    ASSERT_NE(xml.GetRoot(), nullptr);
    EXPECT_EQ(xml.GetRoot(), xml.GetRoot()->ToElement());
}

TEST_F(CXmlTest, LocalRootDefaultsToNull)
{
    EXPECT_EQ(xml.GetLocalRoot(), nullptr);
}

TEST_F(CXmlTest, SetLocalRootChangesNavigationRoot)
{
    XML_NODE* group = xml.NavigateToNode("group");

    ASSERT_NE(group, nullptr);
    xml.SetLocalRoot(group);

    EXPECT_EQ(xml.GetLocalRoot(), group);
    EXPECT_EQ(xml.NavigateToNode("entry", 0), group->FirstChild("entry"));
    EXPECT_STREQ(xml.Read("entry", 0, "missing"), "100");
}

TEST_F(CXmlTest, ClearingLocalRootRestoresDocumentRoot)
{
    XML_NODE* group = xml.NavigateToNode("group");
    ASSERT_NE(group, nullptr);

    xml.SetLocalRoot(group);
    ASSERT_EQ(xml.NavigateToNode("entry", 0), group->FirstChild("entry"));

    xml.SetLocalRoot(nullptr);

    EXPECT_EQ(xml.NavigateToNode("item", 0), xml.GetRoot()->FirstChild("item"));
}

// -----------------------------------------------------------------------------
// NavigateToNode
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, NavigateToNodeFindsDirectChild)
{
    XML_NODE* node = xml.NavigateToNode("item");

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->Value(), "item");
    EXPECT_STREQ(xml.Read(node, "missing"), "hello");
}

TEST_F(CXmlTest, NavigateToNodeSelectsNodeByIndex)
{
    XML_NODE* first = xml.NavigateToNode("item", 0);
    XML_NODE* second = xml.NavigateToNode("item", 1);
    XML_NODE* third = xml.NavigateToNode("item", 2);

    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);
    ASSERT_NE(third, nullptr);

    EXPECT_STREQ(xml.Read(first, ""), "hello");
    EXPECT_STREQ(xml.Read(second, ""), "world");
    EXPECT_STREQ(xml.Read(third, ""), "");
}

TEST_F(CXmlTest, NavigateToNodeReturnsNullForOutOfRangeIndex)
{
    EXPECT_EQ(xml.NavigateToNode("item", 3), nullptr);
    EXPECT_EQ(xml.NavigateToNode("item", 100), nullptr);
}

TEST_F(CXmlTest, NavigateToNodeReturnsNullForMissingNode)
{
    EXPECT_EQ(xml.NavigateToNode("does_not_exist"), nullptr);
}

TEST_F(CXmlTest, NavigateToNodeSupportsColonSeparatedPath)
{
    XML_NODE* node = xml.NavigateToNode("group:entry", 0);

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->Value(), "entry");
    EXPECT_STREQ(xml.Read(node, ""), "100");
}

TEST_F(CXmlTest, NavigateToNodeSupportsNestedColonSeparatedPath)
{
    XML_NODE* node = xml.NavigateToNode("group:entry", 1);

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(xml.Read(node, ""), "200");
}

TEST_F(CXmlTest, NavigateToNodeCanSelectIndexedFirstPathComponent)
{
    // Two "item" nodes exist before any nested navigation.
    XML_NODE* node = xml.NavigateToNode("item", 1);

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(xml.Read(node, ""), "world");
}

TEST_F(CXmlTest, NavigateToNodeFromExplicitStartNode)
{
    XML_NODE* group = xml.NavigateToNode("group");
    ASSERT_NE(group, nullptr);

    XML_NODE* entry = xml.NavigateToNode(group, "entry", 1);

    ASSERT_NE(entry, nullptr);
    EXPECT_STREQ(xml.Read(entry, ""), "200");
}

TEST_F(CXmlTest, NavigateToNodeFromExplicitStartNodeDoesNotUseDocumentRoot)
{
    XML_NODE* group = xml.NavigateToNode("group");
    ASSERT_NE(group, nullptr);

    EXPECT_EQ(xml.NavigateToNode(group, "item", 0), nullptr);
}

// -----------------------------------------------------------------------------
// Read
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, ReadReturnsElementText)
{
    EXPECT_STREQ(xml.Read("item", 0, "default"), "hello");
    EXPECT_STREQ(xml.Read("item", 1, "default"), "world");
}

TEST_F(CXmlTest, ReadReturnsDefaultForMissingNode)
{
    EXPECT_STREQ(xml.Read("missing", 0, "default"), "default");
}

TEST_F(CXmlTest, ReadReturnsDefaultForNodeWithoutText)
{
    XML_NODE* item = xml.NavigateToNode("item", 2);
    ASSERT_NE(item, nullptr);

    EXPECT_STREQ(xml.Read(item, "default"), "default");
}

TEST_F(CXmlTest, ReadCanReadFromExplicitStartNode)
{
    XML_NODE* group = xml.NavigateToNode("group");
    ASSERT_NE(group, nullptr);

    EXPECT_STREQ(
        xml.Read(group, "entry", 0, "default"),
        "100");

    EXPECT_STREQ(
        xml.Read(group, "entry", 1, "default"),
        "200");
}

TEST_F(CXmlTest, ReadIntConvertsText)
{
    EXPECT_EQ(xml.ReadInt("group:entry", 0, -1), 100);
    EXPECT_EQ(xml.ReadInt("group:entry", 1, -1), 200);
}

TEST_F(CXmlTest, ReadIntReturnsDefaultForMissingNode)
{
    EXPECT_EQ(xml.ReadInt("missing", 0, 1234), 1234);
}

TEST_F(CXmlTest, ReadFltConvertsText)
{
    EXPECT_FLOAT_EQ(xml.ReadFlt("group:entry", 0, -1.0f), 100.0f);
    EXPECT_FLOAT_EQ(xml.ReadFlt("group:entry", 1, -1.0f), 200.0f);
}

TEST_F(CXmlTest, ReadFltReturnsDefaultForMissingNode)
{
    EXPECT_FLOAT_EQ(xml.ReadFlt("missing", 0, 12.5f), 12.5f);
}

// -----------------------------------------------------------------------------
// Attributes
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, ReadAttribReturnsAttribute)
{
    EXPECT_STREQ(xml.ReadAttrib("item", 0, "id", "missing"), "10");
    EXPECT_STREQ(xml.ReadAttrib("item", 1, "value", "missing"), "second");
}

TEST_F(CXmlTest, ReadAttribReturnsDefaultForMissingAttribute)
{
    EXPECT_STREQ(
        xml.ReadAttrib("item", 0, "missing", "default"),
        "default");
}

TEST_F(CXmlTest, ReadAttribReturnsDefaultForMissingNode)
{
    EXPECT_STREQ(
        xml.ReadAttrib("missing", 0, "id", "default"),
        "default");
}

TEST_F(CXmlTest, ReadAttribCanStartAtExplicitNode)
{
    XML_NODE* group = xml.NavigateToNode("group");
    ASSERT_NE(group, nullptr);

    EXPECT_STREQ(
        xml.ReadAttrib(group, "entry", 1, "key", "default"),
        "b");
}

TEST_F(CXmlTest, ReadAttribDirectlyFromNode)
{
    XML_NODE* item = xml.NavigateToNode("item", 1);
    ASSERT_NE(item, nullptr);

    EXPECT_STREQ(xml.ReadAttrib(item, "id", "default"), "20");
}

TEST_F(CXmlTest, ReadAttribIntConvertsValue)
{
    EXPECT_EQ(xml.ReadAttribInt("item", 0, "id", -1), 10);
    EXPECT_EQ(xml.ReadAttribInt("item", 1, "id", -1), 20);
    EXPECT_EQ(xml.ReadAttribInt("item", 2, "id", -1), 30);
}

TEST_F(CXmlTest, ReadAttribIntReturnsDefaultForMissingAttribute)
{
    EXPECT_EQ(
        xml.ReadAttribInt("item", 0, "missing", 123),
        123);
}

TEST_F(CXmlTest, ReadAttribFltConvertsValue)
{
    EXPECT_FLOAT_EQ(
        xml.ReadAttribFlt("item", 0, "id", -1.0f),
        10.0f);
}

TEST_F(CXmlTest, ReadAttribFltReturnsDefaultForMissingAttribute)
{
    EXPECT_FLOAT_EQ(
        xml.ReadAttribFlt("item", 0, "missing", 12.5f),
        12.5f);
}

// -----------------------------------------------------------------------------
// GetNodesNum
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, GetNodesNumCountsDirectChildren)
{
    EXPECT_EQ(xml.GetNodesNum(xml.GetRoot(), "item"), 3);
    EXPECT_EQ(xml.GetNodesNum(xml.GetRoot(), "group"), 1);
    EXPECT_EQ(xml.GetNodesNum(xml.GetRoot(), "mixed"), 1);
}

TEST_F(CXmlTest, GetNodesNumReturnsZeroForMissingTag)
{
    EXPECT_EQ(xml.GetNodesNum(xml.GetRoot(), "missing"), 0);
}

TEST_F(CXmlTest, GetNodesNumCanCountAllChildren)
{
    EXPECT_EQ(xml.GetNodesNum(xml.GetRoot(), nullptr), 4);
}

TEST_F(CXmlTest, GetNodesNumCanUsePath)
{
    EXPECT_EQ(xml.GetNodesNum("group", 0, "entry"), 3);
}

TEST_F(CXmlTest, GetNodesNumCanUseNestedPath)
{
    EXPECT_EQ(xml.GetNodesNum("group:entry", 0, "entry"), 0);
}

TEST_F(CXmlTest, GetNodesNumUsesRootWhenPathDoesNotExist)
{
    // This is current implementation behavior:
    //
    //   if NavigateToNode() returns null, node is replaced with root.
    //
    // Therefore this does NOT return zero.
    EXPECT_EQ(xml.GetNodesNum("missing", 0, "item"), 3);
}

// -----------------------------------------------------------------------------
// SearchForAttribute
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, SearchForAttributeFindsMatchingNode)
{
    XML_NODE* node =
        xml.SearchForAttribute("group", 0, "entry", "key", "b");

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->Value(), "entry");
    EXPECT_STREQ(xml.Read(node, ""), "200");
}

TEST_F(CXmlTest, SearchForAttributeReturnsNullWhenAttributeDoesNotMatch)
{
    EXPECT_EQ(
        xml.SearchForAttribute(
            "group",
            0,
            "entry",
            "key",
            "does-not-exist"),
        nullptr);
}

TEST_F(CXmlTest, SearchForAttributeReturnsNullWhenTagDoesNotMatch)
{
    EXPECT_EQ(
        xml.SearchForAttribute(
            "group",
            0,
            "item",
            "id",
            "10"),
        nullptr);
}

TEST_F(CXmlTest, SearchForAttributeSearchesDescendants)
{
    XML_NODE* node =
        xml.SearchForAttribute(
            "root",
            0,
            "entry",
            "key",
            "b");

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(xml.Read(node, ""), "200");
}

TEST_F(CXmlTest, SearchForAttributeCanFindFirstMatchingDuplicate)
{
    XML_NODE* node =
        xml.SearchForAttribute(
            "group",
            0,
            "entry",
            "key",
            "a");

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(xml.Read(node, ""), "100");
}

// -----------------------------------------------------------------------------
// NavigateToNodeWithAttribute
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, NavigateToNodeWithAttributeFindsNode)
{
    XML_NODE* node =
        xml.NavigateToNodeWithAttribute("item", "id", "20");

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(xml.Read(node, ""), "world");
}

TEST_F(CXmlTest, NavigateToNodeWithAttributeReturnsNullWhenNotFound)
{
    EXPECT_EQ(
        xml.NavigateToNodeWithAttribute("item", "id", "999"),
        nullptr);
}

TEST_F(CXmlTest, NavigateToNodeWithAttributeUsesLocalRoot)
{
    XML_NODE* group = xml.NavigateToNode("group");
    ASSERT_NE(group, nullptr);

    xml.SetLocalRoot(group);

    XML_NODE* node =
        xml.NavigateToNodeWithAttribute("entry", "key", "b");

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(xml.Read(node, ""), "200");
}

// -----------------------------------------------------------------------------
// Node navigation
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, FirstChildElementSkipsNonElements)
{
    XML_NODE* mixed = xml.NavigateToNode("mixed");
    ASSERT_NE(mixed, nullptr);

    XML_NODE* first = mixed->FirstChildElement();

    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "element");
}

TEST_F(CXmlTest, FirstChildElementByNameFindsElement)
{
    XML_NODE* mixed = xml.NavigateToNode("mixed");
    ASSERT_NE(mixed, nullptr);

    XML_NODE* element = mixed->FirstChildElement("element");

    ASSERT_NE(element, nullptr);
    EXPECT_STREQ(xml.Read(element, ""), "element text");
}

TEST_F(CXmlTest, NextSiblingElementSkipsNonElements)
{
    XML_NODE* mixed = xml.NavigateToNode("mixed");
    ASSERT_NE(mixed, nullptr);

    XML_NODE* first = mixed->FirstChildElement();
    ASSERT_NE(first, nullptr);

    XML_NODE* second = first->NextSiblingElement();

    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(xml.Read(second, ""), "another text");
}

TEST_F(CXmlTest, FirstAndLastChildByValue)
{
    XML_NODE* root = xml.GetRoot();
    ASSERT_NE(root, nullptr);

    XML_NODE* first = root->FirstChild("item");
    XML_NODE* last = root->LastChild("item");

    ASSERT_NE(first, nullptr);
    ASSERT_NE(last, nullptr);

    EXPECT_STREQ(xml.Read(first, ""), "hello");
    EXPECT_STREQ(xml.Read(last, ""), "");
}

TEST_F(CXmlTest, SiblingTraversalWorks)
{
    XML_NODE* first = xml.NavigateToNode("item", 0);
    ASSERT_NE(first, nullptr);

    XML_NODE* second = first->NextSibling("item");
    ASSERT_NE(second, nullptr);

    XML_NODE* third = second->NextSibling("item");
    ASSERT_NE(third, nullptr);

    EXPECT_STREQ(xml.Read(second, ""), "world");
    EXPECT_STREQ(xml.Read(third, ""), "");
    EXPECT_EQ(third->NextSibling("item"), nullptr);
}

// -----------------------------------------------------------------------------
// Node type / casts
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, ElementHasCorrectTypeAndCast)
{
    XML_NODE* root = xml.GetRoot();

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Type(), TiXmlNode::ELEMENT);
    EXPECT_EQ(root->ToElement(), root);
    EXPECT_EQ(root->ToText(), nullptr);
    EXPECT_EQ(root->ToComment(), nullptr);
    EXPECT_EQ(root->ToDeclaration(), nullptr);
}

TEST_F(CXmlTest, TextHasCorrectTypeAndCast)
{
    XML_NODE* item = xml.NavigateToNode("item", 0);
    ASSERT_NE(item, nullptr);

    XML_NODE* text = item->FirstChild();

    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->Type(), TiXmlNode::TEXT);
    EXPECT_EQ(text->ToText(), text);
    EXPECT_STREQ(text->Value(), "hello");
}

#if 0
TEST_F(CXmlTest, ParentAndDocumentNavigation)
{
    XML_NODE* item = xml.NavigateToNode("item", 0);
    ASSERT_NE(item, nullptr);

    EXPECT_EQ(item->Parent(), xml.GetRoot());
    EXPECT_EQ(item->GetDocument(), &xml.GetRoot()->GetDocument()[0]);
}
#endif

TEST_F(CXmlTest, ParentAndDocumentNavigation)
{
    XML_NODE* item = xml.NavigateToNode("item", 0);
    ASSERT_NE(item, nullptr);

    EXPECT_EQ(item->Parent(), xml.GetRoot());
    EXPECT_EQ(item->GetDocument(), xml.GetRoot()->GetDocument());
}

// -----------------------------------------------------------------------------
// Reloading / clearing
// -----------------------------------------------------------------------------

TEST_F(CXmlTest, LoadFromStringReplacesPreviousDocument)
{
    ASSERT_NE(xml.GetRoot(), nullptr);
    EXPECT_STREQ(xml.GetRoot()->Value(), "root");

    xml.LoadFromString("<new_root><value>123</value></new_root>");

    ASSERT_NE(xml.GetRoot(), nullptr);
    EXPECT_STREQ(xml.GetRoot()->Value(), "new_root");
    EXPECT_EQ(xml.NavigateToNode("item"), nullptr);
    EXPECT_STREQ(xml.Read("value", 0, "missing"), "123");
}

TEST_F(CXmlTest, ClearInternalRemovesDocumentNodes)
{
    ASSERT_NE(xml.GetRoot(), nullptr);

    xml.ClearInternal();

    EXPECT_EQ(xml.GetRoot(), nullptr);
}

TEST_F(CXmlTest, LoadFromStringAfterClearWorks)
{
    xml.ClearInternal();
    ASSERT_EQ(xml.GetRoot(), nullptr);

    xml.LoadFromString("<root><value>hello</value></root>");

    ASSERT_NE(xml.GetRoot(), nullptr);
    EXPECT_STREQ(xml.Read("value", 0, "missing"), "hello");
}

// -----------------------------------------------------------------------------
// Visitor
// -----------------------------------------------------------------------------

namespace
{

class RecordingVisitor final : public TiXmlVisitor
{
public:
    int documents = 0;
    int elements = 0;
    int comments = 0;
    int texts = 0;
    int declarations = 0;
    int unknowns = 0;

    bool VisitEnter(const TiXmlDocument&) override
    {
        ++documents;
        return true;
    }

    bool VisitEnter(
        const TiXmlElement&,
        const TiXmlAttribute*) override
    {
        ++elements;
        return true;
    }

    bool Visit(const TiXmlComment&) override
    {
        ++comments;
        return true;
    }

    bool Visit(const TiXmlText&) override
    {
        ++texts;
        return true;
    }

    bool Visit(const TiXmlDeclaration&) override
    {
        ++declarations;
        return true;
    }

    bool Visit(const TiXmlUnknown&) override
    {
        ++unknowns;
        return true;
    }
};

} // namespace

TEST_F(CXmlTest, VisitorVisitsDocumentTree)
{
    RecordingVisitor visitor;

    ASSERT_TRUE(xml.GetRoot()->GetDocument()->Accept(&visitor));

    EXPECT_EQ(visitor.documents, 1);
    EXPECT_EQ(visitor.elements, 12);
    EXPECT_EQ(visitor.comments, 1);
    EXPECT_GT(visitor.texts, 0);
}

// -----------------------------------------------------------------------------
// DEBUG-only behavior
// -----------------------------------------------------------------------------

#ifdef DEBUG

TEST_F(CXmlTest, CheckUniqueAttribReturnsNullWhenValuesAreUnique)
{
    XML_NODE* root = xml.GetRoot();

    ASSERT_NE(root, nullptr);

    EXPECT_EQ(
        xml.CheckUniqueAttrib(root, "item", "id"),
        nullptr);
}

TEST_F(CXmlTest, CheckUniqueAttribFindsDuplicate)
{
    XML_NODE* group = xml.NavigateToNode("group");

    ASSERT_NE(group, nullptr);

    EXPECT_STREQ(
        xml.CheckUniqueAttrib(group, "entry", "key"),
        "a");
}

TEST_F(CXmlTest, CheckUniqueAttribReturnsNullForMissingTag)
{
    XML_NODE* root = xml.GetRoot();

    ASSERT_NE(root, nullptr);

    EXPECT_EQ(
        xml.CheckUniqueAttrib(root, "missing", "id"),
        nullptr);
}

#endif // DEBUG
