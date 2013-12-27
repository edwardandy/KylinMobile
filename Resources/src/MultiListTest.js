/**
 * Created by may on 12/27/13.
 */
var MultiListLayer = cc.Layer.extend({
    isMouseDown: false,
    helloImg: null,
    helloLabel: null,
    circle: null,
    sprite: null,
    ctor: function () {
        this._super();
    },

    init: function () {
        this._super();
        this.testMultiList();
        return true;
    },
    testMultiList:function(){
        var arr = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15];

        var ml = new MultiList(TestItem,5,2,5,5,150,40);
        ml.setPosition(cc.p(10,500))
        this.addChild(ml);
        ml.setData(arr);


        var ml2 = new MultiList(TestItem,5,2,5,5,150,40,cc.SCROLLVIEW_DIRECTION_VERTICAL);
        ml2.setPosition(cc.p(400,500))
        this.addChild(ml2);
        ml2.setData(arr);
    }

});


///////////////////////////////MainScene////////////////////////////////
var MultiListScene = cc.Scene.extend({
    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Scene);
    },
                                     
    onEnter: function () {
        this._super();
        var layer = new MultiListLayer();
        this.addChild(layer);
        layer.init();
    }
});

///////////////////////////////TestItem////////////////////////////////
var TestItem = MultiListItem.extend({
    width:Number,height:Number,
    ctor:function(){
        this._super();
    },
    init:function(){
        this._super()
    },
    setData:function(value){
        this._data = value

        this.removeAllChildren();
        if(value){
            var sprite = cc.Sprite.create("res/testItemBg.png");

            this.width = sprite.getContentSize().width;
            this.height = sprite.getContentSize().height;
            sprite.setAnchorPoint(cc.p(0,0))
            sprite.setPosition(cc.p(0,-this.height));
            this.addChild(sprite);

            this._textField = cc.LabelTTF.create(value.toString(), "Arial", 14);
            this.addChild(this._textField);
            this._textField.setPosition(cc.p(this.width/2,-this.height/2));
        }


    },
    getData:function(){
        return this._data;
    }
})