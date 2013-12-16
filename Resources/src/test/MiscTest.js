/**
 * Created by chenyonghua on 13-11-29.
 */
var MiscTest = cc.Scene.extend({
    _layer:null,
    ctor:function()
    {
        this._super();
        cc.SpriteFrameCache.getInstance().addSpriteFrames(s_soldier_plist,s_soldier_png);
        this.createLayer();
    },
    createLayer:function()
    {
        this._layer = cc.Layer.create();
        this.addChild(this._layer);
//        var i = 0;
//        var batchNode = cc.SpriteBatchNode.create(s_soldier_png,10000);
//        this.addChild(batchNode);
//        while(i<100)
//        {
//            var sprite = cc.Sprite.createWithSpriteFrame(cc.SpriteFrameCache.getInstance().getSpriteFrame("Sprite-body.png"));
//            sprite.setPosition(cc.p( 50 + 50*Math.floor(i/15) , 100 + (i%15)*50));
//            batchNode.addChild(sprite);
//            i++;
//        }


        var sprite_1 = cc.Sprite.createWithSpriteFrame(cc.SpriteFrameCache.getInstance().getSpriteFrame("Sprite-body.png"));
        sprite_1.setPosition(cc.p(100,100));
        this.addChild(sprite_1);
        var sprite_2 = cc.Sprite.createWithSpriteFrame(cc.SpriteFrameCache.getInstance().getSpriteFrame("Sprite-body.png"));
        sprite_2.setPosition(cc.p(100,100));
        sprite_1.addChild(sprite_2);
    }
});