/**
 * Created by chenyonghua on 13-11-6.
 */
GameController = Controller.extend( {
    ctor: function( viewComponent )
    {
        this._super( GameController.NAME, viewComponent );
    },
    onRegister: function()
    {
        this.addContextListener(ContextEvent.START_UP, this.onNotify );
    },
    onNotify: function( first, rank, isFirst, object )
    {
        cc.log("=================");
        cc.log( "first= " + first );
        cc.log( "rank= " + rank );
        cc.log( "isFirst= " + isFirst );
        cc.log( object );
    }
} );
GameController.NAME = "GameController";