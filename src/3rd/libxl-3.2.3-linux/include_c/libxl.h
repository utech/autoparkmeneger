#ifndef LIBXL_C_H
#define LIBXL_C_H

#define LIBXL_VERSION 0x03020300

#ifdef _UNICODE

    #include "BookW.h"
    #include "SheetW.h"
    #include "FormatW.h"
    #include "FontW.h"

    #define xlCreateBook xlCreateBookCW
    #define xlCreateXMLBook xlCreateXMLBookCW
    #define xlBookLoad xlBookLoadW
    #define xlBookSave xlBookSaveW
    #define xlBookLoadRaw xlBookLoadRawW
    #define xlBookSaveRaw xlBookSaveRawW
    #define xlBookAddSheet xlBookAddSheetW
    #define xlBookInsertSheet xlBookInsertSheetW
    #define xlBookGetSheet xlBookGetSheetW
    #define xlBookDelSheet xlBookDelSheetW
    #define xlBookSheetCount xlBookSheetCountW
    #define xlBookAddFormat xlBookAddFormatW
    #define xlBookAddFont xlBookAddFontW
    #define xlBookAddCustomNumFormat xlBookAddCustomNumFormatW
    #define xlBookCustomNumFormat xlBookCustomNumFormatW
    #define xlBookFormat xlBookFormatW
    #define xlBookFormatSize xlBookFormatSizeW
    #define xlBookFont xlBookFontW
    #define xlBookFontSize xlBookFontSizeW
    #define xlBookDatePack xlBookDatePackW
    #define xlBookDateUnpack xlBookDateUnpackW
    #define xlBookColorPack xlBookColorPackW
    #define xlBookColorUnpack xlBookColorUnpackW
    #define xlBookActiveSheet xlBookActiveSheetW
    #define xlBookSetActiveSheet xlBookSetActiveSheetW
    #define xlBookPictureSize xlBookPictureSizeW
    #define xlBookGetPicture xlBookGetPictureW
    #define xlBookAddPicture xlBookAddPictureW
    #define xlBookAddPicture2 xlBookAddPicture2W
    #define xlBookDefaultFont xlBookDefaultFontW
    #define xlBookSetDefaultFont xlBookSetDefaultFontW
    #define xlBookSetKey xlBookSetKeyW
    #define xlBookRgbMode xlBookRgbModeW
    #define xlBookSetRgbMode xlBookSetRgbModeW
    #define xlBookBiffVersion xlBookBiffVersionW
    #define xlBookSetLocale xlBookSetLocaleW
    #define xlBookErrorMessage xlBookErrorMessageW
    #define xlBookRelease xlBookReleaseW

    #define xlSheetCellType xlSheetCellTypeW
    #define xlSheetCellFormat xlSheetCellFormatW
    #define xlSheetSetCellFormat xlSheetSetCellFormatW
    #define xlSheetIsFormula xlSheetIsFormulaW
    #define xlSheetReadStr xlSheetReadStrW
    #define xlSheetWriteStr xlSheetWriteStrW
    #define xlSheetReadNum xlSheetReadNumW
    #define xlSheetWriteNum xlSheetWriteNumW
    #define xlSheetReadBool xlSheetReadBoolW
    #define xlSheetWriteBool xlSheetWriteBoolW
    #define xlSheetReadBlank xlSheetReadBlankW
    #define xlSheetWriteBlank xlSheetWriteBlankW
    #define xlSheetReadFormula xlSheetReadFormulaW
    #define xlSheetWriteFormula xlSheetWriteFormulaW
    #define xlSheetReadComment xlSheetReadCommentW
    #define xlSheetWriteComment xlSheetWriteCommentW
    #define xlSheetIsDate xlSheetIsDateW
    #define xlSheetReadError xlSheetReadErrorW
    #define xlSheetColWidth xlSheetColWidthW
    #define xlSheetRowHeight xlSheetRowHeightW
    #define xlSheetSetCol xlSheetSetColW
    #define xlSheetSetRow xlSheetSetRowW
    #define xlSheetRowHidden xlSheetRowHiddenW
    #define xlSheetSetRowHidden xlSheetSetRowHiddenW
    #define xlSheetColHidden xlSheetColHiddenW
    #define xlSheetSetColHidden xlSheetSetColHiddenW
    #define xlSheetGetMerge xlSheetGetMergeW
    #define xlSheetSetMerge xlSheetSetMergeW
    #define xlSheetDelMerge xlSheetDelMergeW
    #define xlSheetPictureSize xlSheetPictureSizeW
    #define xlSheetGetPicture xlSheetGetPictureW
    #define xlSheetSetPicture xlSheetSetPictureW
    #define xlSheetSetPicture2 xlSheetSetPicture2W
    #define xlSheetGetHorPageBreak xlSheetGetHorPageBreakW
    #define xlSheetGetHorPageBreakSize xlSheetGetHorPageBreakSizeW
    #define xlSheetGetVerPageBreak xlSheetGetVerPageBreakW
    #define xlSheetGetVerPageBreakSize xlSheetGetVerPageBreakSizeW
    #define xlSheetSetHorPageBreak xlSheetSetHorPageBreakW
    #define xlSheetSetVerPageBreak xlSheetSetVerPageBreakW
    #define xlSheetSplit xlSheetSplitW
    #define xlSheetGroupRows xlSheetGroupRowsW
    #define xlSheetGroupCols xlSheetGroupColsW
    #define xlSheetGroupSummaryBelow xlSheetGroupSummaryBelowW
    #define xlSheetSetGroupSummaryBelow xlSheetSetGroupSummaryBelowW
    #define xlSheetGroupSummaryRight xlSheetGroupSummaryRightW
    #define xlSheetSetGroupSummaryRight xlSheetSetGroupSummaryRightW
    #define xlSheetClear xlSheetClearW
    #define xlSheetInsertCol xlSheetInsertColW
    #define xlSheetInsertRow xlSheetInsertRowW
    #define xlSheetRemoveCol xlSheetRemoveColW
    #define xlSheetRemoveRow xlSheetRemoveRowW
    #define xlSheetCopyCell xlSheetCopyCellW
    #define xlSheetFirstRow xlSheetFirstRowW
    #define xlSheetLastRow xlSheetLastRowW
    #define xlSheetFirstCol xlSheetFirstColW
    #define xlSheetLastCol xlSheetLastColW
    #define xlSheetDisplayGridlines xlSheetDisplayGridlinesW
    #define xlSheetSetDisplayGridlines xlSheetSetDisplayGridlinesW
    #define xlSheetPrintGridlines xlSheetPrintGridlinesW
    #define xlSheetSetPrintGridlines xlSheetSetPrintGridlinesW
    #define xlSheetZoom xlSheetZoomW
    #define xlSheetSetZoom xlSheetSetZoomW
    #define xlSheetPrintZoom xlSheetPrintZoomW
    #define xlSheetSetPrintZoom xlSheetSetPrintZoomW
    #define xlSheetGetPrintFit xlSheetGetPrintFitW
    #define xlSheetSetPrintFit xlSheetSetPrintFitW
    #define xlSheetLandscape xlSheetLandscapeW
    #define xlSheetSetLandscape xlSheetSetLandscapeW
    #define xlSheetPaper xlSheetPaperW
    #define xlSheetSetPaper xlSheetSetPaperW
    #define xlSheetHeader xlSheetHeaderW
    #define xlSheetSetHeader xlSheetSetHeaderW
    #define xlSheetHeaderMargin xlSheetHeaderMarginW
    #define xlSheetFooter xlSheetFooterW
    #define xlSheetSetFooter xlSheetSetFooterW
    #define xlSheetFooterMargin xlSheetFooterMarginW
    #define xlSheetHCenter xlSheetHCenterW
    #define xlSheetSetHCenter xlSheetSetHCenterW
    #define xlSheetVCenter xlSheetVCenterW
    #define xlSheetSetVCenter xlSheetSetVCenterW
    #define xlSheetMarginLeft xlSheetMarginLeftW
    #define xlSheetSetMarginLeft xlSheetSetMarginLeftW
    #define xlSheetMarginRight xlSheetMarginRightW
    #define xlSheetSetMarginRight xlSheetSetMarginRightW
    #define xlSheetMarginTop xlSheetMarginTopW
    #define xlSheetSetMarginTop xlSheetSetMarginTopW
    #define xlSheetMarginBottom xlSheetMarginBottomW
    #define xlSheetSetMarginBottom xlSheetSetMarginBottomW
    #define xlSheetPrintRowCol xlSheetPrintRowColW
    #define xlSheetSetPrintRowCol xlSheetSetPrintRowColW
    #define xlSheetSetPrintRepeatRows xlSheetSetPrintRepeatRowsW
    #define xlSheetSetPrintRepeatCols xlSheetSetPrintRepeatColsW
    #define xlSheetSetPrintArea xlSheetSetPrintAreaW
    #define xlSheetClearPrintRepeats xlSheetClearPrintRepeatsW
    #define xlSheetClearPrintArea xlSheetClearPrintAreaW
    #define xlSheetGetNamedRange xlSheetGetNamedRangeW
    #define xlSheetSetNamedRange xlSheetSetNamedRangeW
    #define xlSheetDelNamedRange xlSheetDelNamedRangeW
    #define xlSheetNamedRangeSize xlSheetNamedRangeSizeW
    #define xlSheetNamedRange xlSheetNamedRangeW
    #define xlSheetName xlSheetNameW
    #define xlSheetSetName xlSheetSetNameW
    #define xlSheetProtect xlSheetProtectW
    #define xlSheetSetProtect xlSheetSetProtectW
    #define xlSheetHidden xlSheetHiddenW
    #define xlSheetSetHidden xlSheetSetHiddenW

    #define xlFontSize xlFontSizeW
    #define xlFontSetSize xlFontSetSizeW
    #define xlFontItalic xlFontItalicW
    #define xlFontSetItalic xlFontSetItalicW
    #define xlFontStrikeOut xlFontStrikeOutW
    #define xlFontSetStrikeOut xlFontSetStrikeOutW
    #define xlFontColor xlFontColorW
    #define xlFontSetColor xlFontSetColorW
    #define xlFontBold xlFontBoldW
    #define xlFontSetBold xlFontSetBoldW
    #define xlFontScript xlFontScriptW
    #define xlFontSetScript xlFontSetScriptW
    #define xlFontUnderline xlFontUnderlineW
    #define xlFontSetUnderline xlFontSetUnderlineW
    #define xlFontName xlFontNameW
    #define xlFontSetName xlFontSetNameW

    #define xlFormatFont xlFormatFontW
    #define xlFormatSetFont xlFormatSetFontW
    #define xlFormatNumFormat xlFormatNumFormatW
    #define xlFormatSetNumFormat xlFormatSetNumFormatW
    #define xlFormatAlignH xlFormatAlignHW
    #define xlFormatSetAlignH xlFormatSetAlignHW
    #define xlFormatAlignV xlFormatAlignVW
    #define xlFormatSetAlignV xlFormatSetAlignVW
    #define xlFormatWrap xlFormatWrapW
    #define xlFormatSetWrap xlFormatSetWrapW
    #define xlFormatRotation xlFormatRotationW
    #define xlFormatSetRotation xlFormatSetRotationW
    #define xlFormatIndent xlFormatIndentW
    #define xlFormatSetIndent xlFormatSetIndentW
    #define xlFormatShrinkToFit xlFormatShrinkToFitW
    #define xlFormatSetShrinkToFit xlFormatSetShrinkToFitW
    #define xlFormatSetBorder xlFormatSetBorderW
    #define xlFormatSetBorderColor xlFormatSetBorderColorW
    #define xlFormatBorderLeft xlFormatBorderLeftW
    #define xlFormatSetBorderLeft xlFormatSetBorderLeftW
    #define xlFormatBorderRight xlFormatBorderRightW
    #define xlFormatSetBorderRight xlFormatSetBorderRightW
    #define xlFormatBorderTop xlFormatBorderTopW
    #define xlFormatSetBorderTop xlFormatSetBorderTopW
    #define xlFormatBorderBottom xlFormatBorderBottomW
    #define xlFormatSetBorderBottom xlFormatSetBorderBottomW
    #define xlFormatBorderLeftColor xlFormatBorderLeftColorW
    #define xlFormatSetBorderLeftColor xlFormatSetBorderLeftColorW
    #define xlFormatBorderRightColor xlFormatBorderRightColorW
    #define xlFormatSetBorderRightColor xlFormatSetBorderRightColorW
    #define xlFormatBorderTopColor xlFormatBorderTopColorW
    #define xlFormatSetBorderTopColor xlFormatSetBorderTopColorW
    #define xlFormatBorderBottomColor xlFormatBorderBottomColorW
    #define xlFormatSetBorderBottomColor xlFormatSetBorderBottomColorW
    #define xlFormatBorderDiagonal xlFormatBorderDiagonalW
    #define xlFormatSetBorderDiagonal xlFormatSetBorderDiagonalW
    #define xlFormatBorderDiagonalStyle xlFormatBorderDiagonalStyleW
    #define xlFormatSetBorderDiagonalStyle xlFormatSetBorderDiagonalStyleW
    #define xlFormatBorderDiagonalColor xlFormatBorderDiagonalColorW
    #define xlFormatSetBorderDiagonalColor xlFormatSetBorderDiagonalColorW
    #define xlFormatFillPattern xlFormatFillPatternW
    #define xlFormatSetFillPattern xlFormatSetFillPatternW
    #define xlFormatPatternForegroundColor xlFormatPatternForegroundColorW
    #define xlFormatSetPatternForegroundColor xlFormatSetPatternForegroundColorW
    #define xlFormatPatternBackgroundColor xlFormatPatternBackgroundColorW
    #define xlFormatSetPatternBackgroundColor xlFormatSetPatternBackgroundColorW
    #define xlFormatLocked xlFormatLockedW
    #define xlFormatSetLocked xlFormatSetLockedW
    #define xlFormatHidden xlFormatHiddenW
    #define xlFormatSetHidden xlFormatSetHiddenW

#else

    #include "BookA.h"
    #include "SheetA.h"
    #include "FormatA.h"
    #include "FontA.h"

    #define xlCreateBook xlCreateBookCA
    #define xlCreateXMLBook xlCreateXMLBookCA
    #define xlBookLoad xlBookLoadA
    #define xlBookSave xlBookSaveA
    #define xlBookLoadRaw xlBookLoadRawA
    #define xlBookSaveRaw xlBookSaveRawA
    #define xlBookAddSheet xlBookAddSheetA
    #define xlBookInsertSheet xlBookInsertSheetA
    #define xlBookGetSheet xlBookGetSheetA
    #define xlBookDelSheet xlBookDelSheetA
    #define xlBookSheetCount xlBookSheetCountA
    #define xlBookAddFormat xlBookAddFormatA
    #define xlBookAddFont xlBookAddFontA
    #define xlBookAddCustomNumFormat xlBookAddCustomNumFormatA
    #define xlBookCustomNumFormat xlBookCustomNumFormatA
    #define xlBookFormat xlBookFormatA
    #define xlBookFormatSize xlBookFormatSizeA
    #define xlBookFont xlBookFontA
    #define xlBookFontSize xlBookFontSizeA
    #define xlBookDatePack xlBookDatePackA
    #define xlBookDateUnpack xlBookDateUnpackA
    #define xlBookColorPack xlBookColorPackA
    #define xlBookColorUnpack xlBookColorUnpackA
    #define xlBookActiveSheet xlBookActiveSheetA
    #define xlBookSetActiveSheet xlBookSetActiveSheetA
    #define xlBookPictureSize xlBookPictureSizeA
    #define xlBookGetPicture xlBookGetPictureA
    #define xlBookAddPicture xlBookAddPictureA
    #define xlBookAddPicture2 xlBookAddPicture2A
    #define xlBookDefaultFont xlBookDefaultFontA
    #define xlBookSetDefaultFont xlBookSetDefaultFontA
    #define xlBookSetKey xlBookSetKeyA
    #define xlBookRgbMode xlBookRgbModeA
    #define xlBookSetRgbMode xlBookSetRgbModeA
    #define xlBookBiffVersion xlBookBiffVersionA
    #define xlBookSetLocale xlBookSetLocaleA
    #define xlBookErrorMessage xlBookErrorMessageA
    #define xlBookRelease xlBookReleaseA

    #define xlSheetCellType xlSheetCellTypeA
    #define xlSheetCellFormat xlSheetCellFormatA
    #define xlSheetSetCellFormat xlSheetSetCellFormatA
    #define xlSheetIsFormula xlSheetIsFormulaA
    #define xlSheetReadStr xlSheetReadStrA
    #define xlSheetWriteStr xlSheetWriteStrA
    #define xlSheetReadNum xlSheetReadNumA
    #define xlSheetWriteNum xlSheetWriteNumA
    #define xlSheetReadBool xlSheetReadBoolA
    #define xlSheetWriteBool xlSheetWriteBoolA
    #define xlSheetReadBlank xlSheetReadBlankA
    #define xlSheetWriteBlank xlSheetWriteBlankA
    #define xlSheetReadFormula xlSheetReadFormulaA
    #define xlSheetWriteFormula xlSheetWriteFormulaA
    #define xlSheetReadComment xlSheetReadCommentA
    #define xlSheetWriteComment xlSheetWriteCommentA
    #define xlSheetIsDate xlSheetIsDateA
    #define xlSheetReadError xlSheetReadErrorA
    #define xlSheetColWidth xlSheetColWidthA
    #define xlSheetRowHeight xlSheetRowHeightA
    #define xlSheetSetCol xlSheetSetColA
    #define xlSheetSetRow xlSheetSetRowA
    #define xlSheetRowHidden xlSheetRowHiddenA
    #define xlSheetSetRowHidden xlSheetSetRowHiddenA
    #define xlSheetColHidden xlSheetColHiddenA
    #define xlSheetSetColHidden xlSheetSetColHiddenA
    #define xlSheetGetMerge xlSheetGetMergeA
    #define xlSheetSetMerge xlSheetSetMergeA
    #define xlSheetDelMerge xlSheetDelMergeA
    #define xlSheetPictureSize xlSheetPictureSizeA
    #define xlSheetGetPicture xlSheetGetPictureA
    #define xlSheetSetPicture xlSheetSetPictureA
    #define xlSheetSetPicture2 xlSheetSetPicture2A
    #define xlSheetGetHorPageBreak xlSheetGetHorPageBreakA
    #define xlSheetGetHorPageBreakSize xlSheetGetHorPageBreakSizeA
    #define xlSheetGetVerPageBreak xlSheetGetVerPageBreakA
    #define xlSheetGetVerPageBreakSize xlSheetGetVerPageBreakSizeA
    #define xlSheetSetHorPageBreak xlSheetSetHorPageBreakA
    #define xlSheetSetVerPageBreak xlSheetSetVerPageBreakA
    #define xlSheetSplit xlSheetSplitA
    #define xlSheetGroupRows xlSheetGroupRowsA
    #define xlSheetGroupCols xlSheetGroupColsA
    #define xlSheetGroupSummaryBelow xlSheetGroupSummaryBelowA
    #define xlSheetSetGroupSummaryBelow xlSheetSetGroupSummaryBelowA
    #define xlSheetGroupSummaryRight xlSheetGroupSummaryRightA
    #define xlSheetSetGroupSummaryRight xlSheetSetGroupSummaryRightA
    #define xlSheetClear xlSheetClearA
    #define xlSheetInsertCol xlSheetInsertColA
    #define xlSheetInsertRow xlSheetInsertRowA
    #define xlSheetRemoveCol xlSheetRemoveColA
    #define xlSheetRemoveRow xlSheetRemoveRowA
    #define xlSheetCopyCell xlSheetCopyCellA
    #define xlSheetFirstRow xlSheetFirstRowA
    #define xlSheetLastRow xlSheetLastRowA
    #define xlSheetFirstCol xlSheetFirstColA
    #define xlSheetLastCol xlSheetLastColA
    #define xlSheetDisplayGridlines xlSheetDisplayGridlinesA
    #define xlSheetSetDisplayGridlines xlSheetSetDisplayGridlinesA
    #define xlSheetPrintGridlines xlSheetPrintGridlinesA
    #define xlSheetSetPrintGridlines xlSheetSetPrintGridlinesA
    #define xlSheetZoom xlSheetZoomA
    #define xlSheetSetZoom xlSheetSetZoomA
    #define xlSheetPrintZoom xlSheetPrintZoomA
    #define xlSheetSetPrintZoom xlSheetSetPrintZoomA
    #define xlSheetGetPrintFit xlSheetGetPrintFitA
    #define xlSheetSetPrintFit xlSheetSetPrintFitA
    #define xlSheetLandscape xlSheetLandscapeA
    #define xlSheetSetLandscape xlSheetSetLandscapeA
    #define xlSheetPaper xlSheetPaperA
    #define xlSheetSetPaper xlSheetSetPaperA
    #define xlSheetHeader xlSheetHeaderA
    #define xlSheetSetHeader xlSheetSetHeaderA
    #define xlSheetHeaderMargin xlSheetHeaderMarginA
    #define xlSheetFooter xlSheetFooterA
    #define xlSheetSetFooter xlSheetSetFooterA
    #define xlSheetFooterMargin xlSheetFooterMarginA
    #define xlSheetHCenter xlSheetHCenterA
    #define xlSheetSetHCenter xlSheetSetHCenterA
    #define xlSheetVCenter xlSheetVCenterA
    #define xlSheetSetVCenter xlSheetSetVCenterA
    #define xlSheetMarginLeft xlSheetMarginLeftA
    #define xlSheetSetMarginLeft xlSheetSetMarginLeftA
    #define xlSheetMarginRight xlSheetMarginRightA
    #define xlSheetSetMarginRight xlSheetSetMarginRightA
    #define xlSheetMarginTop xlSheetMarginTopA
    #define xlSheetSetMarginTop xlSheetSetMarginTopA
    #define xlSheetMarginBottom xlSheetMarginBottomA
    #define xlSheetSetMarginBottom xlSheetSetMarginBottomA
    #define xlSheetPrintRowCol xlSheetPrintRowColA
    #define xlSheetSetPrintRowCol xlSheetSetPrintRowColA
    #define xlSheetSetPrintRepeatRows xlSheetSetPrintRepeatRowsA
    #define xlSheetSetPrintRepeatCols xlSheetSetPrintRepeatColsA
    #define xlSheetSetPrintArea xlSheetSetPrintAreaA
    #define xlSheetClearPrintRepeats xlSheetClearPrintRepeatsA
    #define xlSheetClearPrintArea xlSheetClearPrintAreaA
    #define xlSheetGetNamedRange xlSheetGetNamedRangeA
    #define xlSheetSetNamedRange xlSheetSetNamedRangeA
    #define xlSheetDelNamedRange xlSheetDelNamedRangeA
    #define xlSheetNamedRangeSize xlSheetNamedRangeSizeA
    #define xlSheetNamedRange xlSheetNamedRangeA
    #define xlSheetName xlSheetNameA
    #define xlSheetSetName xlSheetSetNameA
    #define xlSheetProtect xlSheetProtectA
    #define xlSheetSetProtect xlSheetSetProtectA
    #define xlSheetHidden xlSheetHiddenA
    #define xlSheetSetHidden xlSheetSetHiddenA

    #define xlFontSize xlFontSizeA
    #define xlFontSetSize xlFontSetSizeA
    #define xlFontItalic xlFontItalicA
    #define xlFontSetItalic xlFontSetItalicA
    #define xlFontStrikeOut xlFontStrikeOutA
    #define xlFontSetStrikeOut xlFontSetStrikeOutA
    #define xlFontColor xlFontColorA
    #define xlFontSetColor xlFontSetColorA
    #define xlFontBold xlFontBoldA
    #define xlFontSetBold xlFontSetBoldA
    #define xlFontScript xlFontScriptA
    #define xlFontSetScript xlFontSetScriptA
    #define xlFontUnderline xlFontUnderlineA
    #define xlFontSetUnderline xlFontSetUnderlineA
    #define xlFontName xlFontNameA
    #define xlFontSetName xlFontSetNameA

    #define xlFormatFont xlFormatFontA
    #define xlFormatSetFont xlFormatSetFontA
    #define xlFormatNumFormat xlFormatNumFormatA
    #define xlFormatSetNumFormat xlFormatSetNumFormatA
    #define xlFormatAlignH xlFormatAlignHA
    #define xlFormatSetAlignH xlFormatSetAlignHA
    #define xlFormatAlignV xlFormatAlignVA
    #define xlFormatSetAlignV xlFormatSetAlignVA
    #define xlFormatWrap xlFormatWrapA
    #define xlFormatSetWrap xlFormatSetWrapA
    #define xlFormatRotation xlFormatRotationA
    #define xlFormatSetRotation xlFormatSetRotationA
    #define xlFormatIndent xlFormatIndentA
    #define xlFormatSetIndent xlFormatSetIndentA
    #define xlFormatShrinkToFit xlFormatShrinkToFitA
    #define xlFormatSetShrinkToFit xlFormatSetShrinkToFitA
    #define xlFormatSetBorder xlFormatSetBorderA
    #define xlFormatSetBorderColor xlFormatSetBorderColorA
    #define xlFormatBorderLeft xlFormatBorderLeftA
    #define xlFormatSetBorderLeft xlFormatSetBorderLeftA
    #define xlFormatBorderRight xlFormatBorderRightA
    #define xlFormatSetBorderRight xlFormatSetBorderRightA
    #define xlFormatBorderTop xlFormatBorderTopA
    #define xlFormatSetBorderTop xlFormatSetBorderTopA
    #define xlFormatBorderBottom xlFormatBorderBottomA
    #define xlFormatSetBorderBottom xlFormatSetBorderBottomA
    #define xlFormatBorderLeftColor xlFormatBorderLeftColorA
    #define xlFormatSetBorderLeftColor xlFormatSetBorderLeftColorA
    #define xlFormatBorderRightColor xlFormatBorderRightColorA
    #define xlFormatSetBorderRightColor xlFormatSetBorderRightColorA
    #define xlFormatBorderTopColor xlFormatBorderTopColorA
    #define xlFormatSetBorderTopColor xlFormatSetBorderTopColorA
    #define xlFormatBorderBottomColor xlFormatBorderBottomColorA
    #define xlFormatSetBorderBottomColor xlFormatSetBorderBottomColorA
    #define xlFormatBorderDiagonal xlFormatBorderDiagonalA
    #define xlFormatSetBorderDiagonal xlFormatSetBorderDiagonalA
    #define xlFormatBorderDiagonalStyle xlFormatBorderDiagonalStyleA
    #define xlFormatSetBorderDiagonalStyle xlFormatSetBorderDiagonalStyleA
    #define xlFormatBorderDiagonalColor xlFormatBorderDiagonalColorA
    #define xlFormatSetBorderDiagonalColor xlFormatSetBorderDiagonalColorA
    #define xlFormatFillPattern xlFormatFillPatternA
    #define xlFormatSetFillPattern xlFormatSetFillPatternA
    #define xlFormatPatternForegroundColor xlFormatPatternForegroundColorA
    #define xlFormatSetPatternForegroundColor xlFormatSetPatternForegroundColorA
    #define xlFormatPatternBackgroundColor xlFormatPatternBackgroundColorA
    #define xlFormatSetPatternBackgroundColor xlFormatSetPatternBackgroundColorA
    #define xlFormatLocked xlFormatLockedA
    #define xlFormatSetLocked xlFormatSetLockedA
    #define xlFormatHidden xlFormatHiddenA
    #define xlFormatSetHidden xlFormatSetHiddenA

#endif

#endif
