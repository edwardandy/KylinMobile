/**
 * Created by chenyonghua on 13-12-9.
 */
var ArmatureTest = cc.Layer.extend( {
    ctor: function()
    {
        this._super();
//        ccs.ArmatureDataManager.getInstance().addArmatureFileInfo("soldier.png","soldier.plist","skeleton.xml");
//        ccs.ArmatureDataManager.getInstance().addArmatureFileInfo(s_dragon_png,s_dragon_plist,s_dragon_xml);
//        doAdd();
        ccs.ArmatureDataManager.getInstance().addArmatureFileInfoAsync( s_dragon_png, s_dragon_plist, s_dragon_xml, this.doAdd, this );
    },
    doAdd: function()
    {
        var armature = ccs.Armature.create( "Dragon" );
//        armature.getAnimation().play( "walk", 0, 0, 1 );
        armature.getAnimation().playByIndex( 0, 0, 0, 1 );
        armature.setAnchorPoint( cc.p( 0, 0 ) );
        armature.ignoreAnchorPointForPosition( false );

        var animation = armature.getAnimation();
        animation.setAnimationScale( 0.5 );
        armature.setScale(1);
        this.addChild( armature );
    }

} );

var Lesson5 = cc.Scene.extend( {
    ctor: function()
    {
        this._super();
    },

    onEnter: function()
    {
        this._super();
        var layer = new ArmatureTest();
        this.addChild( layer );
    }
} );