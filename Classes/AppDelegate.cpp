#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include "generated/jsb_cocos2dx_auto.hpp"
#include "generated/jsb_cocos2dx_extension_auto.hpp"
#include "generated/jsb_cocos2dx_studio_auto.hpp"
#include "jsb_cocos2dx_extension_manual.h"
#include "jsb_cocos2dx_studio_manual.h"
#include "cocos2d_specifics.hpp"
#include "js_bindings_chipmunk_registration.h"
#include "js_bindings_system_registration.h"
#include "js_bindings_ccbreader.h"
#include "jsb_opengl_registration.h"
#include "XMLHTTPRequest.h"
#include "jsb_websocket.h"
#import "jsb_smartfish_extension_auto.hpp"
#import "js_bindings_smartfish_manual.h"
#import "JSHttpRequestTest.h"
#import "LoaderMaxTest.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    CCScriptEngineManager::purgeSharedManager();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector( );
	pDirector->setOpenGLView( CCEGLView::sharedOpenGLView( ) );
	pDirector->setProjection( kCCDirectorProjection2D );


	CCSize screenSize = CCEGLView::sharedOpenGLView( )->getFrameSize( );

	CCSize designSize = CCSizeMake(960, 640);

	std::vector<std::string> searchPaths;

	TargetPlatform platform = CCApplication::sharedApplication( )->getTargetPlatform( );
	if ( platform == kTargetIphone || platform == kTargetIpad )
	{
		if ( screenSize.height > 320 )
		{
			searchPaths.push_back( "hd" );
		}
		else
		{
			searchPaths.push_back( "sd" );
		}
		CCFileUtils::sharedFileUtils( )->setSearchPaths( searchPaths );
	}

	CCEGLView::sharedOpenGLView( )->setDesignResolutionSize( designSize.width, designSize.height, kResolutionFixedHeight );

	//test
//	IsometricTest* test = new IsometricTest();
//	JSHttpRequestTest* jsHttpRequest = new JSHttpRequestTest();
//	ThreadTest* threadTest = new ThreadTest();
	LoaderMaxTest* loaderMaxTest = new LoaderMaxTest();
//	MiscTest* miscTest = new MiscTest();
//	EntityTest* miscTest = new EntityTest();
	return true;

    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(register_all_cocos2dx_studio);
    sc->addRegisterCallback(register_all_cocos2dx_studio_manual);
    sc->addRegisterCallback(register_CCBuilderReader);
    sc->addRegisterCallback(jsb_register_chipmunk);
    sc->addRegisterCallback(jsb_register_system);
    sc->addRegisterCallback(JSB_register_opengl);
    sc->addRegisterCallback(MinXmlHttpRequest::_js_register);
    sc->addRegisterCallback(register_jsb_websocket);

	//modify by chenyonghua
	sc->addRegisterCallback( register_all_smartfish );
	sc->addRegisterCallback( register_smartfish_js_extensions );

    sc->start();
    
    CCScriptEngineProtocol *pEngine = ScriptingCore::getInstance();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    ScriptingCore::getInstance()->runScript("cocos2d-jsb.js");
       
    return true;
}

void handle_signal(int signal) {
    static int internal_state = 0;
    ScriptingCore* sc = ScriptingCore::getInstance();
    // should start everything back
    CCDirector* director = CCDirector::sharedDirector();
    if (director->getRunningScene()) {
        director->popToRootScene();
    } else {
        CCPoolManager::sharedPoolManager()->finalize();
        if (internal_state == 0) {
            //sc->dumpRoot(NULL, 0, NULL);
            sc->start();
            internal_state = 1;
        } else {
            sc->runScript("hello.js");
            internal_state = 0;
        }
    }
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
