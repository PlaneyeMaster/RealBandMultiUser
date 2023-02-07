//Copyright(C) 2022 VAXPORT all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Docking/SDockTab.h"






DECLARE_LOG_CATEGORY_EXTERN(LogManager, Log, All);



class FRealBandBackUpUIManagerImpl : public TSharedFromThis<FRealBandBackUpUIManagerImpl>
{

private:

	TSharedPtr<SWindow> pDialogMainWindow;
	TSharedPtr<SOverlay> pOverlay;
	TSharedPtr<SCanvas> pCanvas;
	void SetupMenuItem();
	void FillToolbar(FToolBarBuilder& ToolbarBuilder);
public:

	virtual ~FRealBandBackUpUIManagerImpl();
	void Initialize();
	void CreateWindow();
	void InitMultiUserEditorControls();
};


class FRealBandBackUpUIManager
{
public:
	static void Initialize();
	//static bool DisplayStartWindow();
	static TSharedPtr<FRealBandBackUpUIManagerImpl> Instance;
	~FRealBandBackUpUIManager();
};
