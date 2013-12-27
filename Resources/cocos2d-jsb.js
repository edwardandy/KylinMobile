/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org

 http://www.cocos2d-x.org


 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

// boot code needed for cocos2d + JS bindings.
// Not needed by cocos2d-html5

require("jsb.js");
require( 'jsb_smartfish_extension_auto_api.js' );
require( 'jsb_smartfish_extension.js' );
require( 'src/libs/turbo/turbo.js' );
require( 'src/libs/http/http.js' );

var appFiles = [
    'src/lesson5.js',
    'src/lesson3.js',
    'src/resource.js',
    'src/myApp.js',

    'src/test/MiscTest.js',
    'src/TouchScaleLayer.js',
    'src/VisibleRect.js',
    'src/view/isometric/isometricScene.js',
    'src/view/isometric/isoLayer.js',
    'src/isometric/IsoSprite.js',
    'src/isometric/IsoScene.js',
    'src/isometric/astar/astar.js',
    'src/isometric/astar/graph.js',

    'src/sample/ContextEvent.js',
    'src/sample/GameController.js',
    'src/sample/GameStartService.js',
    'src/sample/UserModel.js',
    'src/myMVC.js',
    'src/test/HttpTest.js',
    'src/libs/UIComponent/MultiList.js',
    'src/MultiListTest.js'
];

cc.dumpConfig();

for( var i=0; i < appFiles.length; i++) {
    require( appFiles[i] );
}

var director = cc.Director.getInstance();
director.setDisplayStats(true);

// set FPS. the default value is 1.0/60 if you don't call this
director.setAnimationInterval(1.0 / 60);

//var http = new HttpTest();

// create a scene. it's an autorelease object
var myScene = new MultiListScene();
//var myScene = new IsometricScene();
//var myScene = new Lesson5();

// run
director.runWithScene(myScene);

