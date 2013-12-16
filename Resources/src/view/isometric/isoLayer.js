/**
 * Created by chenyonghua on 13-10-25.
 */

var TAG_TILE_MAP = 1;
var TAG_BACKGROUND_MAP = 2;
var IsoLayer = TouchScaleLayer.extend( {
    tamara: null,
    color: null,
    player: null,
    isSeachPath: false,
    isoScene: null,
    ctor: function()
    {
        this._super();
        cc.associateWithNative( this, cc.Layer );

        if( 'touches' in sys.capabilities )
            this.setTouchEnabled( true );
        else if( 'mouse' in sys.capabilities )
            this.setMouseEnabled( true );
    },

    init: function()
    {
        this.ignoreAnchorPointForPosition( true );
        //////////////////////////////
        // 1. super init first
        this._super();

        cc.log( "load assets finish" );

        sf.IsoConfig.setCellSize(20);
        sf.IsoConfig.setGridSize( cc.p( 50, 50 ) );

        //add background
        var batchNode = cc.SpriteBatchNode.create( s_floor_png, 10000 );
        var background = new IsoScene();
        background.retain();
        background.setContainer( batchNode );
        background.setSize( sf.IsoConfig.getGridSize().x, sf.IsoConfig.getGridSize().y, 1 );
        for( var i = 0; i < sf.IsoConfig.getGridSize().x; i++ )
        {
            for( var j = 0; j < sf.IsoConfig.getGridSize().y; j++ )
            {
                var isoSprite = new IsoSprite();
                isoSprite.retain();
                isoSprite.initialize( "0001-2.png" );
                isoSprite.setSize( 1, 1, 1 );
                isoSprite.setIsoPosition( sf.makeIsoPoint( i, j, 0 ) );
                isoSprite.setAnchorPoint( cc.p( 0.5, 1 ) );

                background.addIsoNode( isoSprite );
            }
        }
        batchNode.setAnchorPoint( cc.p( 0.5, 0.5 ) );
        batchNode.setPosition( VisibleRect.center() );
        this.addChild( batchNode, 0, TAG_BACKGROUND_MAP );

        // add tiles
        var hostContainer = cc.SpriteBatchNode.create( s_parterre_png, 10000 );
//        var hostContainer   = cc.Layer.create();

        this.isoScene = new IsoScene();
        this.isoScene.retain();
        this.isoScene.setSize( sf.IsoConfig.getGridSize().x, sf.IsoConfig.getGridSize().y, 1 );
        this.isoScene.setContainer( hostContainer );

        for( var i = 0; i < sf.IsoConfig.getGridSize().x; i++ )
        {
            for( var j = sf.IsoConfig.getGridSize().y - 1; j >= 0; j-- )
            {
                if( Math.random() * 100 < 40 && i != 0 && j != 0 )
                {
                    var filename = (Math.floor( Math.random() * 1000 % 12 ) + 1002) + "-2.png";
                    var isoSprite = new IsoSprite();
                    isoSprite.retain();
                    isoSprite.initialize( filename );
                    isoSprite.setSize( 1, 1, 1 );
                    isoSprite.setIsoPosition( sf.makeIsoPoint( i, j, 0 ) );
                    isoSprite.setAnchorPoint( cc.p( 0.5, 0 ) );
                    isoSprite.setOffsetIsoPosition( sf.makeIsoPoint( 1, 1, 0 ) );
                    isoSprite.setWalkable( false );
                    this.isoScene.addIsoNode( isoSprite );
                }
            }
        }

        var player_file = "player.png";
        this.player = new IsoSprite();
        this.player.retain();
        this.player.initialize( "player.png" );
        this.player.setSize( 1, 1, 1 );
        this.player.setIsoPosition( sf.makeIsoPoint( 0, 0, 0 ) );
        this.player.setAnchorPoint( cc.p( 0.5, 0 ) );
        this.player.setOffsetIsoPosition( sf.makeIsoPoint( 1, 1, 0 ) );
        cc.log( "this.player.x:" + this.player.getIsoX() + ",this.player.y:" + this.player.getIsoY() + ",this.player.z:" + this.player.getIsoZ() );
        this.isoScene.addIsoNode( this.player );

        hostContainer.setAnchorPoint( cc.p( 0.5, 0.5 ) );
        hostContainer.setPosition( VisibleRect.center() );
        this.addChild( hostContainer, 100, TAG_TILE_MAP );

        cc.log( "sort depth start" );
        this.isoScene.sortChildren();
        cc.log( "sort depth end" );
        cc.log( this.isoScene.getGraph().toString() );
    },
    onExit: function()
    {
        this._super();
    },
    onTouchesBegan: function( touches, event )
    {
        if( touches.length == 1 )
        {
            this.isSeachPath = true;
        }
        this._super( touches, event );
    },
    onTouchesMoved: function( touches, event )
    {
        if( touches.length == 1 )
        {
            this.isSeachPath = false;
        }
        this._super( touches, event );
    },
    onTouchesEnded: function( touches, event )
    {
        if( touches.length == 1 && this.isSeachPath )
        {
            var touch = touches[0];
            var touchLocation = touch.getLocation();
            var background = this.getChildByTag( TAG_BACKGROUND_MAP );
            var local = background.convertToNodeSpace( touchLocation );
            var isoPoint = sf.IsoMath.screenToIso( local );
            cc.log( "local:{x:" + local.x + ",y:" + local.y + "}" );
            cc.log( "isoPoint:{x:" + Math.floor( isoPoint.getX() / sf.IsoConfig.getCellSize() ) + ",y:" + Math.floor( isoPoint.getY() / sf.IsoConfig.getCellSize() ) + "}" );
            if( this.player )
            {
                this.isoScene.moveTo( this.player, Math.floor( isoPoint.getX() / sf.IsoConfig.getCellSize() ), Math.floor( isoPoint.getY() / sf.IsoConfig.getCellSize() ) );
            }
        }
        this._super( touches, event );
    }
} )