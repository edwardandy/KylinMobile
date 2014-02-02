/**
 * Created by chenyonghua on 13-11-6.
 */
GameStartService = HttpService.extend( {
    ctor: function()
    {
        this._super( GameStartService.NAME );
    },
    onRegister:function()
    {
        this.dispatch(ContextEvent.START_UP,"GameStartService",2,true,{"go":"yes"});
    },
    success:function(object)
    {
        cc.log("data[0]:"+object[0]);
        cc.log("data[1]:"+object[1]);
    },
    fault:function(object)
    {
        cc.log("data:"+object);
    }
} );
GameStartService.NAME = "I1001";