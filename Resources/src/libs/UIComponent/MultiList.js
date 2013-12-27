/**
 * Created by may on 12/11/13.
 */
var MultiList = cc.Layer.extend({
    ctor:function(clazz,row,col,rowSpace,colSpace,faceWidth,faceHeight,direction){
        this._super();
        var size = cc.Director.getInstance().getWinSize();

        this.itemClazz = clazz;
        this.row = row;
        this.col = col;
        this.rowSpace = rowSpace;
        this.colSpace = colSpace;

        this.faceWidth = faceWidth||100;
        this.faceHeight = faceHeight||100;
        this.direction = direction||cc.SCROLLVIEW_DIRECTION_HORIZONTAL;

        var color = cc.c4b(100,100,100,255);
        this.mask = cc.LayerColor.create(color,this.faceWidth * col,(this.faceHeight + rowSpace) * row);
        this.mask.setPosition(cc.p(0, -(this.faceHeight + rowSpace) * row));
        var clipper = cc.ClippingNode.create();
        clipper.setStencil(this.mask);
        this.addChild(clipper);

        this.mContainer = cc.Layer.create();
        clipper.addChild(this.mContainer)

        this.make();

    },
    init: function () {   //
        this._super();
    },
    make:function(){
        this.mList = [];
        var item;
        var len1;
        var len2;
        if(this.direction == cc.SCROLLVIEW_DIRECTION_HORIZONTAL){
            len1 = this.row;
            len2 = this.col
        }else{
            len1 = this.col;
            len2 = this.row
        }
        for(var i = 0;i < len1 + 1;i++){
            if(this.mList[i] == null){
                this.mList[i] = [];
            }
            for(var j = 0;j < len2;j++){
                item = this.getNewItem();
                item.itemId = -1;
                this.mList[i].push(item);
            }
        }
    },
    getNewItem:function(){
        var item = new this.itemClazz();
        this.mContainer.addChild(item);
        return item;

    },
    setData:function(value){
        this._data = value;
        this._currentPoint = 0;
        if(this._currentRow > 0 && this._currentRow > this.totalRows){
            this._currentRow = 0;
        }
        this.fill(true);

        this.setTouchEnabled(true);
    },
    onTouchesMoved: function (touches, event) {
        if(this.isDraging){
            for (var i = 0; i < touches.length; i++) {
                var touch = touches[i];
                var pos = touch.getLocation();
                var id = touch.getId();
            }


            var curTouchLocation = touches[0].getLocation();
            if(this.direction == cc.SCROLLVIEW_DIRECTION_HORIZONTAL){
                this._currentPoint = this.originPoint + (curTouchLocation.y - this.touchLocation.y);
            }else{
                this._currentPoint = this.originPoint + (curTouchLocation.x - this.touchLocation.x);
                //            this._currentPoint = this.originPosition.x + (curTouchLocation.x - this.touchLocation.x);
            }
            //        this.mContainer.setPosition(this.originPosition.x, this._currentPoint);
            this.fill()
        }
    },
    onTouchesCancelled: function (touches, event) {
    },

    onTouchesBegan: function (touches, event) {
        this.touchLocation = touches[0].getLocation();
        this.originPosition = this.mContainer.getPosition()
        this.originPoint = this._currentPoint;
        var point = this.convertToWorldSpace(this.mask.getPosition());
        var size  = this.mask.getContentSize();
        var tx = this.touchLocation.x;
        var ty = this.touchLocation.y;
        if(tx>point.x && tx<point.x + size.width && ty>point.y && ty<point.y+size.height){
            this.isDraging = true;
        }
    },

    onTouchesEnded: function (touches, event) {
        this.isDraging = false;
        for (var i = 0; i < touches.length; i++) {
            var touch = touches[i];
            var pos = touch.getLocation();
            var id = touch.getId();
        }
    },
    getData:function(){
        return this._data;
    },
    fill:function(isAll){
        var len;
        var item;
        var isNeed;
        var needList = [];
        var outList = [];
        var rowNum = -1;
        len = this.mList.length;
        if(isAll){
            for(var i = 0;i < len;i++){
                rowNum = Math.floor((this._currentPoint + (i * this.itemSize())) / this.itemSize());
                for(var j = 0;j < this.mList[i].length;j++){

                    item = this.mList[i][j];
                    if(this.direction == cc.SCROLLVIEW_DIRECTION_HORIZONTAL){
                        item.itemId = rowNum * this.col + j;
                        item.data = this._data[item.itemId];
                        var x = j * (this.faceWidth + this.colSpace);
                        var y = -(rowNum * this.itemSize()) - this._currentPoint;
                        item.setPosition(cc.p(x,y));
                    }else{
                        item.itemId = rowNum * this.row + j;
                        item.data = this._data[item.itemId];
                        var x = (rowNum * this.itemSize()) - this._currentPoint;
                        var y = -j * (this.faceHeight + this.colSpace);
                        item.setPosition(cc.p(x,y));
                    }
                }
            }
        }else{
            for(var i = 0;i < len;i++){
                if(this.direction == cc.SCROLLVIEW_DIRECTION_HORIZONTAL){
                    needList.push(Math.floor((this._currentPoint + (i * this.itemSize())) / this.itemSize()));
                }else{
                    needList.push(Math.floor((-this._currentPoint + (i * this.itemSize())) / this.itemSize()));
                }
            }
            //找到显示区域外的子项
            for(var i = 0;i < len;i++){
                if(this.direction == cc.SCROLLVIEW_DIRECTION_HORIZONTAL){
                    rowNum = Math.floor(this.mList[i][0].itemId / this.col);
                }else{
                    rowNum = Math.floor(this.mList[i][0].itemId / this.row);
                }
                isNeed = false;
                for(var j = 0;j < needList.length;j++){
                    if(rowNum == needList[j]){
                        isNeed = true;
                        needList.splice(j,1);
                        break;
                    }
                }
                if(!isNeed){
                    outList.push(this.mList[i]);
                }else{
                    for(var k = 0,llen = this.mList[i].length; k < llen; k++){
                        item = this.mList[i][k];
                        if(this.direction == cc.SCROLLVIEW_DIRECTION_HORIZONTAL){
                            item.setPosition(cc.p(item.getPosition().x,   (-Math.floor(item.itemId / this.col) * this.itemSize()) + this._currentPoint));
                        }else{
                            item.setPosition(cc.p((Math.floor(item.itemId / this.row) * this.itemSize()) + this._currentPoint,   item.getPosition().y));
                        }
//                        item.setPosition(cc.p(item.getPosition().x,   (-Math.floor(item.itemId / this.col) * this.itemSize()) + 50));
                    }
                }
            }
            //列表外的子项修正到显示区域内
            len	= outList.length;
            for(var i = 0; i < len ; i++){

                var temp = outList[i];
                rowNum = needList[i];
                for(var j = 0 , tlen = temp.length;j < tlen;j++){
                    item = temp[j];

                    if(this.direction == cc.SCROLLVIEW_DIRECTION_HORIZONTAL){
                        item.itemId = rowNum * this.col + j;
                        item.data = this._data[item.itemId];
                        item.setPosition(cc.p(item.getPosition().x ,   (-Math.floor(item.itemId / this.col) * this.itemSize()+this._currentPoint)));
                    }else{
                        item.itemId = rowNum * this.row + j;
                        item.data = this._data[item.itemId];
                        item.setPosition(cc.p((Math.floor(item.itemId / this.row) * this.itemSize()+this._currentPoint) ,   item.getPosition().y));
                    }
                }
            }
        }

    },
    itemSize:function(){
        if(this.direction == cc.SCROLLVIEW_DIRECTION_HORIZONTAL){
            return this.faceHeight + this.rowSpace;
        }else{
            return this.faceWidth + this.colSpace;
        }

    }
})


var MultiListItem = cc.Layer.extend({
    itemId:Number,
    ctor:function(){
        this._super();
    },
    init:function(){
        this._super();
    },
    setData:function(value){
        this._data = value;
    },
    getData:function(){
        return this._data;
    }

});
MultiListItem.prototype.__defineGetter__('data',function(){
    return this.getData();
});
MultiListItem.prototype.__defineSetter__('data',function(value){
    this.setData(value);
});