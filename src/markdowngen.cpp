#include <stdlib.h>

#include <assert.h>
#include <qdir.h>
#include <qregexp.h>
#include "message.h"
#include "markdowngen.h"
#include "config.h"
#include "util.h"
#include "doxygen.h"
#include "logos.h"
#include "diagram.h"
#include "version.h"
#include "dot.h"
#include "language.h"
#include "htmlhelp.h"
#include "docparser.h"
#include "htmldocvisitor.h"
#include "searchindex.h"
#include "pagedef.h"
#include "debug.h"
#include "dirdef.h"
#include "vhdldocgen.h"
#include "layout.h"
#include "image.h"
#include "ftvhelp.h"
#include "bufstr.h"
#include "resourcemgr.h"

//#define DBG_MARKDOWN(x) x;


MarkdownGenerator::MarkdownGenerator() : OutputGenerator(){ // @suppress("Class members should be properly initialized")
	dir = Config_getString(MARKDOWN_OUTPUT);
}

MarkdownGenerator::~MarkdownGenerator(){

}
void MarkdownGenerator::init(){
	  QCString dname=Config_getString(MARKDOWN_OUTPUT);
	  QDir d(dname);
	  if (!d.exists() && !d.mkdir(dname))
	  {
	    err("Could not create output directory %s\n",dname.data());
	    exit(1);
	  }
	  // FIXIT:   What is SubDir???
	  createSubDirs(d);
}


void MarkdownGenerator::enable(){}
void MarkdownGenerator::disable() {}
void MarkdownGenerator::enableIf(OutputType o){}
void MarkdownGenerator::disableIf(OutputType o){}
void MarkdownGenerator::disableIfNot(OutputType o){}
bool MarkdownGenerator::isEnabled(OutputType o){ return true; }  // TODO : WHy is this>

OutputGenerator *MarkdownGenerator::get(OutputType o){}
//    void startPlainFile(const char *name);
//    void endPlainFile();

//    void pushGeneratorState();
//    void popGeneratorState();
void MarkdownGenerator::writeDoc(DocNode *,Definition *ctx,MemberDef *md){}


///////////////////////////////////////////////////////////////
// structural output interface
///////////////////////////////////////////////////////////////
void MarkdownGenerator::startFile(const char *name,const char *manName,
                      const char *title){}
void MarkdownGenerator::writeSearchInfo() {}
void MarkdownGenerator::writeFooter(const char *navPath) {}
void MarkdownGenerator::endFile() {}
void MarkdownGenerator::startIndexSection(IndexSections) {}
void MarkdownGenerator::endIndexSection(IndexSections) {}
void MarkdownGenerator::writePageLink(const char *,bool) {}
void MarkdownGenerator::startProjectNumber() {}
void MarkdownGenerator::endProjectNumber() {}
void MarkdownGenerator::writeStyleInfo(int part) {}
void MarkdownGenerator::startTitleHead(const char *) {}
void MarkdownGenerator::endTitleHead(const char *fileName,const char *name) {}
void MarkdownGenerator::startIndexListItem() {}
void MarkdownGenerator::endIndexListItem()  {}
void MarkdownGenerator::startIndexList() {}
void MarkdownGenerator::endIndexList()   {}
void MarkdownGenerator::startIndexKey() {}
void MarkdownGenerator::endIndexKey() {}
void MarkdownGenerator::startIndexValue(bool) {}
void MarkdownGenerator::endIndexValue(const char *,bool) {}
void MarkdownGenerator::startIndexItem(const char *ref,const char *file) {}
void MarkdownGenerator::endIndexItem(const char *ref,const char *file) {}
void MarkdownGenerator::startGroupHeader(int) {}
void MarkdownGenerator::endGroupHeader(int) {}
void MarkdownGenerator::startMemberSections() {}
void MarkdownGenerator::endMemberSections() {}
void MarkdownGenerator::startHeaderSection() {}
void MarkdownGenerator::endHeaderSection() {}
void MarkdownGenerator::startMemberHeader(const char *anchor, int typ) {}
void MarkdownGenerator::endMemberHeader() {}
void MarkdownGenerator::startMemberSubtitle() {}
void MarkdownGenerator::endMemberSubtitle() {}
void MarkdownGenerator::startMemberDocList() {}
void MarkdownGenerator::endMemberDocList() {}
void MarkdownGenerator::startMemberList() {}
void MarkdownGenerator::endMemberList() {}
void MarkdownGenerator::startInlineHeader() {}
void MarkdownGenerator::endInlineHeader() {}
void MarkdownGenerator::startAnonTypeScope(int) {}
void MarkdownGenerator::endAnonTypeScope(int) {}
void MarkdownGenerator::startMemberItem(const char *,int,const char *) {}
void MarkdownGenerator::endMemberItem() {}
void MarkdownGenerator::startMemberTemplateParams() {}
void MarkdownGenerator::endMemberTemplateParams(const char *,const char *) {}
void MarkdownGenerator::startMemberGroupHeader(bool) {}
void MarkdownGenerator::endMemberGroupHeader() {}
void MarkdownGenerator::startMemberGroupDocs() {}
void MarkdownGenerator::endMemberGroupDocs() {}
void MarkdownGenerator::startMemberGroup() {}
void MarkdownGenerator::endMemberGroup(bool) {}
void MarkdownGenerator::insertMemberAlign(bool) {}
void MarkdownGenerator::insertMemberAlignLeft(int,bool) {}
void MarkdownGenerator::startMemberDoc(const char *,const char *,
                           const char *,const char *,int,int,bool) {}
void MarkdownGenerator::endMemberDoc(bool) {}
void MarkdownGenerator::startDoxyAnchor(const char *fName,const char *manName,
                            const char *anchor,const char *name,
                            const char *args) {}
void MarkdownGenerator::endDoxyAnchor(const char *fileName,const char *anchor) {}
void MarkdownGenerator::writeLatexSpacing() {}
void MarkdownGenerator::writeStartAnnoItem(const char *type,const char *file,
                               const char *path,const char *name) {}
void MarkdownGenerator::writeEndAnnoItem(const char *name) {}
void MarkdownGenerator::startMemberDescription(const char *anchor,const char *inheritId, bool typ) {}
void MarkdownGenerator::endMemberDescription() {}
void MarkdownGenerator::startMemberDeclaration() {}
void MarkdownGenerator::endMemberDeclaration(const char *anchor,const char *inheritId) {}
void MarkdownGenerator::writeInheritedSectionTitle(const char *id,const char *ref,
                                       const char *file,const char *anchor,
                                       const char *title,const char *name) {}
void MarkdownGenerator::startIndent() {}
void MarkdownGenerator::endIndent() {}
void MarkdownGenerator::writeSynopsis() {}
void MarkdownGenerator::startClassDiagram() {}
void MarkdownGenerator::endClassDiagram(const ClassDiagram &,const char *,const char *) {}
void MarkdownGenerator::startDotGraph() {}
void MarkdownGenerator::endDotGraph(const DotClassGraph &g) {}
void MarkdownGenerator::startInclDepGraph() {}
void MarkdownGenerator::endInclDepGraph(const DotInclDepGraph &g) {}
void MarkdownGenerator::startGroupCollaboration() {}
void MarkdownGenerator::endGroupCollaboration(const DotGroupCollaboration &g) {}
void MarkdownGenerator::startCallGraph() {}
void MarkdownGenerator::endCallGraph(const DotCallGraph &g) {}
void MarkdownGenerator::startDirDepGraph() {}
void MarkdownGenerator::endDirDepGraph(const DotDirDeps &g) {}
void MarkdownGenerator::writeGraphicalHierarchy(const DotGfxHierarchyTable &g) {}
void MarkdownGenerator::startQuickIndices() {}
void MarkdownGenerator::endQuickIndices() {}
void MarkdownGenerator::writeSplitBar(const char *) {}
void MarkdownGenerator::writeNavigationPath(const char *) {}
void MarkdownGenerator::writeLogo() {}
void MarkdownGenerator::writeQuickLinks(bool compact,HighlightedItem hli,const char *file) {}
void MarkdownGenerator::writeSummaryLink(const char *file,const char *anchor,const char *title,bool first) {}
void MarkdownGenerator::startContents() {}
void MarkdownGenerator::endContents() {}
void MarkdownGenerator::startPageDoc(const char *pageTitle) {}
void MarkdownGenerator::endPageDoc() {}
void MarkdownGenerator::startTextBlock(bool) {}
void MarkdownGenerator::endTextBlock(bool) {}
void MarkdownGenerator::lastIndexPage() {}
void MarkdownGenerator::startMemberDocPrefixItem() {}
void MarkdownGenerator::endMemberDocPrefixItem() {}
void MarkdownGenerator::startMemberDocName(bool) {}
void MarkdownGenerator::endMemberDocName() {}
void MarkdownGenerator::startParameterType(bool,const char *key) {}
void MarkdownGenerator::endParameterType() {}
void MarkdownGenerator::startParameterName(bool) {}
void MarkdownGenerator::endParameterName(bool,bool,bool) {}
void MarkdownGenerator::startParameterList(bool) {}
void MarkdownGenerator::endParameterList() {}
void MarkdownGenerator::exceptionEntry(const char*,bool) {}

void MarkdownGenerator::startConstraintList(const char *) {}
void MarkdownGenerator::startConstraintParam() {}
void MarkdownGenerator::endConstraintParam() {}
void MarkdownGenerator::startConstraintType() {}
void MarkdownGenerator::endConstraintType() {}
void MarkdownGenerator::startConstraintDocs() {}
void MarkdownGenerator::endConstraintDocs() {}
void MarkdownGenerator::endConstraintList(){}

void MarkdownGenerator::startMemberDocSimple(bool) {}
void MarkdownGenerator::endMemberDocSimple(bool) {}
void MarkdownGenerator::startInlineMemberType() {}
void MarkdownGenerator::endInlineMemberType() {}
void MarkdownGenerator::startInlineMemberName() {}
void MarkdownGenerator::endInlineMemberName() {}
void MarkdownGenerator::startInlineMemberDoc() {}
void MarkdownGenerator::endInlineMemberDoc() {}

void MarkdownGenerator::startLabels() {}
void MarkdownGenerator::writeLabel(const char *,bool) {}
void MarkdownGenerator::endLabels(){}


 void MarkdownGenerator::startItemList()  {}
 void MarkdownGenerator::startItemListItem()  {}
 void MarkdownGenerator::endItemListItem()  {}
 void MarkdownGenerator::endItemList()    {}
 void MarkdownGenerator::docify(const char *s) {}
 void MarkdownGenerator::writeChar(char c) {}
 void MarkdownGenerator::writeString(const char *text) {}
 void MarkdownGenerator::startParagraph(const char *classDef) {}
 void MarkdownGenerator::endParagraph() {}
 void MarkdownGenerator::writeObjectLink(const char *ref,const char *file,
                             const char *anchor, const char *name) {}
 void MarkdownGenerator::startHtmlLink(const char *url) {}
 void MarkdownGenerator::endHtmlLink() {}
 void MarkdownGenerator::startBold()      {}
 void MarkdownGenerator::endBold()        {}
 void MarkdownGenerator::startTypewriter() {}
 void MarkdownGenerator::endTypewriter() {}
 void MarkdownGenerator::startEmphasis() {}
 void MarkdownGenerator::endEmphasis() {}
 void MarkdownGenerator::startCodeFragment() {}
 void MarkdownGenerator::endCodeFragment() {}

 void MarkdownGenerator::writeRuler() {}
 void MarkdownGenerator::startDescription() {}
 void MarkdownGenerator::endDescription() {}
 void MarkdownGenerator::startDescItem() {}
 void MarkdownGenerator::startDescForItem() {}
 void MarkdownGenerator::endDescForItem() {}
 void MarkdownGenerator::endDescItem() {}
 void MarkdownGenerator::startCenter() {}
 void MarkdownGenerator::endCenter() {}
 void MarkdownGenerator::startSmall() {}
 void MarkdownGenerator::endSmall() {}

 void MarkdownGenerator::startExamples() {}
 void MarkdownGenerator::endExamples() {}
 void MarkdownGenerator::startParamList(ParamListTypes t,const char *title) {}
 void MarkdownGenerator::endParamList() {}

 void MarkdownGenerator::startTitle() {}
 void MarkdownGenerator::endTitle()   {}

 void MarkdownGenerator::writeAnchor(const char *fileName,const char *name) {}
 void MarkdownGenerator::startSection(const char *,const char *,SectionInfo::SectionType) {}
 void MarkdownGenerator::endSection(const char *,SectionInfo::SectionType) {}

 void MarkdownGenerator::lineBreak(const char *style) {}
 void MarkdownGenerator::addIndexItem(const char *s1,const char *s2) {}

 void MarkdownGenerator::writeNonBreakableSpace(int) {}
 void MarkdownGenerator::startDescTable(const char *title) {}
 void MarkdownGenerator::endDescTable() {}
 void MarkdownGenerator::startDescTableRow() {}
 void MarkdownGenerator::endDescTableRow() {}
 void MarkdownGenerator::startDescTableTitle() {}
 void MarkdownGenerator::endDescTableTitle() {}
 void MarkdownGenerator::startDescTableData() {}
 void MarkdownGenerator::endDescTableData() {}
 void MarkdownGenerator::startTextLink(const char *file,const char *anchor) {}
 void MarkdownGenerator::endTextLink() {}
 void MarkdownGenerator::startPageRef() {}
 void MarkdownGenerator::endPageRef(const char *,const char *) {}
 void MarkdownGenerator::startSubsection() {}
 void MarkdownGenerator::endSubsection() {}
 void MarkdownGenerator::startSubsubsection() {}
 void MarkdownGenerator::endSubsubsection() {}



 // CodeInterfaceBase???
  void MarkdownGenerator::codify(const char *s) {}
  void MarkdownGenerator::writeCodeLink(const char *ref,const char *file,
                            const char *anchor,const char *name,
                            const char *tooltip) {}
  void MarkdownGenerator::writeLineNumber(const char *ref,const char *file,
                              const char *anchor,int lineNumber) {}
  void MarkdownGenerator::writeTooltip(const char *id,
                           const DocLinkInfo &docInfo,
                           const char *decl,
                           const char *desc,
                           const SourceLinkInfo &defInfo,
                           const SourceLinkInfo &declInfo
                          ) {}
  void MarkdownGenerator::startCodeLine(bool hasLineNumbers) {}
  void MarkdownGenerator::endCodeLine() {}
  void MarkdownGenerator::startFontClass(const char *clsName) {}
  void MarkdownGenerator::endFontClass() {}
  void MarkdownGenerator::writeCodeAnchor(const char *name) {}
  void MarkdownGenerator::setCurrentDoc(Definition *context,const char *anchor,bool isSourceFile) {}
  void MarkdownGenerator::addWord(const char *word,bool hiPriority) {}
