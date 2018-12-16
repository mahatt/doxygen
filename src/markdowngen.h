#ifndef MARKDOWNGEN_H
#define MARKDOWNGEN_H

#include "outputgen.h"
#include "ftextstream.h"

class MarkdownGenerator : public OutputGenerator {
public:
	MarkdownGenerator();
	virtual ~MarkdownGenerator();

	static void init();
    ///////////////////////////////////////////////////////////////
    // generic generator methods
    ///////////////////////////////////////////////////////////////
     void enable();
     void disable() ;
     void enableIf(OutputType o);
     void disableIf(OutputType o);
     void disableIfNot(OutputType o);
     bool isEnabled(OutputType o);
     OutputGenerator *get(OutputType o);
//    void startPlainFile(const char *name);
//    void endPlainFile();
    // TODO: Why is This??
    bool isEnabled();
//    void pushGeneratorState();
//    void popGeneratorState();
     void writeDoc(DocNode *,Definition *ctx,MemberDef *md);


    ///////////////////////////////////////////////////////////////
    // structural output interface
    ///////////////////////////////////////////////////////////////
     void startFile(const char *name,const char *manName,
                           const char *title);
     void writeSearchInfo() ;
     void writeFooter(const char *navPath) ;
     void endFile() ;
     void startIndexSection(IndexSections) ;
     void endIndexSection(IndexSections) ;
     void writePageLink(const char *,bool) ;
     void startProjectNumber() ;
     void endProjectNumber() ;
     void writeStyleInfo(int part) ;
     void startTitleHead(const char *) ;
     void endTitleHead(const char *fileName,const char *name) ;
     void startIndexListItem() ;
     void endIndexListItem()   ;
     void startIndexList() ;
     void endIndexList()   ;
     void startIndexKey() ;
     void endIndexKey()   ;
     void startIndexValue(bool) ;
     void endIndexValue(const char *,bool) ;
     void startIndexItem(const char *ref,const char *file) ;
     void endIndexItem(const char *ref,const char *file) ;
     void startGroupHeader(int) ;
     void endGroupHeader(int) ;
     void startMemberSections() ;
     void endMemberSections() ;
     void startHeaderSection() ;
     void endHeaderSection() ;
     void startMemberHeader(const char *anchor, int typ) ;
     void endMemberHeader() ;
     void startMemberSubtitle() ;
     void endMemberSubtitle() ;
     void startMemberDocList() ;
     void endMemberDocList() ;
     void startMemberList() ;
     void endMemberList() ;
     void startInlineHeader() ;
     void endInlineHeader() ;
     void startAnonTypeScope(int) ;
     void endAnonTypeScope(int) ;
     void startMemberItem(const char *,int,const char *) ;
     void endMemberItem() ;
     void startMemberTemplateParams() ;
     void endMemberTemplateParams(const char *,const char *) ;
     void startMemberGroupHeader(bool) ;
     void endMemberGroupHeader() ;
     void startMemberGroupDocs() ;
     void endMemberGroupDocs() ;
     void startMemberGroup() ;
     void endMemberGroup(bool) ;
     void insertMemberAlign(bool) ;
     void insertMemberAlignLeft(int,bool) ;
     void startMemberDoc(const char *,const char *,
                                const char *,const char *,int,int,bool) ;
     void endMemberDoc(bool) ;
     void startDoxyAnchor(const char *fName,const char *manName,
                                 const char *anchor,const char *name,
                                 const char *args) ;
     void endDoxyAnchor(const char *fileName,const char *anchor) ;
     void writeLatexSpacing() ;
     void writeStartAnnoItem(const char *type,const char *file,
                                    const char *path,const char *name) ;
     void writeEndAnnoItem(const char *name) ;
     void startMemberDescription(const char *anchor,const char *inheritId, bool typ) ;
     void endMemberDescription() ;
     void startMemberDeclaration() ;
     void endMemberDeclaration(const char *anchor,const char *inheritId) ;
     void writeInheritedSectionTitle(const char *id,const char *ref,
                                            const char *file,const char *anchor,
                                            const char *title,const char *name) ;
     void startIndent() ;
     void endIndent() ;
     void writeSynopsis() ;
     void startClassDiagram() ;
     void endClassDiagram(const ClassDiagram &,const char *,const char *) ;
     void startDotGraph() ;
     void endDotGraph(const DotClassGraph &g) ;
     void startInclDepGraph() ;
     void endInclDepGraph(const DotInclDepGraph &g) ;
     void startGroupCollaboration() ;
     void endGroupCollaboration(const DotGroupCollaboration &g) ;
     void startCallGraph() ;
     void endCallGraph(const DotCallGraph &g) ;
     void startDirDepGraph() ;
     void endDirDepGraph(const DotDirDeps &g) ;
     void writeGraphicalHierarchy(const DotGfxHierarchyTable &g) ;
     void startQuickIndices() ;
     void endQuickIndices() ;
     void writeSplitBar(const char *) ;
     void writeNavigationPath(const char *) ;
     void writeLogo() ;
     void writeQuickLinks(bool compact,HighlightedItem hli,const char *file) ;
     void writeSummaryLink(const char *file,const char *anchor,const char *title,bool first) ;
     void startContents() ;
     void endContents() ;
     void startPageDoc(const char *pageTitle);
     void endPageDoc();
     void startTextBlock(bool) ;
     void endTextBlock(bool) ;
     void lastIndexPage() ;
     void startMemberDocPrefixItem() ;
     void endMemberDocPrefixItem() ;
     void startMemberDocName(bool) ;
     void endMemberDocName() ;
     void startParameterType(bool,const char *key) ;
     void endParameterType() ;
     void startParameterName(bool) ;
     void endParameterName(bool,bool,bool) ;
     void startParameterList(bool) ;
     void endParameterList() ;
     void exceptionEntry(const char*,bool) ;

     void startConstraintList(const char *) ;
     void startConstraintParam() ;
     void endConstraintParam() ;
     void startConstraintType() ;
     void endConstraintType() ;
     void startConstraintDocs() ;
     void endConstraintDocs() ;
     void endConstraintList() ;

     void startMemberDocSimple(bool) ;
     void endMemberDocSimple(bool) ;
     void startInlineMemberType() ;
     void endInlineMemberType() ;
     void startInlineMemberName() ;
     void endInlineMemberName() ;
     void startInlineMemberDoc() ;
     void endInlineMemberDoc() ;


     void startLabels() ;
     void writeLabel(const char *,bool) ;
     void endLabels() ;


     void codify(const char *s) ;
     void writeCodeLink(const char *ref,const char *file,const char* anchor,const char *name,const char* tooltip);
     void writeLineNumber(const char *ref,const char *file,const char * anchor,int lineNumber);
     void writeTooltip(const char *id,const DocLinkInfo& docInfo,const char * decl,const char* desc, const SourceLinkInfo& defInfo,const SourceLinkInfo&);
     void startCodeLine(bool hasLineNumbers) ;
     void endCodeLine() ;
     void startFontClass(const char *clsName) ;
     void endFontClass() ;
     void writeCodeAnchor(const char *name) ;
     void setCurrentDoc(Definition *context,const char *anchor,bool isSourceFile) ;
     void addWord(const char *word,bool hiPriority) ;
     void startItemList()  ;
     void startItemListItem()  ;
     void endItemListItem()  ;
     void endItemList()    ;
     void docify(const char *s) ;
     void writeChar(char c) ;
     void writeString(const char *text) ;
     void startParagraph(const char *classDef) ;
     void endParagraph() ;
     void writeObjectLink(const char *ref,const char *file,const char* anchor, const char * name);
     void startHtmlLink(const char *url) ;
     void endHtmlLink() ;
     void startBold()      ;
     void endBold()        ;
     void startTypewriter() ;
     void endTypewriter() ;
     void startEmphasis() ;
     void endEmphasis() ;
     void startCodeFragment() ;
     void endCodeFragment() ;
     void writeRuler() ;
     void startDescription() ;
     void endDescription() ;
     void startDescItem() ;
     void startDescForItem() ;
     void endDescForItem() ;
     void endDescItem() ;
     void startCenter() ;
     void endCenter() ;
     void startSmall() ;
     void endSmall() ;
     void startExamples() ;
     void endExamples() ;
     void startParamList(ParamListTypes t,const char *title) ;
     void endParamList() ;
     void startTitle() ;
     void endTitle()   ;
     void writeAnchor(const char *fileName,const char *name) ;
     void startSection(const char *,const char *,SectionInfo::SectionType) ;
     void endSection(const char *,SectionInfo::SectionType) ;
     void lineBreak(const char *style) ;
     void addIndexItem(const char *s1,const char *s2) ;
     void writeNonBreakableSpace(int) ;
     void startDescTable(const char *title) ;
     void endDescTable() ;
     void startDescTableRow() ;
     void endDescTableRow() ;
     void startDescTableTitle() ;
     void endDescTableTitle() ;
     void startDescTableData() ;
     void endDescTableData() ;
     void startTextLink(const char *file,const char *anchor) ;
     void endTextLink() ;
     void startPageRef() ;
     void endPageRef(const char *,const char *) ;
     void startSubsection() ;
     void endSubsection() ;
     void startSubsubsection() ;
     void endSubsubsection() ;


  protected:
    FTextStream t;
    QFile *file;
    QCString fileName;
    QCString dir;


  private:
    MarkdownGenerator(const MarkdownGenerator &o);
    MarkdownGenerator &operator=(const MarkdownGenerator &o);
};

#endif
