#ifndef DOCPARASTYLE_H
#define DOCPARASTYLE_H

class DocImage;


class DocParaStyle
{
public:
    DocParaStyle();
    ~DocParaStyle();
private:
    double spaceAbove;      // 段前间距
    double spaceBelow;      // 段后间距

    double indentFirstLine; // 首行缩进多少字符

    double deltaLineSpace;       // 行距 -- 和字体有关是一行高度的比例
    double fixedLineSpace;       // 固定行距 --  和字体无关，用毫米表示
    int LineSpaceType;           // 0-deltaLineSpace
                                 // 1-fixedlineSpace

    DocImage *background;        // 段落可能需要背景颜色花纹等

    // 大纲级别     -- 用来做大纲

    enum ParaAlign{Left,Centered,Right,Fullness};
    // 段落缩进,居左,居中,居右，撑满
    ParaAlign alignment;

};

#endif // DOCPARASTYLE_H
