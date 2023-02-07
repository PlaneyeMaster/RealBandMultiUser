// Fill out your copyright notice in the Description page of Project Settings.


#include "Config/RealBandConfig.h"
#include "CoreGlobals.h"
#include "CoreMinimal.h"

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



URealBandConfig::URealBandConfig()
{
	
}

void URealBandConfig::SetConfig()
{
	IMultiUserClientModule& MultiUserClientModule = FModuleManager::LoadModuleChecked<IMultiUserClientModule>("MultiUserClient");

	if (MultiUserClientModule.IsAvailable())
	{
	    if (!MultiUserClientModule.GetClient()->GetConcertClient()->GetConfiguration()->bInstallEditorToolbarButton)
	    {
		    UConcertClientConfig *userSettings = GetMutableDefault<UConcertClientConfig>();;
		    userSettings->bInstallEditorToolbarButton = true;
		    MultiUserClientModule.GetClient()->GetConcertClient()->Configure(userSettings);
		    MultiUserClientModule.GetClient()->GetConcertClient()->Startup();
		    MultiUserClientModule.GetClient()->GetConcertClient()->StartDiscovery();
	    }
	    MultiUserClientModule.OpenBrowser();
	}
}