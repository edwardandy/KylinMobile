/**
 * Created by chenyonghua on 13-10-25.
 */
var IsometricScene = cc.Scene.extend({
    ctor:function() {
        this._super();
        cc.associateWithNative( this, cc.Scene );
    },

    onEnter:function () {
        this._super();

        //load texture
        cc.SpriteFrameCache.getInstance().addSpriteFrames( s_floor );
        cc.SpriteFrameCache.getInstance().addSpriteFrames( s_parterre );

        this.color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(this.color, -1);


//        var list = [];
//        for(var i =0;i<50;i++){
//            for(var j =49;j>=0;j--){
//                var isoNode = new sf.IsoNode();
//                isoNode.retain();
//                isoNode.setContainer(new cc.Sprite());
//                isoNode.setSize(1,1,1);
//                isoNode.setIsoPosition(sf.makeIsoPoint(i,j,1));
//                isoNode.renderLogic( );
//                list.push(isoNode);
//            }
//        }
//
//        (new sf.SceneLayoutRenderer()).sortChildren(list);
//
//        for(var k =0 ;k<100;k++)
//        {
//           var target = list[k];
//            cc.log("x:"+target.getIsoX()+",y:"+target.getIsoY()+",depth:"+target.getDepth());
//        }
//
//        return;


        var isoLayer = new IsoLayer();
        isoLayer.retain();
        this.addChild(isoLayer);
        isoLayer.init();
    }
});
