// Copyright RealEye, Inc. All Rights Reserved.

//UI
#include "../UI/FRealBandBackUpUIManager.h"
#include "../Config/RealBandConfig.h"
#include "CoreGlobals.h"
#include "BackUpStyle.h"

#include "Modules/ModuleManager.h"


//Editor
#include "LevelEditor.h"

//#include "MultiUserServerModule.h"
#include "Blutility/Classes/EditorUtilityWidget.h"
#include "Blutility/Classes/EditorUtilityObject.h"

#include "../../../../Engine/Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/ConcertSettings.h"
#include "../../../../Engine/Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/IConcertClient.h"
#include "../../../../Engine/Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertSyncClient.h"
#include "../../../../Engine/Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertSyncClientModule.h"
#include "../../../../Engine/Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public/IMultiUserClientModule.h"


DEFINE_LOG_CATEGORY(LogManager);

TSharedPtr<FRealBandBackUpUIManagerImpl> FRealBandBackUpUIManager::Instance;
#define LEVELEDITOR_MODULE_NAME TEXT("LevelEditor")

#define LOCTEXT_NAMESPACE "RealBandBackUP"



FRealBandBackUpUIManager::~FRealBandBackUpUIManager()
{
	Instance.Reset();
}


FRealBandBackUpUIManagerImpl::~FRealBandBackUpUIManagerImpl()
{
	FRealBandBackUpUIManager::Instance.Reset();
}
void FRealBandBackUpUIManagerImpl::Initialize()
{
	// Menu Setup
//	//SetupMenuItem();
	//Create the MainWindow
//	InitMultiUserEditorControls();
	CreateWindow();

}
//
//
//
void FRealBandBackUpUIManager::Initialize()
{
//	
	if (!Instance.IsValid())
    {
//	//	//FRealBandStyle::Initialize();
	    Instance = MakeShareable(new FRealBandBackUpUIManagerImpl());
//	//	FRealBandStyle::SetSVGIcon("SaveIcon", "saveIcon");
//	//	//FRealBandStyle::SetIcon("Icon8", "IconsB");
//	//	FRealBandStyle::SetIcon("Icon8", "Icon40x40");
	}
//	//
	Instance->InitMultiUserEditorControls();
	Instance->Initialize();
}
//
////bool FRealBandUIManager::DisplayStartWindow()
////{
////	bool bRet = false;
////	if (Instance)
////	{
////		bRet = Instance->RestoreMainWindow();
////	}
////	return bRet;
////}
////
////
void FRealBandBackUpUIManagerImpl::SetupMenuItem()
{
    FBackUpStyle::SetIcon("Logo", "Logo80x80");
	FBackUpStyle::SetIcon("ContextLogo", "Logo32x32");
    //FRealBandStyle::SetSVGIcon("MenuLogo", "QuixelBridgeB");
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(LEVELEDITOR_MODULE_NAME);
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, nullptr, 
		                                 FToolBarExtensionDelegate::CreateRaw(this, &FRealBandBackUpUIManagerImpl::FillToolbar));
////	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
////
////	// Adding Bridge entry to Quick Content menu.
////	UToolMenu* AddMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.AddQuickMenu");
////	FToolMenuSection& Section = AddMenu->FindOrAddSection("Content");
////	Section.AddMenuEntry("OpenRealBand",
////		LOCTEXT("OpenRealBand_Label", "RealBandImporter"),
////		LOCTEXT("OpenRealBand_Desc", "Opens the RealBand Importer."),
////		FSlateIcon(FName("RealBandImporterStyle"), "RealBand.MenuLogo"),
////		FUIAction(FExecuteAction::CreateRaw(this, &FRealBandUIManagerImpl::CreateWindow), FCanExecuteAction())
////	).InsertPosition = FToolMenuInsert("ImportContent", EToolMenuInsertType::After);
}
////
void FRealBandBackUpUIManagerImpl::FillToolbar(FToolBarBuilder& ToolbarBuilder)
{
    	ToolbarBuilder.BeginSection(TEXT("RealBandMultiUserEditor"));
	    {
    		ToolbarBuilder.AddToolBarButton(
			FUIAction(FExecuteAction::CreateRaw(this, &FRealBandBackUpUIManagerImpl::CreateWindow)),
			FName(TEXT("RealBand MultiUser Editor Backup")),
			LOCTEXT("QMSLiveLink_label", "RealBand MultiUser Editor Backup"),
			LOCTEXT("WorldProperties_ToolTipOverride", "Megascans Link"),
			FSlateIcon(FBackUpStyle::GetStyleSetName(), "RealBand.Logo"),
			EUserInterfaceActionType::Button,
			FName(TEXT("RealBand MultiUser Editor Backup"))
		);
    	}
    	ToolbarBuilder.EndSection();
}

//
void FRealBandBackUpUIManagerImpl::CreateWindow()
{
//	bool bIsVisible = false;
	if (!pDialogMainWindow )
	{
		FSlateBrush* CustomBorderBrush = new FSlateBrush();
		CustomBorderBrush->SetResourceObject(FCoreStyle::Get().GetBrush("GenericWhiteBox")->GetResourceObject());
		CustomBorderBrush->ImageSize = FVector2D(0.2f, 0.2f);
		//CustomBorderBrush->Margin = FVector2D(8.2f, 8.2f);


		pDialogMainWindow = SNew(SWindow)
			.Title(FText::FromString("RealBandBackUp MultiUser Session"))
			.ClientSize(FVector2D(1100, 400))
			.SupportsMaximize(false)
			.SupportsMinimize(false)
			.SizingRule(ESizingRule::UserSized)
			.AutoCenter(EAutoCenter::PreferredWorkArea)
			.SupportsMaximize(true)
			.SupportsMinimize(true)
			[
				SAssignNew(pOverlay, SOverlay)
        		+ SOverlay::Slot()
		         .VAlign(VAlign_Fill)
			     .HAlign(HAlign_Fill)			
			    [
				  SNew(SBox)
				 .HAlign(HAlign_Fill)
			     .VAlign(VAlign_Fill)
			      [
				     SAssignNew(pCanvas, SCanvas)
					 + SCanvas::Slot()
			          .HAlign(HAlign_Fill)
			          .VAlign(VAlign_Fill)
			          .Size(FVector2D(120.0f, 100.0f))
			          .Position(FVector2D(30.0f, 45.0f))
			          [
				         SNew(STextBlock)
				         .Text(FText::FromString("Current User"))
			             //.Font(FCoreStyle::Get().GetFontStyle(TEXT("PropertyWindow.NormalFont")))
			             .TextStyle(FAppStyle::Get(), "NormalText")
			             //.TextStyle(FTextBlockStyle)
                         ////			.OnClicked(this, &FRealBandUIManagerImpl::OnLocal)
			          ]
					 + SCanvas::Slot()
		               .HAlign(HAlign_Fill)
		               .VAlign(VAlign_Fill)
		               .Size(FVector2D(120.0f, 100.0f))
		               .Position(FVector2D(30.0f, 85.0f))
		               [
			               SNew(STextBlock)
			               .Text(FText::FromString("Repository Name"))
		                   //.Font(FCoreStyle::Get().GetFontStyle(TEXT("PropertyWindow.NormalFont")))
		                   .TextStyle(FAppStyle::Get(), "NormalText")
		                   
		                   //.TextStyle(FTextBlockStyle)
		////			.OnClicked(this, &FRealBandUIManagerImpl::OnLocal)

		               ]
	                + SCanvas::Slot()
		              .HAlign(HAlign_Fill)
		              .VAlign(VAlign_Fill)
		              .Size(FVector2D(170.0f, 20.0f))
		              .Position(FVector2D(250.0f, 80.0f))
		              [
						  SNew(SBorder)
						  .BorderImage(CustomBorderBrush)
						  .BorderBackgroundColor(FLinearColor::White)
						 // .HAlign(HAlign_Center)
						 // .VAlign(VAlign_Center)
						  .Padding(FMargin(0.2f))
						[
			              SNew(SEditableText)
						  .ColorAndOpacity(FLinearColor::Black)
						  .Font(FAppStyle::GetFontStyle("Regular"))
						  
						]
						  //.Style
		//.Font(FCoreStyle::Get().GetFontStyle(TEXT("PropertyWindow.NormalFont")))
		            //      .TextStyle(FAppStyle::Get(), "NormalText")

		//.TextStyle(FTextBlockStyle)
////			.OnClicked(this, &FRealBandUIManagerImpl::OnLocal)

		              ]

			         + SCanvas::Slot()
			          .HAlign(HAlign_Fill)
			          .VAlign(VAlign_Fill)
			          .Size(FVector2D(120.0f, 50.0f))
			          .Position(FVector2D(30.0f, 180.0f))
			          [
				        SNew(SButton)
				       .HAlign(HAlign_Center)
			           .VAlign(VAlign_Center)
			           .Text(FText::FromString("Start Backup"))
////			.OnClicked(this, &FRealBandUIManagerImpl::OnLocal)

			           ]

					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(70.0f, 40.0f))
						 .Position(FVector2D(450.0f, 68.0f))
						 [
							 SNew(SButton)
							 .HAlign(HAlign_Center)
						     .VAlign(VAlign_Center)
						     .Text(FText::FromString("Sync"))
						 ////			.OnClicked(this, &FRealBandUIManagerImpl::OnLocal)

						 ]
					 + SCanvas::Slot()
						 .HAlign(HAlign_Fill)
						 .VAlign(VAlign_Fill)
						 .Size(FVector2D(70.0f, 40.0f))
						 .Position(FVector2D(550.0f, 68.0f))
						 [
							 SNew(SButton)
							 .HAlign(HAlign_Center)
						 .VAlign(VAlign_Center)
						 .Text(FText::FromString("Save"))
						 ////			.OnClicked(this, &FRealBandUIManagerImpl::OnLocal)

						 ]
		          ]

			   ]

			];


		FSlateApplication::Get().AddWindow(pDialogMainWindow.ToSharedRef());
		TSharedRef<FSlateAccessibleMessageHandler> MessageHandler = FSlateApplication::Get().GetAccessibleMessageHandler();
		
////		//FSlateApplication::Get().OnResizingWindow(pDialogMainWindow)
////
////	//	pSettingsWindow->SetVisibility(EVisibility::Hidden);
////		pApplyButton->SetVisibility(EVisibility::Hidden);
////
////		if(GetAssetViewCount() > 0)
////		    pFRealBandAssetLoader->SetVisibility(EVisibility::Visible);
////		else
////			pFRealBandAssetLoader->SetVisibility(EVisibility::Collapsed);
////
////		pRealBandImportSettings->SetVisibility(EVisibility::Collapsed);
////		
////		
////		pRealBandImportSettings->pSettingsWindow->SetOnWindowClosed(FOnWindowClosed::CreateLambda([this](const TSharedRef<SWindow>& Window)
////			{
////				pImport->SetVisibility(EVisibility::Visible);
////				pRealBandImportSettings->SetVisibility(EVisibility::Hidden);
////				pApplyButton->SetVisibility(EVisibility::Hidden);
////				pDialogMainWindow->BringToFront(true);;
////				
////			}));
////
	}
////	else
////	{
////		if (!pDialogMainWindow->IsVisible())
////		{
////			pDialogMainWindow->SetVisibility(EVisibility::All);
////			pFRealBandAssetLoader->SetVisibility(EVisibility::Visible);
////			pRealBandImportSettings->SetVisibility(EVisibility::Visible);
////		}
////    }
//////	pDialogMainWindow->SetOnWindowClosed(FRequestDestroyWindowOverride::CreateSP(this, &FRealBandUIManagerImpl::OnDialogClosed));
////
////
////
////    if (pRealBandImportSettings && GetAssetViewCount() == 0)
////    {
////	    pRealBandImportSettings->SetVisibility(EVisibility::Visible);
////		pApplyButton->SetVisibility(EVisibility::Visible);
////		pImport->SetVisibility(EVisibility::Hidden);
////	}
////
////	pDialogMainWindow->SetOnWindowClosed(FOnWindowClosed::CreateLambda([this](const TSharedRef<SWindow>& Window)
////		{
////			pRealBandImportSettings->SaveSettings();
////			//pDialogMainWindow->SetVisibility(EVisibility::Collapsed);
////			pDialogMainWindow.Reset();
////		//	pFRealBandAssetImporter.Reset();
////			//FRealBandUIManager::Instance.Reset();
////		}));
//
}


void FRealBandBackUpUIManagerImpl::InitMultiUserEditorControls()
{
	

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	URealBandConfig *pURealBandConfig = GetMutableDefault<URealBandConfig>();
	if (pURealBandConfig)
	{
		pURealBandConfig->SetConfig();
	}

	//TSharedPtr< URealBandConfig> pURealBandConfig =  MakeShareable(new URealBandConfig());

	//IMultiUserClientModule& MultiUserClientModule = IMultiUserClientModule::Get();
	IMultiUserClientModule& MultiUserClientModule = FModuleManager::LoadModuleChecked<IMultiUserClientModule>("MultiUserClient");

	if (!MultiUserClientModule.GetClient()->GetConcertClient()->GetConfiguration()->bInstallEditorToolbarButton)
	{
		UConcertClientConfig userSettings;
		userSettings.bInstallEditorToolbarButton = true;

		
	}
//	MultiUserClientModule.OpenSettings();
	/*

	TSharedRef<SWidget> ParentWidgetRef = pDialogMainWindow->GetParentWidget().ToSharedRef();
	FChildren  *Children = ParentWidgetRef->GetChildren();
	*/
	//for (int  num : Children->Num())
	//{
	//	
	//	UEditorUtilityWidget* EditorUtilityWidget = Cast<UEditorUtilityWidget>(Children->GetChildAt(num));
	//	if (EditorUtilityWidget)
	//	{
	//		// Access the Multi-User Settings
	//		FEditorScriptingToolsEditorSettings& MultiUserSettings = EditorUtilityWidget->GetSettings();

	//		// Enable the Multi-User Toolbar Button
	//		MultiUserSettings.bMultiUserEnabled = true;

	//		// Apply the updated Multi-User Settings to the Editor Utility Widget
	//		EditorUtilityWidget->SetSettings(MultiUserSettings);

	//		break;
	//	}
	//}


	
	//if (EditorUtilityWidget)
	//{
	//	// Access the Multi-User Settings
	//	FEditorScriptingToolsEditorSettings& MultiUserSettings = EditorUtilityWidget->GetSettings();

	//	// Enable the Multi-User Toolbar Button
	//	MultiUserSettings.bMultiUserEnabled = true;

	//	// Apply the updated Multi-User Settings to the Editor Utility Widget
	//	EditorUtilityWidget->SetSettings(MultiUserSettings);
	//}
	/*UEditorUtilityWidget* EditorUtilityWidget = NewObject<UEditorUtilityWidget>(GetTransientPackage(), UEditorUtilityWidget::StaticClass(), NAME_None, RF_Transient);
	EditorUtilityWidget->Create();
	FEditorScriptingToolsEditorMultiUserSettings& MultiUserSettings = EditorUtilityWidget->GetMultiUserSettings();
	MultiUserSettings.bMultiUserEnabled = true;
	EditorUtilityWidget->SetMultiUserSettings(MultiUserSettings);*/
}


#undef LOCTEXT_NAMESPACE