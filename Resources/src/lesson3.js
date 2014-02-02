/**
 * Created by chenyonghua on 13-12-2.
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// MemoryManageTest ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
var MemoryManageTest = cc.Layer.extend( {
    sprite: null,
    ctor: function()
    {
        this._super();

        var size = cc.Director.getInstance().getWinSize();

        //create a CCSprite
        this.sprite = cc.Sprite.create( "res/HelloWorld.png" );   //这时m_uReference ＝ 1
        this.sprite.setAnchorPoint( cc.p( 0.5, 0.5 ) );
        this.sprite.setPosition( cc.p( size.width / 2, size.height / 2 ) );
        this.addChild(this.sprite, 0); //这时m_uReference ＝ 2
        cc.Director.getInstance().getScheduler().scheduleCallbackForTarget( this, this.onThink, 1.0, cc.REPEAT_FOREVER, 0, false );
    },
    onThink: function( dt )
    {
        cc.log( "this.sprite:" + this.sprite );
        cc.log( "x:"+this.sprite.getBoundingBox().width+"y:"+this.sprite.getBoundingBox().height );
    }
} );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// TestScene ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
var TestScene = cc.Scene.extend( {
    ctor: function()
    {
        this._super();
    },

    onEnter: function()
    {
        this._super();
//        var layer = new MemoryManageTest();
//        var layer = new TouchTest();
        var layer = new TouchScaleLayer();
        this.addChild( layer );
        layer.init();
    }
} );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// TouchTest ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
var TouchTest = cc.Layer.extend( {
    sprite: null,
    ctor: function()
    {
        this._super();
        this.setTouchEnabled( true );
        this.setTouchMode( cc.TOUCH_ALL_AT_ONCE );
//        this.setTouchMode( cc.TOUCH_ONE_BY_ONE );

        //create a CCSprite
        var size = cc.Director.getInstance().getWinSize();
        this.sprite = cc.Sprite.create( "res/HelloWorld.png" );   //这时m_uReference ＝ 1
        this.sprite.setAnchorPoint( cc.p( 0.5, 0.5 ) );
        this.sprite.setPosition( cc.p( size.width / 2, size.height / 2 ) );
        this.addChild( this.sprite );
    },
    onTouchBegan: function( touch, event )
    {
        if( !this.containsTouchLocation( touch ) )
        {
            return false;
        }
        cc.log( "onTouchBegan" );
        return true;
    },
    onTouchMoved: function( touch, event )
    {
        var delta = touch.getDelta();
        var diff = cc.pAdd(delta, this.sprite.getPosition());
        this.sprite.setPosition(diff);
//        cc.log("delta.x:"+delta.x + ",delta.y:"+delta.y);
        cc.log( "onTouchMoved" );
    },
    onTouchEnded: function( touch, event )
    {
        cc.log( "onTouchEnded" );
    },
    onTouchCancelled: function( touch, event )
    {
        cc.log( "onTouchCancelled" );
    },
    containsTouchLocation: function( touch )
    {
//        var touchLocation = touch.getLocation(); // Get the touch position
//        touchLocation = this.getParent().convertToNodeSpace(touchLocation);
        var touchLocation = this.getParent().convertTouchToNodeSpace(touch);
        var bBox= this.sprite.getBoundingBox();
        var bLayerBox = this.getBoundingBox();
//        cc.log("width:"+bBox.width+",height:"+bBox.height);
//        cc.log("bLayerBox.width:"+bLayerBox.width+",bLayerBox.height:"+bLayerBox.height);
        return cc.rectContainsPoint(bBox,touchLocation);
    },
    onTouchesBegan:function (touches, event) {
        cc.log(" ==== onTouchesBegan === ");
    },
    onTouchesMoved:function (touches, event) {
        cc.log(" ==== onTouchesMoved === ");
    },
    onTouchesEnded:function (touches, event) {
        cc.log(" ==== onTouchesEnded === ");
    },
    onTouchesCancelled:function (touches, event) {
        cc.log(" ==== onTouchesCancelled === ");
    }
} );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// TouchScaleLayer ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TouchScaleLayer = cc.Layer.extend( {
    sprite:null,
    distance: 0,    //两个触摸点之间的距离
    deltax: 0,    //目标x轴的改变值
    deltay: 0,    //目标y轴的改变值
    mscale: 0,   //初始地图缩放比例
    flag:0,
    ctor:function()
    {
        //create a CCSprite

        this.mscale = 1;
        this._super();

        this.setTouchEnabled(true);
        this.setTouchMode(cc.TOUCH_ALL_AT_ONCE);

        var size = cc.Director.getInstance().getWinSize();
        this.sprite = cc.Sprite.create( "res/HelloWorld.png" );   //这时m_uReference ＝ 1
        this.sprite.setAnchorPoint( cc.p( 0.5, 0.5 ) );
        this.sprite.setPosition( cc.p( size.width / 2, size.height / 2 ) );
        this.addChild( this.sprite );
    },
    onTouchesBegan:function (touches, event) {
        if(touches.length>=2)
        {
            var mPoint1 = touches[0].getLocation();

            var mPoint2 = touches[1].getLocationInView();
            mPoint2     = cc.Director.getInstance().convertToGL(mPoint2);

            this.distance = cc.pDistance(mPoint1,mPoint2);//计算两个触摸点距离
            this.deltax = (mPoint1.x + mPoint2.x)/2;     //得到两个触摸点中点和精灵锚点的差值
            this.deltay = (mPoint1.y + mPoint2.y)/2;
        }
        else
        {
            this.flag = 1;
        }
    },
    onTouchesMoved: function (touches, event) {
        if(touches.length>=2)
        {
            var mPoint1 = touches[0].getLocationInView();
            mPoint1     = cc.Director.getInstance().convertToGL(mPoint1);

            var mPoint2 = touches[1].getLocationInView();
            mPoint2     = cc.Director.getInstance().convertToGL(mPoint2);
            var mdistance = cc.pDistance(mPoint1,mPoint2);
            if(this.distance == 0)
            {
                this.distance = mdistance;
            }
            if (this.flag == 0)
            {
                this.mscale = mdistance/this.distance * this.mscale;
                this.distance = mdistance;
                this.setScale(this.mscale);
            }
            else
            {
                this.distance = mdistance;
            }
            this.deltax = (mPoint1.x + mPoint2.x)/2;     //得到两个触摸点中点和精灵锚点的差值
            this.deltay = (mPoint1.y + mPoint2.y)/2;

            this.flag = 0;
        }
        else if(touches.length == 1)
        {
            var touch = touches[0];
            var delta = touch.getDelta();
            var diff = cc.pAdd(delta, this.getPosition());
            this.setPosition(diff);
        }
    },
    onTouchesEnded:function(touches, event)
    {
        this.mscale = this.getScale();
        this.distance = 0;
        this.flag = 0;
    }
} );
